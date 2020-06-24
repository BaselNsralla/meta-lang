#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <boost/xpressive/xpressive.hpp>
#include <exception>
#include <numeric>
#include "token.h"
#include <array>
#include <fstream>
#include "token_pattern.h"
#include <iterator>
#include <sstream>
#include <map>
#include "coordinate.h"
#include <utility>

using namespace boost::xpressive;

namespace lex {
    /*
    void generate_token(std::string& value) {
	//regex matcha mot token rules
	 sregex rex = sregex::compile( "(\\w+)\\+(\\w+)!" );
	 smatch what;
	 std::cout << "Generating token for: " << value << ";" << std::endl;
	 if( regex_match( value, what, rex ) )
	 {
	     // skapa token som Token och returnera
	     std::cout << what[0] << '\n'; // whole match
	     std::cout << what[1] << '\n'; // first capture
	     std::cout << what[2] << '\n'; // second capture
	 } else {
	     throw std::exception{};
	 }
    }
    */

    std::pair<std::string, std::string> find_token_str(std::string& value, auto& tps) {
	std::cout << value << std::endl;
	for (auto& pair: tps) {	    
	    for (auto& tp: pair.second) {
		auto result = tp.match(value);
		//std::cout << tp.rex.regex_id() << "<==" << std::endl;
		if(result)
		    return std::make_pair(result.value(), pair.first);
	    }
	}
	throw std::exception{};
    }
    
    void tokenize(std::string const& input_str,
		  std::map<std::string, std::vector<lex::TokenPattern>>& tps,
		  std::vector<Token>& tokens) { // T matchable?
	// kan man estimera en size på token vector baserat på strängsize?
	auto not_end_of_token = sregex::compile(R"([^\r\n;\s])");
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
		} catch (const std::exception& e)
		{
		    std::cout << "syntax error, going to abort" << std::endl;
		}

		acc.clear();
		return acc;
	    };
	
	
	std::string s = std::accumulate(input_str.begin(), input_str.end(), std::string{}, functor);
	std:: cout << s << "S should be consumed thus  empty " << s.size() << std::endl;
    }
}





/*
TokenType Token::operator()() {
    return this->tt;
}
*/


template <class T>
concept TokenValueType = std::is_same<T, lex::Token>::value;


void parse(std::string&& a) {
    // vad som görs i tokenize
    /*
    std::cout << a << std::endl;
    Token t1{std::move(a), 1, 1, TokenType::a};
    Token t2{"asd",        2, 1, TokenType::b}; // här kan du inte mova igen
    switch(t1.tokenType()) {
        case TokenType::b:
	    std::cout << "B" << std::endl;
        break;
        case TokenType::a:
            std::cout << "A" << std::endl;
	break;
    }
    std::cout << (t1==t2) << std::endl;
    */
    //lexer::tokenize(a);
}



namespace user {
    inline bool is_header(std::string& line)
    {
	return line[0] == '#';
    }

    inline void insert_or_create(auto& token_map, std::string& key, lex::TokenPattern& val)
    {
	if(token_map.contains(key))
	{
	    token_map[key].push_back(val);
	} else
	{
	    token_map.emplace(key, std::vector<lex::TokenPattern>{val});
	}
    }
    
    void read_patterns(char* path, std::map<std::string, std::vector<lex::TokenPattern>>& token_patterns)
    {
	std::ifstream fs(path);
	std::string line{};
	std::string logical_type{};

	auto eval_header = [&]() -> bool
	{
	    if(is_header(line))
	    {
		logical_type = std::string(line.begin()+1, line.end());
		return true;
	    } else {
		return false;    
	    }
	};

	std::getline(fs, line);
	if(!eval_header()) throw std::exception{};
	
	for(;std::getline(fs, line);)
	{
	    if(eval_header()) continue;
	    
	    
	    std::istringstream iss(line); // vi konstruerar en ny hela tiden wtf
	                                  // då måste den clear:as i slutet också
	    std::string name;
	    std::string arrow;
	    std::string regex;
	    int group{};

	 
	    iss >> name;
	    if(iss.fail()) continue; // tom rad
	    
	    iss >> arrow;
	    iss >> regex;

	    
	    if (iss.fail())
	    {
		std::cout << "\033[1;31mBad format at -> \033[0m" << line << std::endl;
		continue;
	    }

	    
	    iss >> group;
	    std::cout << "-> " << name << ' ' << regex << ' ' << group << '\n';
	  
	    auto pattern = lex::TokenPattern(regex, group);
	    
	    
	    user::insert_or_create(token_patterns, logical_type, pattern);
	}
    }
}


int main(int argc, char** argv ) {
    if(argc < 2) {
	std::cout << "You have to provide a pattern file" << std::endl;
	return 1;
    }
    /*
      std::vector<lexer::TokenPattern>&& vec = std::move(user::read_patterns(argv[1]));
      read_patterns retunerade by value
    */
    std::map<std::string, std::vector<lex::TokenPattern>> token_patterns{};
    user::read_patterns(argv[1], token_patterns); // <-- nu här

    std::vector<lex::Token> tokens{};
    lex::tokenize("if a;", token_patterns, tokens);

    
    
    //parse("abc+aaa! ");
    // P a = std::move(hej());
    //std::cout << hej().k << "\n";    
}



// META LANG
/***


struct P {
    P(char const* a) {
	std::cout << "constructed" << std::endl;
	k = 10;
    }
    int k;
};

P hej() {
    return "sad";
}

std::string s = "split on    whitespace   ";
std::istringstream iss(s);
std::vector<std::string> result{
    std::istream_iterator<std::string>(iss), {}
};

*/



