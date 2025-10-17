#pragma once

#include "marco.h"

SCOPE_EXIT_MODULE_EXPORT namespace lite
{
    // 引用包装器类模板
    template <typename T>
    class reference_wrapper
    {
      public:
        typedef T type;

        // 构造函数，接受一个引用
        explicit reference_wrapper(T& _ref) : m_ptr(&_ref) {}

        // 复制构造函数
        reference_wrapper(const reference_wrapper& _other) : m_ptr(_other.m_ptr)
        {
        }

        // 赋值操作符
        reference_wrapper& operator=(const reference_wrapper& _other)
        {
            if (this != &_other)
            {
                m_ptr = _other.m_ptr;
            }
            return *this;
        }

        // 转换操作符，允许隐式转换回原始类型的引用
        operator T&() const
        {
            return *m_ptr;
        }

        // 获取引用的函数
        T& get() const
        {
            return *m_ptr;
        }

        // 检查是否为空（总是返回false，因为我们不支持空引用）
        bool empty() const
        {
            return false;
        }

      private:
        T* m_ptr; // 存储指向被引用对象的指针
    };

    // ref函数模板，创建引用包装器
    template <typename T>
    SCOPE_EXIT_MODULE_INLINE reference_wrapper<T> ref(T & _t)
    {
        return reference_wrapper<T>(_t);
    }

    // ref函数的特化，不允许对reference_wrapper使用ref
    template <typename T>
    SCOPE_EXIT_MODULE_INLINE reference_wrapper<T> ref(reference_wrapper<T> _t)
    {
        return _t;
    }

    // cref函数模板，创建常量引用包装器
    template <typename T>
    SCOPE_EXIT_MODULE_INLINE reference_wrapper<const T> cref(const T& _t)
    {
        return reference_wrapper<const T>(_t);
    }

    // cref函数的特化，不允许对reference_wrapper使用cref
    template <typename T>
    SCOPE_EXIT_MODULE_INLINE reference_wrapper<const T> cref(
        reference_wrapper<T> _t)
    {
        return reference_wrapper<const T>(_t.get());
    }
} // namespace lite
