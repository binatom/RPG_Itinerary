/* 
 * File:   Spells.cpp
 * Author: Tomas Bina 
 */

#include "Equipments.h"
#include "Spells.h"
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include "sqlite/sqlite3.h"

    /**  A constructor.
    */
    Spells::Spells() {
    }
    //!  A normal member taking one argument.
    /*
        Method set private member variable category.
    */
    void            Spells::set_choice(string choice){
        category = choice;
    }
    //!  A normal member taking one argument.
    /**
        The method sets private member variable action.
    */
    void            Spells::set_action(string Action)
    {
        action = Action;
    }
    //!  A static member taking four argument.
    /**
        The method stores number of row in database using void *count.
    */
    int             Spells::call_back_row(void *count, int argc,char **argv,
                                            char **azColName){
        int *c = (int*)count;
        *c = atoi(argv[0]);
        return 0;
    }
    //  A static member taking four argument.
    /*
        The method prints chosen spell including parameters.        
    */
    int             Spells::call_back_spells(void* NotUsed, int argc, char** argv,
                                            char** azColName){
        string spells_type(argv[2]);
        if(spells_type=="1"){
            cout<<"ID:"<<setw(12)<<""<<"("<<argv[0]<<")"<<"\n"
            <<"Name:"<<setw(10)<<""<<argv[1]<<"\n"
            <<"ManaCost:"<<setw(6)<<""<<argv[3]<<"\n"
            <<"Attack:"<<setw(8)<<""<<argv[4]<<"\n"
            <<"Range:"<<setw(9)<<""<<argv[5]<<"\n";          
        }
        if(spells_type=="2"){
            cout<<"ID:"<<setw(12)<<""<<"("<<argv[0]<<")"<<"\n"
            <<"Name:"<<setw(10)<<""<<argv[1]<<"\n"
            <<"ManaCost:"<<setw(6)<<""<<argv[3]<<"\n"
            <<"Defense:"<<setw(7)<<""<<argv[6]<<"\n"
            <<"Range:"<<setw(9)<<""<<argv[5]<<"\n";              
        }
        return 0;
    }
    //!  A normal member returning string.
    /**
        The method executes sql command and checks the correct execution.
        Method uses the sqlite3_exec() interface, which is a convenience wrapper
        around sqlite3_prepare_v2(), sqlite3_step(), and sqlite3_finalize().
        Third argument of sqlite3_exec() is call_back1 function, which is define
        in abstract class Equipment. The call_back1 function is printing spells 
        categories.
    */
    string Spells::print_categories() {
        cout<<"SPELLS TYPES"<<"\n\n";
        string choice = "";
        const char * sql =  "SELECT ID,Name from Categories WHERE type ="
                            " 'spells' ORDER BY ID";        
        int check = sqlite3_exec(databaseE, sql, call_back1, NULL,NULL);
        if( check != SQLITE_OK ){
            cout<<"Can not open database."<<endl;            
        }
        cout<<"(B"<<left<<setfill(' ')<<setw(5)<<")"<<"Return back"
            <<"\n\n"<<"Select category: ";        
        while(1){           
            cin>>choice;
            string tmp = to_lower(choice);
            if(choice== "1" or choice== "2" or tmp== "b"){
                
                break;            
            }
            else{
                invalid_input();
                continue;
            }
        }
        string temp = to_lower(choice);
        if(temp=="b"){           
            return temp;
        }
        else{
            clear_screen();
            set_choice(choice);
            print_equipments();
            return temp;
        }
    }
    //!  A pure virtual member.
    /**
        The method executes sql command and checks the correct execution.
        Method uses the sqlite3_exec() where the third argument is call_back1
        function, which is define in abstract class Equipment. The call_back1 
        function is printing Name and ID of weapons row by row.
        After sql execution a string from STDIN is accepted. The string is 
        not check here. 
    */
    void            Spells::print_equipments (){
        string choice = "";
        cout<<"SELECTED SPELLS"<<"\n\n";
        string sql = "";
        sql.append("SELECT ID,Name from spells WHERE IDC = ").append(category)
        .append(" ORDER BY lower(Name)");
        int check = sqlite3_exec(databaseE, sql.c_str(), call_back1, NULL,NULL);
        if( check != SQLITE_OK ){
            cout<<"Can not open database."<<endl;            
        }
        cout<<"\n"<<"ACTIONS"<<"\n\n"
            <<"(A"<<left<<setfill(' ')<<setw(5)<<")"<<"Add spell"<<"\n"
            <<"(C"<<left<<setfill(' ')<<setw(5)<<")"<<"Compare spells"<<"\n"    
            <<"(D"<<left<<setfill(' ')<<setw(5)<<")"<<"Delete spell"<<"\n"
            <<"(I"<<left<<setfill(' ')<<setw(5)<<")"<<"Import CSV file"<<"\n"
            <<"(E"<<left<<setfill(' ')<<setw(5)<<")"<<"Export CSV file"<<"\n"    
            <<"(B"<<left<<setfill(' ')<<setw(5)<<")"<<"Return back"<<"\n"
            <<"\n\n"<<"SELECT SPELL NUMBER TO SHOW IT OR SELECT ACTION: "; 
        cin>>choice;
        select_action(to_lower(choice));  
    }
    //!  A pure virtual member taking one argument.
    /**
        The method calls other members method by the taken string. 
    */   
    void            Spells::select_action(string choice)
    {
        if(choice == "a"){
            set_action(choice);
            add_equipment();
        }
        if(choice == "d"){   
            set_action(choice);
            delete_equipment();
            print_equipments(); 
        }
        if(choice == "c"){
            compare_equipment();        
        }
        if(choice == "i"){
            csv_import();
	    clear_screen();
            print_equipments ();                 
        }
        if(choice =="e"){
            csv_export();
        }
        if(choice == "b"){
            clear_screen();          
        }
        if(choice !="b" and choice != "d" and choice !="a" and 
           choice !="c" and choice !="i" and choice != "e"){
            clear_screen();
            set_action(choice);
            show_equipment(choice);
        }    
    }    
    //!  A pure virtual member taking one argument.
    /**
        The method controls validity of taking argument. 
        If the argument is okay, print_equipments()is called and chosen spell 
        including properties is printed.  
    */    
    void            Spells::show_equipment(string choice){
        if(check_id(choice)<=0){
            cout<<"Invalid input. Try again."<<"\n\n";
            cout<<"Press any key to continue.";               
            cin.clear();
            cin.ignore();
            cin.get();
            if(choice != "b"){
            clear_screen();
            print_equipments();}
        }
        else
        {
            cout<<"CHOOSEN SPELL"<<"\n\n";
            print_equipment(choice);
            cout<<"Press any key to continue.";               
            cin.clear();
            cin.ignore();
            cin.get();
            clear_screen();
            print_equipments();
        }
    }
    //!  A pure virtual member.
    /**      
        The method accepts a string from STDIN. The string is checked here.
        If input is valid, sql command is executed and spell is deleted from 
        the database. Correct execution of sql command is also checked here. 
    */ 
    void            Spells::delete_equipment(){
        string choice = "";
        cout<<"Select spell ID: ";
        cin>>choice;      
            if(check_id(choice) <= 0){
                cout<<"\n"<<"Invalid input. Try again."<<endl;                
            }
            else{
                
                string sql ="";
                sql.append("DELETE from spells WHERE ID = ").append(choice);        
                int check = sqlite3_exec(databaseE, sql.c_str(), NULL, NULL,NULL);        
                if( check != SQLITE_OK ){
                    cout<<"Can not open database."<<endl;            
                }
                else
                    cout<<"Weapon was deleted successfully."<<"\n";
            }
        cout<<"Press any key to continue.";               
        cin.clear();
        cin.ignore();
        cin.get();
        clear_screen();
        print_equipments();   
    }
    //!  A pure virtual member taking one argument and returns bool value.
    /**      
        The method taking sql command as a string and executes it. 
        If execution is done correctly, weapon is added to the database and true
        is returned else false is returned.
    */    
    bool            Spells::insert_equipment(string sql){
        sqlite3_stmt *statement;        
        int check = sqlite3_prepare(databaseE,sql.c_str() ,-1,&statement,0);
        bool check_bool = true;
        if(check != SQLITE_OK ){
            cout<<"Can not open database."<<endl;
            check = false;
        }
        sqlite3_step(statement);              
        sqlite3_finalize(statement);
        return check_bool;   
    }
    //!  A pure virtual member taking one argument and returning integer.
    /**      
        The method taking weapon ID (string) and executes sql command. If 
        execution is done correctly, method returns number of row with same name
        in database, else returns -1.
    */   
    int             Spells::check_id(string choice) const
    {    
        int count = -1;
        string sql_check;
	int temp = atoi(choice.c_str());
        if (temp == 0)
            return -1;        
        sql_check.append("SELECT COUNT (*) from spells WHERE ID = ").
                        append(choice).append(" and IDC = ").append(category);
        int check = sqlite3_exec(databaseE, sql_check.c_str(), call_back_row, 
                                 &count, NULL);
        if( check != SQLITE_OK )
        {
            cout<<"Can not open database."<<endl;
	    return -1;	                
        }            
            return count;        
    }
    //!  A pure virtual member.
    /**      
        The method compares two spells by the chosen parameter.
        Spell id and comparison parameter are accepted from STDIN and are 
        checked. If so okay, better spell is printed.        
    */ 
    void            Spells::compare_equipment(){
        string spell_id_1;
        string spell_id_2;
        string temp = "";
        while(1)
        {
            cout<<"Select ID of two spells to compare."<<"\n";
            cout<<"Spell 1: ";       
            cin>>spell_id_1;
            set_action(temp);
            while(1){
                if(check_id(spell_id_1) <= 0){
                    cout<<"\n"<<"Invalid input. Try again or select (B) to "
                        "return back."<<"\n\n"<<"Spell 1: ";
                    cin>>spell_id_1;
                    string temp = to_lower(spell_id_1);
                    set_action(temp);
                    if(temp == "b"){
                        cout<<"dostanu se sem"<<endl;
                        clear_screen();                        
                        break;                   
                    }                
                }
                else{
                    cout<<"\n";
                    break;
                }
            }           
            if(action != "b"){
                cout<<"Spell 2: ";       
                cin>>spell_id_2;
                while(1){
                    if(check_id(spell_id_2) <= 0){
                        cout<<"\n"<<"Invalid input. Try again or select (B) to"
                            "return back."<<"\n\n"<<"Spell 2: ";
                        cin>>spell_id_2;
                        string temp = to_lower(spell_id_2);
                        set_action(temp);
                        if(temp == "b"){                          
                            clear_screen();
                            break;                  
                        }                
                    }
                    else{
                        cout<<"\n";
                        break;
                    }                    
                }
                if(action == "b")
                {break;}
            }
            else
                break;
            int temp1 = stoi(spell_id_1);
            int temp2 = stoi(spell_id_2);
            if(temp1 == temp2){
                cout<<"You choose same spells. Try again."<<"\n\n"<<endl;
                continue;                
            }
            else
                break;            
        }
        if (action != "b"){
            clear_screen();
            cout<<"CHOOSEN SPELLS"<<"\n\n"
                <<"SPELL 1:" <<"\n\n";
            print_equipment(spell_id_1);
            vector<string>spell_1 = get_row(spell_id_1);
            cout<<"\n"<<"SPELL 2:" <<"\n\n";
            print_equipment(spell_id_2);
            vector<string>spell_2 = get_row(spell_id_2);
            unsigned int choice = choice_to_compare();
            int temp_spe1;
            int temp_spe2;
            if(category == "2")
            {
                swap(spell_1[11],spell_1[12]);
                swap(spell_2[11],spell_2[12]);
            }
            clear_screen();
            switch(choice) 
            {                
                case 1 : 
                    temp_spe1 = stoi(spell_1[10]);
                    temp_spe2 = stoi(spell_2[10]);                
                    if(temp_spe1<temp_spe2)
                    {                        
                        cout<<"CHEAPER SPELL."<<"\n\n";
                        print_equipment(spell_id_1);                    
                    }
                    if(temp_spe1>temp_spe2)
                    {                       
                        cout<<"CHEAPER SPELL."<<"\n\n";
                        print_equipment(spell_id_2);                    
                    }    
                    if(temp_spe1==temp_spe2)
                        cout<<"BOTH SPELLS ARE JUST SAME GOOD."<<"\n\n";
                    break;
                case 2 : 
                    temp_spe1 = stoi(spell_1[11]);
                    temp_spe2 = stoi(spell_2[11]);                
                    if(temp_spe1>temp_spe2)
                    {
                        if(category == "2")
                            cout<<"SPELL WITH BETTER DEFENSE."<<"\n\n";
                        else
                            cout<<"SPELL WITH BETTER ATTACK."<<"\n\n";
                        print_equipment(spell_id_1);                    
                    }
                    if(temp_spe1<temp_spe2)
                    {
                        if(category == "1")
                            cout<<"SPELL WITH BETTER ATTACK."<<"\n\n";
                        else
                            cout<<"SPELL WITH BETTER DEFENSE."<<"\n\n";
                        print_equipment(spell_id_2);                    
                    }    
                    if(temp_spe1==temp_spe2)
                        cout<<"SPELL WEAPONS ARE JUST SAME GOOD."<<"\n\n";
                    break;              
                case 3 :
                    temp_spe1 = stoi(spell_1[12]);
                    temp_spe2 = stoi(spell_2[12]);
                    if(temp_spe1>temp_spe2)
                    {                   
                        cout<<"SPELL WITH GREATER RANGE."<<"\n\n";                   
                        print_equipment(spell_id_1);                    
                    }
                    if(temp_spe1<temp_spe2)
                    {
                        cout<<"SPELL WITH GREATER RANGE."<<"\n\n";                    
                        print_equipment(spell_id_2);                    
                    }    
                    if(temp_spe1==temp_spe2)
                        cout<<"BOTH SPELLS ARE JUST SAME GOOD."<<"\n\n";
                    break;              
            }       
            cout<<"\n\n"<<"Press any key to continue.";               
            cin.clear();
            cin.ignore();
            cin.get();            
        
        }
        
        clear_screen();
        print_equipments(); 
    }
    //!  A pure virtual member taking one argument and returns vector.
    /**
        The method executed sql command. If execution is okay, 
        method returns one row of table (one spell) in vector. 
    */
    vector<string>  Spells::get_row(string spell_id) const{
        string sql;
        char** result=NULL;
        int column=0;
        int row=0;
        sql = "";
        sql.append("SELECT * from spells WHERE ID = ").append(spell_id).
                    append(" and IDC = ").append(category);
        if(sqlite3_get_table(databaseE,sql.c_str(),&result,&row,&column,NULL)){       
           cout << "Can not open database."<< endl;           
        }        
        vector<string> table;        
        int counter=((row+1)*column);        
        for (int i=0;i<counter;i++){            
            if(result[i]!=NULL){
                table.push_back(result[i]);                           
            }
        } 
        sqlite3_free_table(result);
        result=NULL;
        return table;   
    }    
    //!  A pure virtual member taking one argument and returns vector.
    /**
        The method executed sql command. If execution is okay, 
        method returns all spells in selected category in vector.  
    */
    vector<string>  Spells::get_table() const{
        string sql;
        char** result=NULL;       
        int column=0;
        int row=0;
        sql = "";
        sql.append("SELECT Name, Attack, Defense, ManaCost, Range from "
                    "spells WHERE IDC = ").append(category);
        if(sqlite3_get_table(databaseE,sql.c_str(),&result,&row,&column,NULL))
        {       
           cout << "Can not open database. " <<endl;           
        }
        vector<string> table;        
        int counter=((row+1)*column);    
        for (int i=0;i<counter;i++){          
            if(result[i]!=NULL){
                table.push_back(result[i]);
            }                
            
        }        
        sqlite3_free_table(result);
        result=NULL;
        return table;   
    }
    //!  A pure virtual member returning vector.
    /**
        The method accepts and checks strings from STDIN. Checked 
        strings are stored in a vector. The vector is returned. 
    */
    vector<string>  Spells::get_equipment() const{
        string Name = "", Attack = "", Defense = "", Range ="",ManaCost="";
        clear_screen();        
        cout<<"ENTER PARAMETRES OF YOUR NEW WEAPON"<<"\n";
        cin.clear();
        cin.ignore();
        while(1){            
            cout<<"Name: ";
            getline(cin, Name);            
            if(check_name(Name)!=0){
                cout<<"WEAPON ALREADY EXISTS. ENTER OTHER NAME."<<"\n";
                continue;            
            }
            if(Name.size()>20 or Name.size()==0){   
                cout<<"\n"<<"ENTER MAX 20 AND AT LEAST ONE CHARACTER."<<"\n";
                continue;
            }
            else{
                break;
            }
        }
        while(1){   
            unsigned int a;
            cout<<"ManaCost: ";            
            cin>>a;
            if (!cin.good()or a >= 200) {
                cout<<"\n"<<"INVALID INPUT. ENTER POSITIVE CELL NUMBER < 200."
                    <<"\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                continue;
            }          
            else{
                ManaCost = to_string(a);
                break;        
            }
        }
        if(category == "2"){
            while(1){   
                unsigned int a;
                cout<<"Defense: ";
                cin>>a;
                if (!cin.good()or a >= 200){
                    cout<<"\n"<<"INVALID INPUT. ENTER POSITIVE CELL NUMBER < 200."<<"\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    continue;
                }             
                else{
                    Defense = to_string(a);
                    break;                
                }
            }
        }
        if(category == "1"){
            while(1){   
                unsigned int a;
                cout<<"Attack: ";
                cin>>a;
                if (!cin.good()or a >= 200){
                    cout<<"\n"<<"INVALID INPUT. ENTER POSITIVE CELL NUMBER < 1000."<<"\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    continue;
                }             
                else{
                    Attack = to_string(a);
                    break;                
                }
            }
        }
        while(1){   
            unsigned int a;
            cout<<"Range: ";
            cin>>a;
            if (!cin.good()or a >= 1000) {
                cout<<"\n"<<"INVALID INPUT. ENTER POSITIVE CELL NUMBER < 1000000."<<"\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                continue;
            }            
            else{
                Range = to_string(a);
                break;                
            }
        }
        string Attack_Defense = "";
        if(category == "1")
            Attack_Defense = Attack ;
        else
            Attack_Defense = Defense;
        vector<string>weapon;
        weapon.push_back(Name);
        weapon.push_back(ManaCost);
        weapon.push_back(Attack_Defense);
        weapon.push_back(Range);
        return weapon;   
    }
    //!  A pure virtual member.
    /**
        The method adds weapons to itinerary. 
    */
    void            Spells::add_equipment(){
        vector<string>weapon = get_equipment();
        string sql;
        string Name = weapon[0];
        string ManaCost = weapon[1];
        string Attack_Defense = weapon[2];
        string Range = weapon[3];
        sql = get_insert_sql(Name, ManaCost, Attack_Defense, Range);       
        bool check = insert_equipment(sql);
        if(!check){            
            cout<<"Spell can not be added."<<"\n"
                <<"Press any key to continue.";         
        }
        else{
            cout<<"\n"<<"Spell successfully added."<<"\n"
                <<"Press any key to continue."<<"\n";       
        }
        cin.clear();
        cin.ignore();
        cin.get();
        clear_screen();
        print_equipments();    
    }
    //!  A pure virtual member taking one argument and returning integer.
    /**      
        The method taking weapon name (string) and executes sql command. If 
        execution is done correctly, method returns number of row with same name
        in database, else returns -1.
    */ 
    int             Spells::check_name(string Name) const{
        int count = -1;
        string sql_check;       
        string name = to_lower(Name);       
        sql_check.append("SELECT COUNT (*) from Spells WHERE lower (Name) = '").
                        append(name).append("' and IDC = ").append(category);      
        int check = sqlite3_exec(databaseE, sql_check.c_str(), call_back_row, 
                                &count, NULL);
        if( check != SQLITE_OK )
        {
            cout<<"Can not open database."<<endl;
            count = -1;
        }            
            return count;    
    }
    //!  A pure virtual member taking four arguments.
    /**
        The method taking four strings and return sql statement as a string. 
    */
    string          Spells::get_insert_sql(string Name, string ManaCost, 
                                           string Attack_Defense ,
                                           string Range)const{
                            
        string sql;
        stringstream str;
        if(category == "1")
        {        
            string Attack = Attack_Defense;
            str <<"INSERT INTO Spells(Name,IDC,ManaCost,Attack,Range)VALUES"
                <<"('"<<Name<<"',"<<"1"<<","<<ManaCost<<","<<Attack<<","<<Range
                <<")";                
            sql = str.str();            
        }
        if(category == "2")
        {
            string Defense = Attack_Defense;
            str <<"INSERT INTO Spells(Name,IDC,ManaCost,Defense,Range)VALUES"
                <<"('"<<Name<<"',"<<"2"<<","<<ManaCost<<","<<Defense<<","
                <<Range<<")";                
            sql = str.str();            
        }
        return sql;   
    }
    //!  A pure virtual member.
    /**      
        The method imports weapons in CSV format. A File name from STDIN is 
        accepted. If the file that name doesn't exists or is corrupted a new 
        file name is demanded. If file is okay, all spells in category are 
        stored in file.
    */  
    void            Spells::csv_import(){
        string file = "";
        string f = "";
        vector<string>table;        
        cout<<"ENTER FILE NAME: ";
        cin.clear();
        cin.ignore();
        getline(cin, f);
        file.append("./examples/").append(f);
        ifstream read;
        read.open(file);        
        if (!read.is_open()) 
        {
            read.close();
            cout<<"\n"<<"File is missing or corrupted. Try again. "<<"\n"               
            <<"Press any key to continue.";               
            cin.clear();
            cin.get();                        
        }
        else
        {                       
            string Name = "";
            string ManaCost = "";
            string Attack_Defense = "";
            string Range = "";
            string sql = "";
            int i = 0;
                while(!read.eof()){
                    i++;
                    getline(read,Name, ',');
                    getline(read,ManaCost, ',');
                    getline(read,Attack_Defense, ',');
                    getline(read,Range, '\n');               
                    if(csv_check(Name,ManaCost,Attack_Defense,Range)){
                        sql =get_insert_sql(Name,ManaCost,Attack_Defense,Range);
                        insert_equipment(sql);
                        cout<<"Spell number "<<i<<" was successfully imported."
                            <<"\n";
                        continue;
                    }
                    else{
                        cout<<"Spell number "<<i<<" can't be imported."
                            <<"\n";                      
                    }
                }            
                cout<<"Press any key to continue."<<"\n";            
            cin.clear();            
            cin.get();
            read.close();
        }
    }
    //!  A pure virtual member returning integer.
    /**      
        The method executes sql command. If execution is done correctly, method 
        returns number of spells in the category, else returns -1.
    */    
    int             Spells::row_count() const{
        
        int count = -1;
        string sql_check;        
        sql_check.append("SELECT COUNT (*) from spells WHERE IDC = ")
                        .append(category);
        int check = sqlite3_exec(databaseE, sql_check.c_str(), call_back_row,
                                &count, NULL);
        if( check != SQLITE_OK ){
            
           cout<<"Can not open database."<<endl;
           count = -1;
        }
        return count;   
    }    
    //!  A pure virtual member.
    /*      
        The method exports all spells to CSV file. File name from STDIN is 
        accepted. If file that name doesn't exists, is based. I/O opening is 
        checked.
    */   
    void            Spells::csv_export(){
        string file = "";
	string f = "";
        cout<<"ENTER FILE NAME: ";
        cin.clear();
        cin.ignore();
        getline(cin, f);        
        while(f.size()==0){          
            
            cout<<"YOU MUST ENTER AT LEAST ONE CHARACTER"<<"\n"
                <<"ENTER FILE NAME: ";
            getline(cin, f);
        }      
        ofstream read;
        file.append("./examples/").append(f);
        while(1){
            read.open(file);            
            if (!read.is_open()){
                read.close();
                cout<<"\n"<<"File is corrupted. Try again or select "
                            "(B) to return back."<<"\n\n"<<"ENTER FILE NAME: ";                
                getline(cin, file);
                file = to_lower(file);
                if(file == "b"){
                    clear_screen();
                    print_equipments();                   
                }                
            }
            else{
                cout<<"\n";
                break;
            }       
        }       
        unsigned int number_row = row_count();
        vector<string>table = get_table();
        if(number_row>0){
            for(unsigned int i = 5; i<(table.size()); i++){
                read<<table[i];               
                if(i%4 == 0 and i!= (table.size()-1) )
                    read<<"\n";                
                else if(i != (table.size()-1))
                    read<<",";               
            }
        }
        read.close();
        cout<<"\n"<<"Spells was exported successfully.";
        cout<<"\n"<<"Press any key to continue.";               
        cin.clear();        
        cin.get();
        clear_screen();
        print_equipments();  
    }
    //!  A pure virtual member taking four argument and returns bool value.
    /**      
        The method checks value in imported CSV file and returns true if it is 
        okay or false if isn't.
    */ 
    bool            Spells::csv_check(string Name, string ManaCost,
                                     string Attack_Defense, string Range) const{        
        bool check = true;
        int row_count = check_name(Name);     
        if(Name.size()>20 or row_count>0 )
            check = false;
        
        int Attack_Defense_int = stoi(Attack_Defense);
        if(Attack_Defense_int<0 or Attack_Defense_int>200)
            check = false;
        
        int ManaCost_int = stoi(ManaCost);
        if(ManaCost_int<0 or ManaCost_int>200)
            check = false;
        
        int Range_int = stoi(Range);
        if(Range_int<0 or Range_int>1000)
            check = false;   
        return check;   
    }    
    //!  A pure virtual member returning unsigned integer.
    /**
        The method accepts and check unsigned integer from STDIN. Checked 
        unsigned integer (user choice} is returned. 
    */   
    unsigned int    Spells::choice_to_compare() const 
    {
        unsigned int choice;
        if(category == "1"){
            cout<<"According to what parameter do you want to compare?"<<"\n"
                <<"(1)"<<setw(5)<<" "<<"Mana_cost"<<"\n"
                <<"(2)"<<setw(5)<<" "<<"Attack"<<"\n"
                <<"(3)"<<setw(5)<<" "<<"Range"<<"\n\n"
                <<"Select parameter: ";        
            while(1){   
                cin>>choice;
                if (!cin.good()or choice>3) {
                    cout<<"\n"<<"INVALID INPUT. TRY AGAIN."<<"\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    continue;
                }          
                else{
                    break;        
                }
            }       
        }
        if(category == "2"){
            cout<<"According to what parameter do you want to compare?"<<"\n"
            <<"(1)"<<setw(5)<<" "<<"Mana_cost"<<"\n"
            <<"(2)"<<setw(5)<<" "<<"Defense"<<"\n"
            <<"(3)"<<setw(5)<<" "<<"Range"<<"\n\n"
            <<"Select parameter: ";
            while(1){                  
                cin>>choice;
                if (!cin.good()or choice>3){
                    cout<<"\n"<<"INVALID INPUT. TRY AGAIN."<<"\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    continue;
                }          
                else{
                    break;        
                }
            }       
       }
        return choice;    
    }
    
    //!  A pure virtual member taking one argument.
    /*
        The method executes sql command. If execution is okay, weapon including 
        all Parameters is printed. 
    */    
    void            Spells::print_equipment(string choice) const
    {
        string sql = "";
        sql.append("SELECT * from spells WHERE ID = ").append(choice).
                   append(" and IDC = ").append(category);
        int check = sqlite3_exec(databaseE, sql.c_str(), call_back_spells, 
                                 NULL,NULL);        
        if( check != SQLITE_OK )
        {
            cout<<"Can not open database."<<endl;           
        }
        cout<<"\n";    
    }
    //!  A destructor.
    /**      
        The databaseE pointer is set to NULL.
    */
    Spells::~Spells() {
        databaseE = NULL;
    }

