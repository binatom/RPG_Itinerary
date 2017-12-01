/* 
 * File:   main.cpp
 * Author: Tomas Bina
  */

#include <iostream>
#include "Equipments.h"
#include "Weapons.h"
#include "CMenu.h"
#include "sqlite/sqlite3.h"

using namespace std;


int main(int argc, char** argv) {    
    
    CMenu Menu;
    if(!Menu.Connection())
    {
        cout<<"Can not open database."<<endl;
        return -1;
    }    
    Menu.Menu1();
    return 0;    
}
