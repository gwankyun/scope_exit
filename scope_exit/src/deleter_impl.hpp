#pragma once

#include "marco.h"

SCOPE_EXIT_MODULE_EXPORT namespace lite
{
    struct DeletePtr
    {
        template <typename T>
        void operator()(T* _ptr)
        {
            delete _ptr;
        }
    };

    struct DeleteArray
    {
        template <typename T>
        void operator()(T* _ptr)
        {
            delete[] _ptr;
        }
    };

    struct FreePtr
    {
        template <typename T>
        void operator()(T* _ptr)
        {
            free(_ptr);
        }
    };

    SCOPE_EXIT_MODULE_INLINE_VALUE DeletePtr delete_ptr;

    SCOPE_EXIT_MODULE_INLINE_VALUE DeleteArray delete_array;

    SCOPE_EXIT_MODULE_INLINE_VALUE FreePtr free_ptr;
} // namespace lite
