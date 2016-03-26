/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_MISC__MEMORYPOOL_HPP
#define CHILA_LIB_MISC__MEMORYPOOL_HPP

#include "macrosDef.hpp"
#include <boost/pool/object_pool.hpp>

#include "macros.fgen.hpp"

MY_NSP_START
{
    template <typename ElementType, typename UserAllocator = boost::default_user_allocator_new_delete>
    class MemoryPool
    {
        public:
            typedef boost::object_pool<ElementType, UserAllocator> Pool;

            struct DestroyFun
            {
                MemoryPool &pool;
                DestroyFun(MemoryPool &pool) : pool(pool) {}

                void operator()(typename MemoryPool::Pool::element_type *p)
                {
                    pool.destroy(p);
                }
            };

            using unique_ptr = std::unique_ptr<typename Pool::element_type, DestroyFun>;

            typename Pool::element_type *malloc()
            {
                boost::mutex::scoped_lock lock(mutex);
                return pool.malloc();
            }

            void free(typename Pool::element_type *p)
            {
                boost::mutex::scoped_lock lock(mutex);
                pool.free(p);
            }

            bool is_from(typename Pool::element_type *p) const
            {
                boost::mutex::scoped_lock lock(mutex);
                return pool.is_from(p);
            }

            template <typename ...Args>
            typename Pool::element_type *construct(Args&&... args)
            {
                boost::mutex::scoped_lock lock(mutex);

                typename Pool::element_type *const ret = pool.malloc();
                if (ret == 0)
                    throw std::bad_alloc();

                try
                {
                    new (ret) typename Pool::element_type(std::forward<Args>(args)...);
                }
                catch (...)
                {
                    pool.free(ret);
                    throw;
                }
                return ret;
            }


            void destroy(typename Pool::element_type *p)
            {
                boost::mutex::scoped_lock lock(mutex);
                pool.destroy(p);
            }

            DestroyFun destroyFun() { return DestroyFun(*this); }

            template <typename ...Args>
            std::shared_ptr<typename Pool::element_type> make_shared(Args&&... args)
            {
                return std::shared_ptr<typename Pool::element_type>(construct(std::forward<Args>(args)...), destroyFun());


            }

            template <typename ...Args>
            unique_ptr make_unique(Args&&... args)
            {
                return unique_ptr(construct(std::forward<Args>(args)...), destroyFun());
            }

        private:
            mutable boost::mutex mutex;

            Pool pool;
    };
}
MY_NSP_END

#include "macros.fgen.hpp"

//#undef DEF_CONSTRUCT

#endif

