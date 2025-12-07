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

int solve(vector<pair<long long, long long>> range, vector<long long> id) {
    int res = 0;
    for(int i = 0; i < id.size(); i++) {
        for(int j = 0; j < range.size(); j++) {
            if(id[i] >= range[j].first && id[i] <= range[j].second) {
                res++;
                break;
            }
        }
    }
    return res;
}


long long solve2(vector<pair<long long, long long>> range) {
    long long res = 0;
    sort(range.begin(), range.end());
    auto n = range.size();
    long long end = -1;
    for(int i = 0; i < n; i++) {
        //No overlap
        if(range[i].first > end) {
            end = range[i].second;
            res += range[i].second - range[i].first + 1;
            continue;
        }

        //Overlap
        res += max(0LL,range[i].second - end);
        end = max(range[i].second, end);
    }
    
    return res;
}

int main(int argc, const char * argv[]) {
    ifstream fin("input");
    vector<pair<long long, long long>> range;
    vector<long long> id;
    
    string s;
    while(getline(fin, s)) {
        if(s == "") break;
        vector<string> tmp = split(s, "-");
        long long a = stol(tmp[0]);
        long long b = stol(tmp[1]);
        range.push_back(make_pair(a,b));
    }
    
    while(getline(fin, s)) {
        id.push_back(stol(s));
    }
    
    fin >> s;
    auto res1 = measureTime([&range, &id]() {
        return solve(range, id);
    });
    
    auto res2 = measureTime([&range]() {
        return solve2(range);
    });
    
    cout << "Part 1: " << res1 << endl;
    cout << "Part 2: " << res2 << endl;
    return 0;
}
