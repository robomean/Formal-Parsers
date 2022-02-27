#include "../lib/DNA.h"
// for char c calculate set First
bool calc_FIRST(vector<set<char>>& FIRST, char c, set<char>& letters, vector<string>& P) {
    int ind = letter_position(letters, c);
    int sz = FIRST[ind].size();
    if (is_terminal(c)) {
        FIRST[ind].insert(c);
        return sz != FIRST[ind].size();
    }
    for (auto rule : P) {
        string X = right_part(rule);
        bool eps = true;
        for (int i = 0; i < X.size(); i++) {
            if (eps) {
                for (auto c : FIRST[letter_position(letters, X[i])]) {
                    FIRST[ind].insert(c);
                }
            }
            if (!contains_eps(FIRST[letter_position(letters, X[i])])) {
                eps = false;
                break;
            }
        }
        if (eps) {
            FIRST[ind].insert('$');
        }
    }
    return sz != FIRST[ind].size();
}

void build_FIRST(vector<set<char>>& FIRST, set<char>& letters, vector<string>& P) {
    bool changed = true;
    while (changed) {
        changed = false;
        for (auto c : letters) {
            if (calc_FIRST(FIRST, c, letters, P)) {
                changed = true;
            }
        }
    }
}

set<char> FIRST_str(string& s, vector<set<char>>& FIRST, set<char>& letters) {
    bool eps = true;
    set <char> ans;
    for (int i = 0; i < s.size(); i++) {
        if (eps) {
            for (auto c : FIRST[letter_position(letters, s[i])]) {
                ans.insert(c);
            }
        }
        if (!contains_eps(FIRST[letter_position(letters, s[i])])) {
            eps = false;
            break;
        }
    }
    if (eps) {
        ans.insert('$');
    }
    return ans;
}

// Достраиваем к вершине из ситуаций все ситуации, к которым добираемся по пустому слову
set<string> closure(set<string>& node, vector<set<char>>& FIRST, set<char>& letters, vector<string>& P) {
    bool changed = true;
    auto st = node;
    set<string> next_node = node;
    while (changed) {
        changed = false;
        int sz = next_node.size();
        for (auto st : next_node) {
            for (auto rule : P) {
                if (rule[0] == after_dot_char(st)) {
                    string s = str_for_FIRST(st);
                    for (auto c : FIRST_str(s, FIRST, letters)) {
                        next_node.insert(make_st(rule, c));
                        if (!changed) {
                            changed = (sz != next_node.size());
                        }
                    }
                }
            }
        }
    }
    return next_node;
}

void GOTO(int num, char c, vector<set<string>>& DNA_nodes,
    vector<vector<int>>& DNA_transitions, vector<string>& P,
    set<char>& letters, vector<set<char>>& FIRST) {
    auto st = DNA_nodes[num]; // ситуации в вершине
    set<string> next_node;
    for (auto situation : st) {
        if (after_dot_char(situation) == c) {
            next_node.insert(mv_dot_right(situation)); // строим след. вершину, переходя по символу c
        }
    }
    next_node = closure(next_node, FIRST, letters, P);
    if (next_node.size() > 0 && node_exists(DNA_nodes, next_node) == -1) {
        DNA_nodes.push_back(next_node); // добавляем вершину, если ее еще нет и она непустая
    }
    DNA_transitions[num][letter_position(letters, c)] = node_exists(DNA_nodes, next_node); // не забываем добавить ребро
}

void build_DNA(int num, vector<set<string>>& DNA_nodes,
    vector<vector<int>>& DNA_transitions, vector<string>& P,
    set<char>& letters, vector<set<char>>& FIRST) {
    DNA_nodes[num] = closure(DNA_nodes[num], FIRST, letters, P); // строим замыкание
    vector <int> a(letters.size(), -1); // если перехода нет, то -1
    DNA_transitions.push_back(a);
    for (auto c : letters) {
        GOTO(num, c, DNA_nodes, DNA_transitions, P, letters, FIRST); // а затем строим GOTO по всем символам
    }
    if (num + 1 != DNA_nodes.size()) {
        build_DNA(num + 1, DNA_nodes, DNA_transitions, P, letters, FIRST); // повторяем для каждого состояния
    }
}
