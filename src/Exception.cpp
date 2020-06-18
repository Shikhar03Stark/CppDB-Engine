#include "Exception.hpp"

db::dbException::dbException(unsigned char err, std::string desc){
    this->err = err;
    this->desc = desc;
    err_data.displayInfo = "<ERROR> ";
    err_data.displayInfo += "\'"+std::to_string(err)+"\': ";
    err_data.displayInfo += desc;
    err_data.message = "err";
    err_data.hasHeader = false;
    err_data.hasRows = false;
    err_data.success = false;
}

db::fetch& db::dbException::what() {

    return (err_data);
}