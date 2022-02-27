#include "additional.h"

bool calc_FIRST(vector<set<char>>& FIRST, char c, set<char>& letters, vector<string>& P);
void build_FIRST(vector<set<char>>& FIRST, set<char>& letters, vector<string>& P);
set <char> FIRST_str(string& s, vector<set<char>>& FIRST, set<char>& letters);
set<string> closure(set<string>& node, vector<set<char>>& FIRST, set<char>& letters, vector<string>& P);
void GOTO(int num, char c, vector<set<string>>& DNA_nodes,
    vector<vector<int>>& DNA_transitions, vector<string>& P,
    set<char>& letters, vector<set<char>>& FIRST);
void build_DNA(int num, vector<set<string>>& DNA_nodes,
    vector<vector<int>>& DNA_transitions, vector<string>& P,
    set<char>& letters, vector<set<char>>& FIRST); 
