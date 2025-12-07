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

int di[] = {-1, -1, -1, 0, 1, 1,  1,  0};
int dj[] = {-1,  0,  1, 1, 1, 0, -1, -1};

int solve(vector<string> mat) {
    int n = (int)mat.size();
    int m = (int)mat[0].size();
    int res = 0;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++) {
            if(mat[i][j] != '@') continue;
            int cnt = 0;
            for(int k = 0; k < 8; k++) {
                int ni = i + di[k];
                int nj = j + dj[k];
                if(ni < 0 || nj < 0 || ni >= n || nj >= m) continue;
                cnt += mat[ni][nj] == '@';
            }
            res += cnt < 4;
        }
    return res;
}

int solve2(vector<string> mat) {
    vector<string> mat2 = mat;
    int n = (int)mat.size();
    int m = (int)mat[0].size();
    int res = 0;
    bool hasChange = true;
    while(hasChange) {
        hasChange = false;
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++) {
                if(mat[i][j] != '@') continue;
                int cnt = 0;
                for(int k = 0; k < 8; k++) {
                    int ni = i + di[k];
                    int nj = j + dj[k];
                    if(ni < 0 || nj < 0 || ni >= n || nj >= m) continue;
                    cnt += mat[ni][nj] == '@';
                }
                if (cnt < 4) {
                    res++;
                    mat2[i][j] = '.';
                    hasChange = true;
                }
            }
        mat = mat2;
    }
    return res;
}

int main(int argc, const char * argv[]) {
    ifstream fin("input");
    vector<string> mat;
    string s;
    while(getline(fin, s)) {
        mat.push_back(s);
    }

    auto res1 = measureTime([&mat]() {
        return solve(mat);
    });
    
    auto res2 = measureTime([&mat]() {
        return solve2(mat);
    });
    
    cout << "Part 1: " << res1 << endl;
    cout << "Part 2: " << res2 << endl;
    return 0;
}
