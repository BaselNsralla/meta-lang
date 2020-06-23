#include <string>

enum class TokenType {
    a,
    b
};


// du kan göra en template class med std::forward till string så får du gratis
// constructorer för att du får en klass för varje typ
struct Token {
    Token(std::string& val, int col, int row, TokenType tt): value{val}, column{col},
							      row{row}, tt{tt} {}
    Token(std::string&& val, int col, int row, TokenType tt): value{std::move(val)}, column{col},
							      row{row}, tt{tt} {}
    std::string value;
    int const column;
    int const row;
    
private:
    TokenType const tt;

public:
    TokenType tokenType();

    bool operator ==(Token const&);
    bool operator ==(TokenType);
    TokenType operator()();
};
