#include <gtest/gtest.h>
#include "queue.h"

class QueueSizeEmptyTest : public ::testing::Test
{
protected:
    queue<int> q;
};

TEST_F(QueueSizeEmptyTest, NewQueueIsEmpty)
{
    EXPECT_TRUE(q.empty());
    EXPECT_EQ(q.size(), 0);
}

TEST_F(QueueSizeEmptyTest, SizeIncreasesOnPush)
{
    q.push(1);
    EXPECT_EQ(q.size(), 1);
    q.push(2);
    EXPECT_EQ(q.size(), 2);
}

TEST_F(QueueSizeEmptyTest, SizeDecreasesOnPop)
{
    q.push(1);
    q.push(2);
    q.pop();
    EXPECT_EQ(q.size(), 1);
}

TEST_F(QueueSizeEmptyTest, NotEmptyAfterPush)
{
    q.push(1);
    EXPECT_FALSE(q.empty());
}

TEST_F(QueueSizeEmptyTest, EmptyAgainAfterPoppingEverything)
{
    q.push(1);
    q.push(2);
    q.pop();
    q.pop();
    EXPECT_TRUE(q.empty());
    EXPECT_EQ(q.size(), 0);
}
