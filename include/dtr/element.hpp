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

//! �f�[�^�v�f
class Element {
public:
    //! �\�z����
    explicit Element() {}

    //! ��͂���
    bool parse(Reader& reader, Information& information);

    //! �f�[�^�v�f�^�O���擾����
    const Tag& get_tag() const {
        return tag_;
    }

    //! �l�\�����擾����
    const std::string& get_vr() const {
        return vr_;
    }

    //! �l�������擾����
    size_t get_value_length() const {
        return value_length_;
    }

    //! �l���擾����
    const char* get_value() const {
        return &value_[0];
    }

    //! ��������
    void swap(Element& rhs);

private:
    Tag tag_;
    std::string vr_;
    size_t value_length_;
    std::vector<char> value_;
};

} // namespace dtr

#endif
