#pragma once
#ifndef SCOPE_GUARD_HPP
#define SCOPE_GUARD_HPP
#include <functional>

class ScopeGuard
{
public:

    enum Type { Delete = 0, DeleteArray };

#ifdef __cpp_lambdas
    explicit ScopeGuard(std::function<void()> onExit_)
        : onExit(onExit_), dismissed(false), base(NULL)
    {
    }
#endif // __cpp_lambdas

    template<typename CB, typename T>
    explicit ScopeGuard(CB callback_, T& value_)
        : dismissed(false), base(new CallBack<CB, T>(callback_, value_))
    {
    }

    template<typename P>
    explicit ScopeGuard(P procedure_)
        : dismissed(false), base(new Procedure<P>(procedure_))
    {
    }

    template<typename T>
    explicit ScopeGuard(Type type, T*& value_)
        : dismissed(false), base(new Ptr<T>(type, value_))
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

    struct Base
    {
        Base()
        {
        }

        virtual ~Base()
        {
        }
    };

    template<typename CB, typename T>
    struct CallBack : public Base
    {
        CallBack(CB callback_, T& value_) : value(value_), callback(callback_), hasCallBack(true)
        {
        }

        ~CallBack()
        {
            if (hasCallBack)
            {
                callback(value);
            }
        }

        T& value;
        CB callback;
        bool hasCallBack;
    };

    template<typename P>
    struct Procedure : public Base
    {
        Procedure(P procedure_) : procedure(procedure_), hasProcedure(true)
        {
        }

        ~Procedure()
        {
            if (hasProcedure)
            {
                procedure();
            }
        }

        P procedure;
        bool hasProcedure;
    };

    template<typename T>
    struct Ptr : public Base
    {
        Ptr(Type type_, T*& value_) : type(type_), value(value_)
        {
        }

        ~Ptr()
        {
            if (value != NULL)
            {
                switch (type)
                {
                case ScopeGuard::Delete:
                    delete value;
                    break;
                case ScopeGuard::DeleteArray:
                    delete[] value;
                    break;
                default:
                    break;
                }
                value = NULL;
            }
        }

        T*& value;
        Type type;
    };

#ifdef __cpp_lambdas
    std::function<void()> onExit;
#endif // __cpp_lambdas
    bool dismissed;
    Base* base;
};

#define SCOPE_GUARD_LINENAME_CAT(name, line) name##line
#define SCOPE_GUARD_LINENAME(name, line) SCOPE_GUARD_LINENAME_CAT(name, line)
#define ON_SCOPE_EXIT(...) ScopeGuard SCOPE_GUARD_LINENAME(ScopeGuard, __LINE__)(##__VA_ARGS__)
#endif // !SCOPE_GUARD_HPP
