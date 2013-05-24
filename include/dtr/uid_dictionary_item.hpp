#ifndef CSN7_UID_DICTIONARY_ITEM_HPP
#define CSN7_UID_DICTIONARY_ITEM_HPP

#include <string>

namespace dtr
{

//! 固有識別子辞書の項目
        class Uid_Dictionary_Item
        {
        public:
                //! 構築する
                explicit Uid_Dictionary_Item( const std::string& name, const std::string& type );

                //! 名前を取得する
                const std::string& get_name() const {
                        return name_;
                }

                //! タイプを取得する
                const std::string& get_type() const {
                        return type_;
                }

        private:
                std::string name_;
                std::string type_;
        };

} // namespace dtr

#endif
