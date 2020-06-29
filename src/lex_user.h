#include <vector>
#include <map>
#include <string>
#include "pattern.h"


namespace lex {
    namespace user {
	//void tokenize_code(char const* file_name, std::vector<lex::Pattern>& token_patterns);
        void generate_patterns(char const* path,
			       std::vector<lex::Pattern>& token_patterns);

	
    }
}
