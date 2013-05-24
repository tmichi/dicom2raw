#ifndef DTR_INFORMATION_HPP
#define DTR_INFORMATION_HPP

#include <stdint.hpp>
#include <string>

namespace dtr
{

//! ���
        /*!
            ���i�[�p�̍\���̂ł���B�t�@�C����͂̉ߒ��œK�؂Ȓl���ݒ肳���B
         */
        class Information
        {
        public:
                //! �\�z����
                explicit Information() {
                        clear();
                }

                //! ��������
                void clear();

                //! �ÖٓIVR���ǂ�����ݒ肷��
                void set_implicit_vr( bool implicit_vr ) {
                        implicit_vr_ = implicit_vr;
                }

                //! ���g���G���f�B�A�����ǂ�����ݒ肷��
                void set_little_endian( bool little_endian ) {
                        little_endian_ = little_endian;
                }

                //! ��f������T���v����ݒ肷��
                void set_samples_per_pixel( uint16_t samples_per_pixel ) {
                        samples_per_pixel_ = samples_per_pixel;
                }

                //! �s����ݒ肷��
                void set_rows( uint16_t rows ) {
                        rows_ = rows;
                }

                //! �񐔂�ݒ肷��
                void set_columns( uint16_t columns ) {
                        columns_ = columns;
                }

                //! �s�̃s�N�Z���Ԋu���w�肷��
                void set_pixel_spacing_row( double pixel_spacing_row ) {
                        pixel_spacing_row_ = pixel_spacing_row;
                }

                //! ��̃s�N�Z���Ԋu���w�肷��
                void set_pixel_spacing_column( double pixel_spacing_column ) {
                        pixel_spacing_column_ = pixel_spacing_column;
                }

                //! �摜�Ԃ̃s�N�Z���Ԋu���w�肷��
                void set_slice_thickness( double slice_thickness ) {
                        slice_thickness_ = slice_thickness;
                }

                void set_spacing_between_slices( double spacing_between_slices ) {
                        spacing_between_slices_ = spacing_between_slices;
                }

		void set_image_position_patient( double x, double y , double z) {
			image_position_patient_x_ = x;
			image_position_patient_y_ = y;
			image_position_patient_z_ = z;
		}

                //! ���蓖�ăr�b�g��ݒ肷��
                void set_bits_allocated( uint16_t bits_allocated ) {
                        bits_allocated_ = bits_allocated;
                }

                //! �i�[�r�b�g��ݒ肷��
                void set_bits_stored( uint16_t bits_stored ) {
                        bits_stored_ = bits_stored;
                }

                //! ���ʃr�b�g��ݒ肷��
                void set_high_bit( uint16_t high_bit ) {
                        high_bit_ = high_bit;
                }

                //! �ÖٓIVR���ǂ������擾����
                bool get_implicit_vr() const {
                        return implicit_vr_;
                }

                //! ���g���G���f�B�A�����ǂ������擾����
                bool get_little_endian() const {
                        return little_endian_;
                }

                //! ��f������T���v�����擾����
                uint16_t get_samples_per_pixel() const {
                        return samples_per_pixel_;
                }

                //! �s�����擾����
                uint16_t get_rows() const {
                        return rows_;
                }

                //! �񐔂��擾����
                uint16_t get_columns() const {
                        return columns_;
                }

                //! �s�̃s�N�Z���Ԋu���擾����
                double get_pixel_spacing_row() const {
                        return pixel_spacing_row_;
                }

                //! ��̃s�N�Z���Ԋu���擾����
                double get_pixel_spacing_column() const {
                        return pixel_spacing_column_;
                }

                //! �摜�Ԃ̃s�N�Z���Ԋu���擾����
                double get_slice_thickness() const {
                        return slice_thickness_;
                }
                double get_spacing_between_slices() const {
                        return spacing_between_slices_ ;
                }
		double get_image_position_patient_x() const{
			return image_position_patient_x_;
		}

		double get_image_position_patient_y()const{
			return image_position_patient_y_;
		}

		double get_image_position_patient_z()const{
			return image_position_patient_z_;
		}

                //! ���蓖�ăr�b�g���擾����
                uint16_t get_bits_allocated() const {
                        return bits_allocated_;
                }

                //! �i�[�r�b�g���擾����
                uint16_t get_bits_stored() const {
                        return bits_stored_;
                }

                //! ���ʃr�b�g���擾����
                uint16_t get_high_bit() const {
                        return high_bit_;
                }

        private:
                bool implicit_vr_;
                bool little_endian_;
                uint16_t samples_per_pixel_;
                uint16_t rows_;
                uint16_t columns_;
                double pixel_spacing_row_;
                double pixel_spacing_column_;
                double slice_thickness_;
                double  spacing_between_slices_;
                double image_position_patient_x_;
                double image_position_patient_y_;
                double image_position_patient_z_;
                uint16_t bits_allocated_;
                uint16_t bits_stored_;
                uint16_t high_bit_;
                bool pixel_representation_;
        };

} // namespace dtr

#endif
