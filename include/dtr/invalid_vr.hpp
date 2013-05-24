#ifndef DTR_INVALID_VR_HPP
#define DTR_INVALID_VR_HPP

#include <exception>

namespace dtr
{

//! ‘Ã“–‚Å‚È‚¢’l•\Œ»‚Å‚ ‚é‚±‚Æ‚ðŽ¦‚·—áŠO
        class Invalid_Vr : public std::exception
        {
        public:
                virtual const char* what() const throw() {
                        return "Invalid vr";
                }
        };

} // namespace dtr

#endif
