#include "Exception.hpp"

db::dbException::dbException(unsigned char err, std::string desc){
    this->err = err;
    this->desc = desc;
    err_data.message = "<ERROR> ";
    err_data.message += "\'"+std::to_string(err)+"\': ";
    err_data.message += desc;
}

db::fetch& db::dbException::what() {

    return (err_data);
}