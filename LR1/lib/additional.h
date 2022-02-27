#include <set>
#include <string>
#include <vector>
using namespace std;

char after_dot_char(string& s);
string right_part(string& s);
string mv_dot_right(string s);
string mv_dot_start(string s);
bool ends_on_dot(string& s);
void rm_dot(string& s);
pair<string, string> div_rule(string s);
int rule_num(vector<string>& P, string s);
int node_exists(vector<set<string>>& DNA_nodes, set<string>& new_node);
int letter_position(set<char>& letters, char c);
bool is_terminal(char letter);
bool is_digit(char c);
bool contains_eps(set<char>& st);
string str_for_FIRST(string& s);
string make_st(string& s, char c);
void build_letters(vector<string>& P, set<char>& letters);
