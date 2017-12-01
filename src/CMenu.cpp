/* 
 * File:   CMenu.cpp
 * Author: Tomas Bina 
 */

#include "CMenu.h"
#include "sqlite/sqlite3.h"
#include "Equipments.h"
#include "Weapons.h"
#include "Spells.h"
#include <iomanip>
#include <string>
#include <iostream>

using namespace std;

 /**  A constructor.
  */
CMenu::CMenu() {
}
//!  A normal member returning bool.
    /**
        The method connects database.If connection is set successfully returns
        true else false.
    */
bool        CMenu::Connection(){
    
    int rc = -5;
    rc = sqlite3_open_v2("./examples/data.sqlite", &database,SQLITE_OPEN_READWRITE, NULL);
    if(rc==0){
        return true;        
    }
    else 
        return false;
    
}
//!  A normal member.
    /**
        Method accepts and check a string from STDIN. Other members methods are 
        called by the string.
    */
void        CMenu::Menu1(){
    CleanScreen();
    cout<<"CATEGORIES"<<"\n\n"
    <<"(1"<<left<<setfill(' ')<<setw(5)<<")"<<"Weapons"<<"\n"
    <<"(2"<<left<<setfill(' ')<<setw(5)<<")"<<"Spells"<<"\n"    
    <<"(E"<<left<<setfill(' ')<<setw(5)<<")"<<"EXIT"<<"\n\n"    
    <<"\n"<<"Select category: ";
    choice = "";    
    cin>>choice; 
    while(1){
        if(choice == "E" or choice == "e")
            choice = "e";         
        if(choice !="1" and choice !="2" and choice != "e"){
            cout<<"Invalid input.\n"<<endl;
            cout<<"Select category: ";
            cin>>choice;            
            continue;
        }
        else{
            break;           
        }  
    }
    if(choice == "e"){        
        CleanScreen();
        cout<<"Good bye!"<<endl;        
    }
    else
        CleanScreen();
        Menu2();  
}
//!  A normal member.
    /**
        Method clears console.
    */
void        CMenu::CleanScreen()const{
    
    std::cout << "\x1B[2J\x1B[H";   
}
//!  A normal member.
    /**
        Method moves to other friend class by the user choice.
    */
void        CMenu::Menu2(){
    if(choice=="1")
    {
        Weapons WP;
        WP.get_database(database);
        while(1){
            string choice = WP.print_categories();
            if(choice == "b")
            {break;}
        }
        Menu1();
    }
    if(choice=="2")
    {
        Spells SP;
        SP.get_database(database);
        while(1){
            string choice = SP.print_categories();
            if(choice == "b")
            {break;}
        }
        Menu1();
    }    
}
//!  A destructor.
    /**      
        The destructor closes database connection.
    */ 
            CMenu::~CMenu(){
    sqlite3_close(database);        
}

