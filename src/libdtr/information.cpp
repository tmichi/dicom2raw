#include <dtr/information.hpp>

namespace dtr
{

        void Information::clear()
        {
                implicit_vr_ = true;
                little_endian_ = true;
                samples_per_pixel_ = 0;
                rows_ = 0;
                columns_ = 0;
                pixel_spacing_row_ = 1;
                pixel_spacing_column_ = 1;
                slice_thickness_ = 1;
                spacing_between_slices_ = 1;
                bits_allocated_ = 0;
                bits_stored_ = 0;
                high_bit_ = 0;
        }

} // namespace dtr
