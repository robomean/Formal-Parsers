#include "../lib/earley.h"

using namespace std;
// Если следующий за точкой символ из алфавита, передвигает точку за этот символ
void scan(vector<set<pair<string, int>>>& D, int j, Language& G, string& w) {
    if (j == 0) {
        return;
    }
    for (auto st : D[j - 1]) {
        // не делаем проверку, что из алфавита, т.   к. все символы w из алфавита
        if (after_dot(st.first) == w[j - 1]) {
            D[j].insert({ mv_dot_right(st.first), st.second });
        }
    }
}
// Возврат наверх
void complete(vector<set<pair<string, int>>>& D, int j, Language& G, string& w) {
    for (auto st_j : D[j]) {
        if (ends_on_dot(st_j.first)) {
            for (auto st_i : D[st_j.second]) {
                // взять только те, где точка перед B
                if (after_dot(st_i.first) == st_j.first[0]) {
                    D[j].insert({ mv_dot_right(st_i.first), st_i.second });
                }
            }
        }
    }
}
// Если следующий за точкой символ из вспомогательных символов, передвигает точку за этот символ
void predict(vector<set<pair<string, int>>>& D, int j, Language& G, string& w) {
    for (auto st : D[j]) {
        for (auto rule : G.P) {
            if (rule[0] == after_dot(st.first)) {
                D[j].insert({ mv_dot_start(rule), j });
            }
        }
    }
}
// Основной код
bool earley(Language& G, string w) {
    int n = w.size();
    vector<set<pair<string, int>>> D(n + 1); // В D[j] храним все ситуации, заканчивающиеся в j (невключительно в 0-индексации)
    D[0].insert({ "F -> #S", 0 }); // F - новое стартовое
    for (int j = 0; j <= n; j++) {
        scan(D, j, G, w);
        set<pair<string, int>> prev_Dj;
        // Проверяем, изменилось ли D[j]
        while (prev_Dj != D[j]) {
            prev_Dj = D[j];
            complete(D, j, G, w);
            predict(D, j, G, w);
        }
    }
    if (D[n].find({ "F -> S#", 0 }) != D[n].end()) {
        return true;
    }
    return false;
}
