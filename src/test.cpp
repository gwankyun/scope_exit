#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
//#define SCOPE_GUARD_HAS_CXX_11 0
#include <ScopeGuard.hpp>

#ifndef REF
#  define REF SCOPE_GUARD_REF
#endif // !REF

#ifndef CREF
#  define CREF SCOPE_GUARD_CREF
#endif // !CREF

int add(int a, int b)
{
    return a + b;
}

void add_1(int& a)
{
    a += 1;
}

int add_const(const int& a)
{
    return a + 1;
}

TEST_CASE("ScopeGuard", "[]")
{
    auto i = new int(0);
    {
        ON_SCOPE_EXIT(ScopeGuard::Delete, i);
    }
    REQUIRE(i == nullptr);

    auto array = new int[10];
    {
        ON_SCOPE_EXIT(ScopeGuard::DeleteArray, array);
    }
    REQUIRE(array == nullptr);

    int n = 0;
    int a = 1;
    int b = 2;

    {
        ON_SCOPE_EXIT(REF(n), add, 10, 20);
    }
    REQUIRE(n == 30);

    {
        ON_SCOPE_EXIT(REF(n), add, a, b);
    }
    REQUIRE(n == 3);

    {
#if SCOPE_GUARD_HAS_CXX_11
        ON_SCOPE_EXIT(add_1, n);
#else
        ON_SCOPE_EXIT(add_1, REF(n));
#endif // SCOPE_GUARD_HAS_CXX_11
    }
    REQUIRE(n == 4);

    {
#if SCOPE_GUARD_HAS_CXX_11
        ON_SCOPE_EXIT(REF(n), add_const, n);
#else
        ON_SCOPE_EXIT(REF(n), add_const, CREF(n));
#endif // SCOPE_GUARD_HAS_CXX_11
    }
    REQUIRE(n == 5);

    {
        ON_SCOPE_EXIT([&n]()
            {
                n = 6;
            });
    }
    REQUIRE(n == 6);

    {
        ScopeGuard set7([&n]()
            {
                n = 7;
            });
        set7.release();
    }
    REQUIRE(n == 6);
}

