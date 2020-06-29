#include "lex_builder.h"
#include <string>
#include "token.h"
#include "pattern.h"
#include <functional>
void lex::Builder::token(std::string regex_str,
			 const std::function <void (lex::Token)>& lambda,
			 int group) {

    patterns.emplace_back(regex_str, std::string(), group);
    // kolla generate tokenxs
}
