#ifndef H_IO
#define H_IO
#include "Parser.hpp"
#include "Fetch.hpp"
#include "Exception.hpp"
namespace db{
    //Accept Input from Console and tokenize
    fetch acceptInput();

    //Present Output to Console
    void displayOutput(fetch);
}

#endif