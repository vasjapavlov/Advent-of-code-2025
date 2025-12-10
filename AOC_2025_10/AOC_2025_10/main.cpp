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

// #..#
int parseIndicator(string s) {
    int res = 0;
    s = s.substr(1, s.size() - 2);
//    reverse(s.begin(), s.end());
    for(int i = 0; i < s.size(); i++) {
        if(s[i] == '#') {
            res |= (1 << i);
        }
    }
    return res;
}

// (1,2,3)
int parseButton(string s) {
    int button = 0;
    s = s.substr(1, s.size() -2);
    vector<string> tmp = split(s, ",");
    for(int i = 0; i < tmp.size(); i++) {
        button |= (1 << stoi(tmp[i]));
    }
    return button;
}

// {10,11,11,5,10,5}
vector<int> parseJoltage(string s) {
    vector<int> joltage;
    s = s.substr(1, s.size() -2);
    vector<string> tmp = split(s, ",");
    for(int i = 0; i < tmp.size(); i++) {
        joltage.push_back(stoi(tmp[i]));
    }
    return joltage;
}

struct Machine {
    int ind;
    vector<int> buttons;
    vector<int> joltage;
    Machine(int _ind, vector<int> _buttons, vector<int> _joltage) {
        ind = _ind;
        buttons = _buttons;
        joltage = _joltage;
    }
    
};

Machine parseMachine(string s) {
    vector<string> v = split(s, " ");
    int indicator = parseIndicator(v[0]);
    vector<int> buttons;
    for(int i = 1; i < v.size() -1; i++) {
        buttons.push_back(parseButton(v[i]));
    }
    vector<int> joltage = parseJoltage(v[v.size()-1]);
    return Machine(indicator, buttons, joltage);
}

int solve(vector<Machine> machines) {
    int res = 0;
    for(int i = 0; i < machines.size(); i++) {
        Machine m = machines[i];
        int nb = (int)m.buttons.size();
        int tmpRes = 20;
        if(m.ind == 0) continue;
        for(int mask = 0; mask < (1 << nb); mask++) {
            int x = 0;
            for(int k = 0; k < nb; k++) {
                if((mask & (1 << k)) != 0) {
                    x ^= m.buttons[k];
                }
            }
            int popCount = __builtin_popcount(mask);
            if(x == m.ind && popCount < tmpRes) {
                tmpRes = popCount;
            }
        }
        res += tmpRes;
    }
    return res;
}

int main(int argc, const char * argv[]) {
    ifstream fin("input");
    string s;
    
    vector<Machine> machines;
    while(getline(fin, s)) {
        machines.push_back(parseMachine(s));
    }

    auto res1 = measureTime([&machines]() {
        return solve(machines);
    });
    
//    auto res2 = measureTime([&machines]() {
//        return solve2(machines);
//    });
    
    cout << "Part 1: " << res1 << endl;
//    cout << "Part 2: " << res2 << endl;
    return 0;
}
