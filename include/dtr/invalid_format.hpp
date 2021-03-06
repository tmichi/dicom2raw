#ifndef DTR_INVALID_FORMAT_HPP
#define DTR_INVALID_FORMAT_HPP

#include <exception>

namespace dtr
{

//! 妥当でない形式であることを示す例外
        class Invalid_Format : public std::exception
        {
        public:
                virtual const char* what() const throw() {
                        return "Invalid format";
                }
        };

} // namespace dtr

#endif
