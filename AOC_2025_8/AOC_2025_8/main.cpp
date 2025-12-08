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

struct Vertex {
    int i;
    int x,y,z;
};

struct Edge {
    Vertex p1, p2;
    long long distSq;

    struct Comparator {
        bool operator ()(const Edge &e1, const Edge &e2) {
            return e1.distSq > e2.distSq;
        }
    };
};

long long distSq(Vertex p1, Vertex p2) {
    int dx = p2.x - p1.x;
    int dy = p2.y - p1.y;
    int dz = p2.z - p1.z;
    return (long long)dx * dx + (long long)dy * dy + (long long)dz * dz;
}

priority_queue<Edge, vector<Edge>, Edge::Comparator>sortedEdges(vector<Vertex> points) {
    auto n = points.size();
    priority_queue<Edge, vector<Edge>, Edge::Comparator> q;
        for(int i = 0; i < n; i++) {
            for(int j = i+1; j< n; j++) {
                Edge e;
                e.p1 = points[i];
                e.p2 = points[j];
                e.distSq = distSq(points[i],points[j]);
                q.push(e);
            }
        }
    return q;
}

long long solve(vector<Vertex> points) {
    int n = (int)points.size();
    auto q = sortedEdges(points);
    auto unionFind = UnionFind(n);
    
    for(int steps = 0; steps < 1000; steps++) {
        Edge e = q.top();
        q.pop();
        unionFind.unite(e.p1.i, e.p2.i);
    }
    long long res = 1;
    vector<int> islandSizes = unionFind.getIslandSizes();
    for(int i = 0; i < 3; i++) {
        res *= islandSizes[i];
    }
    return res;
}

long long solve2(vector<Vertex> points) {
    int n = (int)points.size();
    auto q = sortedEdges(points);
    auto unionFind = UnionFind(n);

    while(!q.empty()) {
        Edge tmp = q.top();
        q.pop();
        int u = tmp.p1.i;
        int v = tmp.p2.i;
        if(unionFind.find(u, v)) continue;
        int circuitSize = unionFind.unite(u, v);
        if(circuitSize == n) {
            return (long long)tmp.p1.x * (long long)tmp.p2.x;
        }
    }
    return -1;
}

int main(int argc, const char * argv[]) {
    ifstream fin("input");
    
    string s;
    vector<Vertex> points;

    int cnt = 0;
    while(getline(fin, s)) {
        vector<string> v = split(s, ",");
        Vertex p;
        
        p.x = stoi(v[0]);
        p.y = stoi(v[1]);
        p.z = stoi(v[2]);
        p.i = cnt++;
        points.push_back(p);
    }
    
    auto res1 = measureTime([&points]() {
        return solve(points);
    });
    
    auto res2 = measureTime([&points]() {
        return solve2(points);
    });
    
    cout << "Part 1: " << res1 << endl;
    cout << "Part 2: " << res2 << endl;
    return 0;
}
