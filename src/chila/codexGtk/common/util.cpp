/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "util.hpp"
#include <boost/filesystem.hpp>
#include "macros.fgen.hpp"

MY_NSP_START
{
    Glib::RefPtr<Gtk::Builder> loadGtkBuilder(const boost::filesystem::path &file)
    {
        app_assert(bfs::is_regular(file), "file " << file << " does not exists or is not a regular file");

        return Gtk::Builder::create_from_file(file.string());
    }
}
MY_NSP_END
