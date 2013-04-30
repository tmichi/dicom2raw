#ifndef DTR_UNSUPPORTED_TRANSFER_SYNTAX_HPP
#define DTR_UNSUPPORTED_TRANSFER_SYNTAX_HPP

#include <exception>

namespace dtr {

//! ‘Î‰‚µ‚Ä‚¢‚È‚¢“]‘—\•¶‚Å‚ ‚é‚±‚Æ‚ğ¦‚·—áŠO
class Unsupported_Transfer_Syntax : public std::exception {
public:
    virtual const char* what() const throw() {
        return "Unsupported transfer syntax";
    }
};

} // namespace dtr

#endif
