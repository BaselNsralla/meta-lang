#include <boost/xpressive/xpressive.hpp>
#include <optional>

using namespace boost::xpressive;


template <class T>
concept stringType = std::is_same<typename std::decay<T>::type,
                                  std::string>::value;

namespace lexer {
    class TokenPattern {
    public:
    template<stringType T> 
    TokenPattern(T&&);

    std::optional<std::string> match(std::string& value, int group = 0);
    
    private:
        sregex rex;
    };
}

template<stringType T> 
lexer::TokenPattern::TokenPattern(T&& str) {
    rex = sregex::compile(std::forward<T>(str));
}
