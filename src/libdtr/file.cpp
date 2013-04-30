#include <algorithm>
#include <functional>
#include <iostream>
#include <dtr/file.hpp>
#include <dtr/invalid_format.hpp>
#include <dtr/tag.hpp>
#include <dtr/value.hpp>

namespace dtr
{

        namespace
        {
                class Find_Pixel_Data : public std::unary_function<const Element&, bool>
                {
                public:
                        bool operator()( const Element& element ) const {
                                return element.get_tag() == Tag( 0x7FE0, 0x0010 );
                        }
                };
        }

        std::string File::parse( std::istream& in )
        {
                try {
                        Reader reader( in );
                        parse( reader );
                } catch ( const std::exception& e ) {
                        return e.what();
                } catch ( ... ) {
                        return "Unknown error";
                }
                return std::string();
        }

        void File::parse( Reader& reader )
        {
                // ファイルプリアンブル
                preamble_.resize( 128 );
                reader.read( &preamble_[0], 1, preamble_.size() );

                // DICOMプレフィックス
                std::vector<char> prefix( 4 );
                reader.read( &prefix[0], 1, prefix.size() );
                if ( std::string( prefix.begin(), prefix.end() ) != "DICM" ) {
                        // 古い形式だと、ファイルプリアンブルやDICOMプレフィックスがない
                        reader.seek_beg( 0 );
                }

                // データ要素
                information_.clear();
                element_.clear();
                while ( true ) {
                        Element element;
                        if ( ! element.parse( reader, information_ ) ) {
                                break;
                        }
                        element_.push_back( element );
                }
        }

        const void* File::get_pixel_data() const
        {
                std::vector<Element>::const_reverse_iterator i = std::find_if( element_.rbegin(), element_.rend(), Find_Pixel_Data() );
                if ( i == element_.rend() ) {
                        return 0;
                } else {
                        return i->get_value();
                }
        }

        size_t File::get_pixel_data_length() const
        {
                std::vector<Element>::const_reverse_iterator i = std::find_if( element_.rbegin(), element_.rend(), Find_Pixel_Data() );
                if ( i == element_.rend() ) {
                        return 0;
                } else {
                        return i->get_value_length();
                }
        }

} // namespace dtr
