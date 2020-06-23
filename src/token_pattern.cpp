#include "token_pattern.h"
#include <optional>
#include <string>

using namespace boost::xpressive;
using namespace lexer;

std::optional<std::string> TokenPattern::match(std::string& value,
					       int group)
{
    smatch what;
    if(regex_match(value, what, rex))
	return what[group];
    
    return {};
}


