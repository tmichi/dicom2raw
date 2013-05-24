#ifndef DTR_FILE_HPP
#define DTR_FILE_HPP

#include <stddef.h>
#include <iosfwd>
#include <string>
#include <vector>
#include "element.hpp"
#include "information.hpp"
#include "reader.hpp"

namespace dtr
{

//! ファイル
        class File
        {
        public:
                //! 構築する
                explicit File() {}

                //! 解析する
                /*!
                    \retval 空文字列
                        エラーが発生しなかった
                    \retval エラー内容
                        エラーが発生した
                 */
                std::string parse( std::istream& in ); // throw()

                //! 解析する
                /*!
                    エラーが発生した場合、例外を送出する。
                 */
                void parse( Reader& reader );

                //! ファイルプリアンブルを取得する
                const std::vector<char>& get_preamble() const {
                        return preamble_;
                }

                //! 情報を取得する
                const Information& get_information() const {
                        return information_;
                }

                //! データ要素を取得する
                const std::vector<Element>& get_element() const {
                        return element_;
                }

                //! ピクセルデータを取得する
                const void* get_pixel_data() const;

                //! ピクセルデータ長さを取得する
                size_t get_pixel_data_length() const;

        private:
                std::vector<char> preamble_;
                Information information_;
                std::vector<Element> element_;

                //! 複製不可
                explicit File( const File& rhs );

                //! 複製不可
                File& operator=( const File& rhs );
        };

} // namespace dtr

#endif
