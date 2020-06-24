#include "token.h"

using namespace lex;


/*
TokenType Token::tokenType() {
    return this->tt;
}
*/


std::string const& Token::tokenType() {
    return this->logical_type;
}


bool Token::operator ==(Token const& rhs) {
    return rhs.logical_type == this->logical_type;
}

/*
bool Token::operator ==(TokenType rhs) {
    return this->logical_type == rhs;
}
*/
