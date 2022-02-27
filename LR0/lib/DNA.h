#include "additional.h"

void closure(set<string>& node, vector<string>& P);
void GOTO(int num, char c, vector<set<string>>& DNA_nodes,
    vector<vector<int>>& DNA_transitions, vector<string>& P,
    set<char>& letters);
void build_DNA(int num, vector<set<string>>& DNA_nodes,
    vector<vector<int>>& DNA_transitions, vector<string>& P,
    set<char>& letters); 
