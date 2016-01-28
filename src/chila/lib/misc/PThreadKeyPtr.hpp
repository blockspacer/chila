/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_MISC__PTHREADKEYPTR_HPP
#define CHILA_LIB_MISC__PTHREADKEYPTR_HPP

#include <chila/lib/misc/util.hpp>
#include <pthread.h>

#include "macros.fgen.hpp"

MY_NSP_START
{
    template <typename Type>
    class PThreadKeyPtr
    {
        public:
            PThreadKeyPtr()
            {
                check_call_errno(::pthread_key_create(&key, PThreadKeyPtr::destroyKey));
            }

            explicit PThreadKeyPtr(void(*cleanup)(Type*))
            {
                check_call_errno(::pthread_key_create(&key, cleanup));
            }

            Type *get()
            {
                return reinterpret_cast<unsigned*>(pthread_getspecific(key));
            }

            Type *operator->() const
            {
                Type *ret = get();
                if (!ret)
                    BOOST_THROW_EXCEPTION(ValueNotSet());
                else
                    return ret;
            }

            Type &operator*() const
            {
                Type *ret = get();
                if (!ret)
                    BOOST_THROW_EXCEPTION(ValueNotSet());
                else
                    return *ret;
            }

            Type *release()
            {
                Type *ret = get();
                check_call_errno(::pthread_setspecific(key, nullptr));
                return ret;
            }

            void reset(Type *value = nullptr)
            {
                auto old = get();
                if (old)
                    destroyKey(old);

                check_call_errno(::pthread_setspecific(key, value));
            }

        private:
            pthread_key_t key;

            static void destroyKey(void *key)
            {
                if (key)
                {
                    delete reinterpret_cast<Type*>(key);
                }
            }
    };

}
MY_NSP_END

#include "macros.fgen.hpp"


#endif

