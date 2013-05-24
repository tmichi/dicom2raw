#ifndef DTR_INFORMATION_HPP
#define DTR_INFORMATION_HPP

#include <stdint.hpp>
#include <string>

namespace dtr
{

//! 情報
        /*!
            情報格納用の構造体である。ファイル解析の過程で適切な値が設定される。
         */
        class Information
        {
        public:
                //! 構築する
                explicit Information() {
                        clear();
                }

                //! 消去する
                void clear();

                //! 暗黙的VRかどうかを設定する
                void set_implicit_vr( bool implicit_vr ) {
                        implicit_vr_ = implicit_vr;
                }

                //! リトルエンディアンかどうかを設定する
                void set_little_endian( bool little_endian ) {
                        little_endian_ = little_endian;
                }

                //! 画素あたりサンプルを設定する
                void set_samples_per_pixel( uint16_t samples_per_pixel ) {
                        samples_per_pixel_ = samples_per_pixel;
                }

                //! 行数を設定する
                void set_rows( uint16_t rows ) {
                        rows_ = rows;
                }

                //! 列数を設定する
                void set_columns( uint16_t columns ) {
                        columns_ = columns;
                }

                //! 行のピクセル間隔を指定する
                void set_pixel_spacing_row( double pixel_spacing_row ) {
                        pixel_spacing_row_ = pixel_spacing_row;
                }

                //! 列のピクセル間隔を指定する
                void set_pixel_spacing_column( double pixel_spacing_column ) {
                        pixel_spacing_column_ = pixel_spacing_column;
                }

                //! 画像間のピクセル間隔を指定する
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

                //! 割り当てビットを設定する
                void set_bits_allocated( uint16_t bits_allocated ) {
                        bits_allocated_ = bits_allocated;
                }

                //! 格納ビットを設定する
                void set_bits_stored( uint16_t bits_stored ) {
                        bits_stored_ = bits_stored;
                }

                //! 高位ビットを設定する
                void set_high_bit( uint16_t high_bit ) {
                        high_bit_ = high_bit;
                }

                //! 暗黙的VRかどうかを取得する
                bool get_implicit_vr() const {
                        return implicit_vr_;
                }

                //! リトルエンディアンかどうかを取得する
                bool get_little_endian() const {
                        return little_endian_;
                }

                //! 画素あたりサンプルを取得する
                uint16_t get_samples_per_pixel() const {
                        return samples_per_pixel_;
                }

                //! 行数を取得する
                uint16_t get_rows() const {
                        return rows_;
                }

                //! 列数を取得する
                uint16_t get_columns() const {
                        return columns_;
                }

                //! 行のピクセル間隔を取得する
                double get_pixel_spacing_row() const {
                        return pixel_spacing_row_;
                }

                //! 列のピクセル間隔を取得する
                double get_pixel_spacing_column() const {
                        return pixel_spacing_column_;
                }

                //! 画像間のピクセル間隔を取得する
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

                //! 割り当てビットを取得する
                uint16_t get_bits_allocated() const {
                        return bits_allocated_;
                }

                //! 格納ビットを取得する
                uint16_t get_bits_stored() const {
                        return bits_stored_;
                }

                //! 高位ビットを取得する
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
