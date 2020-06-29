#pragma once
#include <boost/xpressive/xpressive.hpp>
#include <optional>
#include <string>
#include "m_types.h"
#include <iostream>
#include <regex>
using namespace boost::xpressive;

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
    class TokenPattern;
    class TokenPattern {
    public:
	struct MatchResult {
        MatchResult(size_t a, std::string&& b , std::string c):
	        match_size{a}, token_match{std::move(b)}, logical_type{c} {}
	size_t match_size;
	std::string token_match;
	std::string logical_type;
    };


    public:
	template<StringType T> 
	TokenPattern(T&&, T&&, int);
	
	std::optional<typename lex::TokenPattern::MatchResult> match(std::string& value);
	std::optional<typename TokenPattern::MatchResult>      search(std::string& value);
	    
	//private:
        sregex rex;
	//std::regex rex;
	int group;
	std::string logical_type;
	std::string rex_str;



    };
}

template<StringType T> 
lex::TokenPattern::TokenPattern(T&& str, T&& type, int grp) {
    //std::cout << temp << " är du verkligen som du är " << std::endl;
    //rex   = std::regex(temp, std::regex_constants::ECMAScript | std::regex_constants::icase);
    std::string regex_str = "^"+str;
    rex_str = regex_str;
    rex   = sregex::compile(regex_str);//std::forward<T>(str)); //std::forward moves if the generated function is of r-val
    group = grp; //+ 1;
}
