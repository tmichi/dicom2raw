#ifndef DTR_UID_DICTIONARY_DATA_HPP
#define DTR_UID_DICTIONARY_DATA_HPP

#include <utility>

namespace dtr
{

//! 固有識別子辞書のデータ
        struct Uid_Dictionary_Data {
                const char* uid;
                const char* name;
                const char* type;
        };

//! 固有識別子辞書のデータを取得する
        std::pair<const Uid_Dictionary_Data*, const Uid_Dictionary_Data*> get_uid_dictionary_data();

} // namespace dtr

#endif
