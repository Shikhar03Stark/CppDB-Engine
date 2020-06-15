#ifndef H_NEW
#define H_NEW
#include "Fetch.hpp"
#include <filesystem>
#include <fstream>

namespace db{
    fetch createNewDB(std::string dbname, std::string dbpass);
    fetch listDB();
    fetch useDB();
    fetch setNewDir(std::string path);
}
#endif