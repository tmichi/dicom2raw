#ifndef DTR_ELEMENT_DICTIONARY_HPP
#define DTR_ELEMENT_DICTIONARY_HPP

#include <map>
#include <set>
#include "element_dictionary_item.hpp"
#include "tag.hpp"

namespace dtr
{

//! データ要素タグ辞書
        class Element_Dictionary
        {
        public:
                //! インスタンスを取得する
                static Element_Dictionary& get_instance();

                //! 追加する
                void insert( uint16_t group_mask, uint16_t element_mask, uint16_t group_number, uint16_t element_number, const std::string& name, const std::string& vr, const std::string& vm, bool retired );

                //! 検索する
                const Element_Dictionary_Item* find( const Tag& tag ) const;

        private:
                std::set<Tag> mask_;
                std::map<Tag, Element_Dictionary_Item> dictionary_;

                //! 構築する
                explicit Element_Dictionary();
        };

} // namespace dtr

#endif
