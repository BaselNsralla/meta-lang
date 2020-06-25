#pragma once
#include <string>
#include <vector>
#include <map>
#include "token.h"
#include "token_pattern.h"



namespace lex {
    void tokenize(std::string const& input_str,
		  std::vector<lex::TokenPattern>& tps,
		  std::vector<Token>& tokens);
}
