/* 
 * File:   CMenu.h
 * Author: Tomas Bina 
 */

#ifndef CMENU_H
#define	CMENU_H
#include "sqlite/sqlite3.h"
#include <string>


class CMenu {
public:
                        CMenu();
    bool                Connection();    
    void                Menu1();
    void                CleanScreen()const;
    void                Menu2();
                        ~CMenu();
    
    friend class Equipments;
    sqlite3 * database;
       
private:
    std::string choice;
    

};

#endif	/* CMENU_H */

