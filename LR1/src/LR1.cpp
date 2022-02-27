#include "../lib/LR1.h"

bool LR_algorithm(string w, set<char>& letters, stack<string>& st,
    vector<string>& P, vector<vector<int>> DNA_transitions,
    vector<vector<string>>& table) {
    for (int i = 0; i < w.size(); i++) {
        int cur_state = stoi(st.top());
        string t_status = table[cur_state][letter_position(letters, w[i])];
        if (t_status[0] == 's') { // shift
            st.push(string(1, w[i]));
            string state = t_status.substr(2);
            state.pop_back();
            st.push(state);
        }
        if (is_digit(t_status[0])) { // shift
            st.push(string(1, w[i]));
            st.push(t_status);
        }
        if (t_status == "r(0)") { // accept
            return true;
        }
        if (t_status[0] == 'r') { // reduce
            string state = t_status.substr(2);
            state.pop_back();
            string s = P[stoi(state)];
            auto rule = div_rule(s);
            for (int j = 0; j < rule.second.size(); j++) {
                st.pop();
                st.pop();
            }
            s = st.top();
            st.push(rule.first);
            st.push(to_string(DNA_transitions[stoi(s)][letter_position(letters, rule.first[0])]));
            i--; // не должны переходить на след. букву в reduce
        }
        if (t_status == "") { // error
            return false;
        }
    }
    return false;
}

bool in_language(vector<string>& P, string& w) {
    int n, alph_sz;
    set<char> letters = { '$' }; // пустое слово
    vector<set<string>> DNA_nodes;
    vector<vector <int>> DNA_transitions;
    vector<vector <string>> table;
    stack<string> st;
    DNA_nodes.push_back({ "S->#E,$" });
    build_letters(P, letters);
    vector<set<char>> FIRST(letters.size());
    build_FIRST(FIRST, letters, P);
    build_DNA(0, DNA_nodes, DNA_transitions, P, letters, FIRST);
    n = DNA_nodes.size();
    alph_sz = letters.size();
    build_table(n, alph_sz, letters, DNA_nodes, DNA_transitions, table, P);
    st.push("0");
    w += '$';
    for (auto letter : w) {
        if (letter_position(letters, letter) == -1) {
            return false;
        }
    }
    if (LR_algorithm(w, letters, st, P, DNA_transitions, table)) {
        return true;
    }
    else {
        return false;
    }
}
