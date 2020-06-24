#include <string>
#include "coordinate.h"


// du kan göra en template class med std::forward till string så får du gratis
// constructorer för att du får en klass för varje typ


template <class T>
concept StringType = std::is_same<typename std::decay<T>::type,
                                  std::string>::value;

namespace lex {
    /*
    enum class TokenType {
	a,
	b
    };
    */
    struct Token {

	template <StringType T>
	Token(T&& val, Coordinate coordinate, T&& type):
	    value{std::forward<T>(val)},
	    coordinate{std::move(coordinate)},
	    logical_type{std::forward<T>(type)} {};
        
	std::string const value;
	Coordinate const coordinate;

    private:
	std::string const logical_type;
		
    public:
	std::string const& tokenType();
	
	bool operator ==(Token const&);
	//bool operator ==(TokenType);
	//TokenType operator()();
    };
}
