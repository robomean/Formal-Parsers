#include "gtest/gtest.h"

#include "../lib/CYK.h"

class TestSerialization : public ::testing::Test {};

TEST_F(TestSerialization, SimpleYes1) {
    vector<string> P = {"S->AB", "A->a", "B->b"};
    string w = "ab";
    bool f = in_language(w, P);
    ASSERT_EQ(f, true);
}

TEST_F(TestSerialization, SimpleNo1) {
     vector<string> P = {"S->AB", "A->a", "B->b"};
     string w = "a";
     bool f = in_language(w, P);
     ASSERT_EQ(f, false);
}

TEST_F(TestSerialization, EmptyWordNo) {
     vector<string> P = {"S->AB", "A->a", "B->b"};
     string w = "";
     bool f = in_language(w, P);
     ASSERT_EQ(f, false);
}

TEST_F(TestSerialization, EmptyWordYes) {
     vector<string> P = {"S->AB", "A->a", "B->b", "S->$"};
     string w = "";
     bool f = in_language(w, P);
     ASSERT_EQ(f, true);
}

TEST_F(TestSerialization, PSPYes) {
     vector<string> P = {"S->BB", "S->CD", "B->BB", "B->CD", "C->(", "D->BE", "D->)", "E->)", "S->$"};
     string w = "()(())";
     bool f = in_language(w, P);
     ASSERT_EQ(f, true);
}

TEST_F(TestSerialization, PSPNo) {
     vector<string> P = {"S->BB", "S->CD", "B->BB", "B->CD", "C->(", "D->BE", "D->)", "E->)", "S->$"};
     string w = "()(()";
     bool f = in_language(w, P);
     ASSERT_EQ(f, false);
}

TEST_F(TestSerialization, PSPEmpty) {
     vector<string> P = {"S->BB", "S->CD", "B->BB", "B->CD", "C->(", "D->BE", "D->)", "E->)", "S->$"};
     string w = "";
     bool f = in_language(w, P);
     ASSERT_EQ(f, true);
}

TEST_F(TestSerialization, PSPError) {
     vector<string> P = {"S->S", "S->BB", "S->CD", "B->BB", "B->CD", "C->(", "D->BE", "D->)", "E->)", "S->$"};
     string w = "()(())!";
     ASSERT_THROW(in_language(w, P), std::runtime_error);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
