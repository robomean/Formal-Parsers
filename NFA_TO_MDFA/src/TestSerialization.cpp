#include "gtest/gtest.h"

#include <fstream>
#include <set>
#include <string>
#include <streambuf>
#include <vector>
using namespace std;

string process(int& num_of_states, int& num_of_finals, int& alph_sz,
    set<int>final_states, vector <vector <vector <int>>> nfa_transitions); 

class TestSerialization : public ::testing::Test {};

TEST_F(TestSerialization, HardTest) {
    int num_of_states = 7;
    int num_of_finals = 1;
    int alph_sz = 2;
    set <int> final_states = {2};
    vector <vector <vector <int>>> nfa_transitions(num_of_states + 1, vector <vector<int>>(alph_sz + 1));
    nfa_transitions[1][0].push_back(2);
    nfa_transitions[2][1].push_back(2);
    nfa_transitions[2][0].push_back(3);
    nfa_transitions[3][0].push_back(2);
    nfa_transitions[3][0].push_back(6);
    nfa_transitions[3][0].push_back(4);
    nfa_transitions[4][0].push_back(5);
    nfa_transitions[5][1].push_back(7);
    nfa_transitions[5][1].push_back(2);
    nfa_transitions[6][1].push_back(3);
    nfa_transitions[7][0].push_back(5);
    string f = process(num_of_states, num_of_finals, alph_sz, final_states, nfa_transitions);
    string ans = "8 5";
    ASSERT_EQ(f, ans);
}

TEST_F(TestSerialization, SimpleTest1) {
    int num_of_states = 2;
    int num_of_finals = 1;
    int alph_sz = 2;
    set <int> final_states = {2};
    vector <vector <vector <int>>> nfa_transitions(num_of_states + 1, vector <vector<int>>(alph_sz + 1));
    nfa_transitions[1][0].push_back(2);
    nfa_transitions[1][1].push_back(1);
    nfa_transitions[1][0].push_back(1);
    nfa_transitions[2][1].push_back(2);
    nfa_transitions[2][1].push_back(1);
    string f = process(num_of_states, num_of_finals, alph_sz, final_states, nfa_transitions);
    string ans = "2 1";
    ASSERT_EQ(f, ans);
}

TEST_F(TestSerialization, SimpleTest2) {
    int num_of_states = 3;
    int num_of_finals = 1;
    int alph_sz = 1;
    set <int> final_states = {2};
    vector <vector <vector <int>>> nfa_transitions(num_of_states + 1, vector <vector<int>>(alph_sz + 1));
    nfa_transitions[1][1].push_back(2);
    nfa_transitions[2][1].push_back(3);
    nfa_transitions[1][1].push_back(3);
    nfa_transitions[2][0].push_back(2);
    string f = process(num_of_states, num_of_finals, alph_sz, final_states, nfa_transitions);
    string ans = "1 1";
    ASSERT_EQ(f, ans);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

