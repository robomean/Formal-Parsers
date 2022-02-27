#include <string>
#include <vector>

using namespace std;

struct Language {
    vector <string> P; // P - правила нашего языка
};

char after_dot(string& s);
string mv_dot_right(string& s);
string mv_dot_start(string& s);
bool ends_on_dot(string& s);
