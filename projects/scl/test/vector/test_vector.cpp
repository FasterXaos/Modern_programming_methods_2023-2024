#include <gtest/gtest.h>

#include "vector.hpp"

TEST(VectorTest, DefaultConstructor) {
    EAbrakhin::Vector<int> v;
    EXPECT_EQ(v.get_size(), 0);
}

TEST(VectorTest, PushBack) {
    EAbrakhin::Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    EXPECT_EQ(v.get_size(), 3);
}

TEST(VectorTest, HasItem) {
    EAbrakhin::Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    EXPECT_TRUE(v.has_item(2));
    EXPECT_FALSE(v.has_item(4));
}

TEST(VectorTest, Insert) {
    EAbrakhin::Vector<int> v;
    v.push_back(1);
    v.push_back(3);
    v.insert(1, 2);
    EXPECT_EQ(v.get_size(), 3);
    EXPECT_EQ(v.has_item(2), true);
    EXPECT_EQ(v.has_item(3), true);
}

TEST(VectorTest, RemoveFirst) {
    EAbrakhin::Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(1);
    v.remove_first(1);
    EXPECT_EQ(v.get_size(), 2);
    EXPECT_EQ(v.has_item(1), true);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
