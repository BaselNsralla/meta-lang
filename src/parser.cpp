#include <regex>
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
#include "lex_user.h"
#include "tokenize.h"

using namespace boost::xpressive;




/*
TokenType Token::operator()() {
    return this->tt;
}
*/



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






int main(int argc, char** argv ) {
    if(argc < 2)
    {
	std::cout << "You have to provide a pattern file" << std::endl;
	return 1;
    }
    
    /*
      std::vector<lexer::TokenPattern>&& vec = std::move(user::read_patterns(argv[1]));
      read_patterns retunerade by value
    */
    std::vector<lex::TokenPattern> token_patterns{};
    lex::user::generate_patterns(argv[1], token_patterns); // <-- nu här

    std::vector<lex::Token> tokens{};

    if(argc > 2)
    {
	lex::user::tokenize_code(argv[2], token_patterns);
    }

    //    lex::tokenize("if a;", token_patterns, tokens);



    

    
    std::string s="^what";
    std::string target = "what=";
    auto a = lex::TokenPattern(s, s, -1);
    auto b = a.search(target); 
    if(b){
	std::cout << "MATcHED " << b.value().token_match  << "SD" << std::endl;
    } else {
	std::cout << "No match" << std::endl;
    }
    
    
    
    /*
    std::string s="if";
    std::string front = R"(^()";
    std::string back  = R"()(?![a-zA-Z0-9]))";
    
    std::string regex = front + s + back;//"^(while)(?![a-zA-Z0-9])"; 
    std::cout << regex << std::endl;
    smatch what;
    auto rex = sregex::compile(std::move(regex));
    
    if(regex_search(target, what, rex)) {
	std::cout << what[0] << std::endl;
    }
    else {
	std::cout << "#ShIET" << std::endl;
    }
    */
    
    /*
    std::regex self_regex(R"((while)(?![a-zA-Z1-9]))",
            std::regex_constants::ECMAScript | std::regex_constants::icase);
    std::string target = "while*";
     std::smatch base_match;
     if (std::regex_search(target, base_match, self_regex)) {
	 std::cout << base_match[1] << std::endl;
     } else {
	 std::cout << "SHEIT" << std::endl;
     }

*/
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



