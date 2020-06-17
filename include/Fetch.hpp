#ifndef H_FETCH
#define H_FETCH
#include <vector>
#include <string>
#include <map>
#include <filesystem>
namespace db{
    struct state{ //stores the current DB state for each instance of Engine
        bool usingDB;
        std::string DBname;
        char pathType; // a = absolute and r = relative
        std::filesystem::directory_entry currDir;
    };

    struct option{
        bool isWhere; //conditional selection
        bool isSort; //sorting
        bool hasRows; //conditional reading
        bool insertInto;
        struct where
        {
            std::vector<std::pair<std::string, std::string> > whereList;
        };
        struct sort{
            char type; //a = ascending, d = descending
        };
        struct row{
            std::vector<std::string> rows;
        };
        struct insert{
            std::vector<std::pair<std::string, std::vector<std::string> > > insertList;
        };
        
    };

    struct fetch{ //function return handler
        bool success;
        bool hasHeader;
        bool hasRows;
        std::string message;

        //console IO variables
        std::vector<std::string> header;
        std::map<std::string, std::vector<std::string> > rows;
        std::string displayInfo;
    };
}
#endif