#include <iostream>
#include <ScopeGuard/ScopeGuard.hpp>

class Object
{
public:
    Object() : value(0)
    {
    }

    Object(int value_) : value(value_)
    {
    }

    ~Object()
    {
        std::cout << __func__ << ":" << value << std::endl;
    }

private:
    int value;
};

void deleteObject(Object*& obj)
{
    delete obj;
    obj = NULL;
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

    {
        ON_SCOPE_EXIT(bye);
    }

    auto obj1 = new Object(1);
    auto obj2 = new Object(2);

    {
        ON_SCOPE_EXIT(deleteObject, obj1);
    }

    {
        ON_SCOPE_EXIT(ScopeGuard::Delete, obj2);
    }

    if (obj1 == NULL)
    {
        std::cout << "obj1 NULL" << std::endl;
    }

    if (obj2 == NULL)
    {
        std::cout << "obj2 NULL" << std::endl;
    }

    {
        auto objArray = new Object[3];
        ON_SCOPE_EXIT(ScopeGuard::DeleteArray, objArray);
    }

    return 0;
}
