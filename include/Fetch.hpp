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
        bool isWhere = false; //conditional selection
        bool isSort = false; //sorting
        bool hasRows = false; //conditional reading
        bool insertInto = false;
        bool tableCreation = false;
        struct where
        {
            std::vector<std::pair<std::string, std::string> > list;
        } whereList;
        struct sort{
            char type; //a = ascending, d = descending
        };
        struct rows{
            std::vector<std::string> list;
        } rowsList;
        struct insert{
            std::vector<std::pair<std::string, std::vector<std::string> > > list;
        } insertList;
        struct tableCreate{
            std::vector<std::pair<std::string, std::vector<std::string> > > list;
        } createTableList;
        
    };

    struct fetch{ //function return handler
        bool success = false;
        bool hasHeader = false;
        bool hasRows = false;
        std::string message;

        //console IO variables
        std::vector<std::string> header;
        std::map<std::string, std::vector<std::string> > rows;
        std::string displayInfo;
    };
}
#endif