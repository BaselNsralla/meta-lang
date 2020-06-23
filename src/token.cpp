#include "token.h"

TokenType Token::tokenType() {
    return this->tt;
}

bool Token::operator ==(Token const& rhs) {
    return rhs.tt == this->tt;
}

bool Token::operator ==(TokenType rhs) {
    return this->tt == rhs;
}
