#include <gtest/gtest.h>
#include <lib/array.h>

#include <sstream>
using namespace ArrayUInt17_t;

TEST(ArrayTestSuite, CreateTest) {
    Array arr(2, 2, 2);
    arr[0][0][0] = 1;
    arr[1][0][0] = 2;
    arr[0][1][0] = 4;
    arr[1][1][0] = 8;
    arr[0][0][1] = 16;
    arr[1][0][1] = 32;
    arr[0][1][1] = 64;
    arr[1][1][1] = 128;

    EXPECT_EQ(arr[0][0][0].Get(), 1);
    EXPECT_EQ(arr[1][0][0].Get(), 2);
    EXPECT_EQ(arr[0][1][0].Get(), 4);
    EXPECT_EQ(arr[1][1][0].Get(), 8);
    EXPECT_EQ(arr[0][0][1].Get(), 16);
    EXPECT_EQ(arr[1][0][1].Get(), 32);
    EXPECT_EQ(arr[0][1][1].Get(), 64);
    EXPECT_EQ(arr[1][1][1].Get(), 128);
}

TEST(ArrayTestSuite, UpdateTest) {
    Array arr(2, 2, 2);
    arr[0][0][0] = 0x1ffff;
    arr[1][0][0] = 0x1ffff;
    arr[0][1][0] = 0x1ffff;
    arr[1][1][0] = 0x1ffff;
    arr[0][0][1] = 0x1ffff;
    arr[1][0][1] = 0x1ffff;
    arr[0][1][1] = 0x1ffff;
    arr[1][1][1] = 0x1ffff;

    EXPECT_EQ(arr[0][1][0].Get(), 0x1ffff);

    arr[0][1][0] = 100;

    EXPECT_EQ(arr[0][1][0].Get(), 100);

    arr[0][1][0] = 0;

    EXPECT_EQ(arr[0][1][0].Get(), 0);
}

TEST(ArrayTestSuite, ExcessTest) {
    Array arr(2, 2, 2);
    uint32_t value = INT32_MAX;

    arr[0][0][0] = value;
    arr[1][0][0] = value;
    arr[0][1][0] = value;
    arr[1][1][0] = value;
    arr[0][0][1] = value;
    arr[1][0][1] = value;
    arr[0][1][1] = value;
    arr[1][1][1] = value;

    EXPECT_EQ(arr[0][0][0].Get(), 0x1ffff);
    EXPECT_EQ(arr[1][0][0].Get(), 0x1ffff);
    EXPECT_EQ(arr[0][1][0].Get(), 0x1ffff);
    EXPECT_EQ(arr[1][1][0].Get(), 0x1ffff);
    EXPECT_EQ(arr[0][0][1].Get(), 0x1ffff);
    EXPECT_EQ(arr[1][0][1].Get(), 0x1ffff);
    EXPECT_EQ(arr[0][1][1].Get(), 0x1ffff);
    EXPECT_EQ(arr[1][1][1].Get(), 0x1ffff);
}

TEST(ArrayTestSuite, CopyTest) {
    Array arr1(2, 2, 2);
    arr1[0][0][0] = 1;
    arr1[1][0][0] = 2;
    arr1[0][1][0] = 4;
    arr1[1][1][0] = 8;
    arr1[0][0][1] = 16;
    arr1[1][0][1] = 32;
    arr1[0][1][1] = 64;
    arr1[1][1][1] = 128;

    Array arr2 = arr1;

    EXPECT_EQ(arr2[0][0][0].Get(), 1);
    EXPECT_EQ(arr2[1][0][0].Get(), 2);
    EXPECT_EQ(arr2[0][1][0].Get(), 4);
    EXPECT_EQ(arr2[1][1][0].Get(), 8);
    EXPECT_EQ(arr2[0][0][1].Get(), 16);
    EXPECT_EQ(arr2[1][0][1].Get(), 32);
    EXPECT_EQ(arr2[0][1][1].Get(), 64);
    EXPECT_EQ(arr2[1][1][1].Get(), 128);
}

TEST(ArrayTestSuite, MultByValueTest) {
    Array arr1(2, 2, 2);
    arr1[0][0][0] = 1;
    arr1[1][0][0] = 2;
    arr1[0][1][0] = 4;
    arr1[1][1][0] = 8;
    arr1[0][0][1] = 16;
    arr1[1][0][1] = 32;
    arr1[0][1][1] = 64;
    arr1[1][1][1] = 128;

    Array arr2 = arr1 * 2;

    EXPECT_EQ(arr2[0][0][0].Get(), arr1[0][0][0].Get() * 2);
    EXPECT_EQ(arr2[1][0][0].Get(), arr1[1][0][0].Get() * 2);
    EXPECT_EQ(arr2[0][1][0].Get(), arr1[0][1][0].Get() * 2);
    EXPECT_EQ(arr2[1][1][0].Get(), arr1[1][1][0].Get() * 2);
    EXPECT_EQ(arr2[0][0][1].Get(), arr1[0][0][1].Get() * 2);
    EXPECT_EQ(arr2[1][0][1].Get(), arr1[1][0][1].Get() * 2);
    EXPECT_EQ(arr2[0][1][1].Get(), arr1[0][1][1].Get() * 2);
    EXPECT_EQ(arr2[1][1][1].Get(), arr1[1][1][1].Get() * 2);
}

TEST(ArrayTestSuite, AddArrayTest) {
    Array arr1(2, 2, 2);
    arr1[0][0][0] = 1;
    arr1[1][0][0] = 2;
    arr1[0][1][0] = 4;
    arr1[1][1][0] = 8;
    arr1[0][0][1] = 16;
    arr1[1][0][1] = 32;
    arr1[0][1][1] = 64;
    arr1[1][1][1] = 128;

    Array arr2(2, 2, 2);
    arr2[0][0][0] = 1;
    arr2[1][0][0] = 2;
    arr2[0][1][0] = 4;
    arr2[1][1][0] = 8;
    arr2[0][0][1] = 16;
    arr2[1][0][1] = 32;
    arr2[0][1][1] = 64;
    arr2[1][1][1] = 128;

    Array arr3 = arr1 + arr2;

    EXPECT_EQ(arr3[0][0][0].Get(), arr1[0][0][0].Get() + arr2[0][0][0].Get());
    EXPECT_EQ(arr3[1][0][0].Get(), arr1[1][0][0].Get() + arr2[1][0][0].Get());
    EXPECT_EQ(arr3[0][1][0].Get(), arr1[0][1][0].Get() + arr2[0][1][0].Get());
    EXPECT_EQ(arr3[1][1][0].Get(), arr1[1][1][0].Get() + arr2[1][1][0].Get());
    EXPECT_EQ(arr3[0][0][1].Get(), arr1[0][0][1].Get() + arr2[0][0][1].Get());
    EXPECT_EQ(arr3[1][0][1].Get(), arr1[1][0][1].Get() + arr2[1][0][1].Get());
    EXPECT_EQ(arr3[0][1][1].Get(), arr1[0][1][1].Get() + arr2[0][1][1].Get());
    EXPECT_EQ(arr3[1][1][1].Get(), arr1[1][1][1].Get() + arr2[1][1][1].Get());
}

TEST(ArrayTestSuite, MultArrayTest) {
    Array arr1(2, 2, 2);
    arr1[0][0][0] = 1;
    arr1[1][0][0] = 2;
    arr1[0][1][0] = 4;
    arr1[1][1][0] = 8;
    arr1[0][0][1] = 16;
    arr1[1][0][1] = 32;
    arr1[0][1][1] = 64;
    arr1[1][1][1] = 128;

    Array arr2(2, 2, 2);
    arr2[0][0][0] = 1;
    arr2[1][0][0] = 2;
    arr2[0][1][0] = 4;
    arr2[1][1][0] = 8;
    arr2[0][0][1] = 16;
    arr2[1][0][1] = 32;
    arr2[0][1][1] = 64;
    arr2[1][1][1] = 128;

    Array arr3 = arr1 * arr2;

    EXPECT_EQ(arr3[0][0][0].Get(), arr1[0][0][0].Get() * arr2[0][0][0].Get());
    EXPECT_EQ(arr3[1][0][0].Get(), arr1[1][0][0].Get() * arr2[1][0][0].Get());
    EXPECT_EQ(arr3[0][1][0].Get(), arr1[0][1][0].Get() * arr2[0][1][0].Get());
    EXPECT_EQ(arr3[1][1][0].Get(), arr1[1][1][0].Get() * arr2[1][1][0].Get());
    EXPECT_EQ(arr3[0][0][1].Get(), arr1[0][0][1].Get() * arr2[0][0][1].Get());
    EXPECT_EQ(arr3[1][0][1].Get(), arr1[1][0][1].Get() * arr2[1][0][1].Get());
    EXPECT_EQ(arr3[0][1][1].Get(), arr1[0][1][1].Get() * arr2[0][1][1].Get());
    EXPECT_EQ(arr3[1][1][1].Get(), arr1[1][1][1].Get() * arr2[1][1][1].Get());
}