/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CODEX_TEXT_LIB__BUFFERACTION_HPP
#define CHILA_CODEX_TEXT_LIB__BUFFERACTION_HPP

#include <chila/lib/misc/util.hpp>
#include "fwd.hpp"

#include "macros.fgen.hpp"

MY_NSP_START
{
    struct BufferActionBase
    {
        virtual void undo(const GtkTextBufferPtr &buffer) const = 0;
        virtual void redo(const GtkTextBufferPtr &buffer) const = 0;

        virtual ~BufferActionBase() {}
    };

    class BufferActionGroup : public BufferActionBase
    {
        public:
            void undo(const GtkTextBufferPtr &buffer) const;
            void redo(const GtkTextBufferPtr &buffer) const;

            void add(const BufferActionBaseSPtr &action)
            {
                bActionList.push_back(action);
            }

        private:
            BufferActionList bActionList;
    };

    class BufferAction : public BufferActionBase
    {
        public:
            enum class Type { INSERT, ERASE };

            CHILA_LIB_MISC__NAMED_TUPLE_BODY
            (
                BufferAction,
                ((Type)(type))
                ((unsigned)(pos))
                ((Glib::ustring)(text))
            )
            {
            }

            void undo(const GtkTextBufferPtr &buffer) const;
            void redo(const GtkTextBufferPtr &buffer) const;

        private:
            void insert(const GtkTextBufferPtr &buffer) const;
            void erase(const GtkTextBufferPtr &buffer) const;
    };
}
MY_NSP_END

#include "macros.fgen.hpp"

#endif
