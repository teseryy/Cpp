#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <set>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <iterator>
#include <functional>
using namespace std;

class CDate
{
public:
    //---------------------------------------------------------------------------------------------
    CDate                         ( int               y,
                                    int               m,
                                    int               d )
            : m_Year ( y ),
              m_Month ( m ),
              m_Day ( d )
    {
    }
    //---------------------------------------------------------------------------------------------
    int                      compare                       ( const CDate     & x ) const
    {
        if ( m_Year != x . m_Year )
            return m_Year - x . m_Year;
        if ( m_Month != x . m_Month )
            return m_Month - x . m_Month;
        return m_Day - x . m_Day;
    }
    //---------------------------------------------------------------------------------------------
    int                      year                          ( void ) const
    {
        return m_Year;
    }
    //---------------------------------------------------------------------------------------------
    int                      month                         ( void ) const
    {
        return m_Month;
    }
    //---------------------------------------------------------------------------------------------
    int                      day                           ( void ) const
    {
        return m_Day;
    }
    //---------------------------------------------------------------------------------------------
    friend ostream         & operator <<                   ( ostream         & os,
                                                             const CDate     & x )
    {
        char oldFill = os . fill ();
        return os << setfill ( '0' ) << setw ( 4 ) << x . m_Year << "-"
                  << setw ( 2 ) << static_cast<int> ( x . m_Month ) << "-"
                  << setw ( 2 ) << static_cast<int> ( x . m_Day )
                  << setfill ( oldFill );
    }
    //---------------------------------------------------------------------------------------------
private:
    int16_t                  m_Year;
    int8_t                   m_Month;
    int8_t                   m_Day;
};
#endif /* __PROGTEST__ */

bool isSpace(char symb){
    return (symb == ' ' || symb == '\n' || symb == '\t' || symb == '\r');
}

string normalisedString(const string& original){
    string normalised;
    int len = original.length();

    while (isSpace(original[len-1])){
        len--;
    }

    int start = 0;
    while (isSpace(original[start])){
        start++;
    }

    string newStr(original.c_str() + start, original.c_str() + len);
    int counter = 0;
    for (char symb : newStr){
        if (isSpace(symb)){
            counter += 1;
            if (counter <= 1){
                normalised.push_back(symb);
            }
        }
        else{
            counter = 0;
            normalised.push_back(symb);
        }
    }

    return normalised;
}

/*int nameComparator(const string& fName, const string& sName){
    string fNameNormalised = normalisedString(fName);
    string sNameNormalised = normalisedString(sName);

    return strcasecmp(fNameNormalised.c_str(), sNameNormalised.c_str());
}*/

class CmpNames{
public:
    bool operator() (const string& fName, const string& sName){
        return strcasecmp(fName.c_str(), sName.c_str()) < 0;
    }

    bool operator() (const string& fName, const string& sName) const{
        return strcasecmp(fName.c_str(), sName.c_str()) < 0;
    }
};

class CInvoice
{
public:
    CInvoice                      ( const CDate     & date,
                                    const string    & seller,
                                    const string    & buyer,
                                    unsigned int      amount,
                                    double            vat ) : m_Date(date), m_Seller(seller), m_Buyer(buyer), m_Amount(amount), m_Vat(vat), addedState(0) {};
    CDate                    date                          ( void ) const;
    string                   buyer                         ( void ) const;
    string                   seller                        ( void ) const;
    unsigned int             amount                        ( void ) const;
    double                   vat                           ( void ) const;

    friend bool operator ==(const CInvoice& fInvoice, const CInvoice& sInvoice);
    friend bool operator <(const CInvoice& fInvoice, const CInvoice& sInvoice);

    void setAddedState(int state);
    int getAddedState() const;

    void setMSeller(const string &mSeller);

    void setMBuyer(const string &mBuyer);

private:
    CDate m_Date;
    string m_Seller;
    string m_Buyer;
    unsigned int m_Amount;
    double m_Vat;
    int addedState;
};

CDate CInvoice::date( void ) const {
    return m_Date;
}

string CInvoice::buyer( void ) const {
    return m_Buyer;
}

string CInvoice::seller( void ) const {
    return m_Seller;
}

unsigned int CInvoice::amount( void ) const {
    return m_Amount;
}

double CInvoice::vat( void ) const {
    return m_Vat;
}

/*bool operator==(const CInvoice &fInvoice, const CInvoice &sInvoice) {
    if (nameComparator(fInvoice.seller(), sInvoice.seller()) != 0){
        return false;
    }
    if (nameComparator(fInvoice.buyer(), sInvoice.buyer()) != 0){
        return false;
    }
    if (fInvoice.amount() != sInvoice.amount()){
        return false;
    }
    if (fInvoice.vat() != sInvoice.vat()){
        return false;
    }
    if (fInvoice.date().compare(sInvoice.date()) != 0){
        return false;
    }

    return true;
}*/

bool operator<(const CInvoice &fInvoice, const CInvoice &sInvoice) {
    if (fInvoice.seller() != sInvoice.seller()){
        if (fInvoice.seller() < sInvoice.seller()) {
            return true;
        }
        else{
            return false;
        }
    }
    if (fInvoice.buyer() != sInvoice.buyer()){
        if (fInvoice.buyer() < sInvoice.buyer()) {
            return true;
        }
        else{
            return false;
        }
    }
    if (fInvoice.amount() != sInvoice.amount()){
        if (fInvoice.amount() < sInvoice.amount()) {
            return true;
        }
        else{
            return false;
        }
    }
    if (fInvoice.vat() != sInvoice.vat()){
        if (fInvoice.vat() < sInvoice.vat()) {
            return true;
        }
        else{
            return false;
        }
    }
    int res = fInvoice.date().compare(sInvoice.date());
    if (res < 0){
        return true;
    }

    return false;
}

void CInvoice::setMSeller(const string &mSeller) {
    m_Seller = mSeller;
}

void CInvoice::setMBuyer(const string &mBuyer) {
    m_Buyer = mBuyer;
}

void CInvoice::setAddedState(int state) {
    CInvoice::addedState = state;
}

int CInvoice::getAddedState() const {
    return addedState;
}

class CmpInv{
public:
    bool operator() (const CInvoice& fInvoice, const CInvoice& sInvoice){
        return fInvoice < sInvoice;
    }

    bool operator() (const CInvoice& fInvoice, const CInvoice& sInvoice) const{
        return fInvoice < sInvoice;
    }
};

class CSortOpt
{
public:
    static const int         BY_DATE                       = 0;
    static const int         BY_BUYER                      = 1;
    static const int         BY_SELLER                     = 2;
    static const int         BY_AMOUNT                     = 3;
    static const int         BY_VAT                        = 4;
    CSortOpt                      ( void ) {};
    CSortOpt               & addKey                        ( int               key,
                                                             bool              ascending = true );

    const vector<pair<int, bool>> &getKeys() const;
    bool operator() (const CInvoice& fInvoice, const CInvoice& sInvoice) const;
private:
    vector<pair<int, bool>> keys;
};

CSortOpt &CSortOpt::addKey(int key, bool ascending) {
    pair<int, bool> pair;
    pair = make_pair(key, ascending);

    keys.push_back(pair);

    return *this;
}

const vector<pair<int, bool>> &CSortOpt::getKeys() const {
    return keys;
}

bool CSortOpt::operator() (const CInvoice& fInvoice, const CInvoice& sInvoice) const{
    size_t len = keys.size();
    int res = 0;

    for (int i = 0; i < int(len); i++){
        if (keys[i].second){
            switch (keys[i].first) {
                case 0:
                    res = fInvoice.date().compare(sInvoice.date());
                    if (res != 0){
                        return res < 0;
                    }
                    break;
                case 1:
                    res = strcasecmp(fInvoice.buyer().c_str(), sInvoice.buyer().c_str());
                    if (res != 0) {
                        return  res < 0;
                    }
                    break;
                case 2:
                    res = strcasecmp(fInvoice.seller().c_str(), sInvoice.seller().c_str());
                    if (res != 0) {
                        return res < 0;
                    }
                    break;
                case 3:
                    if (fInvoice.amount() != sInvoice.amount()) {
                        return fInvoice.amount() < sInvoice.amount();
                    }
                    break;
                case 4:
                    if (fInvoice.vat() != sInvoice.vat()) {
                        return fInvoice.vat() < sInvoice.vat();
                    }
                    break;
            }
        }
        else{
            switch (keys[i].first) {
                case 0:
                    res = fInvoice.date().compare(sInvoice.date());
                    if (res != 0){
                        return res > 0;
                    }
                    break;
                case 1:
                    res = strcasecmp(fInvoice.buyer().c_str(), sInvoice.buyer().c_str());
                    if (res != 0) {
                        return  res > 0;
                    }
                    break;
                case 2:
                    res = strcasecmp(fInvoice.seller().c_str(), sInvoice.seller().c_str());
                    if (res != 0) {
                        return res > 0;
                    }
                    break;
                case 3:
                    if (fInvoice.amount() != sInvoice.amount()) {
                        return fInvoice.amount() > sInvoice.amount();
                    }
                    break;
                case 4:
                    if (fInvoice.vat() != sInvoice.vat()) {
                        return fInvoice.vat() > sInvoice.vat();
                    }
                    break;
            }
        }
    }

    return fInvoice.getAddedState() < sInvoice.getAddedState();
}

class CVATRegister
{
public:
    CVATRegister                  ( void ) = default;
    bool                     registerCompany               ( const string    & name );
    bool                     addIssued                     ( const CInvoice & x );
    bool                     addAccepted                   ( const CInvoice & x );
    bool                     delIssued                     ( const CInvoice  & x );
    bool                     delAccepted                   ( const CInvoice  & x );
    list<CInvoice>           unmatched                     ( const string    & company,
                                                             const CSortOpt  & sortBy ) const;
    void print();
private:
    int counter = 0;

    map<string, string, CmpNames> originalNames;

    mutable map<string, pair<set<CInvoice, CmpInv>, set<CInvoice, CmpInv>>, CmpNames> invoices;

};

bool CVATRegister::registerCompany(const std::string &name) {
    string normalisedName = normalisedString(name);

    auto it = originalNames.find(normalisedName);
    if (it == originalNames.end()){
        originalNames.insert(make_pair(normalisedName, name));
        set<CInvoice, CmpInv> issued;
        set<CInvoice,CmpInv> accepted;
        invoices.insert(make_pair(normalisedName, make_pair(issued, accepted)));
        return true;
    }

    return false;
}

bool CVATRegister::addIssued(const CInvoice & x) {
    string normalisedBuyer = normalisedString(x.buyer());
    auto buyer = originalNames.find(normalisedBuyer);
    if (buyer == originalNames.end()){
        return false;
    }

    string normalisedSeller = normalisedString(x.seller());
    auto seller = originalNames.find(normalisedSeller);
    if (seller == originalNames.end()){
        return false;
    }

    if (seller->second == buyer->second){
        return false;
    }

    CInvoice ins = CInvoice(x.date(), seller->second, buyer->second, x.amount(), x.vat());
    auto issuedItem = invoices[normalisedSeller].first.find(ins);
    if (issuedItem == invoices[normalisedSeller].first.end()){
        ins.setAddedState(counter);
        counter += 1;
        auto inName = invoices[normalisedSeller].first.insert(ins);
        inName = invoices[normalisedBuyer].first.insert(ins);

        return true;
    }

    return false;
}

bool CVATRegister::addAccepted(const CInvoice& x) {
    string normalisedBuyer = normalisedString(x.buyer());
    auto buyer = originalNames.find(normalisedBuyer);
    if (buyer == originalNames.end()){
        return false;
    }

    string normalisedSeller = normalisedString(x.seller());
    auto seller = originalNames.find(normalisedSeller);
    if (seller == originalNames.end()){
        return false;
    }

    if (seller->second == buyer->second){
        return false;
    }

    CInvoice ins = CInvoice(x.date(), seller->second, buyer->second, x.amount(), x.vat());
    auto issuedItem = invoices[normalisedBuyer].second.find(ins);
    if (issuedItem == invoices[normalisedBuyer].second.end()){
        ins.setAddedState(counter);
        counter += 1;
        auto inName = invoices[normalisedBuyer].second.insert(ins);
        inName = invoices[normalisedSeller].second.insert(ins);

        return true;
    }

    return false;
}

bool CVATRegister::delIssued(const CInvoice &x) {
    string normalisedBuyer = normalisedString(x.buyer());
    auto buyer = originalNames.find(normalisedBuyer);
    if (buyer == originalNames.end()){
        return false;
    }

    string normalisedSeller = normalisedString(x.seller());
    auto seller = originalNames.find(normalisedSeller);
    if (seller == originalNames.end()){
        return false;
    }

    CInvoice ins = CInvoice(x.date(), seller->second, buyer->second, x.amount(), x.vat());
    auto issuedItem = invoices[normalisedSeller].first.find(ins);
    if (issuedItem != invoices[normalisedSeller].first.end()){
        invoices[normalisedSeller].first.erase(ins);
        invoices[normalisedBuyer].first.erase(ins);

        return true;
    }

    return false;
}

bool CVATRegister::delAccepted(const CInvoice &x) {
    string normalisedBuyer = normalisedString(x.buyer());
    auto buyer = originalNames.find(normalisedBuyer);
    if (buyer == originalNames.end()){
        return false;
    }

    string normalisedSeller = normalisedString(x.seller());
    auto seller = originalNames.find(normalisedSeller);
    if (seller == originalNames.end()){
        return false;
    }

    CInvoice ins = CInvoice(x.date(), seller->second, buyer->second, x.amount(), x.vat());
    auto issuedItem = invoices[normalisedBuyer].second.find(ins);
    if (issuedItem != invoices[normalisedBuyer].second.end()){
        invoices[normalisedBuyer].second.erase(ins);
        invoices[normalisedSeller].second.erase(ins);

        return true;
    }

    return false;
}

list<CInvoice> CVATRegister::unmatched(const string &company, const CSortOpt &sortBy) const {
    list<CInvoice> unmatch;

    string normalisedBuyer = normalisedString(company);

    set<CInvoice, CmpInv> diff;

    set_difference(invoices[normalisedBuyer].first.begin(), invoices[normalisedBuyer].first.end(),
                   invoices[normalisedBuyer].second.begin(), invoices[normalisedBuyer].second.end(),
                   inserter(diff, diff.end()));

    set_difference(invoices[normalisedBuyer].second.begin(), invoices[normalisedBuyer].second.end(),
                   invoices[normalisedBuyer].first.begin(), invoices[normalisedBuyer].first.end(),
                   inserter(diff, diff.end()));

    for (const auto & it : diff){
        unmatch.push_back(it);
    }

    unmatch.sort(sortBy);

    return unmatch;
}



/*void CVATRegister::print() {
    for (auto & it : issued){
        cout << "date : " << it.date() << ", fComp : " << it.seller() << ", sComp : " << it.buyer() << ", amount : " << it.amount() << ", vat : " << it.vat() << ", idx : " << it.getAddedState() << endl;
    }
}*/


#ifndef __PROGTEST__
/*bool equalLists ( const list<CInvoice> & a, const list<CInvoice> & b )
{
  // todo
}*/

int main ( void )
{

    CVATRegister r;
    assert ( r . registerCompany ( "first Company" ) );
    assert ( r . registerCompany ( "Second     Company" ) );
    assert ( r . registerCompany ( "ThirdCompany, Ltd." ) );
    assert ( r . registerCompany ( "Third Company, Ltd." ) );
    assert ( !r . registerCompany ( "Third Company, Ltd." ) );
    assert ( !r . registerCompany ( " Third  Company,  Ltd.  " ) );
    assert ( r . addIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", "Second Company ", 100, 20 ) ) );
    assert ( r . addIssued ( CInvoice ( CDate ( 2000, 1, 2 ), "FirSt Company", "Second Company ", 200, 30 ) ) );
    assert ( r . addIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", "Second Company ", 100, 30 ) ) );
    assert ( r . addIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", "Second Company ", 300, 30 ) ) );
    assert ( r . addIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", " Third  Company,  Ltd.   ", 200, 30 ) ) );
    assert ( r . addIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "Second Company ", "First Company", 300, 30 ) ) );
    assert ( r . addIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "Third  Company,  Ltd.", "  Second    COMPANY ", 400, 34 ) ) );
    assert ( !r . addIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", "Second Company ", 300, 30 ) ) );
    assert ( !r . addIssued ( CInvoice ( CDate ( 2000, 1, 4 ), "First Company", "First   Company", 200, 30 ) ) );
    assert ( !r . addIssued ( CInvoice ( CDate ( 2000, 1, 4 ), "Another Company", "First   Company", 200, 30 ) ) );

    //r.print();
    assert ( equalLists ( r . unmatched ( "First Company", CSortOpt () . addKey ( CSortOpt::BY_SELLER, true ) . addKey ( CSortOpt::BY_BUYER, false ) . addKey ( CSortOpt::BY_DATE, false ) ),
             list<CInvoice>
             {
               CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Third Company, Ltd.", 200, 30.000000 ),
               CInvoice ( CDate ( 2000, 1, 2 ), "first Company", "Second     Company", 200, 30.000000 ),
               CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 20.000000 ),
               CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 30.000000 ),
               CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 300, 30.000000 ),
               CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 30.000000 )
             } ) );
    assert ( equalLists ( r . unmatched ( "First Company", CSortOpt () . addKey ( CSortOpt::BY_DATE, true ) . addKey ( CSortOpt::BY_SELLER, true ) . addKey ( CSortOpt::BY_BUYER, true ) ),
             list<CInvoice>
             {
               CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 20.000000 ),
               CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 30.000000 ),
               CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 300, 30.000000 ),
               CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Third Company, Ltd.", 200, 30.000000 ),
               CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 30.000000 ),
               CInvoice ( CDate ( 2000, 1, 2 ), "first Company", "Second     Company", 200, 30.000000 )
             } ) );
    assert ( equalLists ( r . unmatched ( "First Company", CSortOpt () . addKey ( CSortOpt::BY_VAT, true ) . addKey ( CSortOpt::BY_AMOUNT, true ) . addKey ( CSortOpt::BY_DATE, true ) . addKey ( CSortOpt::BY_SELLER, true ) . addKey ( CSortOpt::BY_BUYER, true ) ),
             list<CInvoice>
             {
               CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 20.000000 ),
               CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 30.000000 ),
               CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Third Company, Ltd.", 200, 30.000000 ),
               CInvoice ( CDate ( 2000, 1, 2 ), "first Company", "Second     Company", 200, 30.000000 ),
               CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 300, 30.000000 ),
               CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 30.000000 )
             } ) );
    assert ( equalLists ( r . unmatched ( "First Company", CSortOpt () ),
             list<CInvoice>
             {
               CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 20.000000 ),
               CInvoice ( CDate ( 2000, 1, 2 ), "first Company", "Second     Company", 200, 30.000000 ),
               CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 30.000000 ),
               CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 300, 30.000000 ),
               CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Third Company, Ltd.", 200, 30.000000 ),
               CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 30.000000 )
             } ) );
    assert ( equalLists ( r . unmatched ( "second company", CSortOpt () . addKey ( CSortOpt::BY_DATE, false ) ),
             list<CInvoice>
             {
               CInvoice ( CDate ( 2000, 1, 2 ), "first Company", "Second     Company", 200, 30.000000 ),
               CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 20.000000 ),
               CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 30.000000 ),
               CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 300, 30.000000 ),
               CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 30.000000 ),
               CInvoice ( CDate ( 2000, 1, 1 ), "Third Company, Ltd.", "Second     Company", 400, 34.000000 )
             } ) );
    assert ( equalLists ( r . unmatched ( "last company", CSortOpt () . addKey ( CSortOpt::BY_VAT, true ) ),
             list<CInvoice>
             {
             } ) );
    assert ( r . addAccepted ( CInvoice ( CDate ( 2000, 1, 2 ), "First Company", "Second Company ", 200, 30 ) ) );
    assert ( r . addAccepted ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", " Third  Company,  Ltd.   ", 200, 30 ) ) );
    assert ( r . addAccepted ( CInvoice ( CDate ( 2000, 1, 1 ), "Second company ", "First Company", 300, 32 ) ) );

    assert ( equalLists ( r . unmatched ( "First Company", CSortOpt () . addKey ( CSortOpt::BY_SELLER, true ) . addKey ( CSortOpt::BY_BUYER, true ) . addKey ( CSortOpt::BY_DATE, true ) ),
             list<CInvoice>
             {
               CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 20.000000 ),
               CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 30.000000 ),
               CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 300, 30.000000 ),
               CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 30.000000 ),
               CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 32.000000 )
             } ) );
    assert (!r.delIssued(CInvoice(CDate(2001, 1, 1), "First Company", "Second Company ", 200, 30)));
    assert ( !r . delIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "A First Company", "Second Company ", 200, 30 ) ) );
    assert ( !r . delIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", "Second Hand", 200, 30 ) ) );
    assert ( !r . delIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", "Second Company", 1200, 30 ) ) );
    assert ( !r . delIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", "Second Company", 200, 130 ) ) );
    assert ( r . delIssued ( CInvoice ( CDate ( 2000, 1, 2 ), "First Company", "Second Company", 200, 30 ) ) );
    assert ( equalLists ( r . unmatched ( "First Company", CSortOpt () . addKey ( CSortOpt::BY_SELLER, true ) . addKey ( CSortOpt::BY_BUYER, true ) . addKey ( CSortOpt::BY_DATE, true ) ),
             list<CInvoice>
             {
               CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 20.000000 ),
               CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 30.000000 ),
               CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 300, 30.000000 ),
               CInvoice ( CDate ( 2000, 1, 2 ), "first Company", "Second     Company", 200, 30.000000 ),
               CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 30.000000 ),
               CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 32.000000 )
             } ) );
    assert ( r . delAccepted ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", " Third  Company,  Ltd.   ", 200, 30 ) ) );

    assert ( equalLists ( r . unmatched ( "First Company", CSortOpt () . addKey ( CSortOpt::BY_SELLER, true ) . addKey ( CSortOpt::BY_BUYER, true ) . addKey ( CSortOpt::BY_DATE, true ) ),
             list<CInvoice>
             {
               CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 20.000000 ),
               CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 30.000000 ),
               CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 300, 30.000000 ),
               CInvoice ( CDate ( 2000, 1, 2 ), "first Company", "Second     Company", 200, 30.000000 ),
               CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Third Company, Ltd.", 200, 30.000000 ),
               CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 30.000000 ),
               CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 32.000000 )
             } ) );
    assert ( r . delIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", " Third  Company,  Ltd.   ", 200, 30 ) ) );

    /*list<CInvoice> inv =  r . unmatched ( "First Company", CSortOpt () . addKey ( CSortOpt::BY_SELLER, true ) . addKey ( CSortOpt::BY_BUYER, true ) . addKey ( CSortOpt::BY_DATE, true ) );
    for (auto & it : inv){
        cout << "date : " << it.date() << ", fComp : " << it.seller() << ", sComp : " << it.buyer() << ", amount : " << it.amount() << ", vat : " << it.vat() << ", idx : " << it.getAddedState() << endl;
    }*/
    assert ( equalLists ( r . unmatched ( "First Company", CSortOpt () . addKey ( CSortOpt::BY_SELLER, true ) . addKey ( CSortOpt::BY_BUYER, true ) . addKey ( CSortOpt::BY_DATE, true ) ),
             list<CInvoice>
             {
               CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 20.000000 ),
               CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 30.000000 ),
               CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 300, 30.000000 ),
               CInvoice ( CDate ( 2000, 1, 2 ), "first Company", "Second     Company", 200, 30.000000 ),
               CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 30.000000 ),
               CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 32.000000 )
             } ) );
    return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */