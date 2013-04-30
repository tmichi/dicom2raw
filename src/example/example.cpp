#include <fstream>
#include <iostream>
#include <dtr.hpp>

// Visual C++またはNo-Cygwinで標準出力をバイナリモードにするハックが必要とするヘッダ
#if defined(_MSC_VER) || defined(__MINGW32__)
#include <io.h>
#include <fcntl.h>
#endif

//! サンプルのmain関数
/*!
    入力ファイル名を引数に取り、標準出力にピクセルデータをRAW形式で出力する。DICOM規格に含まれるピクセルデータ以外の情報を、標準エラー出力に出力する。
 */
int main( int ac, char* av[] )
{
    // 入力ファイル名
    static const char* input_file = av[1];

    // 標準ファイル入力ストリームをバイナリモードで開く
    std::ifstream in( input_file, std::ios::in | std::ios::binary );

    // なんらかのエラーが発生した場合、偽に評価されるストリームが返される
    if ( ! in ) {
        // エラーを表示して終了する
        std::cerr << "[ERROR]: Could not open file [" << input_file << "]\n";
        return 1;
    }

    // DICOMファイルを構築する
    dtr::File file;

    // ファイル入力ストリームを解析する
    std::string error = file.parse( in );

    // なんらかのエラーが発生した場合、空でない文字列が返される
    if ( ! error.empty() ) {
        // エラーを表示して終了する
        std::cerr << "[ERROR]: " << error << "\n";
        return 1;
    }

    // ピクセルデータのサイズを表示する
    std::cerr << "Pixel Data Length: " << file.get_pixel_data_length() << "\n";

#if defined(_MSC_VER) || defined(__MINGW32__)
    // Visual C++またはNo-Cygwinで標準出力をバイナリモードにするハック
    std::cout << std::flush;
    _setmode( _fileno( stdout ), _O_BINARY );
#endif

    // ピクセルデータを標準出力に書き出す
    std::cout.write( static_cast<const char*>( file.get_pixel_data() ), file.get_pixel_data_length() );

    // DICOMファイルのメタ情報を取得する
    const dtr::Information& information = file.get_information();

    std::cerr
    // 行数（画像高さ）を表示する
            << "Rows: " << information.get_rows() << "\n"
            // 列数（画像幅）を表示する
            << "Columns: " << information.get_columns() << "\n"
            // 行方向（Y方向）のピクセル間隔を表示する
            << "Pixel Spacing (Row): " << information.get_pixel_spacing_row() << "\n"
            // 列方向（X方向）のピクセル間隔を表示する
            << "Pixel Spacing (Column): " << information.get_pixel_spacing_column() << "\n";

    return 0;
}
