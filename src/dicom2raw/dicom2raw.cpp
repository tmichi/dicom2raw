#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <dtr.hpp>
#include "dicom2raw_epilogue_html.hpp"
#include "dicom2raw_prologue_html.hpp"

// Visual C++またはNo-Cygwinで標準出力をバイナリモードにするハックが必要とするヘッダ
#if defined(_MSC_VER) || defined(__MINGW32__)
#include <io.h>
#include <fcntl.h>
#endif

//! HTML出力
class Html_Printer : public std::unary_function<const dtr::Element&, void>
{
public:
    explicit Html_Printer( std::ostream& out ) : out_( &out ) {}

    void operator()( const dtr::Element& element ) const {
        std::ostringstream out;
        if ( element.get_value_length() > 0 ) {
            out << dtr::Value( element.get_vr(), element.get_value(), element.get_value_length() );
        }
        std::string value = out.str();

        while ( true ) {
            std::string::size_type pos = value.find( '\n' );
            if ( pos == std::string::npos ) {
                break;
            }
            value.replace( pos, 1, "<br/>" );
        }

        const dtr::Element_Dictionary_Item* element_dictionary_item = dtr::Element_Dictionary::get_instance().find( element.get_tag() );
        *out_
                << std::setfill( '0' ) << std::hex
                << "            <tr>"
                << "<td>" << std::setw( 4 ) << element.get_tag().get_group_number() << "</td>"
                << "<td>" << std::setw( 4 ) << element.get_tag().get_element_number() << "</td>"
                << std::setfill( ' ' ) << std::dec
                << "<td>" << ( element_dictionary_item ? element_dictionary_item->get_name() : "&nbsp;" ) << "</td>"
                << "<td>" << element.get_vr() << "</td>"
                << "<td>" << element.get_value_length() << "</td>"
                << "<td>" << value << "</td>"
                << "</tr>\n";
    }

private:
    std::ostream* out_;
};

int main( int ac, char* av[] )
{
    std::string input_file;
    std::string output_file;
    std::string output_mode;

    int opt_i = 1;
    while ( opt_i < ac ) {
        std::string opt = av[opt_i++];
        bool opt_arg = false;

        if ( opt.find( "-m" ) == 0 || opt.find( "--m" ) == 0 ) {
            output_mode = "meta";
            opt_arg = true;
        } else if ( opt.find( "-H" ) == 0 || opt.find( "--ht" ) == 0 ) {
            output_mode = "html";
            opt_arg = true;
        } else if ( opt.find( "-h" ) == 0 || opt.find( "--he" ) == 0 ) {
            output_mode = "help";
            break;
        } else {
            input_file = opt;
        }

        if ( opt_arg ) {
            if ( opt_i >= ac ) {
                output_mode = "help";
                break;
            }
            output_file = av[opt_i++];
        }
    }
    if ( output_mode == "help" ) {
        std::cerr
                << av[0] << " INPUT.dcm > OUTPUT.raw\n"
                << av[0] << " INPUT.dcm [-m|-meta|--meta] OUTPUT.meta\n"
                << av[0] << " INPUT.dcm [-H|-html|--html] OUTPUT.html\n"
                << av[0] << " [-h|-help|--help]\n";
        return 1;
    }

    std::ifstream in( input_file.c_str(), std::ios::in | std::ios::binary );
    if ( ! in ) {
        std::cerr << "[ERROR]: Could not open file [" << input_file << "]\n";
        return 1;
    }

    dtr::File file;
    std::string error = file.parse( in );
    if ( ! error.empty() ) {
        std::cerr << "[ERROR]: " << error << "\n";
        return 1;
    }

    if ( output_mode == "meta" ) {
        std::ofstream out( output_file.c_str() );
        const dtr::Information& information = file.get_information();
        out << "Rows: " << information.get_rows() << "\n"
            << "Columns: " << information.get_columns() << "\n"
            << "Pixel Spacing: " << information.get_pixel_spacing_row() << ", " << information.get_pixel_spacing_column() << "\n"
            << "Bits Stored: " << information.get_bits_stored() << "\n"
            << "Bits Allocated: " << information.get_bits_allocated() << "\n"
            << "High Bit: " << information.get_high_bit() << "\n";
    } else if ( output_mode == "html" ) {
        std::ofstream out( output_file.c_str() );
        out << DICOM2RAW_PROLOGUE_HTML;
        std::for_each( file.get_element().begin(), file.get_element().end(), Html_Printer( out ) );
        out << DICOM2RAW_EPILOGUE_HTML;
    }

#if defined(_MSC_VER) || defined(__MINGW32__)
    // Visual C++またはNo-Cygwinで標準出力をバイナリモードにするハック
    std::cout << std::flush;
    _setmode( _fileno( stdout ), _O_BINARY );
#endif

    std::cout.write( static_cast<const char*>( file.get_pixel_data() ), file.get_pixel_data_length() );

    return 0;
}
