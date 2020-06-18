#include "IO.hpp"

db::fetch db::acceptInput(db::state &currentState){
    //start with newline
    std::cout << std::endl;
    //input should have '>>' on each line at beginning
    std::cout << ">> ";

    //accept line, if the line ends with '(', ',' then continue reading next line;
    std::string inBuffer;
    std::string line_str;
    std::getline(std::cin, line_str);
    line_str.push_back(' ');
    inBuffer += line_str;
    //untill a complete statment is genrated accept input
    //better ';' means complete statement
    while(line_str[line_str.size()-1] != ';' && line_str[line_str.size()-2] != ';'){
        std::cout << ">> ";
        std::getline(std::cin, line_str);
        line_str.push_back(' ');
        inBuffer += line_str;
    }

    line_str.~basic_string();
    //CppDB command is stored in inBuffer

    std::vector<std::string> tokens; //tokenization process
    // blankpsace, '(', ',', ')' are delimiter
    //spaces between field name are not allowed, use _ instead
    std::string token;
    for(char c: inBuffer){
        if(c == '(' || c == ',' || c==')' || c ==' ' || c == ';'){
            //split point
            if(token != "")
                tokens.push_back(token);
            //clearing token
            //pushing delimiter to tokens
            if(c == ' ' || c == ';'){
                token = "";
                continue;
            }
            token = c;
            if(token != "")
                tokens.push_back(token);
            token = "";
            continue;
        }
        
        //build token
        token.push_back(c);
    }
    //push_back left token into tokens
    if(token.size() != 0)
        tokens.push_back(token);


    //parse input
    db::fetch data;
    try{
        data = db::parseInput(tokens, currentState);
    }
    catch(db::dbException &e){
        throw e;
    }
    catch(...){
        throw(db::dbException(200, "Undefined Behaviour : IO::ParseInput()"));
    }
    return data;
}

void db::displayOutput(db::fetch data){
    //display Header
    //display Rows
    //displayInfo

    int n_cols = 0;
    int n_rows = 0;
    int cell_span = 15; //max width of cell
    std::string line; //constructing row divider, line
    for(int i =0; i<(n_cols*cell_span)+1; i++){
        if(i == 0 || i%(cell_span) == 0){
            line.push_back('+');
            continue;
        }
        line.push_back('-');
    }

    //display header if exist
    if(data.hasHeader){
        n_cols = data.header.size();
        std::cout << line << std::endl << "|";
        for(int i = 0; i<n_cols; i++){
            std::cout << std::setw(cell_span-1) << std::left << data.header[i] << "|";
        }
        std::cout << std::endl;
    }
    //header complete

    //display all rows if exist
    if(data.hasRows){
        //gather number of rows; header[0] exists as hasRows exists
        n_rows = data.rows[data.header[0]].size();
        for(int r = 0; r< n_rows; r++){
            std::cout << line << std::endl << "|";
            for(int c = 0; c<n_cols; c++){
                std::cout << std::setw(cell_span-1) << std::right << data.rows[data.header[c]][r] << "|";
            }
            std::cout << std::endl;
        }
        std::cout << line << std::endl;
    }
    //rows complete
    //add ending line

    //display info if any
    if(data.displayInfo.size() != 0){
        std::cout << std::endl << data.displayInfo << std::endl;
    }

    //Error output
    if(data.message == "err"){
        std::cout << data.displayInfo << std::endl;
    }
}