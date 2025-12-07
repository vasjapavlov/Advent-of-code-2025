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

void input1(vector<vector<long long>> &nums, vector<char> &op) {
    ifstream fin("input");
    
    
    string s;
    
    while(getline(fin, s)) {
        vector<string> v = split(s, " ");
        vector<string> v2;
        vector<long long> tmp;
        bool isLastRow = false;
        for(int i = 0; i < v.size(); i++) {
            tmp.clear();
            if(v[i] == "") {continue;}
            v2.push_back(v[i]);
            if(v2[0] == "*" || v2[0] == "+") {
                isLastRow = true;
                op.push_back(v2[v2.size()-1][0]);
            } else {
                for(int i = 0; i < v2.size(); i++) {
                    tmp.push_back(stol(v2[i]));
                }
            }
        }
        if(!isLastRow)
            nums.push_back(tmp);
    }
}

long long solve1() {
    vector<vector<long long>> nums;
    vector<char> op;
    input1(nums, op);
    auto n = nums.size();
    auto m = nums[0].size();
    long long res = 0;
    
    for(int j = 0; j < m; j++) {
        if(op[j] == '*') {
            long long tmp = 1;
            for(int i = 0; i < n; i++) {
                tmp *= nums[i][j];
            }
            res += tmp;
        }
        if(op[j] == '+') {
            long long tmp = 0;
            for(int i = 0; i < n; i++) {
                tmp += nums[i][j];
            }
            res += tmp;
        }
    }
    return res;
}

void input2(vector<string> &v, vector<string> &op) {
    ifstream fin("input");
    string s;
    int m = 0;
    while(getline(fin, s)) {
        v.push_back(s);
        m = max(m, (int)s.size());
    }
    auto n = v.size();
    for(int i = 0; i < n; i++) {
        if(v[i].size() < m) {
            v[i] += " ";
        }
        v[i] = " " + v[i];
    }
    vector<string> tmp = split(v[v.size()-1], " ");
    for(int i = 0; i < tmp.size(); i++) {
        if(tmp[i] != "") {
            op.push_back(tmp[i]);
        }
    }
    v.pop_back();
}

long long solve2() {
    vector<string> v;
    vector<string> op;
    input2(v, op);
    
    int n = (int)v.size();
    int m = (int)v[0].size();
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cout << v[i][j];
        }
        cout << "|\n";
    }
    
    for(int i = 0; i < op.size(); i++) {
        cout << op[i] << " ";
    } cout << endl;
    
    int opIndex = (int)op.size() - 1;
    long long res= 0, tmp;
    if(op[opIndex] == "*") tmp = 1; else tmp = 0;
    for(int j = m - 1; j>= 0; j--) {
        int num = 0;
        for(int i = 0; i < n; i++) {
            if(v[i][j] >= '0' && v[i][j] <= '9') {
                num = num * 10 + (v[i][j]-'0');
            }
        }
        if(num > 0) {
            if(op[opIndex] == "*") {
                tmp *= num;
            } else {
                tmp += num;
            }
        } else {
            res += tmp;
            opIndex = max(0, opIndex-1);
            if(op[opIndex] == "*") tmp = 1; else tmp = 0;
            
        }
    }
    return res;
}

int main(int argc, const char * argv[]) {
    
    auto res1 = measureTime([]() {
        return solve1();
    });
    
    auto res2 = measureTime([]() {
        return solve2();
    });
    
    cout << "Part 1: " << res1 << endl;
    cout << "Part 2: " << res2 << endl;
    return 0;
}
