#pragma once

#include "marco.h"

#ifndef SCOPE_EXIT_MODULE
#include <type_traits>
#endif // !SCOPE_EXIT_MODULE

SCOPE_EXIT_MODULE_EXPORT namespace lite
{
    struct scope_exit
    {
        struct callback
        {
            callback() : release(false) {}
            virtual ~callback() {}
            bool release;
        };

        explicit scope_exit(callback* _callback) : m_callback(_callback) {}

        ~scope_exit()
        {
            if (m_callback != 0)
            {
                reset();
            }
        }

        void release() CXX_NOEXCEPT
        {
            m_callback->release = true;
        }

        void reset() CXX_NOEXCEPT
        {
            delete m_callback;
            m_callback = 0;
        }

        void reset(callback* _callback) CXX_NOEXCEPT
        {
            release();
            reset();
            m_callback = _callback;
        }

      private:
        scope_exit(const scope_exit&);
        scope_exit& operator=(const scope_exit&)
        {
            return *this;
        }

        callback* m_callback;
    };
} // namespace lite
