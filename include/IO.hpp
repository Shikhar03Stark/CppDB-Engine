#ifndef H_IO
#define H_IO
#include <iostream>
#include <iomanip>
#include "Parser.hpp"
#include "Fetch.hpp"
#include "Exception.hpp"
namespace db{
    //Accept Input from Console and tokenize
    db::fetch acceptInput(db::state currentState);

    //Present Output to Console
    void displayOutput(db::fetch);
}

#endif