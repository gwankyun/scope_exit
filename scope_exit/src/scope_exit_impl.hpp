namespace lite
{
    struct scope_exit
    {
        struct base
        {
            base() {}
            virtual ~base() {}
        };

        explicit scope_exit(base* _base) : m_base(_base) {}

        ~scope_exit()
        {
            delete m_base;
        }

      private:
        scope_exit(const scope_exit&);
        scope_exit& operator=(const scope_exit&);

        base* m_base;
    };

    template <typename F>
    scope_exit::base* make_callback(F _f)
    {
        struct CB : public scope_exit::base
        {
            CB() {}
            ~CB()
            {
                f();
            }
            F f;
        };
        CB* cb = new CB();
        cb->f = _f;
        return cb;
    }

    template <typename F, typename T1>
    scope_exit::base* make_callback(F _f, T1 _t1)
    {
        struct CB : public scope_exit::base
        {
            CB() {}
            ~CB()
            {
                f(t1);
            }
            F f;
            T1 t1;
        };
        CB* cb = new CB();
        cb->f = _f;
        cb->t1 = _t1;
        return cb;
    }

    template <typename F, typename T1, typename T2>
    scope_exit::base* make_callback(F _f, T1 _t1, T2 _t2)
    {
        struct CB : public scope_exit::base
        {
            CB() {}
            ~CB()
            {
                f(t1, t2);
            }
            F f;
            T1 t1;
            T2 t2;
        };
        CB* cb = new CB();
        cb->f = _f;
        cb->t1 = _t1;
        cb->t2 = _t2;
        return cb;
    }

    template <typename F, typename T1, typename T2, typename T3>
    scope_exit::base* make_callback(F _f, T1 _t1, T2 _t2, T3 _t3)
    {
        struct CB : public scope_exit::base
        {
            CB() {}
            ~CB()
            {
                f(t1, t2, t3);
            }
            F f;
            T1 t1;
            T2 t2;
            T3 t3;
        };
        CB* cb = new CB();
        cb->f = _f;
        cb->t1 = _t1;
        cb->t2 = _t2;
        cb->t3 = _t3;
        return cb;
    }
} // namespace lite
