#ifndef H_DBEXCEPTION
#define H_DBEXCEPTION
#include <exception>
#include <string>
#include "Fetch.hpp"

namespace db{
    class dbException: public std::exception{
    private:
        unsigned char err; // 0 -255 error numbers
        std::string desc;
        db::fetch err_data;

    public:
        dbException() = default;
        //ctor of Exception Class
        dbException(unsigned char err, std::string desc);
        //Description of Error in fetch format
        db::fetch& what();

    };
}

#endif