#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <dtr.hpp>

int main( int argc, char* argv[] )
{
	if( argc == 1 ) {
		std::cerr << argv[0] << " input0.dcm input1.dcm ...."<<std::endl;
		std::cerr << argv[0] << " *.dcm "<<std::endl;
		return 1;
	}
	std::vector<std::string> files;
	for( int i = 1 ; i < argc ; ++i ) {
		files.push_back( std::string( argv[i] ) );
	}
	
	std::string output_file;
	
	if( files.size() == 0 ) {
		std::cerr<<"[error] number of DICOM files is zero"<<std::endl;
		return -1;
	}
	
	int sx, sy, sz;
	double px, py, pz;
	double ox, oy, oz;
	int voxelSize = 1;
	
	std::vector<std::pair<double, int> > sorted_indices;
	for ( int i = 0 ; i < files.size() ; ++i ) {
		const std::string& dicomFile = files.at( i );
		std::ifstream fin( dicomFile.c_str(), std::ios::in | std::ios::binary );
		if ( ! fin ) {
			std::cerr << "[error]: Could not open file [" << files.at( i ) << "]\n";
			return -2;
		}
		dtr::File file;
		std::string error = file.parse( fin );
		if ( ! error.empty() ) {
			std::cerr << "[error]: " << error << "\n";
			return -2;
		}
		const dtr::Information& information = file.get_information();
		if ( i == 0 ) {
			voxelSize = static_cast<int> ( ( information.get_bits_stored() -1 ) / 8 ) + 1  ;
			std::cout<<"voxel size: "<<voxelSize<<std::endl;
			
			sx = information.get_rows();
			sy = information.get_columns();
			sz = static_cast<int>(files.size());
			
			px = information.get_pixel_spacing_row();
			py = information.get_pixel_spacing_column();
			pz = information.get_spacing_between_slices();
			
			ox = information.get_image_position_patient_x();
			oy = information.get_image_position_patient_y();
		}
		sorted_indices.push_back ( std::make_pair( oz, i ) );
	}	    
	// sort indices by z coordinate
	std::sort ( sorted_indices.begin(), sorted_indices.end() );
	oz = sorted_indices[0].first;
	std::cout<<"origin:"<<ox<<","<<oy<<","<<oz<<std::endl;
	std::string output_header = files[0];
	std::stringstream ss;
	ss<<output_header<<"-"<<sx<<"x"<<sy<<"x"<<sz<<"-"<<px<<"x"<<py<<"x"<<pz<<".raw";
	output_file = ss.str();   
	std::cerr<<"saving raw file to "<<output_file<<std::endl;
	
	std::ofstream fout( output_file.c_str(), std::ios::binary );
	if( !fout ) {
		std::cerr << "[error]: could not open file [" << output_file << "]\n";
		return -1;
	}
	for( int i = 0 ; i < static_cast<int>( files.size() ) ; ++i ) {
		std::string& slice_name =  files[sorted_indices[i].second];
		std::cerr<<slice_name<<" "<<sorted_indices[i].first<<std::endl;
		std::ifstream fin(slice_name.c_str(), std::ios::in | std::ios::binary );
		if ( !fin ) {
			std::cerr << "[error]: could not open file [" << slice_name << "]\n";
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
