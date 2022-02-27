#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
using namespace std;

void push_start_state(queue <set<int>>& cur_dfa_states, map <set <int>, int>& dfa_numeration,
    int& num_of_node_in_dfa, set <set <int>>& processed, vector <vector <pair<set<int>, char>>>& dfa_transitions) {
    cur_dfa_states.push({ 1 });
    dfa_numeration[{1}] = num_of_node_in_dfa;
    num_of_node_in_dfa++;
    processed.insert({ 1 });
    dfa_transitions.push_back({});
}

void check_if_new(set <set <int>>& processed, set <int>& new_state, set <int>& cur_state,
    int& num_of_node_in_dfa, queue <set<int>>& cur_dfa_states, map <set <int>, int >& dfa_numeration,
    vector <vector <pair<set<int>, char>>>& dfa_transitions, int letter) {
    if (processed.find(new_state) == processed.end()) {
        processed.insert(new_state);
        cur_dfa_states.push(new_state);
        dfa_numeration[new_state] = num_of_node_in_dfa;
        num_of_node_in_dfa++;
    }
    dfa_transitions[dfa_numeration[cur_state]].push_back({ new_state, 'a' + letter });
}

void build_dfa(set <set <int>>& processed, vector <vector <vector <int>>>& nfa_transitions,
    int& num_of_node_in_dfa, queue <set<int>>& cur_dfa_states, map <set <int>, int >& dfa_numeration,
    vector <vector <pair<set<int>, char>>>& dfa_transitions, int alph_sz) {
    while (!cur_dfa_states.empty()) {
        set <int> cur_state = cur_dfa_states.front();
        cur_dfa_states.pop();
        dfa_transitions.push_back({});
        for (int letter = 0; letter < alph_sz; letter++) {
            set <int> new_state;
            for (auto state : cur_state) { // for each node from cur
                for (auto node : nfa_transitions[state][letter])
                    new_state.insert(node); // insert points of arrivals in set
            }
            if (new_state.size() == 0) continue;
            check_if_new(processed, new_state, cur_state, num_of_node_in_dfa, cur_dfa_states, dfa_numeration, dfa_transitions, letter);
        }
    }
}

void find_new_finals(set <set <int>>& processed, set <int>& final_states, set <set<int>>& dfa_final_states) {
    for (auto compound_state : processed) {
        for (auto final_state : final_states) {
            if (compound_state.find(final_state) != compound_state.end()) {
                dfa_final_states.insert(compound_state);
            }
        }
    }
}
