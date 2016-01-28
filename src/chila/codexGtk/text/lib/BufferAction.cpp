/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "BufferAction.hpp"
#include <boost/range/adaptors.hpp>

#include "macros.fgen.hpp"

MY_NSP_START
{
    void BufferAction::undo(const GtkTextBufferPtr &buffer) const
    {
        switch (type)
        {
            case Type::INSERT: erase(buffer); break;
            case Type::ERASE: insert(buffer); break;
            default: abort();
        }
    }

    void BufferAction::redo(const GtkTextBufferPtr &buffer) const
    {
        switch (type)
        {
            case Type::ERASE: erase(buffer); break;
            case Type::INSERT: insert(buffer); break;
            default: abort();
        }
    }

    void BufferAction::insert(const GtkTextBufferPtr &buffer) const
    {
        buffer->insert(buffer->get_iter_at_offset(pos), text);
        buffer->place_cursor(buffer->get_iter_at_offset(pos + text.size()));
    }

    void BufferAction::erase(const GtkTextBufferPtr &buffer) const
    {
        auto begin = buffer->get_iter_at_offset(pos);
        auto end = buffer->get_iter_at_offset(pos + text.size());
        buffer->erase(begin, end);

        buffer->place_cursor(buffer->get_iter_at_offset(pos));
    }

    void BufferActionGroup::undo(const GtkTextBufferPtr &buffer) const
    {
        for (auto &action : bActionList | boost::adaptors::reversed)
        {
            action->undo(buffer);
        }
    }

    void BufferActionGroup::redo(const GtkTextBufferPtr &buffer) const
    {
        for (auto &action : bActionList)
        {
            action->redo(buffer);
        }

    }

}
MY_NSP_END

