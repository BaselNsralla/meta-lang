#pragma once
#include <string>
#include <vector>
#include <map>
#include "token.h"
#include "pattern.h"



namespace lex {
    void tokenize(std::string const& input_str,
		  std::vector<lex::Pattern>& tps,
		  std::vector<Token>& tokens);
}
