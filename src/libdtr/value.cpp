#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <dtr/invalid_vr.hpp>
#include <dtr/uid_dictionary.hpp>
#include <dtr/uid_dictionary_item.hpp>
#include <dtr/value.hpp>

namespace dtr
{

        namespace
        {
                template <typename T>
                std::vector<T> get_sequence( const char* value, size_t value_length )
                {
                        std::string string( value, value_length );
                        std::vector<T> vector;
                        std::string::size_type i = 0;
                        while ( true ) {
                                std::string::size_type j = string.find( '\\', i );
                                std::istringstream in( j == std::string::npos ? string.substr( i ) : string.substr( i, j - i ) );
                                T v = 0;
                                in >> v;
                                vector.push_back( v );
                                if ( j == std::string::npos ) {
                                        break;
                                }
                                i = j + 1;
                        }
                        return vector;
                }
        }

        bool Value::vr_is_string( const std::string& vr )
        {
                return vr == "AE"
                       || vr == "AS"
                       || vr == "CS"
                       || vr == "DA"
                       || vr == "DS"
                       || vr == "DT"
                       || vr == "IS"
                       || vr == "LO"
                       || vr == "LT"
                       || vr == "PN"
                       || vr == "SH"
                       || vr == "ST"
                       || vr == "TM"
                       || vr == "UI"
                       || vr == "UT";
        }

        size_t Value::vr_get_unit_size( const std::string& vr )
        {
                if ( vr_is_string( vr ) ) {
                        return 1;
                } else if ( vr == "AT" || vr == "OW" || vr == "US" ) {
                        // uint16_t
                        return 2;
                } else if ( vr == "FL" || vr == "OF" ) {
                        // float
                        return 4;
                } else if ( vr == "FD" ) {
                        // double
                        return 8;
                } else if ( vr == "OB" ) {
                        // uint8_t
                        return 1;
                } else if ( vr == "SL" ) {
                        // int32_t
                        return 4;
                } else if ( vr == "SS" ) {
                        // int16_t
                        return 2;
                } else if ( vr == "UL" ) {
                        // uint32_t
                        return 4;
                } else {
                        return 1;
                }
        }

        Value::Value( const std::string& vr, const char* value, size_t value_length )
                : vr_( vr )
                , value_( value )
                , value_length_( value_length ) {}

        std::string Value::get_string() const
        {
                if ( ! vr_is_string( vr_ ) ) {
                        throw Invalid_Vr();
                }
                std::string string( value_, value_length_ );
                // UIÇÃèÍçáÅANULï∂éöÇ™ññîˆÇ…Ç¬Ç¢ÇƒÇ¢ÇÈÇ©Ç‡ÇµÇÍÇ»Ç¢
                if ( string[string.size() - 1] == '\0' ) {
                        return string.substr( 0, string.size() - 1 );
                } else {
                        return string;
                }
        }

        uint16_t Value::get_us() const
        {
                if ( vr_ != "US" ) {
                        throw Invalid_Vr();
                }
                return *reinterpret_cast<const uint16_t*>( value_ );
        }

        std::vector<double> Value::get_ds() const
        {
                if ( vr_ != "DS" ) {
                        throw Invalid_Vr();
                }
                return get_sequence<double>( value_, value_length_ );
        }

        void Value::print_( std::ostream& out ) const
        {
                if ( vr_is_string( vr_ ) ) {
                        if ( vr_ == "UI" ) {
                                std::string uid = get_string();
                                out << uid;
                                const Uid_Dictionary_Item* uid_dictionary_item = Uid_Dictionary::get_instance().find( uid );
                                if ( uid_dictionary_item ) {
                                        out << "\n"
                                            << "Name: " << uid_dictionary_item->get_name() << "\n"
                                            << "Type: " << uid_dictionary_item->get_type();
                                }
                        } else {
                                out << get_string();
                        }
                } else if ( vr_ == "AT" ) {
                        // attribute tag
                } else if ( vr_ == "FL" || vr_ == "OF" ) {
                        out << *reinterpret_cast<const float*>( value_ );
                        // other float string (OF) ÇÕïÇìÆè¨êîì_êîÇÃóÒÅH
                } else if ( vr_ == "FD" ) {
                        out << *reinterpret_cast<const double*>( value_ );
                } else if ( vr_ == "OB" ) {
                        const uint8_t* ptr = reinterpret_cast<const uint8_t*>( value_ );
                        size_t value_length = std::min<size_t>( value_length_, 16 );
                        out << std::setfill( '0' ) << std::hex;
                        for ( size_t i = 0; i < value_length; ++i, ++ptr ) {
                                if ( i > 0 ) {
                                        out << ", ";
                                }
                                out << std::setw( 2 ) << static_cast<uint16_t>( *ptr );
                        }
                        out << std::setfill( ' ' ) << std::dec;
                        if ( value_length < value_length_ ) {
                                out << "...";
                        }
                } else if ( vr_ == "OW" ) {
                        const uint16_t* ptr = reinterpret_cast<const uint16_t*>( value_ );
                        size_t value_length = std::min<size_t>( value_length_, 16 );
                        out << std::setfill( '0' ) << std::hex;
                        for ( size_t i = 0; i < value_length; ++i, ++ptr ) {
                                if ( i > 0 ) {
                                        out << ", ";
                                }
                                out << std::setw( 4 ) << *ptr;
                        }
                        out << std::setfill( ' ' ) << std::dec;
                        if ( value_length < value_length_ ) {
                                out << "...";
                        }
                } else if ( vr_ == "SL" ) {
                        out << *reinterpret_cast<const int32_t*>( value_ );
                } else if ( vr_ == "SQ" ) {
                        // sequence of items
                } else if ( vr_ == "SS" ) {
                        out << *reinterpret_cast<const int16_t*>( value_ );
                } else if ( vr_ == "UL" ) {
                        out << *reinterpret_cast<const uint32_t*>( value_ );
                } else if ( vr_ == "UN" ) {
                        // unknown
                } else if ( vr_ == "US" ) {
                        out << *reinterpret_cast<const uint16_t*>( value_ );
                } else {
                        throw Invalid_Vr();
                }
        }

} // namespace dtr
