#include "../lib/additional.h"

bool is_terminal(char letter) {
    return (letter < 'A' || letter > 'Z');
}

void check_P(vector<string>& P) {
    bool error = false;
    for (auto rule : P) {
        if (rule.size() < 4 || is_terminal(rule[0]) || rule[1] != '-' || rule[2] != '>') {
            error = true;
            continue;
        }
        if (is_terminal(rule[3])) {
            if (rule.size() != 4) {
                error = true;
            }
            continue;
        }
        if (rule.size() != 5 || is_terminal(rule[4])) {
            error = true;
        }
    }
    if (error) {
        throw runtime_error("Wrong input format!");
    }
}

void divide_P(vector<string>& P, vector<string>& rules_one_terminal, vector<string>& rules_two_non_terminal) {
    for (auto rule : P) {
        if (is_terminal(rule[3])) {
            rules_one_terminal.push_back(rule);
        }
        else {
            rules_two_non_terminal.push_back(rule);
        }
    }
}

int pos_in_set(set<char>& non_terminals, char find) {
    int cnt = 0;
    for (auto c : non_terminals) {
        if (c == find) {
            return cnt;
        }
        cnt++;
    }
    return -1;
}
