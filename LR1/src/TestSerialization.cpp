#include "gtest/gtest.h"

#include "../lib/LR1.h"

class TestSerialization : public ::testing::Test {};

TEST_F(TestSerialization, SimpleYes1) {
    vector<string> P = {"S->E", "E->E+T", "E->T", "T->a", "T->(E)", "T->b"};
    string w = "(a+a)+a";
    bool f = in_language(P, w);
    ASSERT_EQ(f, true);
}

TEST_F(TestSerialization, SimpleNo1) {
    vector<string> P = {"S->E", "E->E+T", "E->T", "T->a", "T->(E)", "T->b"};
    string w = "(a+a)a";
    bool f = in_language(P, w);
    ASSERT_EQ(f, false);
}

TEST_F(TestSerialization, SimpleNo2) {
    vector<string> P = {"S->E", "E->E+T", "E->T", "T->a", "T->(E)", "T->b"};
    string w = "(a+a+a";
    bool f = in_language(P, w);
    ASSERT_EQ(f, false);
}

TEST_F(TestSerialization, SimpleNo3) {
    vector<string> P = {"S->E", "E->E+T", "E->T", "T->a", "T->(E)"};
    string w = "(a+a)+b";
    bool f = in_language(P, w);
    ASSERT_EQ(f, false);
}

TEST_F(TestSerialization, SimpleYes2) {
    vector<string> P = {"S->E", "E->aDc", "D->Db", "D->b"};
    string w = "abbc";
    bool f = in_language(P, w);
    ASSERT_EQ(f, true);
}

TEST_F(TestSerialization, SimpleNo4) {
    vector<string> P = {"S->E", "E->aDc", "D->Db", "D->b"};
    string w = "ac";
    bool f = in_language(P, w);
    ASSERT_EQ(f, false);
}

TEST_F(TestSerialization, HardYes) {
    vector<string> P = {"S->E", "E->aDc", "D->Db", "D->b"};
    string w = "a";
    for (int i = 0; i < 1000000; i++) {
        w.push_back('b');
    }
    w.push_back('c');
    bool f = in_language(P, w);
    ASSERT_EQ(f, true);
}

TEST_F(TestSerialization, HardNo) {
    vector<string> P = {"S->E", "E->aDc", "D->Db", "D->b"};
    string w = "a";
    for (int i = 0; i < 1000000; i++) {
        w.push_back('b');
    }
    bool f = in_language(P, w);
    ASSERT_EQ(f, false);
}

TEST_F(TestSerialization, LR1No) {
    vector<string> P = {"S->E", "E->CC", "C->cC", "C->d"};
    string w = "cc";
    bool f = in_language(P, w);
    ASSERT_EQ(f, false);
}

TEST_F(TestSerialization, LR1Yes) {
    vector<string> P = {"S->E", "E->CC", "C->cC", "C->d"};
    string w = "dd";
    bool f = in_language(P, w);
    ASSERT_EQ(f, true);
}

TEST_F(TestSerialization, LR1HardYes) {
    vector<string> P = {"S->E", "E->CC", "C->cC", "C->d"};
    string w = "cccccccccccccccdcccccccccccccccccccccccccccd";
    bool f = in_language(P, w);
    ASSERT_EQ(f, true);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
