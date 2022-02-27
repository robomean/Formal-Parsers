#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
using namespace std;

// simple find-method in vector
bool in_vector(vector <int> nodes, int node) {
    for (auto e : nodes) {
        if (e == node) return true;
    }
    return false;
}

void add_eps_transitions(vector <vector <vector <int>>>& transitions, int number_of_states, int alph_sz) {
    for (int iteration = 0; iteration < number_of_states; iteration++) {
        for (int from = 1; from <= number_of_states; from++) {
            for (int to_index = 0; to_index < transitions[from][alph_sz].size(); to_index++) { //transitions[from][alph_sz] - nodes that can be achieved by #
                int to = transitions[from][alph_sz][to_index]; //to - node that can be achieved by # from "from"
                for (int next_to_index = 0; next_to_index < transitions[to][alph_sz].size(); next_to_index++) {
                    if (!in_vector(transitions[from][alph_sz], transitions[to][alph_sz][next_to_index])) //if there are no "to_next" in transitions[from][alph_sz] let's push_back it
                        transitions[from][alph_sz].push_back(transitions[to][alph_sz][next_to_index]);
                }
            }
        }
    }
}

void add_finals(vector <vector <vector <int>>>& transitions, set<int>& final_states, int num_of_states, int alph_sz) {
    for (int from = 1; from <= num_of_states; from++) {
        for (auto to : transitions[from][alph_sz]) {
            if (final_states.find(to) != final_states.end()) {  // if we can reach final_state by #, then we are in final state
                final_states.insert(from);
            }
        }
    }
}

void add_new_transitions(vector <vector <vector <int>>>& transitions, set<int>& final_states, int num_of_states, int alph_sz) {
    for (int iteration = 0; iteration < num_of_states; iteration++) {
        for (int from = 1; from <= num_of_states; from++) {
            for (int to_index = 0; to_index < transitions[from][alph_sz].size(); to_index++) {
                int to = transitions[from][alph_sz][to_index];
                for (int letter = 0; letter < alph_sz; letter++) {
                    for (int next_to_index = 0; next_to_index < transitions[to][letter].size(); next_to_index++) {
                        if (!in_vector(transitions[from][letter], transitions[to][letter][next_to_index])) { // if we can reach next_to, but we don't have it in transitions, let's add it
                            transitions[from][letter].push_back(transitions[to][letter][next_to_index]);
                        }
                    }
                }
            }
        }
    }
}
