#ifndef DTR_INVALID_FORMAT_HPP
#define DTR_INVALID_FORMAT_HPP

#include <exception>

namespace dtr
{

//! ‘Ã“–‚Å‚È‚¢Œ`Ž®‚Å‚ ‚é‚±‚Æ‚ðŽ¦‚·—áŠO
        class Invalid_Format : public std::exception
        {
        public:
                virtual const char* what() const throw() {
                        return "Invalid format";
                }
        };

} // namespace dtr

#endif
