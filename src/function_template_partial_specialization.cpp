#include <gtest/gtest.h>

////////////////////////////////////////////////////////////////////////////////
// Codes
//
// Use SFINAE and std::enable_if to implement function template partial
// specialization.
//
////////////////////////////////////////////////////////////////////////////////

template<typename A, typename B>
typename std::enable_if<not std::is_same<A, B>::value, int>::type
foo()
{
    return 0;
}

template<typename A, typename B>
typename std::enable_if<std::is_same<A, B>::value, int>::type
foo()
{
    return 1;
}

////////////////////////////////////////////////////////////////////////////////
// Tests
////////////////////////////////////////////////////////////////////////////////

class A {
};

class B {
};

class Test : public ::testing::Test {
};

TEST_F(Test, Basic)
{
    ASSERT_EQ((foo<A, B>()), 0);
    ASSERT_EQ((foo<A, A>()), 1);
}
