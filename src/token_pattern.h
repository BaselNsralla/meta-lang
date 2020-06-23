#include <boost/xpressive/xpressive.hpp>
#include <optional>

using namespace boost::xpressive;


template <class T>
concept stringType = std::is_same<typename std::decay<T>::type,
                                  std::string>::value;
// default parametrar gör man .h filen
namespace lexer {
    class TokenPattern {
    public:
	template<stringType T> 
	TokenPattern(T&&, int);
	
	std::optional<std::string> match(std::string& value);
    
    private:
        sregex rex;
	int group;
    };
}

template<stringType T> 
lexer::TokenPattern::TokenPattern(T&& str, int grp) {
    rex   = sregex::compile(std::forward<T>(str));
    group = grp;
}
