#include <stdint.hpp>
#include <iostream>
#include <dtr/reader.hpp>
#include <dtr/unexpected_eof.hpp>

namespace dtr
{

        namespace
        {
                bool host_endian_is_big_endian()
                {
                        uint16_t value = 0x1234;
                        return *reinterpret_cast<const uint8_t*>( &value ) == 0x12;
                }
        }

        Reader::Reader( std::istream& in )
                : in_( in )
                , endian_swap_( host_endian_is_big_endian() ) {}

        void Reader::set_little_endian( bool little_endian )
        {
                if ( host_endian_is_big_endian() ) {
                        endian_swap_ = little_endian;
                } else {
                        endian_swap_ = ! little_endian;
                }
        }

        void Reader::read( void* buffer, size_t size, size_t count )
        {
                char* ptr = static_cast<char*>( buffer );
                if ( ! in_.read( ptr, size * count ) ) {
                        throw Unexpected_Eof();
                }

                if ( size == 1 || ! endian_swap_ ) {
                        return;
                }

                for ( size_t i = 0; i < count; ++i, ptr += size ) {
                        for ( size_t j = 0; j < size / 2; ++j ) {
                                std::swap( ptr[j], ptr[size - j - 1] );
                        }
                }
        }

        void Reader::seek_beg( size_t offset )
        {
                in_.seekg( offset, std::ios::beg );
        }

        void Reader::seek_cur( size_t offset )
        {
                in_.seekg( offset, std::ios::cur );
        }

} // namespace dtr
