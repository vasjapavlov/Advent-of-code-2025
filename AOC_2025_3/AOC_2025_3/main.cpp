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


long long solve1(vector<string> &bat) {
    long long res = 0;
    int n = (int)bat.size();
    
    
    for(int k = 0; k < n; k++) {
        int largest = 0;
        for(int i = 0; i < bat[k].size(); i++) {
            for(int j = i+1; j < bat[k].size(); j++) {
                int num = (bat[k][i] - '0') * 10 + (bat[k][j] - '0');
                largest = max(largest, num);
            }
        }
        res += largest;
    }
    return res;
}


long long solve2(vector<string> &bat) {
    long long res = 0;
    int n = (int)bat.size();
    
    
    for(int k = 0; k < n; k++) {
        long long dp[101][13];
        memset(dp, -1, sizeof dp);
        
        int m = (int)bat[k].size();
        for(int i = 0; i < m; i++) {
            dp[i][1] = bat[k][i]-'0';
        }
        
        for(int i = 1; i < m; i++) {
            for(int d = 2; d <= 12; d++) {
                dp[i][d] = dp[i-1][d];
                for(int j = i - 1; j >= 0; j--) {
                    if(dp[j][d-1] == -1) continue;
                    dp[i][d] = max(dp[i][d], dp[j][d-1] * 10 + (bat[k][i] - '0'));
                }
            }
        }
        res += dp[m-1][12];
    }
    return res;
}

int main(int argc, const char * argv[]) {
    ifstream fin("input");
    vector<string> bat;
    string s;
    while(getline(fin, s)) {
        bat.push_back(s);
    }
    
    auto res1 = measureTime([&bat]() {
        return solve1(bat);
    });
    
    auto res2 = measureTime([&bat]() {
        return solve2(bat);
    });
    cout << "Part 1: " << res1 << endl;
    cout << "Part 2: " << res2 << endl;
    return 0;
}
