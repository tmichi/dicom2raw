#ifndef DTR_ELEMENT_DICTIONARY_ITEM_HPP
#define DTR_ELEMENT_DICTIONARY_ITEM_HPP

#include <string>

namespace dtr {

//! データ要素タグ辞書の項目
class Element_Dictionary_Item {
public:
    //! 構築する
    explicit Element_Dictionary_Item(const std::string& name, const std::string& vr, const std::string& vm, bool retired);

    //! 名前を取得する
    const std::string& get_name() const {
        return name_;
    }

    //! 値表現を取得する
    const std::string& get_vr() const {
        return vr_;
    }

    //! 値複数度を取得する
    const std::string& get_vm() const {
        return vm_;
    }

    //! 退役したかどうかを取得する
    bool get_retired() const {
        return retired_;
    }

private:
    std::string name_;
    std::string vr_;
    std::string vm_;
    bool retired_;
};

} // namespace dtr

#endif
