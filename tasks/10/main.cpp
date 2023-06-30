#include <sstream>
#include <string>
#include <list>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include <memory>
#include <cassert>
using namespace std;

class CDelivery
{
public:
    CDelivery() = default;
    ~CDelivery() = default;

    // add connection from -> to, fluent interface
    CDelivery & addConn ( const string & from, const string & to ){
        if (connections.find(to) != connections.end()){
            connections.find(to)->second.insert(from);
        }
        else{
            set<string> newS;
            newS.insert(from);
            connections.insert(make_pair(to, newS));
        }

        return *this;
    }

    // returns a map containing shortest path to each customer from any of the depots
    // map key is the customer name, value is a list of nodes on the shortest path (depot -> customer)
    // if there is no path, the value is an empty list
    map<string, list<string>> serveCustomers ( const set<string> & customers, const set<string> & depots ) const{
        map<string, list<string>> res;

        for (const auto& customer : customers){
            map<string, string> path;
            path.emplace(customer, "");

            res.emplace(customer, list<string>());

            queue<string> toVisit;
            toVisit.push(customer);

            while (!toVisit.empty()) {
                auto actual = toVisit.front();
                toVisit.pop();

                if (depots.find(actual) != depots.end()){
                    list<string> way;

                    string place = actual;
                    while (place != ""){
                        way.push_back(place);

                        place = path.find(place)->second;
                    }

                    res[customer] = way;
                    break;
                }

                if (connections.find(actual) != connections.end()) {
                    for (const auto &place: connections.find(actual)->second) {
                        if (path.find(place) == path.end()) {
                            path.emplace(place, actual);
                            toVisit.push(place);
                        }
                    }
                }   
            }
        }

        return res;
    }

private:
    map<string, set<string>> connections;
};

int main ()
{
    CDelivery t0;
    map<string, list<string>> r;
    t0.addConn("Austin", "Berlin");
    t0.addConn("Chicago", "Berlin");
    t0.addConn("Berlin", "Dallas");
    t0.addConn("Dallas", "Essen");
    t0.addConn("Essen", "Austin");
    t0.addConn("Frankfurt", "Gyor");
    t0.addConn("Gyor", "Helsinki");
    t0.addConn("Helsinki", "Frankfurt");

    r = t0.serveCustomers(set<string>{"Berlin", "Gyor"}, set<string>{"Essen", "Helsinki"});
    assert ( r == (map<string, list<string>>{ {"Berlin", {"Essen", "Austin", "Berlin"}}, {"Gyor", {"Helsinki", "Frankfurt", "Gyor"}} }) );

    r = t0.serveCustomers(set<string>{"Austin", "Gyor", "Chicago"}, set<string>{"Austin", "Dallas"});
    assert ( r == (map<string, list<string>>{ {"Austin", {"Austin"}}, {"Chicago", { }}, {"Gyor", { }} }) );
    t0.addConn("Chicago", "Helsinki");

    r = t0.serveCustomers(set<string>{"Austin", "Gyor", "Chicago"}, set<string>{"Austin", "Dallas"});
    assert ( r == (map<string, list<string>>{ {"Austin", {"Austin"}}, {"Chicago", { }}, {"Gyor", { }} }) );
    t0.addConn("Berlin", "Chicago");

    r = t0.serveCustomers(set<string>{"Austin", "Gyor", "Chicago"}, set<string>{"Austin", "Dallas"});
    assert ( r == (map<string, list<string>>{ {"Austin", {"Austin"}}, {"Chicago", {"Austin", "Berlin", "Chicago"}}, {"Gyor", {"Austin", "Berlin", "Chicago", "Helsinki", "Frankfurt", "Gyor"}} }) );
    t0.addConn("Essen", "Frankfurt");

    r = t0.serveCustomers(set<string>{"Austin", "Gyor", "Chicago"}, set<string>{"Austin", "Dallas"});
    assert ( r == (map<string, list<string>>{ {"Austin", {"Austin"}}, {"Chicago", {"Austin", "Berlin", "Chicago"}}, {"Gyor", {"Dallas", "Essen", "Frankfurt", "Gyor"}} }) );

    return EXIT_SUCCESS;
}

