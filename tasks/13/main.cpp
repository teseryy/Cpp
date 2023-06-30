#ifndef __PROGTEST__
#include <cassert>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include <forward_list>
#include <algorithm>
#include <memory>
#include <stdexcept>
using namespace std;
#endif /* __PROGTEST__ */

template <typename T_>
class comp{
public:
    bool operator()(const pair<int, T_>& p1, const pair<int, T_>& p2){
        return p1.first < p2.first;
    }
};

template <typename T_>
class CDiagonalMatrix
{
public:
    CDiagonalMatrix(int n, int k){
        if (k > n || k < 1 ){
            throw out_of_range("Error");
        }
        this->k = k;
        this->n = n;

        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                if (exists(i, j)){
                    matrix.push_back({getIdx(i, j), T_()});
                }
            }
        }
    }

    // destructor, copy cons, operator = (if needed)
    T_& operator () ( int row, int col ){
        if (exists(row, col)){
            /*auto iT = std::lower_bound(matrix.begin(), matrix.end(), make_pair(getIdx(row, col), T_()), comp<T_>());
            if (iT != matrix.end()){
                iT.
            }*/
            cout << upper_bound(matrix.begin(), matrix.end(), make_pair(getIdx(row, col), T_()), comp<T_>()) << endl;
            for (auto it = matrix.begin(); it < matrix.end(); it++){
                if (it->first == getIdx(row, col)){
                    return it->second;
                }
            }
        }
        throw out_of_range("ERROR");
    }
    bool exists ( int row, int col ) const{
        if (row < n && col < n && row >= 0 && col >= 0){
            if (col <= row + k - 1 && col >= row - k - 1){
                return true;
            }
        }
        return false;
    }
    void reshape ( int k ){
        this->k = k;


    }

private:
    int getIdx(int i, int j){
        return n * i + j;
    }

    int n;
    int k;
    vector<pair<int, T_>> matrix;
};

#ifndef __PROGTEST__
class CTestCnt
{
public:
    CTestCnt                                ( int                                   val = 0 )
            : m_Val ( val )
    {
        c_Inst ++;
    }
    CTestCnt                                ( const CTestCnt                      & src ) noexcept
            : m_Val ( src . m_Val )
    {
        c_Inst ++;
    }
    CTestCnt                                ( CTestCnt                           && src ) noexcept
            : m_Val ( src . m_Val )
    {
        c_Inst ++;
    }
    ~CTestCnt                               ( void ) noexcept
    {
        c_Inst --;
    }
    CTestCnt                         & operator =                              ( CTestCnt                              src ) noexcept
    {
        swap ( src . m_Val, m_Val );
        return *this;
    }
    inline static size_t               c_Inst                                  = 0;
private:
    int                                m_Val;
};

int main ( void )
{
    CDiagonalMatrix<int> m1 ( 5, 4 );

    for ( int i = 0; i < 5; i ++ )
        m1 ( i, i ) = 10 + i;
    for ( int i = 0; i < 4; i ++ )
    {
        m1 ( i, i + 1 ) = 20 + i;
        m1 ( i + 1, i ) = 30 + i;
    }
    for ( int i = 0; i < 3; i ++ )
    {
        m1 ( i, i + 2 ) = 40 + i;
        m1 ( i + 2, i ) = 50 + i;
    }
    m1 ( 0, 3 ) = 60;
    m1 ( 1, 4 ) = 61;
    m1 ( 3, 0 ) = 70;
    m1 ( 4, 1 ) = 71;

    cout << m1(0, 3) <<endl;

    CDiagonalMatrix<int> m2 ( m1 );

    for ( int i = 0; i < 5; i ++ )
        assert ( m2 ( i, i ) == 10 + i );
    for ( int i = 0; i < 4; i ++ )
    {
        assert ( m2 ( i, i + 1 ) == 20 + i );
        assert ( m2 ( i + 1, i ) == 30 + i );
    }
    for ( int i = 0; i < 3; i ++ )
    {
        assert ( m2 ( i, i + 2 ) == 40 + i );
        assert ( m2 ( i + 2, i ) == 50 + i );
    }
    assert ( m2 ( 0, 3 ) == 60 );
    assert ( m2 ( 1, 4 ) == 61 );
    assert ( m2 ( 3, 0 ) == 70 );
    assert ( m2 ( 4, 1 ) == 71 );


    m2 ( 0, 0 ) = 100;
    assert ( m1 ( 0, 0 ) == 10 );
    assert ( m2 ( 0, 0 ) == 100 );


    assert ( m1 . exists ( 4, 1 ) && m1 ( 4, 1 ) == 71 );
    m1 . reshape ( 2 );
    assert ( m1 . exists ( 0, 1 ) && m1 ( 0, 1 ) == 20 );
    assert ( ! m1 . exists ( 0, 2 ) );
    try
    {
        m1 ( 0, 0 ) = m1 ( 0, 2 );
        assert ( "Missing an exception" == nullptr );
    }
    catch ( const std::out_of_range & e )
    {
        assert ( e . what () == "invalid index ( 0, 2 )"s );
    }


    m1 . reshape ( 4 );
    assert ( m1 . exists ( 0, 1 ) && m1 ( 0, 1 ) == 20 );
    assert ( m1 . exists ( 0, 2 ) && m1 ( 0, 2 ) == 0 );

    try
    {
        m1 . reshape ( 6 );
        assert ( "Missing an exception" == nullptr );
    }
    catch ( const std::out_of_range & e )
    {
        assert ( e . what () == "invalid matrix size"s );
    }

    try
    {
        CDiagonalMatrix<int> m3 ( 5, 6 );
        assert ( "Missing an exception" == nullptr );
    }
    catch ( const std::out_of_range & e )
    {
        assert ( e . what () == "invalid matrix size"s );
    }


    CDiagonalMatrix<CTestCnt>  m10 ( 12, 1 );
    assert ( CTestCnt::c_Inst == 12 );
    m10 . reshape ( 4 );
    assert ( CTestCnt::c_Inst == 72 );
    m10 . reshape ( 2 );
    assert ( CTestCnt::c_Inst == 34 );
    m10 . reshape ( 11 );
    assert ( CTestCnt::c_Inst == 142 );
    m10 . reshape ( 12 );
    assert ( CTestCnt::c_Inst == 144 );
    m10 . reshape ( 8 );
    assert ( CTestCnt::c_Inst == 124 );

    return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */