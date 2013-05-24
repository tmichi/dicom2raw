#ifndef DTR_VALUE_HPP
#define DTR_VALUE_HPP

#include <stddef.h>
#include <stdint.hpp>
#include <iosfwd>
#include <string>
#include <vector>

namespace dtr
{

//! �l
        class Value
        {
        public:
                //! ������̒l�\���ł��邩�ǂ������擾����
                static bool vr_is_string( const std::string& vr );

                //! �l�\���̒P�ʃT�C�Y���擾����
                static size_t vr_get_unit_size( const std::string& vr );

                //! �\�z����
                explicit Value( const std::string& vr, const char* value, size_t value_length );

                //! ������Ƃ��Ď擾����
                std::string get_string() const;

                //! US�Ƃ��Ď擾����
                uint16_t get_us() const;

                //! DS�Ƃ��Ď擾����
                std::vector<double> get_ds() const;

                //! �o�͂���
                friend std::ostream& operator<<( std::ostream& out, const Value& self ) {
                        self.print_( out );
                        return out;
                }

        private:
                std::string vr_;
                const char* value_;
                size_t value_length_;

                //! �o�͂���
                void print_( std::ostream& out ) const;
        };

} // namespace dtr

#endif
