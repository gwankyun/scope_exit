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

    template <typename Fn>
    SCOPE_EXIT_MODULE_INLINE scope_exit::callback* make_callback(Fn _f)
    {
        struct CB : public scope_exit::callback
        {
            CB(Fn _f) : f(_f) {}
            ~CB()
            {
                f();
            }
            Fn f;
        };
        CB* cb = new CB(_f);
        return cb;
    }

    template <typename Fn, typename T1>
    SCOPE_EXIT_MODULE_INLINE scope_exit::callback* make_callback(Fn _f, T1 _t1)
    {
        struct CB : public scope_exit::callback
        {
            CB(Fn _f, T1 _t1) : f(_f), t1(_t1) {}
            ~CB()
            {
                f(t1);
            }
            Fn f;
            T1 t1;
        };
        CB* cb = new CB(_f, _t1);
        return cb;
    }

    template <typename Fn, typename T1, typename T2>
    SCOPE_EXIT_MODULE_INLINE scope_exit::callback* make_callback(
        Fn _f, T1 _t1, T2 _t2)
    {
        struct CB : public scope_exit::callback
        {
            CB(Fn _f, T1 _t1, T2 _t2) : f(_f), t1(_t1), t2(_t2) {}
            ~CB()
            {
                f(t1, t2);
            }
            Fn f;
            T1 t1;
            T2 t2;
        };
        CB* cb = new CB(_f, _t1, _t2);
        return cb;
    }

    template <typename Fn, typename T1, typename T2, typename T3>
    SCOPE_EXIT_MODULE_INLINE scope_exit::callback* make_callback(
        Fn _f, T1 _t1, T2 _t2, T3 _t3)
    {
        struct CB : public scope_exit::callback
        {
            CB(Fn _f, T1 _t1, T2 _t2, T3 _t3) : f(_f), t1(_t1), t2(_t2), t3(_t3)
            {
            }
            ~CB()
            {
                f(t1, t2, t3);
            }
            Fn f;
            T1 t1;
            T2 t2;
            T3 t3;
        };
        CB* cb = new CB(_f, _t1, _t2, _t3);
        return cb;
    }

    template <typename Fn, typename T1, typename T2, typename T3, typename T4>
    SCOPE_EXIT_MODULE_INLINE scope_exit::callback* make_callback(
        Fn _f, T1 _t1, T2 _t2, T3 _t3, T4 _t4)
    {
        struct CB : public scope_exit::callback
        {
            CB(Fn _f, T1 _t1, T2 _t2, T3 _t3, T4 _t4)
                : f(_f), t1(_t1), t2(_t2), t3(_t3), t4(_t4)
            {
            }
            ~CB()
            {
                f(t1, t2, t3, t4);
            }
            Fn f;
            T1 t1;
            T2 t2;
            T3 t3;
            T4 t4;
        };
        CB* cb = new CB(_f, _t1, _t2, _t3, _t4);
        return cb;
    }

    template <typename Fn, typename T1, typename T2, typename T3, typename T4,
        typename T5>
    SCOPE_EXIT_MODULE_INLINE scope_exit::callback* make_callback(
        Fn _f, T1 _t1, T2 _t2, T3 _t3, T4 _t4, T5 _t5)
    {
        struct CB : public scope_exit::callback
        {
            CB(Fn _f, T1 _t1, T2 _t2, T3 _t3, T4 _t4, T5 _t5)
                : f(_f), t1(_t1), t2(_t2), t3(_t3), t4(_t4), t5(_t5)
            {
            }
            ~CB()
            {
                f(t1, t2, t3, t4, t5);
            }
            Fn f;
            T1 t1;
            T2 t2;
            T3 t3;
            T4 t4;
            T5 t5;
        };
        CB* cb = new CB(_f, _t1, _t2, _t3, _t4, _t5);
        return cb;
    }

    template <typename Fn, typename T1, typename T2, typename T3, typename T4,
        typename T5, typename T6>
    SCOPE_EXIT_MODULE_INLINE scope_exit::callback* make_callback(
        Fn _fn, T1 _t1, T2 _t2, T3 _t3, T4 _t4, T5 _t5, T6 _t6)
    {
        struct CB : public scope_exit::callback
        {
            CB(Fn _fn, T1 _t1, T2 _t2, T3 _t3, T4 _t4, T5 _t5, T6 _t6)
                : fn(_fn), t1(_t1), t2(_t2), t3(_t3), t4(_t4), t5(_t5), t6(_t6)
            {
            }
            ~CB()
            {
                fn(t1, t2, t3, t4, t5, t6);
            }
            Fn fn;
            T1 t1;
            T2 t2;
            T3 t3;
            T4 t4;
            T5 t5;
            T6 t6;
        };
        CB* cb = new CB(_fn, _t1, _t2, _t3, _t4, _t5, _t6);
        return cb;
    }

    template <typename Fn, typename T1, typename T2, typename T3, typename T4,
        typename T5, typename T6, typename T7>
    SCOPE_EXIT_MODULE_INLINE scope_exit::callback* make_callback(
        Fn _fn, T1 _t1, T2 _t2, T3 _t3, T4 _t4, T5 _t5, T6 _t6, T7 _t7)
    {
        struct CB : public scope_exit::callback
        {
            CB(Fn _fn, T1 _t1, T2 _t2, T3 _t3, T4 _t4, T5 _t5, T6 _t6, T7 _t7)
                : fn(_fn), t1(_t1), t2(_t2), t3(_t3), t4(_t4), t5(_t5), t6(_t6),
                  t7(_t7)
            {
            }
            ~CB()
            {
                fn(t1, t2, t3, t4, t5, t6, t7);
            }
            Fn fn;
            T1 t1;
            T2 t2;
            T3 t3;
            T4 t4;
            T5 t5;
            T6 t6;
            T7 t7;
        };
        CB* cb = new CB(_fn, _t1, _t2, _t3, _t4, _t5, _t6, _t7);
        return cb;
    }

    template <typename Fn, typename T1, typename T2, typename T3, typename T4,
        typename T5, typename T6, typename T7, typename T8>
    SCOPE_EXIT_MODULE_INLINE scope_exit::callback* make_callback(
        Fn _fn, T1 _t1, T2 _t2, T3 _t3, T4 _t4, T5 _t5, T6 _t6, T7 _t7, T8 _t8)
    {
        struct CB : public scope_exit::callback
        {
            CB(Fn _fn, T1 _t1, T2 _t2, T3 _t3, T4 _t4, T5 _t5, T6 _t6, T7 _t7,
                T8 _t8)
                : fn(_fn), t1(_t1), t2(_t2), t3(_t3), t4(_t4), t5(_t5), t6(_t6),
                  t7(_t7), t8(_t8)
            {
            }
            ~CB()
            {
                fn(t1, t2, t3, t4, t5, t6, t7, t8);
            }
            Fn fn;
            T1 t1;
            T2 t2;
            T3 t3;
            T4 t4;
            T5 t5;
            T6 t6;
            T7 t7;
            T8 t8;
        };
        CB* cb = new CB(_fn, _t1, _t2, _t3, _t4, _t5, _t6, _t7, _t8);
        return cb;
    }

    template <typename Fn, typename T1, typename T2, typename T3, typename T4,
        typename T5, typename T6, typename T7, typename T8, typename T9>
    SCOPE_EXIT_MODULE_INLINE scope_exit::callback* make_callback(Fn _fn, T1 _t1,
        T2 _t2, T3 _t3, T4 _t4, T5 _t5, T6 _t6, T7 _t7, T8 _t8, T9 _t9)
    {
        struct CB : public scope_exit::callback
        {
            CB(Fn _fn, T1 _t1, T2 _t2, T3 _t3, T4 _t4, T5 _t5, T6 _t6, T7 _t7,
                T8 _t8, T9 _t9)
                : fn(_fn), t1(_t1), t2(_t2), t3(_t3), t4(_t4), t5(_t5), t6(_t6),
                  t7(_t7), t8(_t8), t9(_t9)
            {
            }
            ~CB()
            {
                fn(t1, t2, t3, t4, t5, t6, t7, t8, t9);
            }
            Fn fn;
            T1 t1;
            T2 t2;
            T3 t3;
            T4 t4;
            T5 t5;
            T6 t6;
            T7 t7;
            T8 t8;
            T9 t9;
        };
        CB* cb = new CB(_fn, _t1, _t2, _t3, _t4, _t5, _t6, _t7, _t8, _t9);
        return cb;
    }
} // namespace lite
