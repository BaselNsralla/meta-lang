#pragma once

#include <string>
//#include "token.h"
namespace lex{ struct Token; }



template <class T>
concept StringType     = std::is_same<typename std::decay<T>::type,
                                      std::string>::value;

template <class T>
concept TokenValueType = std::is_same<T, lex::Token>::value;

