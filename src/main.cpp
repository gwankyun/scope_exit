#include <catch2/../catch2/catch_session.hpp>
#include <catch2/catch_test_macros.hpp>
#include <spdlog/spdlog.h>

#include <scope_exit/local_function.hpp> // LOCAL_FUNCTION_*
#include <scope_exit/scope_exit.h>       // ON_SCOPE_EXIT

import std;
import scope_exit;
import scope_exit.ref;     // lite::ref lite::cref
import scope_exit.deleter; // lite::delete_ptr lite::delete_array

namespace global
{
    int value = -1;

    struct Object
    {
        Object() = default;
        ~Object()
        {
            ::global::value += 1;
        }
        int value;
    };

    void set_value(int& _i)
    {
        _i = 1;
    }
} // namespace global

TEST_CASE("labmda", "[scope_exit]")
{
    auto value = -1;

    {
        auto cb = [&] { value = 1; };
        ON_SCOPE_EXIT(cb);
    }
    REQUIRE(value == 1);

    {
        auto cb1 = [&](int t1) { value = t1; };
        value = 0;
        ON_SCOPE_EXIT(cb1, 1);
    }
    REQUIRE(value == 1);

    {
        auto cb = [&](int t1, int t2) { value = t1 + t2; };
        value = 0;
        ON_SCOPE_EXIT(cb, 1, 2);
    }
    REQUIRE(value == 3);

    {
        auto cb = [&](int t1, int t2, int t3) { value = t1 + t2 + t3; };
        value = 0;
        ON_SCOPE_EXIT(cb, 1, 2, 3);
    }
    REQUIRE(value == 6);

    {
        auto cb = [&](int t1, int t2, int t3, int t4)
        { value = t1 + t2 + t3 + t4; };
        value = 0;
        ON_SCOPE_EXIT(cb, 1, 2, 3, 4);
    }
    REQUIRE(value == 10);

    {
        auto cb = [&](int t1, int t2, int t3, int t4, int t5)
        { value = t1 + t2 + t3 + t4 + t5; };
        value = 0;
        ON_SCOPE_EXIT(cb, 1, 2, 3, 4, 5);
    }
    REQUIRE(value == 15);

    {
        auto cb = [&](int t1, int t2, int t3, int t4, int t5, int t6)
        { value = t1 + t2 + t3 + t4 + t5 + t6; };
        value = 0;
        ON_SCOPE_EXIT(cb, 1, 2, 3, 4, 5, 6);
    }
    REQUIRE(value == 21);

    {
        auto cb = [&](int t1, int t2, int t3, int t4, int t5, int t6, int t7)
        { value = t1 + t2 + t3 + t4 + t5 + t6 + t7; };
        value = 0;
        ON_SCOPE_EXIT(cb, 1, 2, 3, 4, 5, 6, 7);
    }
    REQUIRE(value == 28);

    {
        auto cb =
            [&](int t1, int t2, int t3, int t4, int t5, int t6, int t7, int t8)
        { value = t1 + t2 + t3 + t4 + t5 + t6 + t7 + t8; };
        value = 0;
        ON_SCOPE_EXIT(cb, 1, 2, 3, 4, 5, 6, 7, 8);
    }
    REQUIRE(value == 36);

    {
        auto cb = [&](int t1, int t2, int t3, int t4, int t5, int t6, int t7,
                      int t8, int t9)
        { value = t1 + t2 + t3 + t4 + t5 + t6 + t7 + t8 + t9; };
        value = 0;
        ON_SCOPE_EXIT(cb, 1, 2, 3, 4, 5, 6, 7, 8, 9);
    }
    REQUIRE(value == 45);
}

TEST_CASE("ref", "[scope_exit]")
{
    auto value = -1;
    auto cb1 = [&](int& t1) { t1 = 1; };
    {
        value = 0;
        ON_SCOPE_EXIT(cb1, std::ref(value));
    }
    REQUIRE(value == 1);
}

TEST_CASE("globel function", "[scope_exit]")
{
    int value = -1;
    {
        ON_SCOPE_EXIT(global::set_value, lite::ref(value));
    }
    REQUIRE(value == 1);
}

TEST_CASE("delete_ptr", "[scope_exit]")
{
    global::value = 0;

    {
        auto obj = new global::Object();
        ON_SCOPE_EXIT(lite::delete_ptr, obj);
    }

    REQUIRE(global::value == 1);
}

TEST_CASE("delete_array", "[scope_exit]")
{
    global::value = 0;

    {
        auto objArray = new global::Object[3];
        ON_SCOPE_EXIT(lite::delete_array, objArray);
    }

    REQUIRE(global::value == 3);
}

TEST_CASE("lite::ref", "[scope_exit]")
{
    int value = -1;

    {
        auto cb1 = [&](int& t1) { t1 = 1; };
        value = 0;
        ON_SCOPE_EXIT(cb1, lite::ref(value));
    }
    REQUIRE(value == 1);

    {
        struct CB
        {
            void operator()(int& t1)
            {
                t1 = 1;
            }
        } cb2;
        value = 0;
        ON_SCOPE_EXIT(cb2, lite::ref(value));
    }
    REQUIRE(value == 1);

    {
        LOCAL_FUNCTION_BEGIN(void)(int& t1)
        {
            t1 = 1;
        }
        LOCAL_FUNCTION_END(cb3);

        value = 0;
        ON_SCOPE_EXIT(cb3, lite::ref(value));
    }
    REQUIRE(value == 1);
}

int main(int _argc, char* _argv[])
{
    spdlog::set_pattern("[%C-%m-%d %T.%e] [%^%L%$] [t:%6t] [%-8!!:%4#] %v");

    auto result = Catch::Session().run(_argc, _argv);
    return result;
}
