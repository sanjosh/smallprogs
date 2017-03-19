#include "set.h"
#include <gtest/gtest.h>

TEST(Set, basic) {
    Set a;
    a.insert(3);
    a.insert(5);

    EXPECT_EQ(a.contains(3), true);
    EXPECT_EQ(a.contains(5), true);

    a.remove(3);
    EXPECT_EQ(a.contains(3), false);

    a.remove(5);
    EXPECT_EQ(a.contains(5), false);
}

