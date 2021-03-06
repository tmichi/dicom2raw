#ifndef DTR_UNSUPPORTED_TRANSFER_SYNTAX_HPP
#define DTR_UNSUPPORTED_TRANSFER_SYNTAX_HPP

#include <exception>

namespace dtr
{

//! 対応していない転送構文であることを示す例外
        class Unsupported_Transfer_Syntax : public std::exception
        {
        public:
                virtual const char* what() const throw() {
                        return "Unsupported transfer syntax";
                }
        };

} // namespace dtr

#endif
