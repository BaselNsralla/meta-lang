#include <boost/xpressive/xpressive.hpp>
#include <optional>
#include <string>

using namespace boost::xpressive;


template <class T>
concept Sype = std::is_same<typename std::decay<T>::type,
                                  std::string>::value;
// default parametrar gör man .h filen
namespace lex {
    /*
    finns en note om hur detta
    skulle kunna fixas med istringstream
    enum TokenLogicalType {
        // commands	
	keyword,
	// primary
	identifier,
	literal
    };
    */
    class TokenPattern {
    public:
	template<Sype T> 
        TokenPattern(T&&, int);
	
	std::optional<std::string> match(std::string& value);
    
	//private:
        sregex rex;
	int group;
    };
}

template<Sype T> 
lex::TokenPattern::TokenPattern(T&& str, int grp) {
    rex   = sregex::compile(std::forward<T>(str));// moves if the generated function is of r-val
    group = grp;
}
