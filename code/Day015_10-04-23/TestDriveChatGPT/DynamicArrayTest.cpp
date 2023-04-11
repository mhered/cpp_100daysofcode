#include <gtest/gtest.h>
#include "DynamicArray.h" 

// test the constructor and print_array method
TEST(DynamicArrayTest, ConstructorAndPrint) {
    DynamicArray a(3);
    a.fill_array(1);
    testing::internal::CaptureStdout();
    a.print_array();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Array size: 3\nArray contents: 1 2 3 \n");
}

// test the copy constructor and fill_array method
TEST(DynamicArrayTest, CopyConstructorAndFill) {
    DynamicArray a(4);
    a.fill_array(5);
    DynamicArray b(a);
    b.fill_array(2);
    testing::internal::CaptureStdout();
    a.print_array();
    b.print_array();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Array size: 4\nArray contents: 5 6 7 8 \nArray size: 4\nArray contents: 2 3 4 5 \n");
}

// test the destructor and fill_array method
TEST(DynamicArrayTest, DestructorAndFill) {
    DynamicArray* a = new DynamicArray(2);
    a->fill_array(3);
    delete a;
    DynamicArray b(2);
    b.fill_array(4);
    testing::internal::CaptureStdout();
    b.print_array();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Array size: 2\nArray contents: 4 5 \n");
}

// main function to run the tests
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}