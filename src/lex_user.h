#include <vector>
#include <map>
#include <string>
#include "token_pattern.h"


namespace lex {
    namespace user {
	void tokenize_code(char const* file_name,
			   std::map<std::string, std::vector<lex::TokenPattern>>& token_patterns);
        void generate_patterns(char const* path,
			       std::map<std::string, std::vector<lex::TokenPattern>>& token_patterns);
    }
}
