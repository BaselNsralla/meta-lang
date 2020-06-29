#include "pattern.h"
#include <optional>
#include <string>
#include <regex>

using namespace boost::xpressive;
using namespace lex;

std::optional<typename Pattern::MatchResult> Pattern::match(std::string& value)
{
    smatch what;
    
    if(regex_match(value, what, this->rex))
	return MatchResult(std::string(what[0]).size(), std::move(what[this->group]), logical_type);
    
    return {};
}


std::optional<typename Pattern::MatchResult> Pattern::search(std::string& value)
{
    smatch what;
    //std::cout << "====SEARCH=====" << std::endl;
    //std::cout << "Target =>" << value <<  std::endl;
    //std::cout << "REGEX  =>" << this->rex_str << std::endl;
    

    if(regex_search(value, what, this->rex))
	return MatchResult(std::string(what[0]).size(), std::move(what[this->group]), logical_type);
    
    return {};
}

