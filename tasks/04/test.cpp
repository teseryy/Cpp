#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <cctype>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;
#endif /* __PROGTEST__ */

//inspired by https://www.geeksforgeeks.org/how-to-create-a-custom-string-class-in-c-with-basic-functionalities/
class String {
    char* str;

public:
    String();

    String(const char* val);

    String(const String& source);
    String(String&& source) noexcept ;

    ~String() {
        delete[] str;
    }

    friend ostream& operator<<(ostream& os, const String& string);

    friend String operator+(const String& a, const String& b);
    friend bool operator<(const String& a, const String& b);
    friend bool operator<=(const String& a, const String& b);
    friend bool operator>(const String& a, const String& b);
    friend bool operator==(const String& a, const String& b);
    friend bool operator!=(const String& a, const String& b);

    bool is_subStr(const String& subStr);

    bool isEmpty() const;

    void push_back(char a);

    void pop_back();

    int size();

    String& operator=(const String& string);
    String& operator=(String&& string) noexcept ;
    String& operator=(const char* string);
};

String::String(){
    str = new char[1];
    str[0] = '\0';
}

String::String(const char* val){
    if (val == nullptr) {
        str = new char[1];
        str[0] = '\0';
    }
    else {
        str = new char[strlen(val) + 1];
        strcpy(str, val);
        str[strlen(val)] = '\0';
    }
}

String::String(const String& source){
    str = new char[strlen(source.str) + 1];
    strcpy(str, source.str);
    str[strlen(source.str)] = '\0';
}

String::String(String&& source)  noexcept : str(source.str) {
    source.str = nullptr;
}

String& String::operator=(const char* string){
    if (this->str == string)
        return *this;
    delete[] str;
    str = new char[strlen(string) + 1];
    strcpy(str, string);
    return *this;
}

String& String::operator=(String&& string) noexcept {
    if (this == &string)
        return *this;
    delete[] str;
    str = string.str;
    string.str = nullptr;

    return *this;
}

String& String::operator=(const String& string){
    if (this == &string)
        return *this;
    delete[] str;
    str = new char[strlen(string.str) + 1];
    strcpy(str, string.str);
    return *this;
}

String operator+(const String& a, const String& b){
    int length = strlen(a.str) + strlen(b.str);

    char* buff = new char[length + 1];

    strcpy(buff, a.str);
    strcat(buff, b.str);
    buff[length] = '\0';

    String tmp(buff) ;

    delete[] buff;

    return tmp;
}

ostream& operator<<(ostream& os, const String& string){
    os << string.str;

    return os;
}

void String::push_back(char a){
    int length = strlen(str);

    char* buff = new char[length + 2];

    for (int i = 0; i < length; i++) {
        buff[i] = str[i];
    }
    buff[length] = a;
    buff[length + 1] = '\0';

    *this = String(buff);

    delete[] buff;
}

int String::size(){
    return strlen(str);
}

bool operator<(const String& a, const String& b){
    return ::strcmp(a.str, b.str) < 0;
}

bool operator<=(const String& a, const String& b){
    return ::strcmp(a.str, b.str) <= 0;
}

bool operator==(const String& a, const String& b){
    return ::strcmp(a.str, b.str) == 0;
}

bool operator>(const String& a, const String& b){
    return ::strcmp(a.str, b.str) > 0;
}

bool operator!=(const String& a, const String& b){
    return ::strcmp(a.str, b.str) != 0;
}

bool String::isEmpty() const{
    return ::strlen(str) == 0;
}

void String::pop_back() {
    int length = strlen(str);
    char* buff = new char[length];

    for (int i = 0; i < length - 1; i++)
        buff[i] = str[i];
    buff[length-1] = '\0';

    *this = String{ buff };

    delete[] buff;
}

bool String::is_subStr(const String& subStr) {
    char * res = strstr(str, subStr.str);
    if (res != nullptr){
        return true;
    }
    return false;
}


//inspired by https://habr.com/ru/post/593803/
template<typename T>
class Vector {
public:
    Vector() {
        array = new T[1];
        capacity = 1;
        length = 0;
    }

    Vector(int capacity) {
        array = new T[capacity];
        this->capacity = capacity;
        length = 0;
    }

    Vector(const Vector& other) {
        array = new T[other.capacity];
        for (size_t i = 0; i < other.length; i++) array[i] = other.array[i];
        length = other.length;
        capacity = other.capacity;
    }

    Vector(Vector&& other)  noexcept {
        if (this != &other) {
            delete[] array;
            array = other.array;
            length = other.length;
            capacity = other.capacity;
            other.array = nullptr;
            other.length = other.capacity = 0;
        }
    }

    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            delete[] array;
            array = other.array;
            length = other.length;
            capacity = other.capacity;
            other.array = nullptr;
            other.length = other.capacity = 0;
        }
        return *this;
    }

    ~Vector() {
        delete[] array;
    }

    bool isEmpty() const {
        return length == 0;
    }

    size_t size() const {
        return length;
    }

    void resize() {
        capacity *= 2;
        T* tmp = array;
        array = new T[capacity];
        for (size_t i = 0; i < length; i++) array[i] = tmp[i];
        delete[] tmp;
    }

    void pushBack(const T& value) {
        if (length >= capacity) resize();
        array[length++] = value;
    }

    void erase(size_t index) {
        for (size_t i = index + 1; i < length; i++) {
            array[i - 1] = array[i];
        }
        length -= 1;
    }
    void insert(int index, const T& value){
        if (index <= int(length)) {
            if (length == 0){
                this->pushBack(value);
            }
            else {
                T tmp;
                if (length >= capacity) resize();
                for (size_t i = index; i < length + 1; i++) {
                    T temp;
                    if (i != length) {
                        temp = array[i];
                    }
                    array[i] = tmp;
                    tmp = temp;
                }
                array[index] = value;
            }
            length += 1;
        }
    }

    T& operator[](size_t index)  {
        return array[index];
    }

    const T& operator[](size_t index) const {
        return array[index];
    }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] array;
            array = new T[other.capacity];
            for (size_t i = 0; i < other.length; i++) array[i] = other.array[i];
            length = other.length;
            capacity = other.capacity;
        }
        return *this;
    }

    T* begin() {
        return &array[0];
    }

    const T* begin() const {
        return &array[0];
    }

    T* end() {
        return &array[length];
    }

    const T* end() const {
        return &array[length];
    }
private:
    T* array;
    size_t length{};
    size_t capacity{};
};


class CMail{
  public:
    CMail() = default;

    CMail                         (const char      * from,
                                   const char      * to,
                                   const char      * body );
    bool                     operator ==                   ( const CMail     & x ) const;
    friend ostream         & operator <<                   ( ostream         & os,
                                                             const CMail     & m );

    const String &getFrom() const;

    const String &getTo() const;

    const String &getBody() const;

private:
    String from, to, body;
};

CMail::CMail(const char *from, const char *to, const char *body) {
    this->from = from;
    this->to = to;
    this->body = body;
}

bool CMail::operator==(const CMail &x) const {
    if (from == x.getFrom() && to == x.getTo() && body == x.getBody()){
        return true;
    }

    return false;
}

ostream& operator<<( ostream& os, const CMail& m ){
    os << "From: " << m.from << ", To: " << m.to << ", Body: " << m.body;

    return os;
}

const String &CMail::getFrom() const {
    return from;
}

const String &CMail::getTo() const {
    return to;
}

const String &CMail::getBody() const {
    return body;
}

class Person{
public:
    String email;
    Vector<CMail> iEmails;
    Vector<CMail> oEmails;

    Person() : email(), iEmails(), oEmails() {};
    Person(const String& email) : email(email), iEmails(), oEmails() {};
    Person(const Person& src){
        email = src.email;
        iEmails = src.iEmails;
        oEmails = src.oEmails;
    }
    Person& operator=(const Person& src){
        email = src.email;
        iEmails = src.iEmails;
        oEmails = src.oEmails;

        return *this;
    }
};

int compare(const Person& person1, const Person& person2){
    int res;

    if (person1.email < person2.email){
        res = 1;
    }
    else if (person1.email == person2.email){
        res = 0;
    }
    else{
        res = -1;
    }

    return res;
}

template<typename T>
int lower_bound(const Vector<T>& arr, const T& value){
    int mid;

    int low = 0;
    int high = arr.size() - 1;

    while (low < high) {
        mid = low + (high - low) / 2;
        int cmp = compare(value, arr[mid]);

        if (cmp >= 0 ) {
            high = mid;
        }

        else {
            low = mid + 1;
        }
    }

    if (!arr.isEmpty()) {
        bool flag = false;
        int cmp = compare(arr[low], value);
        if (cmp > 0) flag = true;
        if (low < int(arr.size()) && flag) {
            low++;
        }
    }

    return low;
}

template<typename T>
bool bin_search(const Vector<T>& arr, const T& value){
    int mid;

    int low = 0;
    int high = arr.size() - 1;

    while (low < high) {
        mid = low + (high - low) / 2;
        int cmp = compare(value, arr[mid]);

        if (cmp == 0) {
            return true;
        }

        else if (cmp > 0) {
            high = mid;
        }

        else {
            low = mid + 1;
        }
    }

    return false;
}

class CMailIterator 
{
  public:
    CMailIterator() : idx(0), mails() {};
    CMailIterator(const CMailIterator& iterator);
    CMailIterator(const Vector<CMail>& iMails);
    CMailIterator& operator=(const CMailIterator& iterator);
    explicit                 operator bool                 ( void ) const;
    bool                     operator !                    ( void ) const;
    const CMail            & operator *                    ( void ) const;
    CMailIterator          & operator ++                   ( void );

    size_t getIdx() const;

    const Vector<CMail> &getMails() const;

private:
    size_t idx;
    Vector<CMail> mails;
};

CMailIterator::CMailIterator(const CMailIterator& iterator) {
    idx = iterator.getIdx();
    mails = iterator.getMails();
}

CMailIterator& CMailIterator::operator=(const CMailIterator& iterator) {
   mails = iterator.getMails();
   idx = iterator.getIdx();

    return *this;
}

CMailIterator::CMailIterator(const Vector<CMail> &iMails) {
    idx = 0;
    mails = iMails;
}

CMailIterator::operator bool() const {
    return idx < mails.size();
}

bool CMailIterator::operator!() const {
    return idx >= mails.size();
}

const CMail& CMailIterator::operator*() const {
    return mails[idx];
}

CMailIterator& CMailIterator::operator++() {
    idx += 1;

    return *this;
}

size_t CMailIterator::getIdx() const {
    return idx;
}

const Vector<CMail> &CMailIterator::getMails() const {
    return mails;
}

class CMailServer 
{
  public:
                             CMailServer                   ( void ) = default;
                             CMailServer                   ( const CMailServer & src );
    CMailServer            & operator =                    ( const CMailServer & src );
                             ~CMailServer                  ( void ) = default;
    void                     sendMail                      ( const CMail     & m );
    CMailIterator            outbox                        ( const char      * email ) const;
    CMailIterator            inbox                         ( const char      * email ) const;

    const Vector<Person> &getUsers() const;

private:
    Vector<Person> users;
};

CMailServer::CMailServer(const CMailServer &src) {
    users = src.getUsers();
}

CMailServer &CMailServer::operator=(const CMailServer &src) {
    users = src.getUsers();

    return *this;
}

void CMailServer::sendMail(const CMail& m) {
    bool flag = bin_search(users, Person(m.getFrom()));
    int idx = lower_bound(users, Person(m.getFrom()));
    if (!flag){
        if (users.isEmpty()){
            users.pushBack(Person(m.getFrom()));
        }
        else {
            users.insert(idx, Person(m.getFrom()));
        }
    }
    users[idx].oEmails.pushBack(m);

    flag = bin_search(users, Person(m.getTo()));
    idx = lower_bound(users, Person(m.getTo()));
    if (!flag){
        if (users.isEmpty()){
            users.pushBack(Person(m.getTo()));
        }
        else {
            users.insert(idx, Person(m.getTo()));
        }
    }
    users[idx].iEmails.pushBack(m);
}

CMailIterator CMailServer::outbox(const char *email) const {
    bool flag = bin_search(users, Person(String(email)));

    if (!flag){
        CMailIterator iterator;
        return iterator;
    }
    else{
        int idx = lower_bound(users, Person(String(email)));
        CMailIterator iterator(users[idx].oEmails);
        return iterator;
    }
}

CMailIterator CMailServer::inbox(const char *email) const {
    bool flag = bin_search(users, Person(String(email)));

    if (!flag){
        CMailIterator iterator;
        return iterator;
    }
    else{
        int idx = lower_bound(users, Person(String(email)));
        CMailIterator iterator(users[idx].iEmails);
        return iterator;
    }
}

const Vector<Person> &CMailServer::getUsers() const {
    return users;
}

#ifndef __PROGTEST__
bool                         matchOutput                   ( const CMail     & m,
                                                             const char      * str )
{
  ostringstream oss;
  oss << m;
  return oss . str () == str;
}

int main ( void )
{
  char from[100], to[100], body[1024];

  Vector<Person> vec;

  assert ( CMail ( "john", "peter", "progtest deadline" ) == CMail ( "john", "peter", "progtest deadline" ) );
  assert ( !( CMail ( "john", "peter", "progtest deadline" ) == CMail ( "john", "progtest deadline", "peter" ) ) );
  assert ( !( CMail ( "john", "peter", "progtest deadline" ) == CMail ( "peter", "john", "progtest deadline" ) ) );
  assert ( !( CMail ( "john", "peter", "progtest deadline" ) == CMail ( "peter", "progtest deadline", "john" ) ) );
  assert ( !( CMail ( "john", "peter", "progtest deadline" ) == CMail ( "progtest deadline", "john", "peter" ) ) );
  assert ( !( CMail ( "john", "peter", "progtest deadline" ) == CMail ( "progtest deadline", "peter", "john" ) ) );
  CMailServer s0;
  s0 . sendMail ( CMail ( "john", "peter", "some important mail" ) );
  strncpy ( from, "john", sizeof ( from ) );
    strncpy ( to, "thomas", sizeof ( to ) );
    strncpy ( body, "another important mail", sizeof ( body ) );
    s0 . sendMail ( CMail ( from, to, body ) );
    strncpy ( from, "john", sizeof ( from ) );
    strncpy ( to, "alice", sizeof ( to ) );
    strncpy ( body, "deadline notice", sizeof ( body ) );
    s0 . sendMail ( CMail ( from, to, body ) );
    s0 . sendMail ( CMail ( "alice", "john", "deadline confirmation" ) );
    s0 . sendMail ( CMail ( "peter", "alice", "PR bullshit" ) );
    CMailIterator i0 = s0 . inbox ( "alice" );
    assert ( i0 && *i0 == CMail ( "john", "alice", "deadline notice" ) );
    assert ( matchOutput ( *i0,  "From: john, To: alice, Body: deadline notice" ) );
    assert ( ++i0 && *i0 == CMail ( "peter", "alice", "PR bullshit" ) );
    assert ( matchOutput ( *i0,  "From: peter, To: alice, Body: PR bullshit" ) );
    assert ( ! ++i0 );

  CMailIterator i1 = s0 . inbox ( "john" );
  assert ( i1 && *i1 == CMail ( "alice", "john", "deadline confirmation" ) );
  assert ( matchOutput ( *i1,  "From: alice, To: john, Body: deadline confirmation" ) );
  assert ( ! ++i1 );

  CMailIterator i2 = s0 . outbox ( "john" );
  assert ( i2 && *i2 == CMail ( "john", "peter", "some important mail" ) );
  assert ( matchOutput ( *i2,  "From: john, To: peter, Body: some important mail" ) );
  assert ( ++i2 && *i2 == CMail ( "john", "thomas", "another important mail" ) );
  assert ( matchOutput ( *i2,  "From: john, To: thomas, Body: another important mail" ) );
  assert ( ++i2 && *i2 == CMail ( "john", "alice", "deadline notice" ) );
  assert ( matchOutput ( *i2,  "From: john, To: alice, Body: deadline notice" ) );
  assert ( ! ++i2 );

  CMailIterator i3 = s0 . outbox ( "thomas" );
  assert ( ! i3 );

  CMailIterator i4 = s0 . outbox ( "steve" );
  assert ( ! i4 );

  CMailIterator i5 = s0 . outbox ( "thomas" );
  s0 . sendMail ( CMail ( "thomas", "boss", "daily report" ) );
  assert ( ! i5 );

  CMailIterator i6 = s0 . outbox ( "thomas" );
  assert ( i6 && *i6 == CMail ( "thomas", "boss", "daily report" ) );
  assert ( matchOutput ( *i6,  "From: thomas, To: boss, Body: daily report" ) );
  assert ( ! ++i6 );

  CMailIterator i7 = s0 . inbox ( "alice" );
  s0 . sendMail ( CMail ( "thomas", "alice", "meeting details" ) );
  assert ( i7 && *i7 == CMail ( "john", "alice", "deadline notice" ) );
  assert ( matchOutput ( *i7,  "From: john, To: alice, Body: deadline notice" ) );
  assert ( ++i7 && *i7 == CMail ( "peter", "alice", "PR bullshit" ) );
  assert ( matchOutput ( *i7,  "From: peter, To: alice, Body: PR bullshit" ) );
  assert ( ! ++i7 );

  CMailIterator i8 = s0 . inbox ( "alice" );
  assert ( i8 && *i8 == CMail ( "john", "alice", "deadline notice" ) );
  assert ( matchOutput ( *i8,  "From: john, To: alice, Body: deadline notice" ) );
  assert ( ++i8 && *i8 == CMail ( "peter", "alice", "PR bullshit" ) );
  assert ( matchOutput ( *i8,  "From: peter, To: alice, Body: PR bullshit" ) );
  assert ( ++i8 && *i8 == CMail ( "thomas", "alice", "meeting details" ) );
  assert ( matchOutput ( *i8,  "From: thomas, To: alice, Body: meeting details" ) );
  assert ( ! ++i8 );

  CMailServer s1 ( s0 );
  s0 . sendMail ( CMail ( "joe", "alice", "delivery details" ) );
  s1 . sendMail ( CMail ( "sam", "alice", "order confirmation" ) );
  CMailIterator i9 = s0 . inbox ( "alice" );
  assert ( i9 && *i9 == CMail ( "john", "alice", "deadline notice" ) );
  assert ( matchOutput ( *i9,  "From: john, To: alice, Body: deadline notice" ) );
  assert ( ++i9 && *i9 == CMail ( "peter", "alice", "PR bullshit" ) );
  assert ( matchOutput ( *i9,  "From: peter, To: alice, Body: PR bullshit" ) );
  assert ( ++i9 && *i9 == CMail ( "thomas", "alice", "meeting details" ) );
  assert ( matchOutput ( *i9,  "From: thomas, To: alice, Body: meeting details" ) );
  assert ( ++i9 && *i9 == CMail ( "joe", "alice", "delivery details" ) );
  assert ( matchOutput ( *i9,  "From: joe, To: alice, Body: delivery details" ) );
  assert ( ! ++i9 );

  CMailIterator i10 = s1 . inbox ( "alice" );
  assert ( i10 && *i10 == CMail ( "john", "alice", "deadline notice" ) );
  assert ( matchOutput ( *i10,  "From: john, To: alice, Body: deadline notice" ) );
  assert ( ++i10 && *i10 == CMail ( "peter", "alice", "PR bullshit" ) );
  assert ( matchOutput ( *i10,  "From: peter, To: alice, Body: PR bullshit" ) );
  assert ( ++i10 && *i10 == CMail ( "thomas", "alice", "meeting details" ) );
  assert ( matchOutput ( *i10,  "From: thomas, To: alice, Body: meeting details" ) );
  assert ( ++i10 && *i10 == CMail ( "sam", "alice", "order confirmation" ) );
  assert ( matchOutput ( *i10,  "From: sam, To: alice, Body: order confirmation" ) );
  assert ( ! ++i10 );

  CMailServer s2;
  s2 . sendMail ( CMail ( "alice", "alice", "mailbox test" ) );
  CMailIterator i11 = s2 . inbox ( "alice" );
  assert ( i11 && *i11 == CMail ( "alice", "alice", "mailbox test" ) );
  assert ( matchOutput ( *i11,  "From: alice, To: alice, Body: mailbox test" ) );
  assert ( ! ++i11 );

  s2 = s0;
  s0 . sendMail ( CMail ( "steve", "alice", "newsletter" ) );
  s2 . sendMail ( CMail ( "paul", "alice", "invalid invoice" ) );
  CMailIterator i12 = s0 . inbox ( "alice" );
  assert ( i12 && *i12 == CMail ( "john", "alice", "deadline notice" ) );
  assert ( matchOutput ( *i12,  "From: john, To: alice, Body: deadline notice" ) );
  assert ( ++i12 && *i12 == CMail ( "peter", "alice", "PR bullshit" ) );
  assert ( matchOutput ( *i12,  "From: peter, To: alice, Body: PR bullshit" ) );
  assert ( ++i12 && *i12 == CMail ( "thomas", "alice", "meeting details" ) );
  assert ( matchOutput ( *i12,  "From: thomas, To: alice, Body: meeting details" ) );
  assert ( ++i12 && *i12 == CMail ( "joe", "alice", "delivery details" ) );
  assert ( matchOutput ( *i12,  "From: joe, To: alice, Body: delivery details" ) );
  assert ( ++i12 && *i12 == CMail ( "steve", "alice", "newsletter" ) );
  assert ( matchOutput ( *i12,  "From: steve, To: alice, Body: newsletter" ) );
  assert ( ! ++i12 );

  CMailIterator i13 = s2 . inbox ( "alice" );
  assert ( i13 && *i13 == CMail ( "john", "alice", "deadline notice" ) );
  assert ( matchOutput ( *i13,  "From: john, To: alice, Body: deadline notice" ) );
  assert ( ++i13 && *i13 == CMail ( "peter", "alice", "PR bullshit" ) );
  assert ( matchOutput ( *i13,  "From: peter, To: alice, Body: PR bullshit" ) );
  assert ( ++i13 && *i13 == CMail ( "thomas", "alice", "meeting details" ) );
  assert ( matchOutput ( *i13,  "From: thomas, To: alice, Body: meeting details" ) );
  assert ( ++i13 && *i13 == CMail ( "joe", "alice", "delivery details" ) );
  assert ( matchOutput ( *i13,  "From: joe, To: alice, Body: delivery details" ) );
  assert ( ++i13 && *i13 == CMail ( "paul", "alice", "invalid invoice" ) );
  assert ( matchOutput ( *i13,  "From: paul, To: alice, Body: invalid invoice" ) );
  assert ( ! ++i13 );
  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
