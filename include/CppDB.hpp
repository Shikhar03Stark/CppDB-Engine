#ifndef H_CPPDB
#define H_CPPDB
#include "Exception.hpp"
#include "DBops.hpp"
#include "Fetch.hpp"
#include "Utility.hpp"
#include "Parser.hpp"
#include "IO.hpp"
#include <thread>
namespace db{
    //Start Database Engine // invokes I/O event loop
    bool startDBEngine();

    //Stop Engine
    bool endDBEngine();
}

#endif