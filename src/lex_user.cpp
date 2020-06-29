#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "pattern.h"
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

static inline void insert_or_create(auto& token_map, std::string& key, lex::Pattern& val)
{
    if(token_map.contains(key))
    {
	token_map[key].push_back(val);
    } else
    {
	token_map.emplace(key, std::vector<lex::Pattern>{val});
    }
}



void lex::user::generate_patterns(char const* path, std::vector<lex::Pattern>& patterns)
{
    std::ifstream fs(path);
    std::string line{};
    std::string logical_type{};

    auto eval_header = [&]() -> bool {
	if(is_header(line)) {
	    logical_type = std::string(line.begin()+1, line.end());
	    return true;
	}
	return false;    
    };

    std::getline(fs, line);
    if(!eval_header()) throw std::exception{};
	
    for(;std::getline(fs, line);) {
	if(eval_header()) continue;
 
	std::istringstream iss(line); // vi konstruerar en ny hela tiden wtf,
	                              // då måste den clear:as i slutet också, om vi ska ha en enda för loopen
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
	  
	patterns.emplace_back(regex, logical_type, group);	
    }
}
