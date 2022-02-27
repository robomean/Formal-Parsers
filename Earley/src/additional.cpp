#include "../lib/additional.h"

using namespace std;

// Выдает символ после точки
char after_dot(string& s) {
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '#' && i + 1 < s.size()) {
            return s[i + 1];
        }
    }
    return '\0';
}
// "A -> α#aβ" -> "A -> αa#β"
string mv_dot_right(string& s) {
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '#') {
            swap(s[i], s[i + 1]);
            return s;
        }
    }
    return s;
}
// Делает точку первым символом правой части правила
string mv_dot_start(string& s) {
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '>') {
            s = s.substr(0, i + 2) + '#' + s.substr(i + 2);
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
