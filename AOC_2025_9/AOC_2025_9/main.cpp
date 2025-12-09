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
#include "Common.h"

using namespace std;

map<int, int> mp, rmp;
char marked[501][501];

long long area(int r1, int c1, int r2, int c2) {
    return (long long)(abs(r1-r2)+1) * (abs(c1-c2) + 1);
}

long long solve(vector<int> r, vector<int> c) {
    int n = (int)r.size();
    
    long long res = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(i == j) continue;
            res = max(res, ((long long)abs(r[i]-r[j])+1) * (abs(c[i]-c[j]) + 1) );
        }
    }
    return res;
}

void minimize(vector<int> r, vector<int> c) {
    set<int> originalSet;
    vector<int> minimized;
    int n = (int)r.size();
    
    for(int i = 0; i < n; i++) {
        originalSet.insert(r[i]);
        originalSet.insert(c[i]);
    }
    vector<int> original = vector<int>(originalSet.begin(), originalSet.end());
    sort(original.begin(), original.end());
    for(int i = 0; i< original.size(); i++) {
        mp[original[i]] = i + 1;
        rmp[i + 1] = original[i];
    }
}

void bfs(int r, int c) {
    int di[] = {-1,1,0,0};
    int dj[] = {0,0,-1,1};
    queue<int> q;
    q.push(r);
    q.push(c);
    marked[r][c] = '-';
    while(!q.empty()) {
        int ii = q.front(); q.pop();
        int jj = q.front(); q.pop();

        for(int k = 0; k < 4; k++) {
            int ni = ii + di[k];
            int nj = jj + dj[k];
            if(marked[ni][nj] != '.') {
                continue;
            }
            marked[ni][nj] = '-';
            q.push(ni);
            q.push(nj);
        }
    }
}

void createMap(vector<int> &r, vector<int> &c) {
    int n = (int)r.size();
    int MAXN = 500;
    for(int i = 0; i < MAXN; i++) {
        for(int j = 0; j < MAXN; j++) {
            marked[i][j] = '.';
        }
    }
    
    for(int i = 0; i < n; i++) {
        int x = mp[r[i]];
        int y = mp[c[i]];
        marked[x][y] = '#';
    }
    
    r.push_back(r[0]);
    c.push_back(c[0]);

    for(int i = 1; i < n+1; i++) {
        int r1 = mp[r[i]];
        int r2 = mp[r[i-1]];
        int c1 = mp[c[i]];
        int c2 = mp[c[i-1]];
        if(r1 == r2) {
            for(int j = min(c1,c2) + 1; j <= max(c1, c2) -1; j++) {
                marked[r1][j] = 'X';
            }
        } else if(c1 == c2) {
            for(int j = min(r1,r2) + 1; j <= max(r1, r2) - 1; j++) {
                marked[j][c1] = 'X';
            }
        }
    }
}

long long solve2(vector<int> &r, vector<int> &c) {
    int n = (int)r.size();
    minimize(r, c);
    createMap(r, c);
    // A point inside; Found manually by exploring minimized map.
    bfs(227,378);
    
    long long res = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(i == j) continue;
            int r1 = mp[r[i]];
            int c1 = mp[c[i]];
            int r2 = mp[r[j]];
            int c2 = mp[c[j]];
            bool isOk = true;
            for(int rr = min(r1,r2); rr <= max(r1,r2); rr++) {
                if(!isOk) break;
                for(int cc = min(c1,c2); cc <= max(c1,c2); cc++) {
                    if(marked[rr][cc] == '.') {
                        isOk = false;
                        break;
                    }
                }
            }
            if(isOk) {
                res = max(res, area(rmp[r1],rmp[c1],rmp[r2],rmp[c2]));
            }
        }
    }

    return res;
}

int main(int argc, const char * argv[]) {
    ifstream fin("input");
    string s;
    vector<int> r,c;
    while(getline(fin, s)) {
        vector<string> tmp = split(s, ",");
        r.push_back(stoi(tmp[1]));
        c.push_back(stoi(tmp[0]));
    }
    
    auto res1 = measureTime([&r, &c]() {
        return solve(r,c);
    });
    
    auto res2 = measureTime([&r, &c]() {
        return solve2(r,c);
    });
    
    cout << "Part 1: " << res1 << endl;
    cout << "Part 2: " << res2 << endl;
    return 0;
}
