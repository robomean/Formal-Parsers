#include "../lib/additional.h"
// Возвращает символ после точки 
char after_dot(string& s) {
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '#' && i + 1 < s.size()) {
            return s[i + 1];
        }
    }
    return '\0';
}
// "A -> z#at" -> "A -> za#t"
string mv_dot_right(string s) {
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '#') {
            swap(s[i], s[i + 1]);
            return s;
        }
    }
    return s;
}
// Делает точку первым символом правой части правила
string mv_dot_start(string s) {
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '>') {
            s = s.substr(0, i + 1) + '#' + s.substr(i + 1);
            return s;
        }
    }
    return s;
}
// Проверяет, заканчивается ли правило на точку
bool ends_on_dot(string& s) {
    if (s[s.size() - 1] == '#') {
        return true;
    }
    return false;
}
// Убирает точку из ситуации
void rm_dot(string& s) {
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '#') {
            s = s.substr(0, i) + s.substr(i + 1);
        }
    }
}
// Делит правило на левую часть и правую
pair<string, string> div_rule(string s) {
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '>') {
            return { s.substr(0, i - 1), s.substr(i + 1) };
        }
    }
    return {"", ""};
}
// Номер правила по правилу
int rule_num(vector<string>& P, string s) {
    rm_dot(s);
    for (int i = 0; i < P.size(); i++) {
        if (P[i] == s) {
            return i;
        }
    }
    return -1;
}
// Номер вершины (если не сущ., то -1)
int node_exists(vector<set<string>>& DNA_nodes, set<string>& new_node) {
    for (int i = 0; i < DNA_nodes.size(); i++) {
        if (DNA_nodes[i] == new_node) {
            return i;
        }
    }
    return -1;
}
// Возвращает позицию буквы в set letters
int letter_position(set<char>& letters, char c) {
    int ans = 0;
    for (auto letter : letters) {
        if (letter == c) {
            return ans;
        }
        ans++;
    }
    return -1;
}

bool is_terminal(char letter) {
    return (letter < 'A' || letter > 'Z');
}

bool is_digit(char c) {
    return (c >= '0' && c <= '9');
}
// Построение set letters
void build_letters(vector<string>& P, set<char>& letters) {
    for (auto s : P) {
        for (auto c : s) {
            if (c != '-' && c != '>') {
                letters.insert(c);
            }
        }
    }
}
