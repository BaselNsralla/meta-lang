#include <functional>
#include <vector>
#include <utility>
#include <string>
#include "token.h"
#include "pattern.h"

namespace lex {
    struct Builder {
	std::vector<lex::Pattern> patterns{};
	void token(std::string regex_str,
		   const std::function <void (lex::Token)>& lambda,
		   int group = 0);
    };
}
