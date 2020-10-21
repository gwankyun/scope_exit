#include <iostream>
//#define SCOPE_GUARD_HAS_CXX_17 0
#include <ScopeGuard.hpp>
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4100)
#endif // _MSC_VER

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

void bye0()
{
    std::cout << __func__ << std::endl;
}

void bye1(int a)
{
    std::cout << __func__ << std::endl;
}

void bye2(int a, int b)
{
    std::cout << __func__ << std::endl;
}

void bye3(int a, int b, int c)
{
    std::cout << __func__ << std::endl;
}

void bye4(int a, int b, int c, int d)
{
    std::cout << __func__ << std::endl;
}

void bye5(int a, int b, int c, int d, int e)
{
    std::cout << __func__ << std::endl;
}

void bye6(int a, int b, int c, int d, int e, int f)
{
    std::cout << __func__ << std::endl;
}

void bye7(int a, int b, int c, int d, int e, int f, int g)
{
    std::cout << __func__ << std::endl;
}

void bye8(int a, int b, int c, int d, int e, int f, int g, int h)
{
    std::cout << __func__ << std::endl;
}

void bye9(int a, int b, int c, int d, int e, int f, int g, int h, int i)
{
    std::cout << __func__ << std::endl;
}

int main()
{
    ON_SCOPE_EXIT([]()
    {
        std::cout << "exit" << std::endl;
    });

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

    {
        int a;
        ON_SCOPE_EXIT(bye0);
        ON_SCOPE_EXIT(bye1, a);
        ON_SCOPE_EXIT(bye2, a, a);
        ON_SCOPE_EXIT(bye3, a, a, a);
        ON_SCOPE_EXIT(bye4, a, a, a, a);
        ON_SCOPE_EXIT(bye5, a, a, a, a, a);
        ON_SCOPE_EXIT(bye6, a, a, a, a, a, a);
        ON_SCOPE_EXIT(bye7, a, a, a, a, a, a, a);
        ON_SCOPE_EXIT(bye8, a, a, a, a, a, a, a, a);
        ON_SCOPE_EXIT(bye9, a, a, a, a, a, a, a, a, a);
    }

    std::cout << sizeof(ScopeGuard) << std::endl;

    return 0;
}
#ifdef _MSC_VER
#pragma warning(pop)
#endif // _MSC_VER
