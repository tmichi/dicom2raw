#ifndef DTR_UID_DICTIONARY_DATA_HPP
#define DTR_UID_DICTIONARY_DATA_HPP

#include <utility>

namespace dtr
{

//! �ŗL���ʎq�����̃f�[�^
        struct Uid_Dictionary_Data {
                const char* uid;
                const char* name;
                const char* type;
        };

//! �ŗL���ʎq�����̃f�[�^���擾����
        std::pair<const Uid_Dictionary_Data*, const Uid_Dictionary_Data*> get_uid_dictionary_data();

} // namespace dtr

#endif
