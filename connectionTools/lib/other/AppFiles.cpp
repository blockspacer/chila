/* Copyright 2011 Roberto Daniel Gimenez Gamarra
 * (C.I.: 1.439.390 - Paraguay)
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "AppFiles.hpp"
#include <boost/filesystem.hpp>
#include <chila/lib/misc/util.hpp>
#include <tinyXPath/tinyxml.h>
#include <chila/lib/tinyXMLUtils/macrosDef.hpp>
#include <chila/lib/tinyXMLUtils/XMLPath.hpp>
#include <chila/lib/misc/macrosDef.hpp>

#define DEF_NAMESPACE           CHILA_LIB_MISC__DEF_NAMESPACE
#define tixml_iterate_elements  CHILA_LIB_TINYXMLUTILS__TIXML_ITERATE_ELEMENTS

#define push_tag CHILA_LIB_TINYXMLUTILS__PUSH_TAG
#define check_tag_and_push CHILA_LIB_TINYXMLUTILS__CHECK_TAG_AND_PUSH

DEF_NAMESPACE(4, (chila,connectionTools,lib,other))
{
    using chila::lib::tinyXMLUtils::XMLPath;

    /** Constructor. */
    AppFiles::AppFiles(const boost::filesystem::path &appFiles)
    {
        TiXmlDocument doc;
        XMLPath path;

        boost::filesystem::path srcDir = appFiles.parent_path();

        doc.LoadFile(appFiles.string().c_str());
        chila::lib::misc::check(doc);

        TiXmlElement *root = doc.RootElement();
        const boost::filesystem::path appFileAttrPath = path.getAttrAndCheck(root, "application");

        appFile = appFileAttrPath.has_root_path() ? appFileAttrPath : (srcDir / appFileAttrPath);

        assert(boost::filesystem::exists(appFile));

        check_tag_and_push(path, root, appFiles);

        // Iterates through the elements
        tixml_iterate_elements(root, argElem)
        {
            check_tag_and_push(path, argElem, connector);
            const boost::filesystem::path fileAttrStr = path.getAttrAndCheck(argElem, "name");

            const boost::filesystem::path file = fileAttrStr.has_root_path() ? fileAttrStr :
                (srcDir / fileAttrStr);

            assert(boost::filesystem::exists(file));

            files.push_back(file);
        }
    }

}}}}
