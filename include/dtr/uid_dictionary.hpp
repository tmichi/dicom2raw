#ifndef DTR_UID_DICTIONARY_HPP
#define DTR_UID_DICTIONARY_HPP

#include <map>
#include <string>
#include "uid_dictionary_item.hpp"

namespace dtr
{

//! 固有識別子辞書
        class Uid_Dictionary
        {
        public:
                //! インスタンスを取得する
                static Uid_Dictionary& get_instance();

                //! 追加する
                void insert( const std::string& uid, const std::string& name, const std::string& type );

                //! 検索する
                const Uid_Dictionary_Item* find( const std::string& uid ) const;

        private:
                std::map<std::string, Uid_Dictionary_Item> dictionary_;

                //! 構築する
                explicit Uid_Dictionary();
        };

} // namespace dtr

#endif
