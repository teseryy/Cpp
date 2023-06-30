#ifndef __PROGTEST__
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <string>
#include <list>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <memory>
using namespace std;
#endif /* __PROGTEST__ */

class CTeleport
{
    //from - {to, {fromTime, toTime}}
    map<string, vector<pair<string, pair<int, int>>>> paths;
public:

    CTeleport() = default;
    ~CTeleport() = default;

    CTeleport & Add ( const string & from, const string & to,
                      unsigned fromTime, unsigned toTime ){

        if (paths.find(from) == paths.end()){
            vector<pair<string, pair<int, int>>> newVec;
            newVec.emplace_back(to, make_pair(fromTime, toTime));
            paths.emplace(from, newVec);
        }
        else{
            paths.find(from)->second.emplace_back(to, make_pair(fromTime, toTime));
        }

        return *this;
    }

    CTeleport & Optimize (){
        return *this;
    }

    unsigned FindWay ( const string & from, const string & to,
                       unsigned time ){

        queue<pair<string, int>> toVisit;
        toVisit.emplace(from, time);
        int finalTime = INT32_MAX;
        map<string, int> visited;
        visited.emplace(from, time);

        while (!toVisit.empty()){
            auto city = toVisit.front();
            toVisit.pop();

            if (city.first == to){
                if (finalTime > city.second){
                    finalTime = city.second;
                }
            }

            if (paths.find(city.first) != paths.end()){
                for (const auto& it : paths.find(city.first)->second){
                    if (city.second <= it.second.first){
                        if (visited.find(it.first) == visited.end()) {
                            toVisit.emplace(it.first, it.second.second);
                            visited.emplace(it.first, it.second.second);
                        }
                        else if (visited.find(it.first)->second > it.second.second){
                            toVisit.emplace(it.first, it.second.second);
                            visited.emplace(it.first, it.second.second);
                        }
                    }
                }
            }
        }

        if (finalTime != INT32_MAX){
            return finalTime;
        }

        throw invalid_argument("ERROR");
    }
};

#ifndef __PROGTEST__
int main ( void )
{
    CTeleport t;
    t . Add ( "Prague", "Vienna", 0, 7 )
            . Add ( "Vienna", "Berlin", 9, 260 )
            . Add ( "Vienna", "London", 8, 120 )
            . Add ( "Vienna", "Chicago", 4, 3 )
            . Add ( "Prague", "Vienna", 10, 10 ) . Optimize ( );

    assert ( t . FindWay ( "Prague", "Vienna", 0 ) == 7 );
    assert ( t . FindWay ( "Prague", "Vienna", 1 ) == 10 );
    assert ( t . FindWay ( "Prague", "London", 0 ) == 120 );
    assert ( t . FindWay ( "Vienna", "Chicago", 4 ) == 3 );

    try { t . FindWay ( "Prague", "London", 2 ); assert ( "Missing exception" == nullptr ); }
    catch ( const invalid_argument & e ) { }
    catch ( ... ) { assert ( "Invalid exception" == nullptr ); }
    try { t . FindWay ( "Prague", "Chicago", 0 ); assert ( "Missing exception" == nullptr ); }
    catch ( const invalid_argument & e ) { }
    catch ( ... ) { assert ( "Invalid exception" == nullptr ); }

    t . Add ( "Dallas", "Atlanta", 150, 30 )
            . Add ( "Berlin", "Helsinki", 1080, 2560 )
            . Add ( "Chicago", "Frankfurt", 50, 0 )
            . Add ( "Helsinki", "Vienna", 3200, 3 )
            . Add ( "Chicago", "London", 10, 12 )
            . Add ( "London", "Atlanta", 20, 40 )
            . Add ( "Vienna", "Atlanta", 10, 50 )
            . Add ( "Prague", "Vienna", 1, 6 )
            . Add ( "Berlin", "Helsinki", 265, 265 )
            . Add ( "Berlin", "London", 259, 0 ) . Optimize ( );
    
    assert ( t . FindWay ( "Prague", "Frankfurt", 0 ) == 0 );

    assert ( t . FindWay ( "Prague", "Atlanta", 0 ) == 40 );
    assert ( t . FindWay ( "Prague", "Atlanta", 10 ) == 50 );

    return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */

