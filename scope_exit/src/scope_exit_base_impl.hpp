#pragma once

#include "marco.h"

SCOPE_EXIT_MODULE_EXPORT namespace lite
{
    struct scope_exit
    {
        struct callback
        {
            callback() {}
            virtual ~callback() {}
        };

        explicit scope_exit(callback* _callback) : m_callback(_callback) {}

        ~scope_exit()
        {
            delete m_callback;
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
