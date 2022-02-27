#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
using namespace std;

void build_reversed_transitions(vector <vector <vector<int>>>& reversed_dfa_transitions, vector <vector <int>>& dfa_transitions, int num_of_states, int alph_sz) {
    for (int state = 0; state < num_of_states; state++) {
        for (int letter = 0; letter < alph_sz; letter++) {
            int to = dfa_transitions[state][letter];
            reversed_dfa_transitions[to][letter].push_back(state);
        }
    }
}

void init_eq_states(int num_of_states, set <int>& dfa_final_states, vector <int>& component) {
    for (auto f_state: dfa_final_states) {
        component[f_state] = 1;
    }
}

void find_eq_states(int num_of_states, int& comp_cnt, vector <int>& component, vector <vector<int>>& dfa_transitions, set <int>& dfa_final_states, int alph_sz) {
    vector <vector <int>> cur_eq_states(num_of_states, vector<int> (alph_sz + 1));
    for (int iter = 0; iter < num_of_states; iter++) {
        map <vector <int>, int> mp;
        comp_cnt = 0;
        for (int state = 1; state < num_of_states; state++) {
            for (int letter = 0; letter < alph_sz; letter++) {
                cur_eq_states[state][letter] = component[dfa_transitions[state][letter]];
            }
            if (dfa_final_states.find(state) != dfa_final_states.end()) {
                cur_eq_states[state][alph_sz] = 1;
            }
            if (mp[cur_eq_states[state]] == 0) {
                mp[cur_eq_states[state]] = ++comp_cnt;
            }
        }
        for (int state = 1; state < num_of_states; state++) {
            component[state] = mp[cur_eq_states[state]];
        }
    }
}


void build_new_dfa(int num_of_states, int alph_sz, vector <int>& component, vector <vector <int>>& mdfa_transitions, vector <vector <int>>& dfa_transitions, set <int>& dfa_final_states, set <int>& mdfa_final_states) {
    for (int state = 0; state < num_of_states; state++) {
        if (component[state] == -1) continue;
        for (int letter = 0; letter < alph_sz; letter++) {
            mdfa_transitions[component[state]][letter] = max(component[dfa_transitions[state][letter]], 0);
        }
    }
    for (auto compound_state : dfa_final_states) {
        mdfa_final_states.insert(component[compound_state]);
    }
}
