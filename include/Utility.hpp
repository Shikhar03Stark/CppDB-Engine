#ifndef H_UTILITY
#define H_UTILITY
#include <fstream>
#include "Fetch.hpp"

namespace db{
    fetch showTable(state &currentState, option optionList);

    fetch newTable(state &currentState, option optionList);

    fetch dropTable(state &currentState, option optionList);

    fetch updateTable(state &currentState, option optionList);

    fetch insertTable(state &currentState, option optionList);
}
#endif