#include "gtest/gtest.h"

#include "../lib/earley.h"

class TestSerialization : public ::testing::Test {};

TEST_F(TestSerialization, SimpleTrueTest) {
    Language G;
    G.P = {"F -> S", "S -> aB", "B -> b"};
    bool f = earley(G, "ab");
    ASSERT_EQ(f, true);
}

TEST_F(TestSerialization, SimpleFalseTest) {
     Language G;
     G.P = {"F -> S", "S -> aB", "B -> b"};
     bool f = earley(G, "ba");
     ASSERT_EQ(f, false);
}

TEST_F(TestSerialization, ancbnTrueTest) {
     Language G;
     G.P = {"F -> S", "S -> c", "S -> aSb"};
     bool f = earley(G, "aacbb");
     ASSERT_EQ(f, true);
}

TEST_F(TestSerialization, ancbnFalseFirstTest) {
      Language G;
      G.P = {"F -> S", "S -> c", "S -> aSb"};
      bool f = earley(G, "acbb");
      ASSERT_EQ(f, false);
}

TEST_F(TestSerialization, ancbnFalseSecondTest) {
       Language G;
       G.P = {"F -> S", "S -> c", "S -> aSb"};
       bool f = earley(G, "aabb");
       ASSERT_EQ(f, false);
}

TEST_F(TestSerialization, EmptyTest) {
       Language G;
       G.P = {"F -> S", "S -> ", "S -> SS", "S -> (S)"};
       bool f = earley(G, "");
       ASSERT_EQ(f, true);
}

TEST_F(TestSerialization, PSPFalseTest) {
        Language G;
        G.P = {"F -> S", "S -> ", "S -> SS", "S -> (S)"};
        bool f = earley(G, "(()(())))");
        ASSERT_EQ(f, false);
}

TEST_F(TestSerialization, PSPTrueTest) {
        Language G;
        G.P = {"F -> S", "S -> ", "S -> SS", "S -> (S)"};
        bool f = earley(G, "(()(()))");
        ASSERT_EQ(f, true);
}

TEST_F(TestSerialization, waeqwbHardTest) {
        Language G;
        G.P = {"F -> S", "S -> aSbS", "S -> bSaS", "S -> "};
        bool f = earley(G,"baabaabbbbbbaaaababaaaaaaabbbbaabaaaaababbbabbabababbaaaabbaabbbabbaababaaabaabaaabaaabbbabbbbaaaaaabaaaabababaabbbbbbbaaabbbabaaabbaabbaaaabbbbabbabbaaabaaabbbaaabbabbabbaabbbbabaaababaaabbbbabbbaabbbbabababaaabbbbaabaabbbbaaababbabababababbaabbabaabbabaaaabbaaabbaaaaaabaaaaaabbabbaaabbaaabbabbbaabbbbbaabbbbabaabbabaaababbabbbbbbabababbbbabaaababbabaababbabbbabaabbbbababababbbbbabbaaaababbbbbaabbbbbbbabaaabbbaabaabbbbbbbaabbbbbaabaababbabbbaabbbbaaaaaaaabbbababaabaabbaaabbaabababbabaabbaababbaabaaaaaabbaaabaaaaabaaabaaaabbababaaaaaabaaabbaabbaaabbbbbbbabaabbabaabababaababaaabbaabbaaabbababbababaaaabbbbabaaabbabaaaabaaaabbaaabababbbbbabbaaaaabaaabbbabbbbabbbabbbbaababaaaaaababbaaababbbbbbabaaabaaabbabaabbaaaaaababbbbabbaaababbabbaaabababaabaaaabaabbaabbabaabbabababbbbbbbbabbabaabbbaaaabbaabaaaaaaababbaabbbabbbabababbaabbaaaaaabaaabbbabbaabbaabaabbbaaababbaabaaabbbbbabbbabababbaaaabbbbbbbbabbabaaabaaaaaaabaaaababbbaabaaaaababaababbababaaaabbbbabbabbaabbbabbabbabbbbbbaaababaaababaabaaabbbbabababbbbabaaabbbbbbabbbbbbabaabbabaababbabaabbbaabbbaaabbbbaaabaaaaaaaaabbababbaaabbbabbabbbbbbabbbbaabaabbaaaaabbaabaababaaaaaabbbbaabaaaabaabaabbbbbbbbaaabbabbbbabaaabbbababbabbababbbaabaaabbaabaabaabbbabbabaababbbbaaabaababbbababababaaaaababbbbabbababaaaaabaabbabbbbabbabaabbbbbbaaabbbbabababaaabbabbbbbbbbababbaaabababbaaaabbaabaabababaabababbaaaabbbbbbabbaababbbabbabbababbbabbabbaabbbbaaaababbaaaababbbabbaabbbaabbbbabaaabbbbbabbababaababbaabbaabbabbbaabbababbbbbbaababaabbaabbaaabababbbbbbbaababbabaaabbbabbaaabbaababbabaaabbaabaaaaaabbaabbbbbabbbaabbabaaaababaaaaabababbbaababbbaabbabbabaabbaababbabaaaabababbaaaabbbbaabababbbbbbaabbaabbabbbaabaaaaabbabbababaabbbbbbaaaaaaabbaaaaaaabbababaaabbbaabaababbaaaaaabbabbabbbbbbbaaaabbaababbaababaaaaabaabbbbaabbabbaaabaaabbbaaaaaababbbbabababaaaaababbaabaabbaabaabbaababaaaaaabbbbaabaaaabbbbbabbbaaababaaababbaaaaabaabbbababaaaaaababbaabaabb");
        ASSERT_EQ(f, true);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
