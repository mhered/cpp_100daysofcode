#link: https://www.youtube.com/watch?v=16FI1-d2P4E

# My notes on Google Test Primer

https://google.github.io/googletest/primer.html![]()

Tests should be:

* independent (isolated from each other) and repeatable
* organized in test suites that reflect the structure of the code and can share data and subroutines
* portable cross-platform and reusable
* provide information when they fail, continue executing to get as much info as possible in a single run
* fast
* the test framework should minimize housekeeping chores



**Assertions** are statements that check a condition, and can result in success, nonfatal or fatal failure.

**Tests** use **Assertions** to verify code behaviour and are grouped in **Test suites**. When several tests in a test suite share data or subroutines they can be put in a **Test Fixture**.

## Assertions

Assertions are implemented as macros that check a condition, if it fails they report source file and line number, and error message (which can be customized):

`EXPECT_*()` generate non fatal failures and continue executing. Generally preferred.

`ASSERT_*()` generate fatal failures and abort execution, possibly skipping tear down

Provide custom error message with `<<`

List of assertions: https://google.github.io/googletest/reference/assertions.html

Example: 

```c++
// check size and abort if fails
ASSERT_EQ(x.size(), y.size()) << "Vectors x and y are of unequal length";
// check value element-wise and continue
for (int i = 0; i < x.size(); ++i) {
  EXPECT_EQ(x[i], y[i]) << "Vectors x and y differ at index " << i;
}
```

## Tests

The `TEST(TestSuiteName, TestName) {}` macro defines and names a test function that don't return a value and contains the assertions. Test fails if any of the assertion fails, succeeds if all its assertions succeed. Arguments `TestSuiteName` and `TestName` valid C++ identifiers without `_`, in PascalCase.

##  Test Fixtures

Allow reusing configuration between tests of the same test suite.

1. to test `Foo`, create a class named `FooTest` and inherited from  `::testing::Test`
2. start the body with a `protected:` section
3. declare the objects
4. prepare the objects in a default constructor `void SetUp() override{};`
5. if needed release allocated resources in a default destructor `TearDown()`
6. if needed define subroutines that tests will share
7. after defining the fixture, define the tests with the macro `TEST_F(TestFixtureClassName, TestName) {}`. Note the first argument is the test fixture not the test suite.
8. Note each test gets a fresh test fixture, and is destroyed at completion, changes do not carry to the next test.

```c++
class FooTest : public ::testing::Test {
protected:
	void SetUp() override {} // constructor
	void TearDown() override {} // destructor
	// objects
  	Foo sample1;
  	Foo sample2 = sample1;
	Foo sample3 sample1+sample2;
    void subroutine(); // subroutines
};

TEST_F(FooTest, Test1) {
	// sample1, sample2, sample3 and subroutine are accessible
 	EXPECT_EQ(sample1, sample2);
}
TEST_F(FooTest, Test2) {
	// sample1, sample2, sample3 and subroutine are accessible
 	EXPECT_NE(sample1, sample3);
}
```

## Invoke tests

Most users should *not* need to write their own `main` function and instead link with `gtest_main` (as opposed to with `gtest`), which defines a suitable entry point. 

If you write it, use the macro `RUN_ALL_TESTS()` which:

- Saves the state of all GoogleTest flags.
- Creates a test fixture object for the first test.
- Initializes it via `SetUp()`.
- Runs the test on the fixture object.
- Cleans up the fixture via `TearDown()`.
- Deletes the fixture.
- Restores the state of all GoogleTest flags.
- Repeats the above steps for the next test, until all tests have run exactly once. No guarantee on the order they are run.

Notes: 

* Call  `RUN_ALL_TESTS()` only once
* `main()` function must return the value of `RUN_ALL_TESTS()` (`0` if all tests in the suite were successful, `1` otherwise)

Boilerplate: 

```c++
#include "foo.h"

#include <gtest/gtest.h>

// The fixture for testing class Foo.
class FooTest : public ::testing::Test {
 protected:
  FooTest() {
     // You can do set-up work for each test here.
  }

  ~FooTest() override {
     // You can do clean-up work that doesn't throw exceptions here.
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  void SetUp() override {
     // Code here will be called immediately after the constructor (right
     // before each test).
  }

  void TearDown() override {
     // Code here will be called immediately after each test (right
     // before the destructor).
  }

  // Class members declared here can be used by all tests in the test suite
  // for Foo.
};

// Define Tests
TEST_F(FooTest, Test1) {
  Foo f;
  EXPECT_EQ(f, 0);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

```

