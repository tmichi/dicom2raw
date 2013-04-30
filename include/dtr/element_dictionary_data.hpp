#ifndef DTR_ELEMENT_DICTIONARY_DATA_HPP
#define DTR_ELEMENT_DICTIONARY_DATA_HPP

#include <stdint.hpp>
#include <utility>

namespace dtr {

//! データ要素タグ辞書のデータ
struct Element_Dictionary_Data {
    uint16_t group_mask;
    uint16_t element_mask;
    uint16_t group_number;
    uint16_t element_number;
    const char* name;
    const char* vr;
    const char* vm;
    bool retired;
};

//! データ要素タグ辞書のデータを取得する
std::pair<const Element_Dictionary_Data*, const Element_Dictionary_Data*> get_element_dictionary_data();

} // namespace dtr

#endif
