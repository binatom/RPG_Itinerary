/* 
 * File:   Equipments.h
 * Author: Tomas Bina 
 */

#ifndef EQUIPMENTS_H
#define	EQUIPMENTS_H
#include "sqlite/sqlite3.h"
#include "CMenu.h"
#include <vector>

using namespace std;
class Equipments {
public:
    
                            Equipments();
    virtual string          print_categories () = 0;
    virtual void            print_equipments()  = 0;
    virtual void            select_action(string) = 0;
    virtual void            show_equipment(string) = 0;
    virtual void            delete_equipment() = 0;
    virtual bool            insert_equipment(string) = 0;
    virtual int             check_id(string) const = 0;
    virtual int             check_name(string) const = 0;
    virtual void            compare_equipment()  = 0;
    virtual unsigned int    choice_to_compare() const = 0;
    virtual void            print_equipment(string) const = 0;
    virtual string          get_insert_sql(string, string, string, string) const = 0;
    virtual void            csv_import() = 0;
    virtual vector<string>  get_row(string) const = 0;
    virtual vector<string>  get_table() const = 0;
    virtual vector<string>  get_equipment() const = 0;
    virtual void            add_equipment() = 0 ;
    virtual bool            csv_check(string, string, string, string) const = 0;
    virtual void            csv_export() = 0;    
    virtual int             row_count() const = 0;
    string                  to_lower(string) const;
    void                    clear_screen() const;
    void                    get_database(sqlite3 *);
    void                    invalid_input()const;
    static int              call_back1(void *NotUsed, int argc, char **argv, char **azColName);
    sqlite3 * databaseE;    
    virtual                 ~Equipments();
private:  
    
};

#endif	/* EQUIPMENTS_H */

