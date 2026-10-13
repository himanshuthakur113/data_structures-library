#include <gtest/gtest.h>
#include <string>
#include <stdexcept>
#include "queue.h"

class QueuePushPopTest : public ::testing::Test
{
protected:
    queue<int> q;
};

TEST_F(QueuePushPopTest, PopReturnsElementsInFifoOrder)
{
    q.push(10);
    q.push(20);
    q.push(30);

    EXPECT_EQ(q.pop(), 10);
    EXPECT_EQ(q.pop(), 20);
    EXPECT_EQ(q.pop(), 30);
}

TEST_F(QueuePushPopTest, PopRemovesElement)
{
    q.push(1);
    q.push(2);

    q.pop();
    EXPECT_EQ(q.size(), 1);
    EXPECT_EQ(q.pop(), 2);
}

TEST_F(QueuePushPopTest, PopFromEmptyQueueThrows)
{
    EXPECT_THROW(q.pop(), std::runtime_error);
}

TEST_F(QueuePushPopTest, PopAfterQueueBecomesEmptyThrows)
{
    q.push(5);
    q.pop();
    EXPECT_THROW(q.pop(), std::runtime_error);
}

TEST_F(QueuePushPopTest, InterleavedPushAndPopKeepsOrder)
{
    q.push(1);
    q.push(2);
    EXPECT_EQ(q.pop(), 1);

    q.push(3);
    EXPECT_EQ(q.pop(), 2);
    EXPECT_EQ(q.pop(), 3);
}

TEST_F(QueuePushPopTest, DuplicateValuesAreAllKept)
{
    q.push(7);
    q.push(7);
    q.push(7);

    EXPECT_EQ(q.size(), 3);
    EXPECT_EQ(q.pop(), 7);
    EXPECT_EQ(q.pop(), 7);
    EXPECT_EQ(q.pop(), 7);
}

TEST_F(QueuePushPopTest, WorksWithStrings)
{
    queue<std::string> sq;
    sq.push("https://example.com");
    sq.push("https://example.org");

    EXPECT_EQ(sq.pop(), "https://example.com");
    EXPECT_EQ(sq.pop(), "https://example.org");
}

TEST_F(QueuePushPopTest, HandlesManyElements)
{
    for(int i = 0; i < 10000; ++i)
        q.push(i);

    EXPECT_EQ(q.size(), 10000);

    for(int i = 0; i < 10000; ++i)
        EXPECT_EQ(q.pop(), i);

    EXPECT_TRUE(q.empty());
}
