#pragma once

#ifndef SCOPE_EXIT_MODULE_EXPORT
#  ifdef SCOPE_EXIT_MODULE
#    define SCOPE_EXIT_MODULE_EXPORT export
#  else
#    define SCOPE_EXIT_MODULE_EXPORT
#  endif // SCOPE_EXIT_MODULE
#endif   // !SCOPE_EXIT_MODULE_EXPORT

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
        scope_exit& operator=(const scope_exit&);

        callback* m_callback;
    };

    template <typename F>
    scope_exit::callback* make_callback(F _f)
    {
        struct CB : public scope_exit::callback
        {
            CB(F _f) : f(_f) {}
            ~CB()
            {
                f();
            }
            F f;
        };
        CB* cb = new CB(_f);
        return cb;
    }

    template <typename F, typename T1>
    scope_exit::callback* make_callback(F _f, T1 _t1)
    {
        struct CB : public scope_exit::callback
        {
            CB(F _f) : f(_f) {}
            ~CB()
            {
                f(t1);
            }
            F f;
            T1 t1;
        };
        CB* cb = new CB(_f);
        cb->t1 = _t1;
        return cb;
    }

    template <typename F, typename T1, typename T2>
    scope_exit::callback* make_callback(F _f, T1 _t1, T2 _t2)
    {
        struct CB : public scope_exit::callback
        {
            CB(F _f) : f(_f) {}
            ~CB()
            {
                f(t1, t2);
            }
            F f;
            T1 t1;
            T2 t2;
        };
        CB* cb = new CB(_f);
        cb->t1 = _t1;
        cb->t2 = _t2;
        return cb;
    }

    template <typename F, typename T1, typename T2, typename T3>
    scope_exit::callback* make_callback(F _f, T1 _t1, T2 _t2, T3 _t3)
    {
        struct CB : public scope_exit::callback
        {
            CB(F _f) : f(_f) {}
            ~CB()
            {
                f(t1, t2, t3);
            }
            F f;
            T1 t1;
            T2 t2;
            T3 t3;
        };
        CB* cb = new CB(_f);
        cb->t1 = _t1;
        cb->t2 = _t2;
        cb->t3 = _t3;
        return cb;
    }
} // namespace lite
