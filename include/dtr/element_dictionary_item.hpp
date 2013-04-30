#ifndef DTR_ELEMENT_DICTIONARY_ITEM_HPP
#define DTR_ELEMENT_DICTIONARY_ITEM_HPP

#include <string>

namespace dtr {

//! �f�[�^�v�f�^�O�����̍���
class Element_Dictionary_Item {
public:
    //! �\�z����
    explicit Element_Dictionary_Item(const std::string& name, const std::string& vr, const std::string& vm, bool retired);

    //! ���O���擾����
    const std::string& get_name() const {
        return name_;
    }

    //! �l�\�����擾����
    const std::string& get_vr() const {
        return vr_;
    }

    //! �l�����x���擾����
    const std::string& get_vm() const {
        return vm_;
    }

    //! �ޖ��������ǂ������擾����
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
