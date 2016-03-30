/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_LIB_MISC__VALUESTREAMER_HPP
#define CHILA_LIB_MISC__VALUESTREAMER_HPP

#include "fwd.hpp"
#include "exceptions.hpp"
#include <map>
#include <boost/any.hpp>
#include <typeindex>
#include <chila/lib/misc/util.hpp>
#include <boost/type_index.hpp>
#include <boost/make_shared.hpp>
#include <boost/utility.hpp>
#include "SinkInserter.hpp"

#include "macros.fgen.hpp"

#define is_not_streamable(ttype) \
    typename boost::disable_if<std::is_base_of<Streamable, Type>, ttype>::type

MY_NSP_START
{
    class ValueStreamer
    {
        public:
            template <typename Type>
            struct Inserter final : public SinkInserter<Inserter<Type>>
            {
                const Type &value;
                const ValueStreamer &valueStreamer;

                Inserter(const ValueStreamer &valueStreamer, const Type &value) :
                    valueStreamer(valueStreamer),
                    value(value)
                {
                }

                void write(std::ostream &out) const
                {
                    valueStreamer.stream(out, value);
                }
            };

            template <typename Type>
            using Fun = std::function<void(std::ostream &out, const Type &value)>;

            struct Streamable
            {
                virtual void stream(std::ostream &out) const = 0;
                virtual ~Streamable() {}
            };

            template <typename Type>
            void addFun(Fun<Type> fun)
            {
                my_assert(map.insert({boost::typeindex::type_id<Type>(), std::make_shared<StreamFunImpl<Type>>(fun)}).second);
            }

            template <typename Type>
            void stream(std::ostream &out, const Type &value) const
            {
                auto it = map.find(boost::typeindex::type_id<Type>());
                if (it == map.end())
                {
                    streamNoMap(out, value, 0, 0);
                }
                else
                {
                    auto pf = std::dynamic_pointer_cast<const StreamFunImpl<Type>>(it->second);
                    pf->stream(out, value);
                }
            }

            template <typename Type>
            Inserter<Type> inserter(const Type &value) const
            {
                return Inserter<Type>(*this, value);
            }

        private:
            struct StreamFun
            {
                virtual ~StreamFun() {}
            };

            template <typename Type>
            struct StreamFunImpl final : public StreamFun
            {
                Fun<Type> fun;

                StreamFunImpl(Fun<Type> fun) : fun(rvalue_cast(fun)) {}

                void stream(std::ostream &out, const Type &value) const
                {
                    fun(out, value);
                }
            };

            CHILA_LIB_MISC__FWDEC_SPTR(StreamFun);

            using Map = std::map<boost::typeindex::type_index, StreamFunSCPtr>;
            Map map;

            void streamNoMap(std::ostream &out, const Streamable &value, int, int) const
            {
                value.stream(out);
            }

            template <typename Type>
            auto streamNoMap(std::ostream &out, const Type &value, int, int) const -> is_not_streamable(decltype(&(*value)))
            {
                stream(out, *value);
                return nullptr;
            }

            template <typename Type>
            auto streamNoMap(std::ostream &out, const Type &value, int, long) const -> decltype(out << value)
            {
                return out << value;
            }

            template <typename Type>
            auto streamNoMap(std::ostream &out, const Type &value, long, long) const -> is_not_streamable(void)
            {
                out << "<?>";
            }
    };
}
MY_NSP_END

#undef is_not_streamable
#include "macros.fgen.hpp"
#endif
