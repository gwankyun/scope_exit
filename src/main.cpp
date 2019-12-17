#include <iostream>
#include "../include/ScopeGuard/ScopeGuard.hpp"

int main()
{
    ON_SCOPE_EXIT([]()
    {
        std::cout << "exit" << std::endl;
    });
    return 0;
}
