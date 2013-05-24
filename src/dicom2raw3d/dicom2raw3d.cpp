#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <dtr.hpp>

int create_output_file_name( const std::vector<std::string> & input_files, std::string& output_file )
{
    if( input_files.size() == 0 ) {
        std::cerr<<"[error] number of DICOM files is zero"<<std::endl;
        return -1;
    }
    std::ifstream fin( input_files[0].c_str(), std::ios::in | std::ios::binary );
    if ( ! fin ) {
        std::cerr << "[error]: Could not open file [" << input_files[0] << "]\n";
        return -1;
    }
    dtr::File file;
    std::string error = file.parse( fin );
    if ( ! error.empty() ) {
        std::cerr << "[error]: " << error << "\n";
        return -1;
    }
    const dtr::Information& information = file.get_information();
    int sx = information.get_rows();
    int sy = information.get_columns();
    int sz = input_files.size();
    double px = information.get_pixel_spacing_row();
    double py = information.get_pixel_spacing_column();
    double pz = information.get_spacing_between_slices();

    double ox = information.get_image_position_patient_x();
    double oy = information.get_image_position_patient_y();
    double oz = information.get_image_position_patient_z();
    std::cerr<<"[info] origin position : ("<<ox<<", "<<oy<<", "<<oz<<")"<<std::endl;
    std::stringstream ss;

    //
    std::string output_header;
    output_header = input_files[0];
    ss<<output_header<<"-"<<sx<<"x"<<sy<<"x"<<sz<<"-"<<px<<"x"<<py<<"x"<<pz<<".raw";
    output_file = ss.str();
    std::cerr<< "[info] bits stored: " << information.get_bits_stored() << std::endl;
    return 1;
}

int main( int argc, char* argv[] )
{
    if( argc == 1 ) {
        std::cerr << argv[0] << " input0.dcm input1.dcm ...."<<std::endl;
        std::cerr << argv[0] << " *.dcm "<<std::endl;
        return 1;
    }
    std::vector<std::string> input_files;
    for( int i = 1 ; i < argc ; ++i ) {
        input_files.push_back( std::string( argv[i] ) );
    }

    std::string output_file;
    if( ! create_output_file_name( input_files, output_file ) ) {
        return -1;
    }

    std::cerr<<"saving raw file to "<<output_file<<std::endl;
    std::ofstream fout( output_file.c_str(), std::ios::binary );
    if( !fout ) {
        std::cerr << "[error]: could not open file [" << output_file << "]\n";
        return -1;
    }
    for( int i = 0 ; i < static_cast<int>( input_files.size() ) ; ++i ) {
        std::ifstream fin( input_files[i].c_str(), std::ios::in | std::ios::binary );
        if ( !fin ) {
            std::cerr << "[error]: could not open file [" << input_files[i] << "]\n";
            return -1;
        }
        dtr::File file;
        std::string error = file.parse( fin );
        if ( ! error.empty() ) {
            std::cerr << "[error]: " << error << "\n";
            return -1;
        }
        const dtr::Information& info = file.get_information();
        fout.write( static_cast<const char*>( file.get_pixel_data() ), file.get_pixel_data_length() );
    }
    return 0;
}
