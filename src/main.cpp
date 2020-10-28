#include <iostream>
//#define SCOPE_GUARD_HAS_CXX_11 0
//#define SCOPE_GUARD_HAS_CXX_17 0
#include <ScopeGuard.hpp>

int add(int a, int b)
{
    return a + b;
}

int main()
{
    int n = 0;
    //ON_SCOPE_EXIT(ScopeGuard::ref(n), n);
    std::cout << std::is_function_v<decltype(add)> << std::endl;
    return 0;
}

