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

#include "GeneratorBase.hpp"
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/assign/list_of.hpp>
#include <chila/lib/misc/RepeatText.hpp>
#include <boost/bind.hpp>
#include <chila/connectionTools/lib/tree/namespace.hpp>

//@TODO Trimear todo

#include <chila/lib/misc/macrosDef.hpp>

#define mtLibTree chila::connectionTools::lib::tree

#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE
#define PREFIX libMisc::repeatText(indent, "    ")
#define INC_INDENT IncIndent incIndent(indent)

#define libMisc chila::lib::misc

DEF_NAMESPACE(3, (chila,connectionTools,docGenerator))
{
    typedef std::vector<std::string> StringVec;

    GeneratorBase::Closer::CloseFun GeneratorBase::startSection(const std::string &title,
            const std::string &extra)
    {
//        out << PREFIX <<   "<section";
//            if (!xmlns.empty()) out << " xmlns='" << xmlns << "'";
//            if (!id.empty()) out << " xml:id='" << id << "'";
//            out << ">\n";

        out << PREFIX << "<section";
        if (!extra.empty()) out << " " << extra;
        out << ">\n";


        out << PREFIX << "    <title>" << title << "</title>\n";

        indent++;

        return boost::bind(&GeneratorBase::endSection, this);
    }

    void GeneratorBase::endSection()
    {
        indent--;
        out << PREFIX <<   "</section>\n";
    }

    GeneratorBase::Closer::CloseFun GeneratorBase::startTable(const ColDataVec &colDataVec)
    {
        out << PREFIX << "<informaltable>\n"
            << PREFIX << "    <tgroup cols='" << colDataVec.size() << "'>\n";

        BOOST_FOREACH(const ColData &colData, colDataVec)
        {
            out << PREFIX << "        <colspec colwidth='" << colData.width << "' colname='" << colData.name << "'/>\n";
        }

        out << PREFIX << "        <thead>\n"
            << PREFIX << "            <row>\n";

        BOOST_FOREACH(const ColData &colData, colDataVec)
        {
            out <<   PREFIX << "                <entry align='center'>" << colData.title << "</entry>\n";
        }

        out << PREFIX << "            </row>\n"
            << PREFIX << "        </thead>\n"
            << PREFIX << "        <tbody>\n";

        indent += 3;
        return boost::bind(&GeneratorBase::endTable, this);
    }

    void GeneratorBase::endTable()
    {
        indent -= 3;
        out << PREFIX << "        </tbody>\n"
            << PREFIX << "    </tgroup>\n"
            << PREFIX << "</informaltable>\n";
    }

    GeneratorBase::Closer::CloseFun GeneratorBase::startTag(const std::string &tag, const std::string &extra)
    {
        out << PREFIX << "<" << tag << (extra.empty() ? std::string() : " " + extra) + ">\n";
        return boost::bind(&GeneratorBase::endTag, this, tag);
    }

    void GeneratorBase::endTag(const std::string &tag)
    {
        out << PREFIX << "</" << tag << ">\n";
    }

}}}
