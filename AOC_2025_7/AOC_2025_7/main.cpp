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
#include <utility>
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

int solve(vector<string> mat) {
    
    int n = (int)mat.size();
    int m = (int)mat[0].size();
    
    int si = -1, sj = -1;
    for(int i = 0; i <n ;i++)
        for(int j = 0; j<m; j++) {
            if(mat[i][j] == 'S') {
                si = i;
                sj = j;
            }
        }
    vector<int> beams;
    
    beams.push_back(sj);
    int splits = 0;
    
    for(int i = 1; i < n; i++) {
        set<int> newBeams;
        for(int j = 0; j < m; j++) {
            if(mat[i][j] == '^') {
                for(int j2 = 0; j2 < beams.size(); j2++) {
                    if(beams[j2] == j) {
                        newBeams.insert(j-1);
                        newBeams.insert(j+1);
                        splits++;
                    }
                }
            } else {
                for(int j2 = 0; j2 < beams.size(); j2++) {
                    if(beams[j2] == j) {
                        newBeams.insert(j);
                    }
                }
            }
        }
        
        beams = vector<int>(newBeams.begin(), newBeams.end());
    }
    
    return splits;
}

long long solve2(vector<string> mat) {
    long long dp[200][200];
    int n = (int)mat.size();
    int m = (int)mat[0].size();
    
    int si = -1, sj = -1;
    for(int i = 0; i <n ;i++)
        for(int j = 0; j<m; j++) {
            if(mat[i][j] == 'S') {
                si = i;
                sj = j;
            }
        }
    dp[si][sj] = 1;
    
    
    for(int i = 1; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(mat[i][j] == '.') {
                dp[i][j] += dp[i-1][j];
            } else {
                dp[i][j-1] += dp[i-1][j];
                dp[i][j+1] += dp[i-1][j];
            }
        }
    }
    
    long long res = 0;
    for(int j = 0; j< m; j++) {
        res += dp[n-1][j];
    }
    return res;
}

int main(int argc, const char * argv[]) {
    ifstream fin("input");
    
    string s;
    vector<string> v;
    while(getline(fin, s)) {
        v.push_back(s);
    }
    
    
    auto res1 = measureTime([&v]() {
        return solve(v);
    });
    
    auto res2 = measureTime([&v]() {
        return solve2(v);
    });
    
    cout << "Part 1: " << res1 << endl;
    cout << "Part 2: " << res2 << endl;
    return 0;
}
