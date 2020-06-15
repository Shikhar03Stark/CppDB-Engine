#ifndef H_PARSER
#define H_PARSER
#include "DBops.hpp"
#include "Utility.hpp"
#include "Parser.hpp"
#include "Fetch.hpp"

namespace db{
    fetch parseInput(std::vector<std::string> token);
}
#endif