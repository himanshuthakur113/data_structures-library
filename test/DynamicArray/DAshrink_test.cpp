#include <gtest/gtest.h>
#include "dynamic_array.h"

TEST(DynamicArrayShrinkTest, ShrinkReducesCapacityToSize)
{
    DA<int> arr;

    for (int i = 0; i < 10; i++)
        arr.append(i);

    EXPECT_GT(arr.capacity(), arr.size());

    arr.shrink();

    EXPECT_EQ(arr.size(), 10);
    EXPECT_EQ(arr.capacity(), 10);
}

TEST(DynamicArrayShrinkTest, ShrinkPreservesElements)
{
    DA<int> arr;

    for (int i = 0; i < 10; i++)
        arr.append(i * 5);

    arr.shrink();

    for (int i = 0; i < 10; i++)
        EXPECT_EQ(arr[i], i * 5);
}

TEST(DynamicArrayShrinkTest, ShrinkEmptyArray)
{
    DA<int> arr;

    arr.shrink();

    EXPECT_EQ(arr.size(), 0);
    EXPECT_EQ(arr.capacity(), 0);
}

TEST(DynamicArrayShrinkTest, ShrinkSingleElement)
{
    DA<int> arr;

    arr.append(100);
    arr.shrink();

    EXPECT_EQ(arr.size(), 1);
    EXPECT_EQ(arr.capacity(), 1);
    EXPECT_EQ(arr[0], 100);
}

TEST(DynamicArrayShrinkTest, AppendAfterShrink)
{
    DA<int> arr;

    for (int i = 0; i < 5; i++)
        arr.append(i);

    arr.shrink();

    EXPECT_EQ(arr.capacity(), 5);

    arr.append(5);

    EXPECT_EQ(arr.size(), 6);
    EXPECT_GE(arr.capacity(), 6);

    for (int i = 0; i < 6; i++)
        EXPECT_EQ(arr[i], i);
}

TEST(DynamicArrayTest, ShrinkString)
{
    DA<std::string> arr;

    arr.append("One");
    arr.append("Two");
    arr.append("Three");

    arr.shrink();

    EXPECT_EQ(arr[0], "One");
    EXPECT_EQ(arr[1], "Two");
    EXPECT_EQ(arr[2], "Three");
}