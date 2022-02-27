#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
using namespace std;

void read_first(int& num_of_states, int& num_of_finals, int& alph_sz);
void read_finals(set <int>& final_states, int num_of_finals);
void read_transitions(vector <vector <vector <int>>>& transitions);

void add_eps_transitions(vector <vector <vector <int>>>& transitions, int number_of_states, int alph_sz);
void add_finals(vector <vector <vector <int>>>& transitions, set<int>& final_states, int num_of_states, int alph_sz);
void add_new_transitions(vector <vector <vector <int>>>& transitions, set<int>& final_states, int num_of_states, int alph_sz);

void push_start_state(queue <set<int>>& cur_dfa_states, map <set <int>, int>& dfa_numeration, int& num_of_node_in_dfa,
    set <set <int>>& processed, vector <vector <int>>& dfa_transitions, int alph_sz);
void build_dfa(set <set <int>>& processed, vector <vector <vector <int>>>& nfa_transitions,
    int& num_of_node_in_dfa, queue <set<int>>& cur_dfa_states, map <set <int>, int >& dfa_numeration,
    vector <vector <int>>& dfa_transitions, int alph_sz);
void find_new_finals(set <set <int>>& processed, map <set <int>, int >& dfa_numeration, set <int>& final_states, set <int>& dfa_final_states);

void build_reversed_transitions(vector <vector <vector<int>>>& reversed_dfa_transitions, vector <vector <int>>& dfa_transitions, int num_of_states, int alph_sz);
void init_eq_states(int num_of_states, set <int>& dfa_final_states, vector <int>& component);
void find_eq_states(int num_of_states, int& comp_cnt, vector <int>& component, vector <vector<int>>& dfa_transitions, set <int>& dfa_final_states, int alph_sz);
void build_new_dfa(int num_of_states, int alph_sz, vector <int>& component, vector <vector <int>>& mdfa_transitions, vector <vector <int>>& dfa_transitions, set <int>& dfa_final_states, set <int>& mdfa_final_states);

string print_res(int num_of_states, int alph_sz, set <int>& dfa_final_states, vector <vector <int>>& dfa_transitions);

string process(int& num_of_states, int& num_of_finals, int& alph_sz,
    set<int>final_states, vector <vector <vector <int>>> nfa_transitions) {
    map <set <int>, int > dfa_numeration;
    set <set <int>> processed;
    // build EPS-closure
    add_eps_transitions(nfa_transitions, num_of_states, alph_sz);
    add_finals(nfa_transitions, final_states, num_of_states, alph_sz);
    add_new_transitions(nfa_transitions, final_states, num_of_states, alph_sz);
    queue <set<int>> cur_dfa_states;
    vector <vector <int>> dfa_transitions;
    int num_of_node_in_dfa = 1;
    push_start_state(cur_dfa_states, dfa_numeration, num_of_node_in_dfa, processed, dfa_transitions, alph_sz);
    build_dfa(processed, nfa_transitions, num_of_node_in_dfa, cur_dfa_states, dfa_numeration, dfa_transitions, alph_sz);
    set <int> dfa_final_states;
    find_new_finals(processed, dfa_numeration, final_states, dfa_final_states);

    // Let's forget about NFA and work with DFA
    num_of_finals = dfa_final_states.size(); num_of_states = dfa_transitions.size();

    vector <int> component(num_of_states, 0);
    int comp_cnt = 1;
    init_eq_states(num_of_states, dfa_final_states, component);
    find_eq_states(num_of_states, comp_cnt, component, dfa_transitions, dfa_final_states, alph_sz);
    vector <vector <int>> mdfa_transitions(comp_cnt + 1, vector <int>(alph_sz));
    set <int> mdfa_final_states;
    build_new_dfa(num_of_states, alph_sz, component, mdfa_transitions, dfa_transitions, dfa_final_states, mdfa_final_states); // step 6

    return print_res(comp_cnt, alph_sz, mdfa_final_states, mdfa_transitions);
}
