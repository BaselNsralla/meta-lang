#pragma once
#include <boost/xpressive/xpressive.hpp>
#include <optional>
#include <string>
#include "m_types.h"

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
    
	//private:
        sregex rex;
	int group;
	std::string logical_type;




    };
}

template<StringType T> 
lex::TokenPattern::TokenPattern(T&& str, T&& type, int grp) {
    rex   = sregex::compile(std::forward<T>(str));// moves if the generated function is of r-val
    logical_type = std::forward<T>(type);
    group = grp;
}
