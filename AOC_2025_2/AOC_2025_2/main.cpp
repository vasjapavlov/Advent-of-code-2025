#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <map>
#include <set>
#include <sstream>
#include <chrono>
#include <functional>

using namespace std;

template<typename Func>
auto measureTime(Func&& func) {
    auto start = std::chrono::system_clock::now();
    auto result = func();
    auto end = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << elapsed.count() << "ms\n";
    return result;
}

vector<string> split(string s, string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

bool isInvalid(long long x) {
    ostringstream os;
    os << x;
    string s = os.str();
    int n = (int)s.size();
    if(n % 2 != 0) return false;
    for(int i = 0; i < n / 2; i++) {
        if(s[i] != s[n/2 + i]) return false;
    }
    return true;
}

bool isInvalid2(long long x) {
    ostringstream os;
    os << x;
    string s = os.str();
    int n = (int)s.size();

    for(int step = 1; step <= n/2; step++) {
        if(n%step != 0) continue;
        bool isValid = true;
        for(int i = step; i < n; i+=step) {
            for(int k = 0; k < step; k++) {
                if(s[k] != s[i + k]) {
                    isValid = false;
                }
            }
        }
        if(isValid) {
            return true;
        }
    }
    return false;
}

long long solve(string &s) {
    
    vector<string> a = split(s, ",");
    long long res = 0;
    for(int i = 0; i < a.size(); i++) {
        istringstream is(a[i]);
        long long l,r;
        char c;
        is >> l >> c >> r;
        for(long long j = l; j <= r; j++) {
//          Part 1
          res += isInvalid(j) ? j : 0;
//            res += isInvalid2(j) ? j : 0;
        }
    }
    return res;
}

int main(int argc, const char * argv[]) {
    ifstream fin("input");
    string s;
    fin >> s;
    
    auto result = measureTime([&s]() {
        return solve(s);
    });
    
    cout << result << endl;
    return 0;
}
