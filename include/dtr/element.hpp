#ifndef DTR_ELEMENT_HPP
#define DTR_ELEMENT_HPP

#include <stddef.h>
#include <stdint.hpp>
#include <string>
#include <vector>
#include "information.hpp"
#include "reader.hpp"
#include "tag.hpp"

namespace dtr {

//! データ要素
class Element {
public:
    //! 構築する
    explicit Element() {}

    //! 解析する
    bool parse(Reader& reader, Information& information);

    //! データ要素タグを取得する
    const Tag& get_tag() const {
        return tag_;
    }

    //! 値表現を取得する
    const std::string& get_vr() const {
        return vr_;
    }

    //! 値長さを取得する
    size_t get_value_length() const {
        return value_length_;
    }

    //! 値を取得する
    const char* get_value() const {
        return &value_[0];
    }

    //! 交換する
    void swap(Element& rhs);

private:
    Tag tag_;
    std::string vr_;
    size_t value_length_;
    std::vector<char> value_;
};

} // namespace dtr

#endif
