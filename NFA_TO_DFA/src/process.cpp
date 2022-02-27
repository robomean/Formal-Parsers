#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
using namespace std;

void add_eps_transitions(vector <vector <vector <int>>>& transitions, int number_of_states, int alph_sz);
void add_finals(vector <vector <vector <int>>>& transitions, set<int>& final_states, int num_of_states, int alph_sz);
void add_new_transitions(vector <vector <vector <int>>>& transitions, set<int>& final_states, int num_of_states, int alph_sz);

void push_start_state(queue <set<int>>& cur_dfa_states, map <set <int>, int>& dfa_numeration, int& num_of_node_in_dfa,
    set <set <int>>& processed, vector <vector <pair<set<int>, char>>>& dfa_transitions);
void build_dfa(set <set <int>>& processed, vector <vector <vector <int>>>& nfa_transitions,
    int& num_of_node_in_dfa, queue <set<int>>& cur_dfa_states, map <set <int>, int >& dfa_numeration,
    vector <vector <pair<set<int>, char>>>& dfa_transitions, int alph_sz);
void find_new_finals(set <set <int>>& processed, set <int>& final_states, set <set<int>>& dfa_final_states);

string print_res(set <set <int>>& processed, set <set<int>>& dfa_final_states,
    vector <vector <pair<set<int>, char>>>& dfa_transitions, map <set <int>, int >& dfa_numeration);

string process(int& num_of_states, int& num_of_finals, int& alph_sz,
    set<int>final_states, vector <vector <vector <int>>> nfa_transitions) {
    map <set <int>, int > dfa_numeration;
    set <set <int>> processed;
    // build EPS-closure
    add_eps_transitions(nfa_transitions, num_of_states, alph_sz);
    add_finals(nfa_transitions, final_states, num_of_states, alph_sz);
    add_new_transitions(nfa_transitions, final_states, num_of_states, alph_sz);
    queue <set<int>> cur_dfa_states;
    vector <vector <pair<set<int>, char>>> dfa_transitions;
    int num_of_node_in_dfa = 1;
    push_start_state(cur_dfa_states, dfa_numeration, num_of_node_in_dfa, processed, dfa_transitions);
    build_dfa(processed, nfa_transitions, num_of_node_in_dfa, cur_dfa_states, dfa_numeration, dfa_transitions, alph_sz);
    set <set <int>> dfa_final_states;
    find_new_finals(processed, final_states, dfa_final_states);
    return print_res(processed, dfa_final_states, dfa_transitions, dfa_numeration);
}
