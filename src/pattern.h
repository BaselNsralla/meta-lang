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
    class Pattern;
    class Pattern {
    public:
	struct MatchResult {
        MatchResult(size_t a, std::string&& b , std::string c):
	        match_size{a}, token_match{std::move(b)}, logical_type{c} {}
	size_t match_size;
	std::string token_match;
	std::string logical_type;
    };


    public:
	template<StringType T, StringType C> 
	Pattern(T&&, C&&, int);
	
	std::optional<typename lex::Pattern::MatchResult> match(std::string& value);
	std::optional<typename Pattern::MatchResult>      search(std::string& value);
	    
	//private:
        sregex rex;
	//std::regex rex;
	int group;
	std::string logical_type;
	std::string rex_str;



    };
}

template<StringType T, StringType C> 
lex::Pattern::Pattern(T&& str, C&& type, int grp) {
    //std::cout << temp << " är du verkligen som du är " << std::endl;
    //rex   = std::regex(temp, std::regex_constants::ECMAScript | std::regex_constants::icase);
    std::string regex_str{std::forward<T>(str)};
    rex_str               = "^"+regex_str;
    rex                   = sregex::compile(regex_str);//std::forward<T>(str));
                                                       //std::forward moves if the generated function is of r-val
    logical_type = std::forward<C>(type);
    group = grp; //+ 1;
}
