#include <algorithm>
#include <iostream>
#include <stack>

#include "table.h"

bool LR_algorithm(string w, set<char>& letters, stack<string>& st,
    vector<string>& P, vector<vector<int>> DNA_transitions,
    vector<vector<string>>& table); 
bool in_language(vector<string>& P, string& w); 
