#ifndef DTR_INVALID_VR_HPP
#define DTR_INVALID_VR_HPP

#include <exception>

namespace dtr
{

//! �Ó��łȂ��l�\���ł��邱�Ƃ�������O
        class Invalid_Vr : public std::exception
        {
        public:
                virtual const char* what() const throw() {
                        return "Invalid vr";
                }
        };

} // namespace dtr

#endif
