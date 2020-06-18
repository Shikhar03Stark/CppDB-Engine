#ifndef H_PARSER
#define H_PARSER
#include "DBops.hpp"
#include "Utility.hpp"
#include "Fetch.hpp"
#include "Exception.hpp"

namespace db{
    db::fetch parseInput(std::vector<std::string> &tokens, db::state &currentState);
    std::string& toUppercase(std::string &str);
}
#endif