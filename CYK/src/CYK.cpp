#include "../lib/CYK.h"

bool in_language(string& w, vector<string>& P) {
    int n = w.size();
    check_P(P);
    if (w.size() == 0) {
        bool empty_word = false;
        for (auto rule : P) {
            if (rule == "S->$") {
                empty_word = true;
            }
        }
        return empty_word;
    }
    vector <string> rules_one_terminal, rules_two_non_terminal;
    divide_P(P, rules_one_terminal, rules_two_non_terminal);
    set<char> non_terminals;
    for (auto rule : P) {
        for (auto c : rule) {
            if (!is_terminal(c)) {
                non_terminals.insert(c);
            }
        }
    }
    int r = non_terminals.size();
    vector<vector<vector<bool>>> T(r, vector<vector<bool>>(n, vector<bool>(n, false)));
    for (int i = 0; i < n; i++) {
        for (auto rule : rules_one_terminal) {
            if (rule[3] == w[i]) {
                T[pos_in_set(non_terminals, rule[0])][i][i] = true; // Если есть правило A -> w[i], то 1
            }
        }
    }
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            for (int k = i; k < j; k++) {
                for (auto rule : rules_two_non_terminal)
                    if (T[pos_in_set(non_terminals, rule[3])][i][k] && T[pos_in_set(non_terminals, rule[4])][k + 1][j]) {
                        T[pos_in_set(non_terminals, rule[0])][i][j] = 1;
                    }
            }
        }
    }
    return T[pos_in_set(non_terminals, 'S')][0][n - 1];
}
