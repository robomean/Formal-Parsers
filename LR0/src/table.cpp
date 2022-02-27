#include "../lib/table.h"

void build_shifts(int n, set<char> letters,
    vector<vector<int>>& DNA_transitions,
    vector<vector<string>>& table) {
    for (int i = 0; i < n; i++) {
        for (auto letter : letters) {
            int letter_pos = letter_position(letters, letter);
            int j = DNA_transitions[i][letter_pos];
            if (j != -1) {
                if (!is_terminal(letter)) {
                    table[i][letter_pos] = to_string(j);
                }
                else {
                    table[i][letter_pos] = "s(" + to_string(j) + ')';
                }
            }
        }
    }
}

void build_reduces(int n, vector<set<string>>& DNA_nodes,
    set<char>& letters, vector<vector<string>>& table,
    vector<string>& P) {
    for (int i = 0; i < n; i++) {
        for (auto s : DNA_nodes[i]) {
            if (ends_on_dot(s)) {
                for (auto letter : letters) {
                    if (is_terminal(letter)) {
                        if (rule_num(P, s) == 0 && letter != '$') {
                            continue;
                        }
                        table[i][letter_position(letters, letter)] = "r(" + to_string(rule_num(P, s)) + ')';
                    }
                }
            }
        }
    }
}

void build_table(int n, int alph_sz, set<char>& letters,
    vector<set<string>>& DNA_nodes, vector<vector<int>>& DNA_transitions,
    vector<vector<string>>& table, vector<string>& P) {
    table.assign(n, vector <string>(alph_sz));
    build_shifts(n, letters, DNA_transitions, table);
    build_reduces(n, DNA_nodes, letters, table, P);
}
