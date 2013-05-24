#ifndef CSN7_UID_DICTIONARY_ITEM_HPP
#define CSN7_UID_DICTIONARY_ITEM_HPP

#include <string>

namespace dtr
{

//! �ŗL���ʎq�����̍���
        class Uid_Dictionary_Item
        {
        public:
                //! �\�z����
                explicit Uid_Dictionary_Item( const std::string& name, const std::string& type );

                //! ���O���擾����
                const std::string& get_name() const {
                        return name_;
                }

                //! �^�C�v���擾����
                const std::string& get_type() const {
                        return type_;
                }

        private:
                std::string name_;
                std::string type_;
        };

} // namespace dtr

#endif
