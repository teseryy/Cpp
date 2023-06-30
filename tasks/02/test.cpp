#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <cassert>
#include <iostream> 
#include <iomanip> 
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <memory>
using namespace std;
#endif /* __PROGTEST__ */

//class for employee representation
class Person{
    string name;
    string surname;
    string email;
    unsigned int salary;

public:
    Person(const string& name, const string& surname, const string& email, unsigned int salary) : name(name), surname(surname), email(email), salary(salary) {};
    Person(const string& name, const string& surname) : name(name), surname(surname), email(), salary() {}; // constructor for compare by surname and name
    Person(const string& email) : name(), surname(), email(email), salary() {}; // constructor for compare by email

    const string &getName() const {
        return name;
    }

    const string &getSurname() const {
        return surname;
    }

    const string &getEmail() const {
        return email;
    }

    unsigned int getSalary() const {
        return salary;
    }

    void setName(const string &name) {
        Person::name = name;
    }

    void setSurname(const string &surname) {
        Person::surname = surname;
    }

    void setEmail(const string &email) {
        Person::email = email;
    }

    void setSalary(unsigned int salary) {
        Person::salary = salary;
    }
};


class CmpName{
public:
    bool operator()(const Person& pers1, const Person& pers2 ){
        if (pers1.getSurname() == pers2.getSurname()){
            return pers1.getName() < pers2.getName();
        }
        return pers1.getSurname() < pers2.getSurname();
    }
};

class CmpEmail{
public:
    bool operator()(const Person& pers1, const Person& pers2 ){
        return pers1.getEmail() < pers2.getEmail();
    }
};

class CPersonalAgenda
{
  public:
                  CPersonalAgenda  (){};
                  ~CPersonalAgenda (){};
    bool          add              ( const string    & name,
                                     const string    & surname,
                                     const string    & email,
                                     unsigned int      salary );
    bool          del              ( const string    & name,
                                     const string    & surname );
    bool          del              ( const string    & email );
    bool          changeName       ( const string    & email,
                                     const string    & newName,
                                     const string    & newSurname );
    bool          changeEmail      ( const string    & name,
                                     const string    & surname,
                                     const string    & newEmail );
    bool          setSalary        ( const string    & name,
                                     const string    & surname,
                                     unsigned int      salary );
    bool          setSalary        ( const string    & email,
                                     unsigned int      salary );
    unsigned int  getSalary        ( const string    & name,
                                     const string    & surname ) const;
    unsigned int  getSalary        ( const string    & email ) const;
    bool          getRank          ( const string    & name,
                                     const string    & surname,
                                     int             & rankMin,
                                     int             & rankMax ) const;
    bool          getRank          ( const string    & email,
                                     int             & rankMin,
                                     int             & rankMax ) const;
    bool          getFirst         ( string          & outName,
                                     string          & outSurname ) const;
    bool          getNext          ( const string    & name,
                                     const string    & surname,
                                     string          & outName,
                                     string          & outSurname ) const;
  private:
    vector<Person> dataBase_byName;
    vector<Person> dataBase_byEmail;

    bool bin_searchEmail(const string& email) const;
    bool bin_searchName(const string &name, const string &surname) const;

    void add_byName(const string &name, const string &surname, const string &email, unsigned int salary);
    void add_byEmail(const string &name, const string &surname, const string &email, unsigned int salary);
};

// function to check is the employee present in the database
bool CPersonalAgenda::bin_searchEmail(const string& email) const{
   return binary_search(dataBase_byEmail.begin(), dataBase_byEmail.end(), Person(email), CmpEmail());
}
// function to check is the employee present in the database
bool CPersonalAgenda::bin_searchName(const string &name, const string &surname) const{
    return binary_search(dataBase_byName.begin(), dataBase_byName.end(), Person(name, surname), CmpName());
}

void CPersonalAgenda::add_byEmail(const string &name, const string &surname, const string &email, unsigned int salary) {

    Person person = Person(name, surname, email, salary);

    //search for a place to add an employee to keep the database in sorted state
    auto itEmail = lower_bound(dataBase_byEmail.begin(), dataBase_byEmail.end(), Person(email), CmpEmail());
    dataBase_byEmail.insert(itEmail, person);
}
void CPersonalAgenda::add_byName(const string &name, const string &surname, const string &email, unsigned int salary) {

    Person person = Person(name, surname, email, salary);

    //search for a place to add an employee to keep the database in sorted state
    auto itName = lower_bound(dataBase_byName.begin(), dataBase_byName.end(), Person(name, surname), CmpName());
    dataBase_byName.insert(itName, person);
}

bool CPersonalAgenda::add(const string &name, const string &surname, const string &email, unsigned int salary) {
    bool i = bin_searchEmail(email);

    if (i){
        return false;
    }

    i = bin_searchName(name, surname);
    if (i){
        return false;
    }

    add_byEmail(name, surname, email, salary);

    add_byName(name, surname, email, salary);

    return true;
}

bool CPersonalAgenda::del (const string& name, const string& surname){
    bool i = bin_searchName(name, surname);
    if (!i){
        return false;
    }

    auto itName = lower_bound(dataBase_byName.begin(), dataBase_byName.end(), Person(name, surname), CmpName());
    auto itEmail = lower_bound(dataBase_byEmail.begin(), dataBase_byEmail.end(), Person(itName->getEmail()), CmpEmail());

    dataBase_byName.erase(itName);
    dataBase_byEmail.erase(itEmail);

    return true;
}
bool CPersonalAgenda::del ( const string& email ){
    bool i = bin_searchEmail(email);
    if (!i){
        return false;
    }

    auto itEmail = lower_bound(dataBase_byEmail.begin(), dataBase_byEmail.end(), Person(email), CmpEmail());
    auto itName = lower_bound(dataBase_byName.begin(), dataBase_byName.end(), Person(itEmail->getName(), itEmail->getSurname()), CmpName());

    dataBase_byName.erase(itName);
    dataBase_byEmail.erase(itEmail);

    return true;
}

bool CPersonalAgenda::changeName (const string& email, const string& newName, const string& newSurname){
    bool i = bin_searchEmail(email);
    bool flag = bin_searchName(newName, newSurname);
    if (!i){
        return false;
    }
    if (flag){
        return false;
    }

    auto itEmail = lower_bound(dataBase_byEmail.begin(), dataBase_byEmail.end(), Person(email), CmpEmail());
    auto itName = lower_bound(dataBase_byName.begin(), dataBase_byName.end(), Person(itEmail->getName(), itEmail->getSurname()), CmpName());

    itEmail->setName(newName);
    itEmail->setSurname(newSurname);

    itName->setName(newName);
    itName->setSurname(newSurname);

    //sorting database after surname and name change
    std::sort(dataBase_byName.begin(), dataBase_byName.end(), CmpName());

    return true;
}

bool CPersonalAgenda::changeEmail (const string& name, const string& surname, const string& newEmail ){
    bool i = bin_searchName(name, surname);
    bool flag = bin_searchEmail(newEmail);
    if (!i){
        return false;
    }
    if (flag){
        return false;
    }
    auto itName = lower_bound(dataBase_byName.begin(), dataBase_byName.end(), Person(name, surname), CmpName());
    auto itEmail = lower_bound(dataBase_byEmail.begin(), dataBase_byEmail.end(), Person(itName->getEmail()), CmpEmail());

    itEmail->setEmail(newEmail);

    //sorting database after email change
    std::sort(dataBase_byEmail.begin(), dataBase_byEmail.end(), CmpEmail());

    itName->setEmail(newEmail);


    return true;
}

bool CPersonalAgenda::setSalary (const string& name, const string& surname, unsigned int salary){
    bool i = bin_searchName(name, surname);
    if (!i){
        return false;
    }

    auto itName = lower_bound(dataBase_byName.begin(), dataBase_byName.end(), Person(name, surname), CmpName());
    auto itEmail = lower_bound(dataBase_byEmail.begin(), dataBase_byEmail.end(), Person(itName->getEmail()), CmpEmail());

    itName->setSalary(salary);
    itEmail->setSalary(salary);

    return true;
}
bool CPersonalAgenda::setSalary (const string &email, unsigned int salary){
    bool i = bin_searchEmail(email);
    if (!i){
        return false;
    }

    auto itEmail = lower_bound(dataBase_byEmail.begin(), dataBase_byEmail.end(), Person(email), CmpEmail());
    auto itName = lower_bound(dataBase_byName.begin(), dataBase_byName.end(), Person(itEmail->getName(), itEmail->getSurname()), CmpName());

    itEmail->setSalary(salary);
    itName->setSalary(salary);

    return true;
}

unsigned int  CPersonalAgenda::getSalary(const string& name, const string& surname ) const{
    bool i = bin_searchName(name, surname);
    if (!i){
        return false;
    }

    auto itName = lower_bound(dataBase_byName.begin(), dataBase_byName.end(), Person(name, surname), CmpName());
    return itName->getSalary();
}
unsigned int  CPersonalAgenda::getSalary(const string& email) const{
    bool i = bin_searchEmail(email);
    if (!i){
        return false;
    }

    auto itEmail = lower_bound(dataBase_byEmail.begin(), dataBase_byEmail.end(), Person(email), CmpEmail());
    return itEmail->getSalary();
}

bool CPersonalAgenda::getFirst(string& outName, string& outSurname) const{
    if (!dataBase_byName.empty()){
        outName = dataBase_byName[0].getName();
        outSurname = dataBase_byName[0].getSurname();
        return true;
    }
    else{
        return false;
    }
}
bool CPersonalAgenda::getNext(const string& name, const string& surname, string& outName, string& outSurname) const{
    bool i = bin_searchName(name, surname);
    if (!i){
        return false;
    }
    else {
        auto itName = lower_bound(dataBase_byName.begin(), dataBase_byName.end(), Person(name, surname), CmpName());
        if (itName + 1 == dataBase_byName.end()) {
            return false;
        } else {
            outName = (itName + 1)->getName();
            outSurname = (itName + 1)->getSurname();
            return true;
        }
    }
}

bool CPersonalAgenda::getRank(const string& name, const string& surname, int & rankMin, int & rankMax) const{
    bool i = bin_searchName(name, surname);
    if (!i){
        return false;
    }

    auto itName = lower_bound(dataBase_byName.begin(), dataBase_byName.end(), Person(name, surname), CmpName());
    unsigned int curSalary = itName->getSalary();
    int same = 0, low = 0;
    size_t len = dataBase_byName.size();

    //search for the number of people with the same salary and less
    for (size_t idx = 0; idx < len; idx++){
        if (dataBase_byName[idx].getSalary() < curSalary){
            low++;
        }
        else if (dataBase_byName[idx].getSalary() == curSalary){
            same++;
        }
    }
    //the person for whom we are looking for a rank was also added
    same -= 1;

    rankMin = low;
    rankMax = low + same;

    return true;
}
bool CPersonalAgenda::getRank(const string& email, int & rankMin, int & rankMax) const{
    bool i = bin_searchEmail(email);
    if (!i){
        return false;
    }

    auto itEmail = lower_bound(dataBase_byEmail.begin(), dataBase_byEmail.end(), Person(email), CmpEmail());
    unsigned int curSalary = itEmail->getSalary();
    int same = 0, low = 0;
    size_t len = dataBase_byEmail.size();

    //search for the number of people with the same salary and less
    for (size_t idx = 0; idx < len; idx++){
        if (dataBase_byEmail[idx].getSalary() < curSalary){
            low++;
        }
        else if (dataBase_byEmail[idx].getSalary() == curSalary){
            same++;
        }
    }
    //the person for whom we are looking for a rank was also added
    same -= 1;

    rankMin = low;
    rankMax = low + same;

    return true;
}


#ifndef __PROGTEST__
int main ( void )
{
  string outName, outSurname;
  int lo, hi;


  CPersonalAgenda b1;

    assert ( b1 . add ( "John", "Smith", "john", 30000 ) );
    assert ( b1 . add ( "John", "Miller", "johnm", 35000 ) );
    assert ( b1 . add ( "Peter", "Smith", "peter", 23000 ) );
    assert ( b1 . getFirst ( outName, outSurname )
             && outName == "John"
             && outSurname == "Miller" );
    assert ( b1 . getNext ( "John", "Miller", outName, outSurname )
             && outName == "John"
             && outSurname == "Smith" );
    assert ( b1 . getNext ( "John", "Smith", outName, outSurname )
             && outName == "Peter"
             && outSurname == "Smith" );
    assert ( ! b1 . getNext ( "Peter", "Smith", outName, outSurname ) );
    assert ( b1 . setSalary ( "john", 32000 ) );
    assert ( b1 . getSalary ( "john" ) ==  32000 );
    assert ( b1 . getSalary ( "John", "Smith" ) ==  32000 );
    assert ( b1 . getRank ( "John", "Smith", lo, hi )
             && lo == 1
             && hi == 1 );
    assert ( b1 . getRank ( "john", lo, hi )
             && lo == 1
             && hi == 1 );
    assert ( b1 . getRank ( "peter", lo, hi )
             && lo == 0
             && hi == 0 );
    assert ( b1 . getRank ( "johnm", lo, hi )
             && lo == 2
             && hi == 2 );
    assert ( b1 . setSalary ( "John", "Smith", 35000 ) );
    assert ( b1 . getSalary ( "John", "Smith" ) ==  35000 );
    assert ( b1 . getSalary ( "john" ) ==  35000 );
    assert ( b1 . getRank ( "John", "Smith", lo, hi )
             && lo == 1
             && hi == 2 );
    assert ( b1 . getRank ( "john", lo, hi )
             && lo == 1
             && hi == 2 );
    assert ( b1 . getRank ( "peter", lo, hi )
             && lo == 0
             && hi == 0 );
    assert ( b1 . getRank ( "johnm", lo, hi )
             && lo == 1
             && hi == 2 );
    assert ( b1 . changeName ( "peter", "James", "Bond" ) );
    assert ( b1 . getSalary ( "peter" ) ==  23000 );
    assert ( b1 . getSalary ( "James", "Bond" ) ==  23000 );
    assert ( b1 . getSalary ( "Peter", "Smith" ) ==  0 );
    assert ( b1 . getFirst ( outName, outSurname )
             && outName == "James"
             && outSurname == "Bond" );
    assert ( b1 . getNext ( "James", "Bond", outName, outSurname )
             && outName == "John"
             && outSurname == "Miller" );
    assert ( b1 . getNext ( "John", "Miller", outName, outSurname )
             && outName == "John"
             && outSurname == "Smith" );
    assert ( ! b1 . getNext ( "John", "Smith", outName, outSurname ) );
    assert ( b1 . changeEmail ( "James", "Bond", "james" ) );
    assert ( b1 . getSalary ( "James", "Bond" ) ==  23000 );
    assert ( b1 . getSalary ( "james" ) ==  23000 );
    assert ( b1 . getSalary ( "peter" ) ==  0 );
    assert ( b1 . del ( "james" ) );
    assert ( b1 . getRank ( "john", lo, hi )
             && lo == 0
             && hi == 1 );
    assert ( b1 . del ( "John", "Miller" ) );
    assert ( b1 . getRank ( "john", lo, hi )
             && lo == 0
             && hi == 0 );
    assert ( b1 . getFirst ( outName, outSurname )
             && outName == "John"
             && outSurname == "Smith" );
    assert ( ! b1 . getNext ( "John", "Smith", outName, outSurname ) );
    assert ( b1 . del ( "john" ) );
    assert ( ! b1 . getFirst ( outName, outSurname ) );
    assert ( b1 . add ( "John", "Smith", "john", 31000 ) );
    assert ( b1 . add ( "john", "Smith", "joHn", 31000 ) );
    assert ( b1 . add ( "John", "smith", "jOhn", 31000 ) );

    CPersonalAgenda b2;
    assert ( ! b2 . getFirst ( outName, outSurname ) );
    assert ( b2 . add ( "James", "Bond", "james", 70000 ) );
    assert ( b2 . add ( "James", "Smith", "james2", 30000 ) );
    assert ( b2 . add ( "Peter", "Smith", "peter", 40000 ) );
    assert ( ! b2 . add ( "James", "Bond", "james3", 60000 ) );
    assert ( ! b2 . add ( "Peter", "Bond", "peter", 50000 ) );
    assert ( ! b2 . changeName ( "joe", "Joe", "Black" ) );
    assert ( ! b2 . changeEmail ( "Joe", "Black", "joe" ) );
    assert ( ! b2 . setSalary ( "Joe", "Black", 90000 ) );
    assert ( ! b2 . setSalary ( "joe", 90000 ) );
    assert ( b2 . getSalary ( "Joe", "Black" ) ==  0 );
    assert ( b2 . getSalary ( "joe" ) ==  0 );
    assert ( ! b2 . getRank ( "Joe", "Black", lo, hi ) );
    assert ( ! b2 . getRank ( "joe", lo, hi ) );
    assert ( ! b2 . changeName ( "joe", "Joe", "Black" ) );
    assert ( ! b2 . changeEmail ( "Joe", "Black", "joe" ) );
    assert ( ! b2 . del ( "Joe", "Black" ) );
    assert ( ! b2 . del ( "joe" ) );
    assert ( ! b2 . changeName ( "james2", "James", "Bond" ) );
    assert ( ! b2 . changeEmail ( "Peter", "Smith", "james" ) );
    assert ( ! b2 . changeName ( "peter", "Peter", "Smith" ) );
    assert ( ! b2 . changeEmail ( "Peter", "Smith", "peter" ) );
    assert ( b2 . del ( "Peter", "Smith" ) );
    assert ( ! b2 . changeEmail ( "Peter", "Smith", "peter2" ) );
    assert ( ! b2 . setSalary ( "Peter", "Smith", 35000 ) );
    assert ( b2 . getSalary ( "Peter", "Smith" ) ==  0 );
    assert ( ! b2 . getRank ( "Peter", "Smith", lo, hi ) );
    assert ( ! b2 . changeName ( "peter", "Peter", "Falcon" ) );
    assert ( ! b2 . setSalary ( "peter", 37000 ) );
    assert ( b2 . getSalary ( "peter" ) ==  0 );
    assert ( ! b2 . getRank ( "peter", lo, hi ) );
    assert ( ! b2 . del ( "Peter", "Smith" ) );
    assert ( ! b2 . del ( "peter" ) );
    assert ( b2 . add ( "Peter", "Smith", "peter", 40000 ) );
    assert ( b2 . getSalary ( "peter" ) ==  40000 );

  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
