#include <gtest/gtest.h>

////////////////////////////////////////////////////////////////////////////////
// Codes
// The codes are stolen from jrok at:
// https://stackoverflow.com/questions/87372/check-if-a-class-has-a-member-function-of-a-given-signature
//
// Template class used to check if a class has a member function of a give
// signature and name.
//
////////////////////////////////////////////////////////////////////////////////

#define HAS_MEMBER_FUNCTION(FUNC)                                       \
    template<typename, typename T>                                      \
    struct has_##FUNC {                                                  \
        static_assert(std::integral_constant<T, false>::value,          \
                      "Second template parameter needs to be of function type."); \
    };                                                                  \
                                                                        \
    template<typename C, typename Ret, typename... Args>                \
    struct has_##FUNC<C, Ret(Args...)> {                                 \
    private:                                                            \
                                                                        \
    /* attempt to call it and see if the return type is correct */      \
    template<typename T>                                                \
    static constexpr auto check(T*)                                     \
        -> typename                                                     \
        std::is_same<decltype(std::declval<T>().FUNC(std::declval<Args>()...)), \
                     Ret>::type;                                        \
                                                                        \
    template<typename>                                                  \
    static constexpr std::false_type check(...);                        \
                                                                        \
    typedef decltype(check<C>(0)) type;                                 \
                                                                        \
    public:                                                             \
    static constexpr bool value = type::value;                          \
    };                                                                  \

////////////////////////////////////////////////////////////////////////////////
// Tests
////////////////////////////////////////////////////////////////////////////////

HAS_MEMBER_FUNCTION(foo);

class HasFoo {
public:
    void foo(int b);
};

class DerivedFoo : public HasFoo {
};

class NoFoo {
};

class IncompatibleFoo {
public:
    void foo();
};

class Test : public ::testing::Test {
};

TEST_F(Test, Basic)
{
    ASSERT_TRUE((has_foo<HasFoo, void(int)>::value));
    ASSERT_TRUE((has_foo<DerivedFoo, void(int)>::value));
    ASSERT_FALSE((has_foo<NoFoo, void(int)>::value));
    ASSERT_FALSE((has_foo<IncompatibleFoo, void(int)>::value));
}
