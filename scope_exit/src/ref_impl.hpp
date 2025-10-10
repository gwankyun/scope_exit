#pragma once

#ifndef SCOPE_EXIT_REF_MODULE_EXPORT
#  ifdef SCOPE_EXIT_REF_MODULE
#    define SCOPE_EXIT_REF_MODULE_EXPORT export
#  else
#    define SCOPE_EXIT_REF_MODULE_EXPORT
#  endif // SCOPE_EXIT_REF_MODULE
#endif   // !SCOPE_EXIT_REF_MODULE_EXPORT

#ifndef SCOPE_EXIT_REF_MODULE_INLINE
#  ifdef SCOPE_EXIT_REF_MODULE
#    define SCOPE_EXIT_REF_MODULE_INLINE
#  else
#    define SCOPE_EXIT_REF_MODULE_INLINE inline
#  endif // SCOPE_EXIT_REF_MODULE
#endif   // !SCOPE_EXIT_REF_MODULE_INLINE

SCOPE_EXIT_REF_MODULE_EXPORT namespace lite
{
    // ���ð�װ����ģ��
    template <typename T>
    class reference_wrapper
    {
      public:
        typedef T type;

        // ���캯��������һ������
        explicit reference_wrapper(T& _ref) : m_ptr(&_ref) {}

        // ���ƹ��캯��
        reference_wrapper(const reference_wrapper& _other) : m_ptr(_other.m_ptr) {}

        // ��ֵ������
        reference_wrapper& operator=(const reference_wrapper& _other)
        {
            if (this != &_other)
            {
                m_ptr = _other.m_ptr;
            }
            return *this;
        }

        // ת����������������ʽת����ԭʼ���͵�����
        operator T&() const
        {
            return *m_ptr;
        }

        // ��ȡ���õĺ���
        T& get() const
        {
            return *m_ptr;
        }

        // ����Ƿ�Ϊ�գ����Ƿ���false����Ϊ���ǲ�֧�ֿ����ã�
        bool empty() const
        {
            return false;
        }

      private:
        T* m_ptr; // �洢ָ�����ö����ָ��
    };

    // ref����ģ�壬�������ð�װ��
    template <typename T>
    SCOPE_EXIT_REF_MODULE_INLINE reference_wrapper<T> ref(T & _t)
    {
        return reference_wrapper<T>(_t);
    }

    // ref�������ػ����������reference_wrapperʹ��ref
    template <typename T>
    SCOPE_EXIT_REF_MODULE_INLINE reference_wrapper<T> ref(reference_wrapper<T> _t)
    {
        return _t;
    }

    // cref����ģ�壬�����������ð�װ��
    template <typename T>
    SCOPE_EXIT_REF_MODULE_INLINE reference_wrapper<const T> cref(const T& _t)
    {
        return reference_wrapper<const T>(_t);
    }

    // cref�������ػ����������reference_wrapperʹ��cref
    template <typename T>
    SCOPE_EXIT_REF_MODULE_INLINE reference_wrapper<const T> cref(reference_wrapper<T> _t)
    {
        return reference_wrapper<const T>(_t.get());
    }
} // namespace lite
