#ifndef DTR_INVALID_FORMAT_HPP
#define DTR_INVALID_FORMAT_HPP

#include <exception>

namespace dtr
{

//! �Ó��łȂ��`���ł��邱�Ƃ�������O
        class Invalid_Format : public std::exception
        {
        public:
                virtual const char* what() const throw() {
                        return "Invalid format";
                }
        };

} // namespace dtr

#endif
