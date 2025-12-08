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
#include "UnionFind.h"
#include "Common.h"

using namespace std;

struct Point {
    int i;
    long long x,y,z;
};

struct Dist {
    Point p1, p2;
    long long distSq;
    bool operator <(const Dist &d) const {
        return distSq < d.distSq;
    }
};

long long distSq(Point p1, Point p2) {
    long long x2 = p2.x - p1.x;
    long long y2 = p2.y - p1.y;
    long long z2 = p2.z - p1.z;
    return x2 * x2 + y2 * y2 + z2 * z2;
}

bool vis[1001][1001];
vector<int> graph[1001];
int N;
bool seen[1001];

int dfs(int u) {
    seen[u] = true;
    int res = 1;
    for(int i = 0; i < graph[u].size(); i++) {
        int v = graph[u][i];
        if(seen[v]) continue;
        res += dfs(v);
    }
    return res;
}

long long solve(vector<Point> p) {
    vector<Dist> d;
    int n = (int)p.size();
    
    for(int i = 0; i < n; i++) {
        for(int j = i+1; j< n; j++) {
            Dist D;
            D.p1 = p[i];
            D.p2 = p[j];
            D.distSq = distSq(p[i],p[j]);
            d.push_back(D);
        }
    }
    sort(d.rbegin(), d.rend());
    
    int cnt = 1000;
    int pos = (int)d.size()-1;
    while(cnt > 0 && pos >= 0) {
        if(d.size() == 0) break;
        Dist tmp = d[pos];
        int u = tmp.p1.i;
        int v = tmp.p2.i;
        if(!vis[u][v]) {
            graph[u].push_back(v);
            graph[v].push_back(u);
            vis[u][v] = vis[v][u] = true;
        }
        cnt--;
        pos--;
        
    }
    
    vector<long long> circuitSizes;
    memset(seen, false, sizeof seen);
    for(int i = 0; i < N; i++) {
        if(!seen[i]) {
            long long circuitSize = dfs(i);
            circuitSizes.push_back(circuitSize);
        }
    }
    
    long long res = 1;
    sort(circuitSizes.rbegin(), circuitSizes.rend());
    for(int i = 0; i < 3; i++) {
        res *= circuitSizes[i];
    }
    return res;
}

long long solve2(vector<Point> p) {
    
    vector<Dist> d;
    
    int n = (int)p.size();
    
    for(int i = 0; i < n; i++) {
        for(int j = i+1; j< n; j++) {
            Dist D;
            D.p1 = p[i];
            D.p2 = p[j];
            D.distSq = distSq(p[i],p[j]);
            d.push_back(D);
        }
    }

    sort(d.rbegin(), d.rend());
    int pos = (int)d.size() - 1;
    
    auto unionFind = UnionFind(N);
    while(pos >= 0) {
        if(d.size() == 0) break;
        Dist tmp = d[pos];
        int u = tmp.p1.i;
        int v = tmp.p2.i;
        if(!unionFind.find(u, v)) {
            int size = unionFind.unite(u, v);
            cout << size << endl;
            if(size == N) {
                return (long long)tmp.p1.x * (long long)tmp.p2.x;
            }
        }
        pos--;
    }

    return -1;
}


int main(int argc, const char * argv[]) {
    ifstream fin("input");
    
    string s;
    vector<Point> p;

    int cnt = 0;
    while(getline(fin, s)) {
        vector<string> v = split(s, ",");
        Point P;
        
        P.x = stoi(v[0]);
        P.y = stoi(v[1]);
        P.z = stoi(v[2]);
        P.i = cnt++;
        p.push_back(P);
    }
    N = cnt;
    
    
    auto res1 = measureTime([&p]() {
        return solve(p);
    });
    
    auto res2 = measureTime([&p]() {
        return solve2(p);
    });
    
    cout << "Part 1: " << res1 << endl;
    cout << "Part 2: " << res2 << endl;
    return 0;
}
