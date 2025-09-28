#include <catch2/../catch2/catch_session.hpp>
#include <catch2/catch_test_macros.hpp>
#include <scope_exit/scope_exit.h>
#include <spdlog/spdlog.h>

import std;
import scope_exit;

TEST_CASE("labmda", "[scope_exit]")
{
    auto value = -1;

    auto cb = [&] { value = 1; };
    {
        ON_SCOPE_EXIT(cb);
    }
    REQUIRE(value == 1);

    auto cb1 = [&](int t1) { value = t1; };
    {
        value = 0;
        ON_SCOPE_EXIT(cb1, 1);
    }
    REQUIRE(value == 1);

    auto cb2 = [&](int t1, int t2) { value = t1 + t2; };
    {
        value = 0;
        ON_SCOPE_EXIT(cb2, 1, 2);
    }
    REQUIRE(value == 3);

    auto cb3 = [&](int t1, int t2, int t3) { value = t1 + t2 + t3; };
    {
        value = 0;
        ON_SCOPE_EXIT(cb3, 1, 2, 3);
    }
    REQUIRE(value == 6);

    auto cb4 = [&](int t1, int t2, int t3, int t4) { value = t1 + t2 + t3 + t4; };
    {
        value = 0;
        ON_SCOPE_EXIT(cb4, 1, 2, 3, 4);
    }
    REQUIRE(value == 10);
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

int main(int _argc, char* _argv[])
{
    spdlog::set_pattern("[%C-%m-%d %T.%e] [%^%L%$] [t:%6t] [%-8!!:%4#] %v");

    auto result = Catch::Session().run(_argc, _argv);
    return result;
}
