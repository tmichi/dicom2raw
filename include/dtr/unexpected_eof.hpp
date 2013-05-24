#ifndef DTR_UNEXPECTED_EOF_HPP
#define DTR_UNEXPECTED_EOF_HPP

#include <exception>

namespace dtr
{

//! �t�@�C���I�[��������O
        class Unexpected_Eof : public std::exception
        {
        public:
                virtual const char* what() const throw() {
                        return "Unexpected eof";
                }
        };

} // namespace dtr

#endif
