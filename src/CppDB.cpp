#include "CppDB.hpp"

bool db::startDBEngine(){
    //initialize State structure
    db::state currentState;
    currentState.DBname = "null";
    currentState.pathType = 'a';
    currentState.usingDB = false;

    //Start Event loop thread
    return true;
}