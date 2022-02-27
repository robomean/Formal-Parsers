#include "../lib/DNA.h"
// Достраиваем к вершине из ситуаций все ситуации, к которым добираемся по пустому слову
void closure(set<string>& node, vector<string>& P) {
    auto st = node;
    for (auto situation : st) {
        char next = after_dot(situation); // символ после точки в ситуации st
        if (is_terminal(next)) {
            return; // выходим, если терминал
        }
        for (auto rule : P) {
            if (rule[0] == next) { // берем правила с символом next в левой части
                auto new_situation = mv_dot_start(rule);
                if (node.find(new_situation) == node.end()) {
                    node.insert(new_situation);
                }
            }
        }
    }
    if (node != st) {
        closure(node, P); // пока вершина меняется, замыкаем ее
    }
}

void GOTO(int num, char c, vector<set<string>>& DNA_nodes,
    vector<vector<int>>& DNA_transitions, vector<string>& P,
    set<char>& letters) {
    auto st = DNA_nodes[num]; // ситуации в вершине
    set<string> next_node;
    for (auto situation : st) {
        if (after_dot(situation) == c) {
            next_node.insert(mv_dot_right(situation)); // строим след. вершину, переходя по символу c
        }
    }
    closure(next_node, P);
    if (next_node.size() > 0 && node_exists(DNA_nodes, next_node) == -1) {
        DNA_nodes.push_back(next_node); // добавляем вершину, если ее еще нет и она непустая
    }
    DNA_transitions[num][letter_position(letters, c)] = node_exists(DNA_nodes, next_node); // не забываем добавить ребро
}

void build_DNA(int num, vector<set<string>>& DNA_nodes,
    vector<vector<int>>& DNA_transitions, vector<string>& P,
    set<char>& letters) {
    closure(DNA_nodes[num], P); // строим замыкание
    vector <int> a(letters.size(), -1); // если перехода нет, то -1
    DNA_transitions.push_back(a);
    for (auto c : letters) {
        GOTO(num, c, DNA_nodes, DNA_transitions, P, letters); // а затем строим GOTO по всем символам
    }
    if (num + 1 != DNA_nodes.size()) {
        build_DNA(num + 1, DNA_nodes, DNA_transitions, P, letters); // повторяем для каждого состояния
    }
}
