#include "DNA.h"
void build_shifts(set<char> letters, vector<vector<int>>& DNA_transitions,
    vector<vector<string>>& table);
void build_reduces(vector<set<string>>& DNA_nodes, set<char>& letters,
    vector<vector<string>>& table, vector<string>& P);
void build_table(int n, int alph_sz, set<char>& letters,
    vector<set<string>>& DNA_nodes, vector<vector<int>>& DNA_transitions,
    vector<vector<string>>& table, vector<string>& P);
