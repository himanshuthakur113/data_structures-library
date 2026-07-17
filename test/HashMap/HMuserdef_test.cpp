#include <gtest/gtest.h>
#include "hash_map.h"
#include <string>

struct Employee
{
    int id;
    std::string name;

    Employee(int i = 0, const std::string& n = "")
        : id(i), name(n) {}
    bool operator==(const Employee& other) const
    {
        return id == other.id;
    }
};

struct EmployeeHasher
{
    size_t operator()(const Employee& emp) const
    {
        return emp.id;
    }
};

TEST(HashMapUserDefined, InsertAndGet)
{
    HashMap<Employee, int, EmployeeHasher> map;

    map.insert(Employee(13, "Himanshu"), 100);
    map.insert(Employee(25, "Divyansh"), 200);

    EXPECT_EQ(map.get(Employee(13)), 100);
    EXPECT_EQ(map.get(Employee(25)), 200);

    EXPECT_EQ(map.size(), 2);
}

TEST(HashMapUserDefined, UpdateExistingKey)
{
    HashMap<Employee, int, EmployeeHasher> map;

    map.insert(Employee(13, "Himanshu"), 100);
    map.insert(Employee(13, "Himanshu Thakur"), 500);

    EXPECT_EQ(map.size(), 1);
    EXPECT_EQ(map.get(Employee(13)), 500);
}

TEST(HashMapUserDefined, Contains)
{
    HashMap<Employee, int, EmployeeHasher> map;

    map.insert(Employee(13, "Himanshu"), 100);
    map.insert(Employee(25, "Divyansh"), 200);

    EXPECT_TRUE(map.contains(Employee(13)));
    EXPECT_TRUE(map.contains(Employee(25)));
    EXPECT_FALSE(map.contains(Employee(99)));
}

TEST(HashMapUserDefined, Remove)
{
    HashMap<Employee, int, EmployeeHasher> map;

    map.insert(Employee(13, "Himanshu"), 100);
    map.insert(Employee(25, "Divyansh"), 200);

    EXPECT_TRUE(map.remove(Employee(13)));
    EXPECT_FALSE(map.contains(Employee(13)));

    EXPECT_EQ(map.size(), 1);

    EXPECT_FALSE(map.remove(Employee(100)));
}

TEST(HashMapUserDefined, Rehash)
{
    HashMap<Employee, int, EmployeeHasher> map;

    for (int i = 0; i < 100; ++i)
    {
        map.insert(Employee(i, "Employee"), i * 10);
    }

    EXPECT_EQ(map.size(), 100);

    for (int i = 0; i < 100; ++i)
    {
        EXPECT_EQ(map.get(Employee(i)), i * 10);
    }
}

TEST(HashMapUserDefined, DefaultHashUsesAddress)
{
    HashMap<Employee, int> map; 

    Employee himanshu(13, "Himanshu");

    map.insert(himanshu, 100);

    EXPECT_TRUE(map.contains(himanshu));
    EXPECT_EQ(map.get(himanshu), 100);
}