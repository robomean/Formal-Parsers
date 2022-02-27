#include <algorithm>
#include <iostream>
#include <set>

#include "additional.h"

using namespace std;

void scan(vector<set<pair<string, int>>>& D, int j, Language& G, string& w);
void complete(vector<set<pair<string, int>>>& D, int j, Language& G, string& w);
void predict(vector<set<pair<string, int>>>& D, int j, Language& G, string& w);
bool earley(Language& G, string w); 
