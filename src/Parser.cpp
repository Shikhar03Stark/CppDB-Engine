#include "Parser.hpp"

std::string db::toUppercase(const std::string &str){
    std::string temp(str);
    for(char &c: temp){
        c = std::toupper(c);
    }
    return temp;
}

db::fetch db::parseInput(std::vector<std::string> &tokens, db::state &currentState){
    //Parsing includes a decision tree
    //CREATE
    //|--TABLE {TABLENAME}
    //|----[{TYPE,COLS}] invoke newTable(...)
    //|--DATABASE {DATABASENAME} invoke createDB(...)

    //SELECT
    //|--[COLS] FROM {TABLENAME}
    //|----WHERE [{CONDITIONS}]
    //|----ORDER BY [COLS] {ASC/DESC} invoke showTable(...)

    //INSERT INTO
    //|--{TABLENAME} [COLS] VALUES 
    //|----[VALUES] invoke insertTable(...)

    //UPDATE
    //|--{TABLENAME} SET
    //|--[{COL,VALUE}]
    //|--WHERE [{CONDITIONS}] invoke updateTable(...)

    //DELETE FROM
    //|--{TABLENAME} WHERE
    //|--[{CONDITIONS}] invoke dropTable(...)

    //DROP
    //|--TABLE {TABLENAME} invoke dropTable(...)
    //|--DATABASE {DATABASENAME} invoke dropDB(...)

    //SHOW DATABASES invoke listDB(...)

    //USE
    //|--{DATABASENAME} invoke useDB(...);

    db:fetch data;
    //Parsing CREATE
    if(toUppercase(tokens[0]) == "CREATE"){
        //TABLE
        if(toUppercase(tokens[1]) == "TABLE"){
            if(tokens.size() > 2){
                std::string tableName = tokens[2];
                // column details are enclosed between (, )
                //generate option data structure
                db::option ds;
                ds.tableCreation = true;
                //while we don't encounter a )
                int index = 4; //index = 3 is (
                std::vector<std::string> elements;
                try{
                    while(index != tokens.size()){
                        if(tokens[index] == "," || tokens[index] == ")"){
                            ds.createTableList.list.resize(ds.createTableList.list.size()+1);
                            ds.createTableList.list[ds.createTableList.list.size()-1].first = elements[0];
                            elements.erase(elements.begin());
                            ds.createTableList.list[ds.createTableList.list.size()-1].second = elements;
                            elements.resize(0);
                            ++index;
                            continue;
                        }
                        //fill elemets vector
                        elements.push_back(tokens[index]);
                        ++index;
                    }
                }
                catch(...){
                    throw(db::dbException(101, "Table column definition list not well defined"));
                }

                //Create Table Parse Complete
                try{
                    data = db::newTable(currentState, ds, tableName);
                    return data;
                }
                catch(db::dbException &e){
                    throw (e);
                }
                catch(...){
                    throw (db::dbException(200, "Undefined Behaviour : Parser::newTable()"));
                }
            }
            else{
                //throw error
                throw (db::dbException(105, "Name of Table not provided @token = 2"));
            }
        }
        //DATABASE
        else if(toUppercase(tokens[1]) == "DATABASE"){
            if(tokens.size() > 2){
                std::string dbname = tokens[2];
                try{
                    //create new database
                    data = db::createNewDB(currentState, dbname);
                    return data;
                }
                catch(db::dbException &e){
                    throw (e);
                }
                catch(...){
                    throw(db::dbException(200, "Undefined Behaviour : Parser::createNewDB()"));
                }
            }
            else{
                //throw error
                throw (db::dbException(105, "Name of Database not provided @token = 2") );
            }
        }
        //Syntax Error
        else{
            throw (db::dbException(101,"Invalid CREATE syntax error @token = 1") );
        }
    }
    //Create Parsing complete

    //SELECT Parsing
    else if(toUppercase(tokens[0]) == "SELECT"){
        //check for * or specified Columns
        db::option ds;
        int index = 1;
        if(tokens[1] == "*"){
            ds.hasAstericks = true;
            ++index;
        }
        //Parse selected Columns
        else{
            ds.hasCols = true;
            //accept tokens untill 'FROM' keyword is hit
            while(toUppercase(tokens[index]) != "FROM" || toUppercase(tokens[index]) != ";"){
                if(tokens[index] == ","){
                    ++index;
                    continue;
                }
                ds.colsList.list.push_back(tokens[index]);
                ++index;
            }
            if(tokens[index] == ";"){
                //bad syntax
                std::string str = "Invalid 'SELECT' Syntax @token = " + std::to_string(index);
                throw (db::dbException(101, str));
            }
        }
        //Cols Parsed
        //store tablename
        std::string tablename = tokens[++index];

        //Check for 'WHERE' clause
        if(toUppercase(tokens[index+1]) == "WHERE") {
            ++index;
            ++index;
            ds.hasWhere = true;
            
            //take next three consecutive token untill ';' or 'ORDER' is hit
            while(tokens[index] == ";" || tokens[index] == "ORDER"){
                if(tokens[index] == ";" || tokens[index] == "ORDER"){
                    ds.whereList.list.resize(ds.whereList.list.size()+1);
                    ds.whereList.list[ds.whereList.list.size()-1].first = tokens[index];
                    ++index;
                }
                if(tokens[index] == ";" || tokens[index] == "ORDER"){
                    ds.whereList.ops.push_back(tokens[index]);
                    ++index;
                }
                if(tokens[index] == ";" || tokens[index] == "ORDER"){
                    ds.whereList.list[ds.whereList.list.size()-1].second = tokens[index];
                    ++index;
                }
            }
            if(tokens[index] == ";"){
                try{
                    data = db::showTable(currentState, ds, tablename);
                    return data;
                }
                catch(db::dbException &e){
                    throw e;
                }
                catch(...){
                    throw(db::dbException(200, "Undefined Behaviour Parser::showTable()"));
                }
            }
            else
                ++index;
        }
        //Check for 'ORDER' clause
        if(toUppercase(tokens[index+1]) == "ORDER"){
            ++index;
            ds.hasSort = true;
            if(toUppercase(tokens[++index]) == "BY"){
                ++index;
                while(tokens[index] != ";" || toUppercase(tokens[index]) != "ASC" || toUppercase(tokens[index]) != "DESC"){
                    ds.sortList.list.push_back(tokens[index]);
                    ++index;
                }
                if(toUppercase(tokens[index]) == "ASC"){
                    ds.sortList.type = 'a';
                }
                else if(toUppercase(tokens[index]) == "DESC"){
                    ds.sortList.type = 'd';
                }

                try{
                    data = db::showTable(currentState, ds, tablename);
                    return data;
                }
                catch(db::dbException &e){
                    throw e;
                }
                catch(...){
                    throw(db::dbException(200, "Undefined Behaviour Parser::showTable()"));
                }
            }
            else{
                //bad syntax
                std::string str = "Invalid 'ORDER' Syntax @token = " + std::to_string(index);
                throw(db::dbException(101, str));
            }
        }
        else{
            //bad syntax
            if(tokens[++index] == ";"){
                try{
                    data = db::showTable(currentState, ds, tablename);
                    return data;
                }
                catch(db::dbException &e){
                    throw e;
                }
                catch(...){
                    throw(db::dbException(200, "Undefined Behaviour Parser::showTable()"));
                }
            }
            std::string str = "Invalid 'ORDER' Syntax @token = " + std::to_string(index);
            throw(db::dbException(101, str));
        }
    }

    else{
        throw (db::dbException(101, "Invalid Syntax @token = 0"));
    }
}