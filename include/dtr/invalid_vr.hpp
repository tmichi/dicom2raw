#ifndef DTR_INVALID_VR_HPP
#define DTR_INVALID_VR_HPP

#include <exception>

namespace dtr
{

//! 妥当でない値表現であることを示す例外
        class Invalid_Vr : public std::exception
        {
        public:
                virtual const char* what() const throw() {
                        return "Invalid vr";
                }
        };

} // namespace dtr

#endif
