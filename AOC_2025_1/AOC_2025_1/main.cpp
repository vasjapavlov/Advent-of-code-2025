#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <map>
#include <set>
#include <sstream>

using namespace std;

int part1() {
    ifstream fin("input");
    string s;
    
    int res = 0;
    int pos = 50;
    while(fin >> s) {
        istringstream is(s);
        
        char c;
        is >> c;
        int x;
        is >> x;
        
        if(c == 'L') {
            pos = ((pos + 100) - x) % 100;
        } else {
            pos = (pos + x) % 100;
        }
        res += (pos == 0);
    }
    
    return res;
}

int part2() {
    ifstream fin("input");
    string s;
    
    int res = 0;
    int pos = 50;
    
    while(fin >> s) {
        istringstream is(s);
        
        char c;
        is >> c;
        int x;
        is >> x;
        
        //brute force
        int x2 = x;
        if(c == 'L') {
            while(x2 > 0) {
                x2--;
                pos--;
                if(pos == 0) res++;
                if(pos < 0) {
                    pos = 99;
                }
            }
        } else {
            while(x2 > 0) {
                x2--;
                pos++;
                if(pos > 99) {
                    pos = 0;
                }
                if(pos == 0) res++;
            }
        }
        
//        if(c == 'L') {
//            if(pos > 0 && pos - x <= 0) { res += (x - pos) / 100 + 1; }
//            pos = ((pos + 10000) - x) % 100;
//        } else {
//            if(pos + x > 99) { res += (x - (99 - pos)) / 100 + 1; }
//            pos = (pos + x) % 100;
//        }
//        res += (pos == 0);
    }
//    cout <<"Res2 = "<< res2 << endl;
    return res;
}

int main(int argc, const char * argv[]) {
    cout << part1() << endl;
    cout << part2() << endl;
    return 0;
}
