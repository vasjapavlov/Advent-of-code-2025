#include <iostream>
#include <fstream>
#include "Common.h"

using namespace std;

int main(int argc, const char * argv[]) {
    ifstream fin("input");
    
    string s;
    int res = 0;
    while(getline(fin, s)) {
        vector<string> vs = split(s, ": ");
        int sum = 0;
        int x;
        istringstream is(vs[1]);
        while(is >> x) {
            sum += x;
        }
        vs = split(vs[0], "x");
        int n = stoi(vs[0]);
        int m = stoi(vs[1]);
        
        res += (n / 3) * (m / 3) >= sum;
        
    }
    cout << res << endl;

    return 0;
}
