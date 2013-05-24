#ifndef DTR_UID_DICTIONARY_HPP
#define DTR_UID_DICTIONARY_HPP

#include <map>
#include <string>
#include "uid_dictionary_item.hpp"

namespace dtr
{

//! �ŗL���ʎq����
        class Uid_Dictionary
        {
        public:
                //! �C���X�^���X���擾����
                static Uid_Dictionary& get_instance();

                //! �ǉ�����
                void insert( const std::string& uid, const std::string& name, const std::string& type );

                //! ��������
                const Uid_Dictionary_Item* find( const std::string& uid ) const;

        private:
                std::map<std::string, Uid_Dictionary_Item> dictionary_;

                //! �\�z����
                explicit Uid_Dictionary();
        };

} // namespace dtr

#endif
