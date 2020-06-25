#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <boost/xpressive/xpressive.hpp>
#include <exception>
#include <numeric>
#include "token.h"
#include <fstream>
#include "token_pattern.h"
#include <iterator>
#include <sstream>
#include <map>
#include "coordinate.h"
#include <utility>
#include "tokenize.h"


using namespace boost::xpressive;
using namespace lex;

static inline std::pair<std::string, std::string> find_token_str(std::string& value, auto& tps) {
    std::cout << value << std::endl;
    for (auto& pair: tps) {	    
	for (auto& tp: pair.second) {
	    auto result = tp.match(value);
	    if(result)
		return std::make_pair(result.value(), pair.first);
	}
    }
    throw std::exception{};
 }


void lex::tokenize(std::string const& input_str,
		  std::map<std::string, std::vector<lex::TokenPattern>>& tps,
		  std::vector<Token>& tokens) { // T matchable?
	
	// kan man estimera en size på token vector baserat på strängsize?
    auto not_end_of_token = sregex::compile(R"([^\r\n\t\s])");
    Coordinate coordinate{0,0};
    
    auto functor = [&](std::string acc, char piece) -> std::string
	{
	    smatch what;
	    // kan man pipe det genom en regex machine, tecken för tecken
	    // så slipper man börja om igen, man slipper spara minne
	    // eftersom det är en composition vilket sparar minne oftast
	    if (regex_match(std::string()+=piece, what, not_end_of_token)) // regex bara
		return acc += piece;

	    try
	    {
		auto str_type = find_token_str(acc, tps);
		Token t{str_type.first, coordinate, str_type.second};
		std::cout << t.tokenType() << std::endl;
		tokens.push_back(std::move(t));
            }
	    catch (const std::exception& e)
            {
		std::cout << "syntax error, going to abort" << std::endl;
	    }
	    
	    acc.clear();
	    return acc;
	};
    
    
    std::string s = std::accumulate(input_str.begin(), input_str.end(), std::string{}, functor);
    std:: cout << s << " the string should be consumed, thus empty " << s.size() << std::endl;
	
    for (auto& token: tokens)
    {
	std::cout << "\e[44m" << token.value << "\e[0m" << std::endl;
    }
}
