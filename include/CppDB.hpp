#ifndef H_CPPDB
#define H_CPPDB
#include "Exception.hpp"
#include "DBops.hpp"
#include "Fetch.hpp"
#include "Utility.hpp"
#include "Parser.hpp"

namespace db{
    //Start Engine Thread and return to main.
    bool startDBEngine();

    //Stop Engine in main
    bool endDBEngine();
}

#endif