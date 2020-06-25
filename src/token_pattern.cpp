#include "token_pattern.h"
#include <optional>
#include <string>

using namespace boost::xpressive;
using namespace lex;

std::optional<typename TokenPattern::MatchResult> TokenPattern::match(std::string& value)
{
    smatch what;
    if(regex_match(value, what, this->rex))
	return MatchResult(std::string(what[0]).size(), std::move(what[this->group]), logical_type);
    
    return {};
}


