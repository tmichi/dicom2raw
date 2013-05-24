#ifndef DTR_TAG_HPP
#define DTR_TAG_HPP

#include <stdint.hpp>
#include "reader.hpp"

namespace dtr
{

//! データ要素タグ
        class Tag
        {
        public:
                //! 構築する
                explicit Tag();

                //! 構築する
                /*!
                    \param[in] group_number
                        グループ番号
                    \param[in] element_number
                        要素番号
                 */
                explicit Tag( uint16_t group_number, uint16_t element_number );

                //! 解析する
                bool parse( Reader& reader );

                //! グループ番号を取得する
                uint16_t get_group_number() const {
                        return group_number_;
                }

                //! 要素番号を取得する
                uint16_t get_element_number() const {
                        return element_number_;
                }

                //! 交換する
                void swap( Tag& rhs );

                //! 同値である
                bool operator==( const Tag& rhs ) const {
                        return group_number_ == rhs.group_number_ && element_number_ == rhs.element_number_;
                }

                //! 同値でない
                bool operator!=( const Tag& rhs ) const {
                        return ! operator==( rhs );
                }

                //! 比較する
                bool operator<( const Tag& rhs ) const;

        private:
                uint16_t group_number_;
                uint16_t element_number_;
        };

} // namespace dtr

#endif
