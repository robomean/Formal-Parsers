#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
using namespace std;

void print_set(set<int>& a) {
    auto it = a.end();
    it--;
    for (auto e : a) {
        cout << e;
        if (e != *it) cout << ',';
    }
}

void print_solid_line() {
    cout << "__________________\n";
}

void print_line() {
    cout << "\n-----------------\n";
}

string print_res(int num_of_states, int alph_sz, set <int>& mdfa_final_states, vector <vector <int>>& mdfa_transitions) {
    string ans = to_string(num_of_states) + ' ' + to_string(mdfa_final_states.size());
    return ans;
}
