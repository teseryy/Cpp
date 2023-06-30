#ifndef __PROGTEST__
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <cctype>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <set>
#include <list>
#include <map>
#include <vector>
#include <queue>
#include <string>
#include <stack>
#include <queue>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <functional>
#include <iterator>
#include <stdexcept>
using namespace std;
#endif /* __PROGTEST__ */

template<typename M_>
struct Match{
    string fContestant;
    string sContestant;
    M_ result;

    pair<string, string> getKey() const {
        if (fContestant < sContestant) {
            return make_pair(fContestant, sContestant);
        } else {
            return make_pair(sContestant, fContestant);
        }
    }
};

//inspired by https://www.quora.com/What-is-a-good-algorithm-for-a-rolling-leaderboard and ChatGPT
bool determinateRanks(vector<string>& teams, vector<vector<int>>& relations, vector<int>& countRelations, vector<int>& ranks){
    queue<int> stack;

    size_t len = teams.size();

    for (int i = 0; i < int(len); i++){
        if (countRelations[i] == 0){
            stack.push(i);
            ranks[i] = 1;
        }
    }

    int processed = 0;
    while (!stack.empty()){
        int current = stack.front();
        stack.pop();
        processed += 1;

        for (int neighbor : relations[current]) {
            ranks[neighbor] = max(ranks[neighbor], ranks[current] + 1);
            countRelations[neighbor]--;
            if (countRelations[neighbor] == 0) {
                stack.push(neighbor);
            }
        }
    }

    return (processed == int(len));
}

bool isTableExist(vector<string>& teams, vector<vector<int>>& relations, vector<int>& ranks, vector<int>& sortedTeams){
    int len = int(teams.size());

    for (int i = 0; i < len; i++) {
        sortedTeams[i] = i;
    }
    sort(sortedTeams.begin(), sortedTeams.end(), [&](int i, int j) {
        if (ranks[i] != ranks[j]) {
            return ranks[i] > ranks[j];
        } else {
            return teams[i] < teams[j];
        }
    });

    vector<int> sorted_ranks(len);
    for (int i = 0; i < len; i++) {
        sorted_ranks[sortedTeams[i]] = ranks[i];
    }

    unordered_set<int> unique_ranks;
    for (int rank : sorted_ranks) {
        if (unique_ranks.count(rank) > 0) {
            return false;
        }
        else {
            unique_ranks.insert(rank);
        }
    }

    return true;

}

class ComparePairs {
public:
    bool operator() (const pair<string, string>& a, const pair<string, string>& b) const {
        if (a.first == b.first) {
            return a.second < b.second;
        } else {
            return a.first < b.first;
        }
    }
};

template<typename M_>
class CContest {
public:
    CContest() = default;
    ~CContest() = default;
    CContest<M_>& addMatch ( const string& contestant1, const string& contestant2, const M_& res);
    bool isOrdered ( function<int (const M_ &)> comparator ) const;
    list<string> results ( function<int (const M_ &)> comparator ) const;
    vector<Match<M_>> matches;
    vector<pair<string, string>> uniquePairs;
    set<string>uniqueTeams;
private:
};

template<typename M_>
CContest<M_>& CContest<M_>::addMatch(const string &contestant1, const string &contestant2, const M_ &res) {
    if (contestant1 == contestant2 || contestant1.empty() || contestant2.empty()){
        throw logic_error("The result of the match between the opponents has already been given.");
    }
    
    Match<M_> newMatch{contestant1, contestant2, res};

    auto contestants = newMatch.getKey();

    auto itF = lower_bound(uniquePairs.begin(), uniquePairs.end(), contestants, ComparePairs());
    auto itS = upper_bound(uniquePairs.begin(), uniquePairs.end(), contestants, ComparePairs());
    if (itF == itS){
        uniquePairs.insert(itF, contestants);
        matches.push_back(newMatch);
    }
    else{
        throw logic_error("The result of the match between the opponents has already been given.");
    }

    uniqueTeams.insert(contestant1);
    uniqueTeams.insert(contestant2);

    return *this;
}

template<typename M_>
bool CContest<M_>::isOrdered(const function<int(const M_ &)> comparator) const {
    vector<int> ranks;
    vector<vector<int>> relations;
    vector<int> countRelations;
    vector<string> teams;
    vector<int> sortedTeams;

    teams.resize(uniqueTeams.size());
    bool isDraw = false;

    unordered_map<string, int> teamIdx;

    int counter = 0;
    for (auto & team : uniqueTeams){
        teams[counter] = team;
        teamIdx[team] = counter;
        counter++;
    }


    relations.resize(uniqueTeams.size());
    countRelations.resize(uniqueTeams.size(), 0);

    for (auto & match : matches){
        int fTeam = teamIdx[match.fContestant];
        int sTeam = teamIdx[match.sContestant];

        int result = comparator(match.result);

        if (result > 0){
            relations[sTeam].push_back(fTeam);
            countRelations[fTeam] += 1;
        }
        else if (result < 0){
            relations[fTeam].push_back(sTeam);
            countRelations[sTeam] += 1;
        }
        else if (result == 0){
            isDraw = true;
        }
    }

    ranks.resize(uniqueTeams.size(), 0);
    sortedTeams.resize(uniqueTeams.size());

    if (!determinateRanks(teams, relations, countRelations, ranks)) {
        return false;
    }

    if (isDraw || !isTableExist(teams, relations, ranks, sortedTeams)) {
        return false;
    }

    return true;
}

template<typename M_>
list<string> CContest<M_>::results(const function<int(const M_ &)> comparator) const{
    vector<int> ranks;
    vector<vector<int>> relations;
    vector<int> countRelations;
    vector<string> teams;
    vector<int> sortedTeams;

    teams.resize(uniqueTeams.size());
    bool isDraw = false;

    unordered_map<string, int> teamIdx;

    int counter = 0;
    for (auto & team : uniqueTeams){
        teams[counter] = team;
        teamIdx[team] = counter;
        counter++;
    }


    relations.resize(uniqueTeams.size());
    countRelations.resize(uniqueTeams.size(), 0);

    for (auto & match : matches){
        int fTeam = teamIdx[match.fContestant];
        int sTeam = teamIdx[match.sContestant];

        int result = comparator(match.result);

        if (result > 0){
            relations[sTeam].push_back(fTeam);
            countRelations[fTeam] += 1;
        }
        else if (result < 0){
            relations[fTeam].push_back(sTeam);
            countRelations[sTeam] += 1;
        }
        else if (result == 0){
            isDraw = true;
        }
    }

    ranks.resize(uniqueTeams.size(), 0);
    sortedTeams.resize(uniqueTeams.size());

    if (!determinateRanks(teams, relations, countRelations, ranks)) {
        throw logic_error("Table can't be defined.");
    }

    if (isDraw || !isTableExist(teams, relations, ranks, sortedTeams)) {
        throw logic_error("Table can't be defined.");
    }


    list<string> leaderBoard;
    size_t len = teams.size();

    for (int i = 0; i < int(len); i++){
        int current = sortedTeams[i];
        leaderBoard.push_back(teams[current]);
    }

    return leaderBoard;
}

#ifndef __PROGTEST__
struct CMatch
{
  public:
                             CMatch                        ( int               a, 
                                                             int               b )
      : m_A ( a ), 
        m_B ( b )
    {
    }
    
    int                      m_A;
    int                      m_B;
};

class HigherScoreThreshold
{
  public:
                             HigherScoreThreshold          ( int diffAtLeast )
      : m_DiffAtLeast ( diffAtLeast )
    {
    }
    int                      operator ()                   ( const CMatch & x ) const
    {
      return ( x . m_A > x . m_B + m_DiffAtLeast ) - ( x . m_B > x . m_A + m_DiffAtLeast );
    }
  private:
    int            m_DiffAtLeast;    
};

int                HigherScore                             ( const CMatch    & x )
{
  return ( x . m_A > x . m_B ) - ( x . m_B > x . m_A );
}

int                main                                    ( void )
{
  CContest<CMatch>  x;

  x . addMatch ( "C++", "Pascal", CMatch ( 10, 3 ) )
    . addMatch ( "C++", "Java", CMatch ( 8, 1 ) )
    . addMatch ( "Pascal", "Basic", CMatch ( 40, 0 ) )
    . addMatch ( "Java", "PHP", CMatch ( 6, 2 ) )
    . addMatch ( "Java", "Pascal", CMatch ( 7, 3 ) )
    . addMatch ( "PHP", "Basic", CMatch ( 10, 0 ) );

  assert ( ! x . isOrdered ( HigherScore ) );
  try
  {
    list<string> res = x . results ( HigherScore );
    assert ( "Exception missing!" == nullptr );
  }
  catch ( const logic_error & e )
  {
  }
  catch ( ... )
  {
    assert ( "Invalid exception thrown!" == nullptr );
  }

  x . addMatch ( "PHP", "Pascal", CMatch ( 3, 6 ) ); 

  assert ( x . isOrdered ( HigherScore ) );
  try
  {
    list<string> res = x . results ( HigherScore );
    assert ( ( res == list<string>{ "C++", "Java", "Pascal", "PHP", "Basic" } ) );
  }
  catch ( ... )
  {
    assert ( "Unexpected exception!" == nullptr );
  }

  
  assert ( ! x . isOrdered ( HigherScoreThreshold ( 3 ) ) );
  try
  {
    list<string> res = x . results ( HigherScoreThreshold ( 3 ) );
    assert ( "Exception missing!" == nullptr );
  }
  catch ( const logic_error & e )
  {
  }
  catch ( ... )
  {
    assert ( "Invalid exception thrown!" == nullptr );
  }
  
  assert ( x . isOrdered ( [] ( const CMatch & x )
  {
    return ( x . m_A < x . m_B ) - ( x . m_B < x . m_A ); 
  } ) );
  try
  {
    list<string> res = x . results ( [] ( const CMatch & x )
    {
      return ( x . m_A < x . m_B ) - ( x . m_B < x . m_A ); 
    } );
    assert ( ( res == list<string>{ "Basic", "PHP", "Pascal", "Java", "C++" } ) );
  }
  catch ( ... )
  {
    assert ( "Unexpected exception!" == nullptr );
  }
  
  CContest<bool>  y;
  
  y . addMatch ( "Python", "PHP", true )
    . addMatch ( "PHP", "Perl", true )
    . addMatch ( "Perl", "Bash", true )
    . addMatch ( "Bash", "JavaScript", true )
    . addMatch ( "JavaScript", "VBScript", true );
  
  assert ( y . isOrdered ( [] ( bool v )
  {
    return v ? 10 : - 10;
  } ) );
  try
  {
    list<string> res = y . results ( [] ( bool v )
    {
      return v ? 10 : - 10;
    });
    assert ( ( res == list<string>{ "Python", "PHP", "Perl", "Bash", "JavaScript", "VBScript" } ) );
  }
  catch ( ... )
  {
    assert ( "Unexpected exception!" == nullptr );
  }
    
  y . addMatch ( "PHP", "JavaScript", false );
  assert ( !y . isOrdered ( [] ( bool v )
  {
    return v ? 10 : - 10;
  } ) );
  try
  {
    list<string> res = y . results ( [] ( bool v )
    {
      return v ? 10 : - 10;
    } );
    assert ( "Exception missing!" == nullptr );
  }
  catch ( const logic_error & e )
  {
  }
  catch ( ... )
  {
    assert ( "Invalid exception thrown!" == nullptr );
  }
  
  try
  {
    y . addMatch ( "PHP", "JavaScript", false );
    assert ( "Exception missing!" == nullptr );
  }
  catch ( const logic_error & e )
  {
  }
  catch ( ... )
  {
    assert ( "Invalid exception thrown!" == nullptr );
  }
  
  try
  {
    y . addMatch ( "JavaScript", "PHP", true );
    assert ( "Exception missing!" == nullptr );
  }
  catch ( const logic_error & e )
  {
  }
  catch ( ... )
  {
    assert ( "Invalid exception thrown!" == nullptr );
  }
  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
