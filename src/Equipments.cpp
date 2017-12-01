/* 
 * File:   Equipments.cpp
 * Author: Tomas Bina 
 */
#include "Equipments.h"
#include "Weapons.h"
#include <iostream>
#include <iomanip>
#include <string>
#include "sqlite/sqlite3.h"
#include "CMenu.h"

using namespace std;
/**  A constructor.
*/
Equipments::Equipments(){
    
}
//!  A normal member taking one argument.
    /**
        Set public member variable databaseE.
    */
void            Equipments::get_database(sqlite3 * database){
    databaseE = database;    
}
//!  A normal constant member.
    /**
        Print invalid input to STDIN.
    */
void            Equipments::invalid_input() const{
    cout<<"Invalid input.\n"<<endl;
    cout<<"Select category: ";
}
//!  A normal constant member.
    /**
        The method clear console.
    */
void            Equipments::clear_screen() const{
    std::cout << "\x1B[2J\x1B[H";
}
//!  A static member taking four argument.
    /**
        The method prints chosen equipment ID and Name.        
    */
int             Equipments::call_back1(void *NotUsed, int argc, char **argv,
                                       char **azColName){   
    string str = argv[0];
    int count = str.size();
    count = 5-count;
    cout<<"("<<argv[0]<<")"<<setw(count)<<""<<argv[1]<<"\n";    
    return 0;
}
//!  A constant member taking one argument and returning string.
    /**
        Method taking one string a returns same string lowercase.        
    */
string          Equipments::to_lower(string str) const{
    string name = "";
    char character =' ';
    for(unsigned int i=0;i<str.length();i++)
    {
        if(str[i] == ' ' and character == ' ')
        {

        }
        else
        name += tolower(str[i]);
        character=str[i];
    }
    size_t last_char = name.find_last_not_of(' ');
    name = name.substr(0,last_char+1  );
    return name;
}
//!  A destructor.
    /*      
        The destructor sets databaseE to NULL.
    */ 
Equipments::~Equipments(){
   databaseE = NULL;
}


