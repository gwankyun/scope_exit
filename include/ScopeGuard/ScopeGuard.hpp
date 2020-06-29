#pragma once
#ifndef SCOPE_GUARD_HPP
#define SCOPE_GUARD_HPP
#include <functional>

class ScopeGuard
{
public:

#ifdef __cpp_lambdas
    explicit ScopeGuard(std::function<void()> onExit_)
        : onExit(onExit_), dismissed(false), base(NULL)
    {
    }
#endif // __cpp_lambdas

    template<typename CallBack, typename T>
    explicit ScopeGuard(CallBack callback_, T& value_)
        : dismissed(false), base(new Derived<T, CallBack, void(*)()>(callback_, value_))
    {
    }

    template<typename Procedure>
    explicit ScopeGuard(Procedure procedure_)
        : dismissed(false), base(new Derived<int, void(*)(int), Procedure>(procedure_))
    {
    }

    ~ScopeGuard()
    {
        if (!dismissed)
        {
            if (base != NULL)
            {
                delete base;
            }
            else
            {
#ifdef __cpp_lambdas
                onExit();
#endif // __cpp_lambdas
            }
        }
    }

    void dissmiss()
    {
        dismissed = true;
    }

private:

    ScopeGuard(const ScopeGuard&);
    ScopeGuard& operator=(const ScopeGuard&);

    class Base
    {
    public:
        Base()
        {
        }

        virtual ~Base()
        {
        }

    private:

    };

    template<typename T, typename CallBack,typename Procedure>
    class Derived : public Base
    {
    public:
        Derived(CallBack callback_, T& value_) : value(&value_), callback(callback_), hasCallBack(true), hasProcedure(false)//, procedure(NULL)
        {
        }

        Derived(Procedure procedure_) : value(NULL), hasCallBack(false), hasProcedure(true), procedure(procedure_)//, procedure(NULL)
        {
        }

        ~Derived()
        {
            if (hasCallBack)
            {
                callback(*value);
            }

            if (hasProcedure)
            {
                procedure();
            }
        }

    private:
        T* value;
        CallBack callback;
        bool hasCallBack;
        Procedure procedure;
        bool hasProcedure;
    };

#ifdef __cpp_lambdas
    std::function<void()> onExit;
#endif // __cpp_lambdas
    bool dismissed;
    Base* base;
};

#define SCOPE_GUARD_LINENAME_CAT(name, line) name##line
#define SCOPE_GUARD_LINENAME(name, line) SCOPE_GUARD_LINENAME_CAT(name, line)
#define ON_SCOPE_EXIT(...) ScopeGuard SCOPE_GUARD_LINENAME(name, __LINE__)(##__VA_ARGS__)
#endif // !SCOPE_GUARD_HPP
