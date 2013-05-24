#ifndef DTR_VALUE_HPP
#define DTR_VALUE_HPP

#include <stddef.h>
#include <stdint.hpp>
#include <iosfwd>
#include <string>
#include <vector>

namespace dtr
{

//! 値
        class Value
        {
        public:
                //! 文字列の値表現であるかどうかを取得する
                static bool vr_is_string( const std::string& vr );

                //! 値表現の単位サイズを取得する
                static size_t vr_get_unit_size( const std::string& vr );

                //! 構築する
                explicit Value( const std::string& vr, const char* value, size_t value_length );

                //! 文字列として取得する
                std::string get_string() const;

                //! USとして取得する
                uint16_t get_us() const;

                //! DSとして取得する
                std::vector<double> get_ds() const;

                //! 出力する
                friend std::ostream& operator<<( std::ostream& out, const Value& self ) {
                        self.print_( out );
                        return out;
                }

        private:
                std::string vr_;
                const char* value_;
                size_t value_length_;

                //! 出力する
                void print_( std::ostream& out ) const;
        };

} // namespace dtr

#endif
