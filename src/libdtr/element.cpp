#include <algorithm>
#include <iostream>
#include <dtr/element.hpp>
#include <dtr/element_dictionary.hpp>
#include <dtr/element_dictionary_item.hpp>
#include <dtr/unsupported_transfer_syntax.hpp>
#include <dtr/value.hpp>

namespace dtr
{

        bool Element::parse( Reader& reader, Information& information )
        {
                // データ要素タグ
                if ( ! tag_.parse( reader ) ) {
                        return false;
                }

                bool implicir_vr = true;
                // メタ情報は明示的値表現のリトルエンディアン構文で転送される
                if ( tag_.get_group_number() == 0x0002 ) {
                        implicir_vr = false;
                        reader.set_little_endian( true );
                }
                // それ以外はメタ情報で規定された転送構文で転送される
                else {
                        implicir_vr = information.get_implicit_vr();
                        reader.set_little_endian( information.get_little_endian() );
                }

                if ( implicir_vr ) {
                        // 値表現を得るために辞書を検索する
                        const Element_Dictionary_Item* element_dictionary_item = Element_Dictionary::get_instance().find( tag_ );
                        if ( element_dictionary_item ) {
                                vr_ = element_dictionary_item->get_vr().substr( 0, 2 );
                        } else {
                                vr_ = "UN";
                        }

                        // デフォルト転送構文では、ピクセルデータの値表現はOWである。
                        if ( tag_ == Tag( 0x7FE0, 0x0010 ) ) {
                                vr_ = "OW";
                        }

                        // 値長さ
                        uint32_t value_length = 0;
                        reader.read( value_length );
                        value_length_ = value_length;
                } else {
                        // 値表現
                        std::vector<char> vr( 2 );
                        reader.read( &vr[0], 1, vr.size() );
                        vr_.assign( vr.begin(), vr.end() );

                        // 値長さ
                        if ( vr_ == "OB" || vr_ == "OW" || vr_ == "OF" || vr_ == "SQ" || vr_ == "UT" || vr_ == "UN" ) {
                                reader.seek_cur( 2 );
                                uint32_t value_length = 0;
                                reader.read( value_length );
                                value_length_ = value_length;
                        } else {
                                uint16_t value_length = 0;
                                reader.read( value_length );
                                value_length_ = value_length;
                        }
                }

                // 値が空の場合でもデータ領域は確保する
                if ( value_length_ == 0 ) {
                        value_.resize( 1 );
                        value_[0] = '\0';
                        return true;
                }

                value_.resize( value_length_ );
                size_t unit_size = Value::vr_get_unit_size( vr_ );
                reader.read( &value_[0], unit_size, value_.size() / unit_size );
                Value value( vr_, &value_[0], value_.size() );

                // メタ情報を設定する
                if ( tag_ == Tag( 0x0002, 0x0010 ) ) {
                        std::string uid = value.get_string();
                        if ( uid == "1.2.840.10008.1.2" ) {
                                information.set_implicit_vr( true );
                                information.set_little_endian( true );
                        } else if ( uid == "1.2.840.10008.1.2.1" ) {
                                information.set_implicit_vr( false );
                                information.set_little_endian( true );
                        } else if ( uid == "1.2.840.10008.1.2.2" ) {
                                information.set_implicit_vr( false );
                                information.set_little_endian( false );
                        } else {
                                throw Unsupported_Transfer_Syntax();
                        }
                } else if ( tag_ == Tag( 0x0028, 0x0002 ) ) {
                        information.set_samples_per_pixel( value.get_us() );
                } else if ( tag_ == Tag( 0x0028, 0x0010 ) ) {
                        information.set_rows( value.get_us() );
                } else if ( tag_ == Tag( 0x0028, 0x0011 ) ) {
                        information.set_columns( value.get_us() );
                } else if ( tag_ == Tag( 0x0028, 0x0030 ) ) {
                        std::vector<double> vector = value.get_ds();
                        information.set_pixel_spacing_row( vector[0] );
                        information.set_pixel_spacing_column( vector[1] );
                } else if ( tag_ == Tag( 0x0028, 0x0100 ) ) {
                        information.set_bits_allocated( value.get_us() );
                } else if ( tag_ == Tag( 0x0028, 0x0101 ) ) {
                        information.set_bits_stored( value.get_us() );
                } else if ( tag_ == Tag( 0x0028, 0x0102 ) ) {
                        information.set_high_bit( value.get_us() );
                } else if ( tag_ == Tag( 0x0018, 0x0050 ) ) {
                        std::vector<double> vector = value.get_ds();
                        information.set_slice_thickness( vector[0] );
                } else if ( tag_ == Tag( 0x0018, 0x0088 ) ) {
                        std::vector<double> vector = value.get_ds();
                        information.set_spacing_between_slices( vector[0] );
                } else if ( tag_ == Tag( 0x0020, 0x0032 ) ) {
			std::vector<double> vector = value.get_ds();
			information.set_image_position_patient(vector[0], vector[1], vector[2]);
		}


                return true;
        }

        void Element::swap( Element& rhs )
        {
                tag_.swap( rhs.tag_ );
                vr_.swap( rhs.vr_ );
                std::swap( value_length_, rhs.value_length_ );
                value_.swap( rhs.value_ );
        }

} // namespace dtr
