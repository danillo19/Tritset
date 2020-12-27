#include <iostream>
#include "Tritset.h"
#include "trit.h"
#include "gtest/gtest.h"
#include <bitset>

const long long int LARGE_SIZE = 100000000;
const int CAPACITY_ONE = 100;
const int CAPACITY_TWO = 20;

TEST(Tests, SHRINK) {

    Tritset::Tritset q(CAPACITY_ONE);
    int firstTrueIndex = 0;
    int lastTrueIndex = 50;
    int firstFalseIndex = 75;
    int lastFalseIndex = 90;

    for (int i = firstTrueIndex; i < lastTrueIndex + 1; i++) {
        q[i] = Trit::True;
    }
    for (int i = firstFalseIndex; i < lastFalseIndex + 1; i++) {
        q[i] = Trit::False;
    }

    EXPECT_EQ(CAPACITY_ONE, q.size());

    q.shrink();
    EXPECT_EQ(lastFalseIndex + 1, q.size());
    EXPECT_EQ((Trit::Trit) q[firstFalseIndex - 1], Trit::Unknown);
    EXPECT_EQ((Trit::Trit) q[lastFalseIndex], Trit::False);
}

TEST(Test, NOT) {
    Tritset::Tritset q(CAPACITY_ONE);
    for (uint i = 0; i < q.size(); i++) {
        switch (i % 3) {
            case 0:
                q[i] = Trit::True;
                break;
            case 1:
                q[i] = Trit::False;
                break;
            case 2:
                q[i] = Trit::Unknown;
                break;
        }
    }
    q = !q;

    for (uint i = 0; i < q.size(); i++) {
        switch (i % 3) {
            case 0:
                EXPECT_EQ(Trit::False, (Trit::Trit) q[i]);
                break;
            case 1:
                EXPECT_EQ(Trit::True, (Trit::Trit) q[i]);
                break;
            case 2:
                EXPECT_EQ(Trit::Unknown, (Trit::Trit) q[i]);
                break;
        }
    }
}

TEST(Tests, AND) {
    Tritset::Tritset a(CAPACITY_TWO);
    int firstFalseIndex = 0;
    int lastFalseIndex = 2;
    int firstTrueIndex = 3;
    int lastTrueIndex = 5;

    for (int i = firstFalseIndex; i < lastFalseIndex + 1; i++) a[i] = Trit::False;
    for (int i = firstTrueIndex; i < lastTrueIndex + 1; i++) a[i] = Trit::True;

    Tritset::Tritset b(CAPACITY_ONE);

    for (uint i = 0; i < b.size(); i++) {
        switch (i % 3) {
            case 0:
                b[i] = Trit::True;
                break;
            case 1:
                b[i] = Trit::False;
                break;
            case 2:
                b[i] = Trit::Unknown;
                break;
        }
    }

    Tritset::Tritset c = a & b;
    EXPECT_EQ(c.size(), b.size());

    for (int i = firstFalseIndex; i < lastFalseIndex; i++) {
        EXPECT_EQ(Trit::False, (Trit::Trit) c[i]);
    }
    EXPECT_EQ(Trit::True, (Trit::Trit) c[firstTrueIndex]);
    EXPECT_EQ(Trit::False, (Trit::Trit) c[firstTrueIndex + 1]);
    EXPECT_EQ(Trit::Unknown, (Trit::Trit) c[firstTrueIndex + 2]);

    EXPECT_EQ(Trit::Unknown, (Trit::Trit) c[lastTrueIndex + 1]);
    EXPECT_EQ(Trit::False, (Trit::Trit) c[lastTrueIndex + 2]);
    EXPECT_EQ(Trit::Unknown, (Trit::Trit) c[lastTrueIndex + 3]);
    //   i   60   61    62
    // b[i] True False Unknown
    EXPECT_EQ(Trit::False, (Trit::Trit) c[61]);

}

TEST(Tests, OR) {
    Tritset::Tritset a(CAPACITY_TWO);
    int firstTrueIndex = 0;
    int lastTrueIndex = 2;
    int firstFalseIndex = 3;
    int lastFalseIndex = 5;
    for (int i = firstTrueIndex; i < lastTrueIndex + 1; i++) a[i] = Trit::True;
    for (int i = firstFalseIndex; i < lastFalseIndex + 1; i++) a[i] = Trit::False;
    Tritset::Tritset b(CAPACITY_ONE);

    for (uint i = 0; i < b.size(); i++) {
        switch (i % 3) {
            case 0:
                b[i] = Trit::True;
                break;
            case 1:
                b[i] = Trit::False;
                break;
            case 2:
                b[i] = Trit::Unknown;
                break;
        }
    }

    Tritset::Tritset c = a | b;
    EXPECT_EQ(c.size(), b.size());

    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(Trit::True, (Trit::Trit) c[i]);
    }
    EXPECT_EQ(Trit::True, (Trit::Trit) c[lastTrueIndex]); // T or F
    EXPECT_EQ(Trit::False, (Trit::Trit) c[firstFalseIndex + 1]); // F or F
    EXPECT_EQ(Trit::Unknown, (Trit::Trit) c[firstFalseIndex + 2]); // U or F

    EXPECT_EQ(Trit::True, (Trit::Trit) c[lastFalseIndex + 1]);
    EXPECT_EQ(Trit::Unknown, (Trit::Trit) c[lastFalseIndex + 2]);
    EXPECT_EQ(Trit::Unknown, (Trit::Trit) c[lastFalseIndex + 3]);

    EXPECT_EQ(Trit::True, (Trit::Trit) c[60]); // b[60] = True;
    EXPECT_EQ(Trit::Unknown, (Trit::Trit) c[61]); //b[61] = False, a[61] = Unknown;

}


TEST(Tests, TRIM) {
    Tritset::Tritset q(CAPACITY_ONE);
    int firstTrueIndex = 0;
    int lastTrueIndex = 19;
    int firstFalseIndex = 20;
    int lastFalseIndex = 39;
    for (uint i = firstTrueIndex; i < lastTrueIndex + 1; i++) q[i] = Trit::True;
    for (uint i = firstFalseIndex; i < lastFalseIndex + 1; i++) q[i] = Trit::False;

    q.trim(60);
    EXPECT_EQ(61, q.size());
    EXPECT_EQ(Trit::Unknown, (Trit::Trit) q[60]);

    q.trim(40);
    EXPECT_EQ(41, q.size());
    EXPECT_EQ(Trit::Unknown, (Trit::Trit) q[60]);

    q.trim(20);
    EXPECT_EQ(21, q.size());
    EXPECT_EQ(Trit::False, (Trit::Trit) q[20]);

    q.trim(1);
    EXPECT_EQ(2, q.size());
    EXPECT_EQ(Trit::True, (Trit::Trit) q[1]);
}

TEST(Tests, CARDINALITY) {
    Tritset::Tritset q(CAPACITY_ONE);
    for (uint i = 0; i < q.size(); i++) {
        switch (i % 3) {
            case 0:
                q[i] = Trit::True;
                break;
            case 1:
                q[i] = Trit::False;
                break;
            case 2:
                q[i] = Trit::Unknown;
                break;
        }
    }

    EXPECT_EQ((CAPACITY_ONE / 3) + 1, q.cardinality(Trit::True));
    EXPECT_EQ(CAPACITY_ONE / 3, q.cardinality(Trit::False));
    EXPECT_EQ(CAPACITY_ONE / 3, q.cardinality(Trit::Unknown));

    Tritset::Tritset b(CAPACITY_ONE);
    int firstTrueIndex = 0;
    int lastTrueIndex = 19;
    for (int i = firstTrueIndex; i < lastTrueIndex + 1; i++) b[i] = Trit::True;

    int firstFalseIndex = 50;
    b[firstFalseIndex] = Trit::False;

    EXPECT_EQ(lastTrueIndex - firstTrueIndex + 1, b.cardinality(Trit::True));
    EXPECT_EQ(1, b.cardinality(Trit::False));
    EXPECT_EQ(firstFalseIndex - (lastTrueIndex - firstTrueIndex + 1), b.cardinality(Trit::Unknown));

}

TEST(Test, LENGTH) {
    Tritset::Tritset q(CAPACITY_ONE);
    int firstTrueIndex = 0;
    int lastTrueIndex = 19;

    for (int i = firstTrueIndex; i < lastTrueIndex + 1; i++) {
        q[i] = Trit::True;
    }

    int firstFalseIndex = 60;
    int secondFalseIndex = 80;
    q[firstFalseIndex] = Trit::False;
    q[secondFalseIndex] = Trit::True;

    EXPECT_EQ(secondFalseIndex + 1, q.length());

    q.trim(secondFalseIndex + 2);
    EXPECT_EQ(secondFalseIndex + 1, q.length());

    q.trim(lastTrueIndex + 2);
    EXPECT_EQ(lastTrueIndex + 1, q.length());
}

TEST(Test, LARGE_TEST) {
    Tritset::Tritset q(LARGE_SIZE);
    for (uint i = 0; i < q.size(); i++) {
        switch (i % 3) {
            case 0:
                q[i] = Trit::True;
                break;
            case 1:
                q[i] = Trit::False;
                break;
            case 2:
                q[i] = Trit::Unknown;
                break;
        }
    }

    std::unordered_map<Trit::Trit, int, std::hash<int>> Stats = q.cardinality();

    EXPECT_EQ((LARGE_SIZE / 3) + 1, Stats[Trit::True]);
    EXPECT_EQ(LARGE_SIZE / 3, Stats[Trit::False]);
    EXPECT_EQ(LARGE_SIZE / 3, Stats[Trit::Unknown]);

    q[LARGE_SIZE] = Trit::True;
    q[LARGE_SIZE + 1] = Trit::False;
    q[LARGE_SIZE + 2] = Trit::Unknown;

    EXPECT_EQ(LARGE_SIZE + 2, q.size());
    EXPECT_EQ(Trit::True, (Trit::Trit) q[LARGE_SIZE]);
    EXPECT_EQ(Trit::False, (Trit::Trit) q[LARGE_SIZE + 1]);
    EXPECT_EQ(Trit::Unknown, (Trit::Trit) q[LARGE_SIZE + 2]);

}

TEST(Tests, ASSIGMENT) {
    Tritset::Tritset q(CAPACITY_ONE);
    Tritset::Tritset b(CAPACITY_TWO);
    b[0] = Trit::True;
    b[1] = Trit::False;
    q[0] = b[0];
    q[1] = b[1];

    EXPECT_EQ(Trit::True, (Trit::Trit) q[0]);
    EXPECT_EQ(Trit::False, (Trit::Trit) q[1]);

}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}