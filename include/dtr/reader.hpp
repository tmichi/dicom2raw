#ifndef DTR_READER_HPP
#define DTR_READER_HPP

#include <stddef.h>
#include <iosfwd>

namespace dtr {

//! �o�C�i���f�[�^���[�_
class Reader {
public:
    //! �\�z����
    explicit Reader(std::istream& in);

    //! ���g���G���f�B�A���œǂݍ��ނ悤�ɐݒ肷��
    void set_little_endian(bool little_endian);

    //! �ǂݍ���
    /*!
        �v�f�̃T�C�Y��2�ȏ�ŁA���̓f�[�^�ƃz�X�g�̃G���f�B�A�����قȂ�ꍇ�A�G���f�B�A�������������s���B

        \param[out] buffer
            �v�f�̃T�C�Y�ƌ��������������̗e�ʂ����o�͐�o�b�t�@
        \param[in] size
            �v�f�̃T�C�Y
        \param[in] count
            �v�f�̌�
     */
    void read(void* buffer, size_t size, size_t count);

    //! �^���t���œǂݍ���
    /*!
        sizeof(T)��2�ȏ�ŁA���̓f�[�^�ƃz�X�g�̃G���f�B�A�����قȂ�ꍇ�A�G���f�B�A�������������s���B
     */
    template <typename T>
    void read(T& value) {
        read(&value, sizeof(value), 1);
    }

    //! �擪�ʒu����̃I�t�Z�b�g��ݒ肷��
    void seek_beg(size_t offset);

    //! ���݈ʒu����̃I�t�Z�b�g��ݒ肷��
    void seek_cur(size_t offset);

private:
    std::istream& in_;
    bool endian_swap_;

    //! �����s��
    explicit Reader(const Reader& rhs);

    //! �����s��
    Reader& operator=(const Reader& rhs);
};

} // namespace dtr

#endif
