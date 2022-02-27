#include <set>
#include <string>
#include <stdexcept>
#include <vector>

using namespace std;

bool is_terminal(char letter);
void check_P(vector<string>& P);
void divide_P(vector<string>& P, vector<string>& rules_one_terminal,
    vector<string>& rules_two_non_terminal);
int pos_in_set(set<char>& non_terminals, char find);
