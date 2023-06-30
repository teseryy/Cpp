#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <ctime>
#include <climits>
#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <stdexcept>
#include <memory>
using namespace std;
#endif /* __PROGTEST__ */

// uncomment if your code implements initializer lists
// #define EXTENDED_SYNTAX

class CRange{
  public:
    CRange(long long lo , long long hi){
        if (lo > hi){
            throw logic_error("ERROR");
        }
        else{
            this->hi = hi;
            this->lo = lo;
        }
    }

    long long int getLo() const {
        return lo;
    }

    long long int getHi() const {
        return hi;
    }

    void setLo(long long int lo) {
        CRange::lo = lo;
    }

    void setHi(long long int hi) {
        CRange::hi = hi;
    }
private:
    long long lo, hi;
};

class CmpRange{
public:
    bool operator()(const CRange& range1, const CRange& range2 ) {
        return range1.getLo() < range2.getLo();
    }
};


class CRangeList{
  public:
    CRangeList() {};

    bool includes (long long element) const;
    bool includes (CRange range) const;

    CRangeList & operator+=(const CRange & range);
    CRangeList & operator+=(const CRangeList & a);
    CRangeList & operator-=(const CRange & range);
    CRangeList & operator-=(const CRangeList & a);
    CRangeList & operator=(const CRange & range);
    CRangeList & operator=(const CRangeList & a);
    bool operator==(const CRangeList & a) const;
    bool operator!=(const CRangeList & a) const;
    friend ostringstream & operator<<(ostringstream & oss, const CRangeList& x);

    void print();

    friend CRangeList operator+(const CRange & a, const CRange & b);
    friend CRangeList operator+(const CRangeList & a, const CRange & b);

    friend CRangeList operator-(const CRange & a, const CRange & b);
    friend CRangeList operator-(const CRangeList & a, const CRange & b);
  private:
    vector<CRange> ranges;
};

bool CRangeList::includes(long long element) const {
    int len = ranges.size();

    for (int i = 0; i < len; i++){
        if (element >= ranges[i].getLo() && element <= ranges[i].getHi()){
            return true;
        }
    }

    return false;
}
bool CRangeList::includes(CRange range) const {
    int len = ranges.size();

    for (int i = 0; i < len; i++){
        if (range.getLo() >= ranges[i].getLo() && range.getHi() <= ranges[i].getHi()){
            return true;
        }
    }

    return false;
}

CRangeList & CRangeList::operator=(const CRange & range) {
    if (!ranges.empty()){
        ranges.clear();
    }

    CRange newRange = CRange(range.getLo(), range.getHi());

    ranges.push_back(newRange);

    return *this;
}
CRangeList & CRangeList::operator=(const CRangeList & a) {
    if (!ranges.empty()){
        ranges.clear();
    }

    ranges = a.ranges;

    return *this;
}

CRangeList & CRangeList::operator+=(const CRange & range){
    int i = 1;

    auto itRange = lower_bound(ranges.begin(), ranges.end(), range, CmpRange());
    ranges.insert(itRange, range);

    itRange = lower_bound(ranges.begin(), ranges.end(), range, CmpRange());

    if (itRange != ranges.begin()){
        if (itRange->getHi() < (itRange - 1)->getHi()){
            itRange->setHi((itRange - 1)->getHi());
        }
        if (itRange->getLo() != LLONG_MIN) {
            if (itRange->getLo() - 1 <= (itRange - 1)->getHi()) {
                itRange->setLo((itRange - 1)->getLo());
                ranges.erase(itRange - 1);
                itRange--;
            }
        }
        else {
            ranges.erase(itRange - 1);
        }
    }

    while (itRange + i != ranges.end()){
        if (itRange->getHi() != LLONG_MAX) {
            if (itRange->getHi() + 1 >= (itRange + i)->getLo()) {
                if (itRange->getHi() + 1 > (itRange + i)->getHi()) {
                    ranges.erase(itRange + i);
                } else if (itRange->getHi() + 1 <= (itRange + i)->getHi()) {
                    itRange->setHi((itRange + i)->getHi());
                    ranges.erase(itRange + i);
                }
            } else {
                break;
            }
        }
        else{
            ranges.erase(itRange + i);
        }
    }

    return *this;
}
CRangeList & CRangeList::operator+=(const CRangeList & a){
    int len = a.ranges.size();

    for (int i = 0; i < len; i++){
        *this += a.ranges[i];
    }

    return *this;
}

CRangeList & CRangeList::operator-=(const CRange & range){
    int len = ranges.size();

    for (int i = 0; i < len; i++) {
        if (ranges[i].getLo() > range.getLo() && ranges[i].getLo() <= range.getHi()) {
            if (ranges[i].getHi() > range.getHi()) {
                ranges[i].setLo(range.getHi() + 1);
                break;
            }
            else if (ranges[i].getHi() < range.getHi()) {
                ranges.erase(ranges.begin() + i);
                len -= 1;
                i -= 1;
            }
            else if (ranges[i].getHi() == range.getHi()){
                ranges.erase(ranges.begin() + i);
                break;
            }
        }
        else if (ranges[i].getLo() == range.getLo()) {
            if (ranges[i].getHi() > range.getHi()) {
                ranges[i].setLo(range.getHi() + 1);
                break;
            }
            else if (ranges[i].getHi() == range.getHi()){
                ranges.erase(ranges.begin() + i);
                break;
            }
            else if (ranges[i].getHi() < range.getHi()) {
                ranges.erase(ranges.begin() + i);
                len -= 1;
                i -= 1;
            }
        }
        else if (ranges[i].getLo() < range.getLo() && ranges[i].getHi() >= range.getLo()){
            if (ranges[i].getHi() > range.getHi()){
                long long hi = ranges[i].getHi();
                ranges[i].setHi(range.getLo() - 1);
                ranges.insert(ranges.begin() + i + 1, CRange(range.getHi() + 1, hi));
                break;
            }
            else if (ranges[i].getHi() == range.getHi()){
                ranges[i].setHi(range.getLo() - 1);
                break;
            }
            else if (ranges[i].getHi() < range.getHi()){
                ranges[i].setHi(range.getLo() - 1);
            }
        }
    }

    return *this;
}
CRangeList & CRangeList::operator-=(const CRangeList & a){
    int len = a.ranges.size();

    for (int i = 0; i < len; i++){
        *this -= a.ranges[i];
    }

    return *this;
}

CRangeList operator+(const CRange & a, const CRange & b){
    CRangeList rangeList;

    rangeList = a;
    rangeList += b;

    return rangeList;
}
CRangeList operator+(const CRangeList & a, const CRange & b){
    CRangeList rangeList;

    rangeList = a;
    rangeList += b;

    return rangeList;
}

CRangeList operator-(const CRange & a, const CRange & b){
    CRangeList rangeList;

    rangeList = a;
    rangeList -= b;

    return rangeList;
}
CRangeList operator-(const CRangeList & a, const CRange & b){
    CRangeList rangeList;

    rangeList = a;
    rangeList -= b;

    return rangeList;
}

bool CRangeList::operator==(const CRangeList & a) const {
    int lenA = a.ranges.size();
    int lenR = ranges.size();

    if (lenA != lenR){
        return false;
    }

    for (int i = 0; i < lenA; i++){
        if (ranges[i].getLo() != a.ranges[i].getLo() || ranges[i].getHi() != a.ranges[i].getHi()){
            return false;
        }
    }

    return true;
}
bool CRangeList::operator!=(const CRangeList & a) const {
    return !(*this == a);
}

ostringstream & operator<<(ostringstream & oss, const CRangeList& x){
    int len = x.ranges.size();
    oss << "{";

    if (!x.ranges.empty()) {
        if (x.ranges[0].getHi() == x.ranges[0].getLo()) {
            oss << x.ranges[0].getHi();
        }
        else{
            oss << "<" << x.ranges[0].getLo() << ".." << x.ranges[0].getHi() << ">";
        }

        for (int i = 1; i < len; i++) {
            if (x.ranges[i].getHi() == x.ranges[i].getLo()) {
                oss << "," << x.ranges[i].getHi();
            } else {
                oss << "," << "<" << x.ranges[i].getLo() << ".." << x.ranges[i].getHi() << ">";
            }
        }
    }

    oss << "}";

    return oss;
}

void CRangeList::print(){
    for (auto range : ranges){
        cout << " lo : " << range.getLo() << " hi : " << range.getHi() << endl;
    }
}

#ifndef __PROGTEST__
string             toString                                ( const CRangeList& x )
{
  ostringstream oss;
  oss << x;
  return oss . str ();
}

int                main                                    ( void )
{
  CRangeList a, b;


  assert ( sizeof ( CRange ) <= 2 * sizeof ( long long ) );
  a = CRange ( 5, 10 );
  a += CRange ( 25, 100 );
  assert ( toString ( a ) == "{<5..10>,<25..100>}" );
  a += CRange ( -5, 0 );
  a += CRange ( 8, 50 );
  assert ( toString ( a ) == "{<-5..0>,<5..100>}" );
  a += CRange ( 101, 105 ) + CRange ( 120, 150 ) + CRange ( 160, 180 ) + CRange ( 190, 210 );
  assert ( toString ( a ) == "{<-5..0>,<5..105>,<120..150>,<160..180>,<190..210>}" );
  a += CRange ( 106, 119 ) + CRange ( 152, 158 );
  assert ( toString ( a ) == "{<-5..0>,<5..150>,<152..158>,<160..180>,<190..210>}" );
  a += CRange ( -3, 170 );
  a += CRange ( -30, 1000 );
  assert ( toString ( a ) == "{<-30..1000>}" );
  b = CRange ( -500, -300 ) + CRange ( 2000, 3000 ) + CRange ( 700, 1001 );
  a += b;
  assert ( toString ( a ) == "{<-500..-300>,<-30..1001>,<2000..3000>}" );
  a -= CRange ( -400, -400 );
  assert ( toString ( a ) == "{<-500..-401>,<-399..-300>,<-30..1001>,<2000..3000>}" );
  a -= CRange ( 10, 20 ) + CRange ( 900, 2500 ) + CRange ( 30, 40 ) + CRange ( 10000, 20000 );
  assert ( toString ( a ) == "{<-500..-401>,<-399..-300>,<-30..9>,<21..29>,<41..899>,<2501..3000>}" );
  try
  {
    a += CRange ( 15, 18 ) + CRange ( 10, 0 ) + CRange ( 35, 38 );
    assert ( "Exception not thrown" == nullptr );
  }
  catch ( const std::logic_error & e )
  {
  }
  catch ( ... )
  {
    assert ( "Invalid exception thrown" == nullptr );
  }
  assert ( toString ( a ) == "{<-500..-401>,<-399..-300>,<-30..9>,<21..29>,<41..899>,<2501..3000>}" );
  b = a;
  assert ( a == b );
  assert ( !( a != b ) );
  b += CRange ( 2600, 2700 );
  assert ( toString ( b ) == "{<-500..-401>,<-399..-300>,<-30..9>,<21..29>,<41..899>,<2501..3000>}" );
  assert ( a == b );
  assert ( !( a != b ) );
  b += CRange ( 15, 15 );
  assert ( toString ( b ) == "{<-500..-401>,<-399..-300>,<-30..9>,15,<21..29>,<41..899>,<2501..3000>}" );
  assert ( !( a == b ) );
  assert ( a != b );
  assert ( b . includes ( 15 ) );
  assert ( b . includes ( 2900 ) );
  assert ( b . includes ( CRange ( 15, 15 ) ) );
  assert ( b . includes ( CRange ( -350, -350 ) ) );
  assert ( b . includes ( CRange ( 100, 200 ) ) );
  assert ( !b . includes ( CRange ( 800, 900 ) ) );
  assert ( !b . includes ( CRange ( -1000, -450 ) ) );
  assert ( !b . includes ( CRange ( 0, 500 ) ) );
  a += CRange ( -10000, 10000 ) + CRange ( 10000000, 1000000000 );
  assert ( toString ( a ) == "{<-10000..10000>,<10000000..1000000000>}" );
  b += a;
  assert ( toString ( b ) == "{<-10000..10000>,<10000000..1000000000>}" );
  b -= a;
  assert ( toString ( b ) == "{}" );
  b += CRange ( 0, 100 ) + CRange ( 200, 300 ) - CRange ( 150, 250 ) + CRange ( 160, 180 ) - CRange ( 170, 170 );
  assert ( toString ( b ) == "{<0..100>,<160..169>,<171..180>,<251..300>}" );
  b -= CRange ( 10, 90 ) - CRange ( 20, 30 ) - CRange ( 40, 50 ) - CRange ( 60, 90 ) + CRange ( 70, 80 );
  assert ( toString ( b ) == "{<0..9>,<20..30>,<40..50>,<60..69>,<81..100>,<160..169>,<171..180>,<251..300>}" );
#ifdef EXTENDED_SYNTAX
  CRangeList x { { 5, 20 }, { 150, 200 }, { -9, 12 }, { 48, 93 } };
  assert ( toString ( x ) == "{<-9..20>,<48..93>,<150..200>}" );
  ostringstream oss;
  oss << setfill ( '=' ) << hex << left;
  for ( const auto & v : x + CRange ( -100, -100 ) )
    oss << v << endl;
  oss << setw ( 10 ) << 1024;
  assert ( oss . str () == "-100\n<-9..20>\n<48..93>\n<150..200>\n400=======" );
#endif /* EXTENDED_SYNTAX */
  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
