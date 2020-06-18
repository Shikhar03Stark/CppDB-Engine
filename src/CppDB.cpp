#include "CppDB.hpp"

bool db::startDBEngine(){
    //initialize State structure
    db::state currentState;
    currentState.DBname = "null";
    currentState.pathType = 'a';
    currentState.usingDB = false;
    currentState.currDir = std::filesystem::directory_entry();

    //Start I/O Event loop thread
    bool continueLoop = true;
    while(continueLoop){
        try{
            std::future<db::fetch> ftr = std::async(std::launch::async, &db::acceptInput, std::ref(currentState));
            db::fetch data = ftr.get();
            db::displayOutput(data);
            if(data.message == "exit"){
                continueLoop = false;
            }
        }
        catch(db::dbException &db_e){
            //Exception Caught
            db::fetch err_data = db_e.what();
            db::displayOutput(err_data);
        }
    }
    return true;
}