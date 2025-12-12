#include <iostream>
#include <fstream>
#include "Common.h"

using namespace std;

int main(int argc, const char * argv[]) {
    ifstream fin("input");
    
    string s;
    int res = 0;
    /* Input assumes that shapes are not there since they are not needed for this solution.
     Expects only regions like so:
     4x4: 0 0 0 0 2 0
     12x5: 1 0 1 0 2 2
     12x5: 1 0 1 0 3 2
    */
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
