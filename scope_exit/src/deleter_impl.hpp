#pragma once

#include "marco.h"

#ifndef SCOPE_EXIT_MODULE
#  include <cstdlib>
#endif // !SCOPE_EXIT_MODULE

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

    SCOPE_EXIT_MODULE_INLINE_VARIABLE DeletePtr delete_ptr;

    SCOPE_EXIT_MODULE_INLINE_VARIABLE DeleteArray delete_array;

    SCOPE_EXIT_MODULE_INLINE_VARIABLE FreePtr free_ptr;
} // namespace lite
