#include <gtest/gtest.h>
#include "queue.h"

TEST(QueueCopyTest, CopyConstructorMakesIndependentCopy)
{
    queue<int> a;
    a.push(1);
    a.push(2);

    queue<int> b(a);
    a.pop();

    EXPECT_EQ(a.size(), 1);
    EXPECT_EQ(b.size(), 2);
    EXPECT_EQ(b.pop(), 1);
    EXPECT_EQ(b.pop(), 2);
}

TEST(QueueCopyTest, AssignmentMakesIndependentCopy)
{
    queue<int> a;
    a.push(1);
    a.push(2);

    queue<int> b;
    b.push(99);
    b = a;

    a.pop();

    EXPECT_EQ(b.size(), 2);
    EXPECT_EQ(b.pop(), 1);
    EXPECT_EQ(b.pop(), 2);
}

TEST(QueueCopyTest, SelfAssignmentIsSafe)
{
    queue<int> a;
    a.push(1);
    a.push(2);

    a = a;

    EXPECT_EQ(a.size(), 2);
    EXPECT_EQ(a.pop(), 1);
    EXPECT_EQ(a.pop(), 2);
}
