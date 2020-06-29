#include <iostream>
#include "../include/ScopeGuard/ScopeGuard.hpp"

class Object
{
public:
    Object()
    {
    }

    ~Object()
    {
        std::cout << __LINE__ << std::endl;
    }

private:

};

void deleteObject(Object*& obj)
{
    delete obj;
}

void bye()
{
    std::cout << __func__ << std::endl;
}

int main()
{
    ON_SCOPE_EXIT([]()
    {
        std::cout << "exit" << std::endl;
    });

    auto obj = new Object();

    //{
    //    ON_SCOPE_EXIT(obj);
    //}

    {
        ON_SCOPE_EXIT(deleteObject, obj);
    }

    {
        ON_SCOPE_EXIT(bye);
    }

    //if (obj == NULL)
    //{
    //    std::cout << "NULL" << std::endl;
    //}

    return 0;
}
