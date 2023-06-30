#ifndef __PROGTEST__
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <cassert>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
#endif /* __PROGTEST__ */

int count_bytes(const string& byte){

    if (byte[0] == '1' && byte[1] == '1' && byte[2] == '1' && byte[3] == '1'){
        if (byte[4] != '0'){
            return -1;
        }
        return 4;
    }
    if (byte[0] == '1' && byte[1] == '1' && byte[2] == '1'){
        if (byte[3] != '0'){
            return -1;
        }
        return 3;
    }
    if (byte[0] == '1' && byte[1] == '1'){
        if (byte[2] != '0'){
            return -1;
        }
        return 2;
    }

    return 0;
}

string reverse(string const &str)
{
    string rev;
    int len = str.size();
    for (int i = len - 1; i >= 0; i--) {
        rev = rev.append(1, str[i]);
    };

    return rev;
}

string decToFib(const vector<int> &fib, long num){
    string nFib;
    size_t len = fib.size();
    int idx = 0;

    for (int i = len - 1; i >= 0; i--){
        if (fib[i] <= num){
            idx = i;
            break;
        }
    }

    nFib.append(idx + 1, '0');
    nFib[idx] = '1';
    num -= fib[idx];

    while (num > 0){
        for (int i = idx; i >= 0; i--){
            if (fib[i] <= num){
                idx = i;
                break;
            }
        }
        nFib[idx] = '1';
        num -= fib[idx];
    }

    nFib.push_back('1');
    return nFib;
}

bool utf8ToFibonacci( const char * inFile, const char * outFile ){
    ifstream fin(inFile);
    ofstream fout(outFile);
    if (!fin.is_open() || !fout.is_open()){
        return false;
    }

    bool rflag = false;
    char symb;
    string byte;
    string nBytes;
    string fCode;
    string fibD;
    int num_bytes = 0;
    long dec_num = 0;

    vector<int> fib;
    int counter = 0;
    fib.push_back(1);
    int num = 2;
    while(num < 1114111){
        fib.push_back(num);
        num += fib[counter];
        counter++;
    }
    fib.push_back(num);


    while (fin.get(symb)){
        rflag = true;
        for (int i = 7; i >= 0; --i) {
            byte.push_back(static_cast<char>((symb >> i) & 1) + '0');
        }

        if (byte.substr(0,5) == "11111"){
            return false;
        }

        if (num_bytes <= 0){
            num_bytes = count_bytes(byte);

            if (num_bytes == -1){
                return false;
            }

            if (num_bytes == 0){
                if (byte[0] == '1'){
                    return false;
                }
                dec_num = ::strtol(byte.substr(num_bytes + 1).c_str(), nullptr, 2);
                if (dec_num < 0 || dec_num > 1114111){
                    return false;
                }
                fibD = decToFib(fib, dec_num + 1);
            }
            else{
                nBytes.append(byte.substr(num_bytes + 1));
                num_bytes -= 1;
            }
        }
        else{
           if (byte.substr(0, 2) != "10"){
                return false;
            }
            num_bytes -= 1;
            nBytes.append(byte.substr(2));
            if (num_bytes == 0){
                dec_num = ::strtol(nBytes.c_str(), nullptr, 2);
                if (dec_num > 1114111 || dec_num < 0){
                    return false;
                }
                nBytes.clear();
                fibD = decToFib(fib, dec_num + 1);
            }
        }


        byte.clear();
        fCode.append(fibD);
        fibD.clear();

        while (fCode.size() > 7){
            string line;
            line.append(fCode.substr(0, 8));
            fCode.erase(0, 8);
            line = reverse(line);
            fout << char (::strtol(line.c_str(), nullptr, 2));

        }
    }
    if (num_bytes != 0){
        return false;
    }

    if ( fCode.size() > 0 && fCode.size() < 8){
        while (fCode.size() < 8){
            fCode.push_back('0');
        }

        fCode = reverse(fCode);
        fout << char (::strtol(fCode.c_str(), nullptr, 2));
    }

    if (!rflag){
        return false;
    }

    fin.close();
    fout.close();

    if (!fout.good()){
        return false;
    }
    return true;
}

int fibToDec(const vector<int> &fib, string fCode){
    int res = 0;
    int len = fCode.size();

    for (int i = 0; i < len; i++){
        if (fCode[i] == '1'){
            res += fib[i];
        }
    }

    return res - 1;
}

string decToBin(int num){
    string bin;

    do{
        bin.push_back(char('0' + num % 2));
        num /= 2;
    }while(num > 0);

    bin = reverse(bin);

    return bin;
}

bool fibonacciToUtf8( const char * inFile, const char * outFile ){
    ifstream fin(inFile);
    ofstream fout(outFile);
    if (!fin.is_open() || !fout.is_open()){
        return false;
    }

    char symb;
    string byte;
    string fCode;
    string bin;
    bool rflag = false;
    bool flag = false;
    int dec_num;

    vector<int> fib;
    int counter = 0;
    fib.push_back(1);
    int num = 2;
    while(num < 1114111){
        fib.push_back(num);
        num += fib[counter];
        counter++;
    }
    fib.push_back(num);

    while (fin.get(symb)) {
        rflag = true;
        for (int i = 7; i >= 0; --i) {
            byte.push_back(static_cast<char>((symb >> i) & 1) + '0');
        }
        flag = false;
        fCode.append(reverse(byte));


        int idx;
        while (fCode.find("11") != string::npos){
            idx = fCode.find("11");
            flag = true;
            dec_num = fibToDec(fib, fCode.substr(0, idx + 1));
            if (dec_num > 1114111 || dec_num < 0){
                return false;
            }
            bin = decToBin(dec_num);

            if (bin.size() < 8){
                fout << char (dec_num);
            }
            else if (bin.size() > 7 && bin.size() < 12){
                string newBin;
                if (bin.size() != 11){
                    newBin.append(11 - bin.size(), '0');
                }
                newBin.append(bin);

                string fbyte = "110";
                fbyte.append(newBin.substr(0,5));
                fout << char (::strtol(fbyte.c_str(), nullptr, 2));

                string sbyte = "10";
                sbyte.append(newBin.substr(5));
                fout << char (::strtol(sbyte.c_str(), nullptr, 2));
            }
            else if (bin.size() > 11 && bin.size() < 17){
                string newBin;
                if (bin.size() != 16){
                    newBin.append(16 - bin.size(), '0');
                }
                newBin.append(bin);

                string fbyte = "1110";
                fbyte.append(newBin.substr(0,4));
                fout << char (::strtol(fbyte.c_str(), nullptr, 2));

                string sbyte = "10";
                sbyte.append(newBin.substr(4, 6));
                fout << char (::strtol(sbyte.c_str(), nullptr, 2));

                string tbyte = "10";
                tbyte.append(newBin.substr(10));
                fout << char (::strtol(tbyte.c_str(), nullptr, 2));
            }
            else if (bin.size() > 16 && bin.size() < 22){
                string newBin;
                if (bin.size() != 21){
                    newBin.append(21 - bin.size(), '0');
                }
                newBin.append(bin);

                string fbyte = "11110";
                fbyte.append(newBin.substr(0,3));
                fout << char (::strtol(fbyte.c_str(), nullptr, 2));

                string sbyte = "10";
                sbyte.append(newBin.substr(3, 6));
                fout << char (::strtol(sbyte.c_str(), nullptr, 2));

                string tbyte = "10";
                tbyte.append(newBin.substr(9, 6));
                fout << char (::strtol(tbyte.c_str(), nullptr, 2));

                string forbyte = "10";
                forbyte.append(newBin.substr(15));
                fout << char (::strtol(forbyte.c_str(), nullptr, 2));
            }
            else{
                return false;
            }

            fCode.erase(0, idx + 2);
        }

        byte.clear();
    }

    if (!flag || !rflag){
        return false;
    }


    fin.close();
    fout.close();

    if (!fout.good()){
        return false;
    }
    return true;
}

#ifndef __PROGTEST__

bool identicalFiles ( const char * file1, const char * file2 ){
  // todo
}

int main ( int argc, char * argv [] ){
    if(utf8ToFibonacci ( "example/src_12.utf8", "output.fib" )){
        cout << "True" << endl;
    }
    else{
        cout << "False" << endl;
    }
    /**
    assert ( utf8ToFibonacci ( "example/src_0.utf8", "output.fib" )
           && identicalFiles ( "output.fib", "example/dst_0.fib" ) );
    assert ( utf8ToFibonacci ( "example/src_1.utf8", "output.fib" )
           && identicalFiles ( "output.fib", "example/dst_1.fib" ) );
    assert ( utf8ToFibonacci ( "example/src_2.utf8", "output.fib" )
           && identicalFiles ( "output.fib", "example/dst_2.fib" ) );
    assert ( utf8ToFibonacci ( "example/src_3.utf8", "output.fib" )
               && identicalFiles ( "output.fib", "example/dst_3.fib" ) );
    assert ( utf8ToFibonacci ( "example/src_4.utf8", "output.fib" )
               && identicalFiles ( "output.fib", "example/dst_4.fib" ) );
    assert ( ! utf8ToFibonacci ( "example/src_5.utf8", "output.fib" ) );
    assert ( fibonacciToUtf8 ( "example/src_6.fib", "output.utf8" )
               && identicalFiles ( "output.utf8", "example/dst_6.utf8" ) );
    assert ( fibonacciToUtf8 ( "example/src_7.fib", "output.utf8" )
               && identicalFiles ( "output.utf8", "example/dst_7.utf8" ) );
    assert ( fibonacciToUtf8 ( "example/src_8.fib", "output.utf8" )
               && identicalFiles ( "output.utf8", "example/dst_8.utf8" ) );
    assert ( fibonacciToUtf8 ( "example/src_9.fib", "output.utf8" )
               && identicalFiles ( "output.utf8", "example/dst_9.utf8" ) );
    assert ( fibonacciToUtf8 ( "example/src_10.fib", "output.utf8" )
               && identicalFiles ( "output.utf8", "example/dst_10.utf8" ) );
    assert ( ! fibonacciToUtf8 ( "example/src_11.fib", "output.utf8" ) );
    **/
     return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
