/* 
 * File:   Weapons.h
 * Author: Tomas Bina  
 */

#ifndef WEAPONS_H
#define	WEAPONS_H

using namespace std;
class Weapons : public Equipments
{
public:
    Weapons();
    void                    set_choice(string choice);
    void                    set_action(string Action);
    static int              call_back_weapons(void *NotUsed, int argc,
                                              char **argv, char **azColName);
    static int              call_back_row(void *count, int argc, 
                                          char **argv, char **azColName);
    virtual string          print_categories ();
    virtual void            print_equipments ();
    virtual void            select_action(string);
    virtual void            show_equipment(string);
    virtual void            delete_equipment();
    virtual bool            insert_equipment(string);
    virtual int             check_id(string) const;
    virtual void            compare_equipment() ;    
    virtual vector<string>  get_row(string) const ;
    virtual vector<string>  get_table() const;
    virtual vector<string>  get_equipment() const;
    virtual void            add_equipment() ;
    virtual int             check_name(string) const;
    virtual string          get_insert_sql(string, string, string, string) 
                                            const;
    virtual void            csv_import();
    virtual int             row_count() const;
    virtual void            csv_export();
    virtual bool            csv_check(string, string, string, string) const;
    virtual unsigned int    choice_to_compare() const ;
    virtual void            print_equipment(string) const;
    virtual                 ~Weapons();
    
private:
    string category;
    string action;

};

#endif	/* WEAPONS_H */

