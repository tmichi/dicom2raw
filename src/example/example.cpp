#include <fstream>
#include <iostream>
#include <dtr.hpp>

// Visual C++�܂���No-Cygwin�ŕW���o�͂��o�C�i�����[�h�ɂ���n�b�N���K�v�Ƃ���w�b�_
#if defined(_MSC_VER) || defined(__MINGW32__)
#include <io.h>
#include <fcntl.h>
#endif

//! �T���v����main�֐�
/*!
    ���̓t�@�C�����������Ɏ��A�W���o�͂Ƀs�N�Z���f�[�^��RAW�`���ŏo�͂���BDICOM�K�i�Ɋ܂܂��s�N�Z���f�[�^�ȊO�̏����A�W���G���[�o�͂ɏo�͂���B
 */
int main( int ac, char* av[] )
{
    // ���̓t�@�C����
    static const char* input_file = av[1];

    // �W���t�@�C�����̓X�g���[�����o�C�i�����[�h�ŊJ��
    std::ifstream in( input_file, std::ios::in | std::ios::binary );

    // �Ȃ�炩�̃G���[�����������ꍇ�A�U�ɕ]�������X�g���[�����Ԃ����
    if ( ! in ) {
        // �G���[��\�����ďI������
        std::cerr << "[ERROR]: Could not open file [" << input_file << "]\n";
        return 1;
    }

    // DICOM�t�@�C�����\�z����
    dtr::File file;

    // �t�@�C�����̓X�g���[������͂���
    std::string error = file.parse( in );

    // �Ȃ�炩�̃G���[�����������ꍇ�A��łȂ������񂪕Ԃ����
    if ( ! error.empty() ) {
        // �G���[��\�����ďI������
        std::cerr << "[ERROR]: " << error << "\n";
        return 1;
    }

    // �s�N�Z���f�[�^�̃T�C�Y��\������
    std::cerr << "Pixel Data Length: " << file.get_pixel_data_length() << "\n";

#if defined(_MSC_VER) || defined(__MINGW32__)
    // Visual C++�܂���No-Cygwin�ŕW���o�͂��o�C�i�����[�h�ɂ���n�b�N
    std::cout << std::flush;
    _setmode( _fileno( stdout ), _O_BINARY );
#endif

    // �s�N�Z���f�[�^��W���o�͂ɏ����o��
    std::cout.write( static_cast<const char*>( file.get_pixel_data() ), file.get_pixel_data_length() );

    // DICOM�t�@�C���̃��^�����擾����
    const dtr::Information& information = file.get_information();

    std::cerr
    // �s���i�摜�����j��\������
            << "Rows: " << information.get_rows() << "\n"
            // �񐔁i�摜���j��\������
            << "Columns: " << information.get_columns() << "\n"
            // �s�����iY�����j�̃s�N�Z���Ԋu��\������
            << "Pixel Spacing (Row): " << information.get_pixel_spacing_row() << "\n"
            // ������iX�����j�̃s�N�Z���Ԋu��\������
            << "Pixel Spacing (Column): " << information.get_pixel_spacing_column() << "\n";

    return 0;
}
