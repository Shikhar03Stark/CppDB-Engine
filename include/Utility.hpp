#ifndef H_UTILITY
#define H_UTILITY
#include <fstream>
#include "Fetch.hpp"

namespace db{
    fetch showTable(state &currentState, option optionList, std::string tablename);

    fetch newTable(state &currentState, option optionList, std::string tablename);

    fetch dropTable(state &currentState, option optionList, std::string tablename);

    fetch updateTable(state &currentState, option optionList, std::string tablename);

    fetch insertTable(state &currentState, option optionList, std::string tablename);
}
#endif