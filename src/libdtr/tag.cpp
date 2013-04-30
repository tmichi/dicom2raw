#include <algorithm>
#include <dtr/unexpected_eof.hpp>
#include <dtr/tag.hpp>

namespace dtr
{

        Tag::Tag()
                : group_number_()
                , element_number_() {}

        Tag::Tag( uint16_t group_number, uint16_t element_number )
                : group_number_( group_number )
                , element_number_( element_number ) {}

        bool Tag::parse( Reader& reader )
        {
                try {
                        reader.read( group_number_ );
                } catch ( const Unexpected_Eof& e ) {
                        return false;
                }
                reader.read( element_number_ );
                return true;
        }

        void Tag::swap( Tag& rhs )
        {
                std::swap( group_number_, rhs.group_number_ );
                std::swap( element_number_, rhs.element_number_ );
        }

        bool Tag::operator<( const Tag& rhs ) const
        {
                if ( group_number_ == rhs.group_number_ ) {
                        return element_number_ < rhs.element_number_;
                }
                return group_number_ < rhs.group_number_;
        }

} // namespace dtr
