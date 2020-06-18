#ifndef H_NEW
#define H_NEW
#include "Fetch.hpp"
#include <filesystem>
#include <fstream>

namespace db{
    fetch createNewDB(state &currentState, std::string dbname);

    fetch listDB(state &currentState);

    fetch useDB(state &currentState, std::string dbname);

    fetch setNewDir(state &currentState, std::string path);
}
#endif