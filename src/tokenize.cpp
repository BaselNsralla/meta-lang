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

static inline TokenPattern::MatchResult find_token_str(std::string& value, auto& tps) {
    for(auto& tp: tps)
    {
        auto result = tp.match(value);
        if(result)
            return result.value();
    } 

    throw std::exception{};
 }


void lex::tokenize(std::string const& input_str,
		  std::vector<lex::TokenPattern>& tps,
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
		auto match_result = find_token_str(acc, tps);
		std::cout << match_result.logical_type << std::endl;
		tokens.emplace_back(match_result.token_match, coordinate, match_result.logical_type);
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
