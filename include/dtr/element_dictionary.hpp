#ifndef DTR_ELEMENT_DICTIONARY_HPP
#define DTR_ELEMENT_DICTIONARY_HPP

#include <map>
#include <set>
#include "element_dictionary_item.hpp"
#include "tag.hpp"

namespace dtr
{

//! �f�[�^�v�f�^�O����
        class Element_Dictionary
        {
        public:
                //! �C���X�^���X���擾����
                static Element_Dictionary& get_instance();

                //! �ǉ�����
                void insert( uint16_t group_mask, uint16_t element_mask, uint16_t group_number, uint16_t element_number, const std::string& name, const std::string& vr, const std::string& vm, bool retired );

                //! ��������
                const Element_Dictionary_Item* find( const Tag& tag ) const;

        private:
                std::set<Tag> mask_;
                std::map<Tag, Element_Dictionary_Item> dictionary_;

                //! �\�z����
                explicit Element_Dictionary();
        };

} // namespace dtr

#endif
