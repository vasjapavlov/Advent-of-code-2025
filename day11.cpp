#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <tuple>
#include <algorithm>
#include <numeric>
#include "Common.h"

using namespace std;

typedef map<string, vector<string>> Graph;
typedef map<tuple<string, bool, bool>, long long> MEMO2;

Graph graph;

Graph parseInput(string input) {
    Graph graph;
    stringstream is(input);
    string line;

    while (getline(is, line)) {
        stringstream isLine(line);
        string source;
        getline(isLine, source, ':');
        string nodes;
        getline(isLine, nodes);
        stringstream isNodes(nodes);
        
        string node;
        while (isNodes >> node) {
            graph[source].push_back(node);
        }
    }
    return graph;
}

long long count1(string cur, map<string, long long> &memo) {
    if (memo.count(cur)) {
        return memo[cur];
    }

    if (cur == "out") {
        return 1;
    }

    long long res = 0;
    
    for(string &next : graph[cur]) {
        res += count1(next, memo);
    }
    
    return memo[cur] = res;
}

long long solve1() {
    map<string, long long> memo;
    return count1("you", memo);
}

long long count2(string cur, bool dac, bool fft, MEMO2 &memo) {
    tuple<string, bool, bool> curState = make_tuple(cur, dac, fft);

    if (memo.count(curState)) {
        return memo[curState];
    }

    if (cur == "out") {
        return (dac && fft) ? 1 : 0;
    }

    long long res = 0;
    
    for(string &next : graph[cur]) {
        bool nDac = dac || (next == "dac");
        bool nFft = fft || (next == "fft");

        res += count2(next, nDac, nFft, memo);
    }
    
    return memo[curState] = res;
}

long long solve2() {
    map<tuple<string, bool, bool>, long long> memo;
    return count2("svr", false, false, memo);
}

int main() {
    ifstream fin("input");
    
    string input((istreambuf_iterator<char>(fin)), istreambuf_iterator<char>());
    
    graph = parseInput(input);
    
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
