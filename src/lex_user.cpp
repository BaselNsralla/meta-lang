#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "token_pattern.h"
#include "tokenize.h"
#include "lex_user.h"
#include <vector>
#include <string>
#include <fstream>


using namespace lex::user;


static inline bool is_header(std::string& line)
{
    return line[0] == '#';
}

static inline void insert_or_create(auto& token_map, std::string& key, lex::TokenPattern& val)
{
    if(token_map.contains(key))
    {
	token_map[key].push_back(val);
    } else
    {
	token_map.emplace(key, std::vector<lex::TokenPattern>{val});
    }
}

void lex::user::tokenize_code(char const* file_name,
		              std::vector<lex::TokenPattern>& token_patterns)
{ // det bästa är att göra det multitrådat här
    std::ifstream fs(file_name);
    std::string line{};
    std::vector<lex::Token> tokens{};
    
    for(;std::getline(fs, line);)
    {
	std::cout << "THE LINE IS " << line << std::endl;
	lex::tokenize(line+='\n', token_patterns, tokens);
    }
}


void lex::user::generate_patterns(char const* path, std::vector<lex::TokenPattern>& token_patterns)
{
    std::ifstream fs(path);
    std::string line{};
    std::string logical_type{};

    auto eval_header = [&]() -> bool
    {
	if(is_header(line))
	{
	    logical_type = std::string(line.begin()+1, line.end());
	    return true;
	} else
	{
	    return false;    
	}
    };

    std::getline(fs, line);
    if(!eval_header()) throw std::exception{};
	
    for(;std::getline(fs, line);)
    {
	if(eval_header()) continue;
	    
	    
	std::istringstream iss(line); // vi konstruerar en ny hela tiden wtf
	// då måste den clear:as i slutet också
	std::string name;
	std::string arrow;
	std::string regex;
	int group{};
	
	
	iss >> name;
	if(iss.fail()) continue; // tom rad
	
	iss >> arrow;
	iss >> regex;
	    
	    
	if (iss.fail())
	{
	    std::cout << "\033[1;31mBad format at -> \033[0m" << line << std::endl;
	    continue;
	}

	    
	iss >> group;
	std::cout << "-> " << name << ' ' << regex << ' ' << group << '\n';
	  
	//auto pattern = lex::TokenPattern(regex, logical_type, group);
	token_patterns.emplace_back(regex, logical_type, group);
	
	//insert_or_create(token_patterns, logical_type, pattern);
    }
}
