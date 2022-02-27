#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
using namespace std;

void print_set(set<int>& a, string& s) {
    auto it = a.end();
    it--;
    for (auto e : a) {
        s += to_string(e);
        if (e != *it) s += ',';
    }
}

void print_solid_line(string& s) {
    s += "__________________\n";
}

void print_line(string& s) {
    s += "\n-----------------\n";
}

string print_res(set <set <int>>& processed, set <set<int>>& dfa_final_states,
    vector <vector <pair<set<int>, char>>>& dfa_transitions, map <set <int>, int >& dfa_numeration) {
    string ans = to_string(dfa_final_states.size()) + ' ' + to_string(processed.size());
    return ans;
}
