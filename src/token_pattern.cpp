#include "token_pattern.h"
#include <optional>
#include <string>

using namespace boost::xpressive;
using namespace lex;

std::optional<std::string> TokenPattern::match(std::string& value)
{
    smatch what;
    if(regex_match(value, what, this->rex))
	return what[this->group];
    
    return {};
}


