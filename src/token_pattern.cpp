#include "token_pattern.h"
#include <optional>
#include <string>
#include <regex>

using namespace boost::xpressive;
using namespace lex;

std::optional<typename TokenPattern::MatchResult> TokenPattern::match(std::string& value)
{
    smatch what;
    std::cout << "======" << value << std::endl;
    if(regex_match(value, what, this->rex))
	return MatchResult(std::string(what[1]).size(), std::move(what[this->group]), logical_type);
    
    return {};
}


std::optional<typename TokenPattern::MatchResult> TokenPattern::search(std::string& value)
{
    smatch what;
    if(regex_search(value, what, this->rex))
	return MatchResult(std::string(what[1]).size(), std::move(what[this->group]), logical_type);
    
    return {};
}

