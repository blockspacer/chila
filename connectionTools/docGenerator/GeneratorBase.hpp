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

#ifndef CHILA_CONNECTIONTOOLS_DOCGENERATOR_UTIL_HPP
#define	CHILA_CONNECTIONTOOLS_DOCGENERATOR_UTIL_HPP

#include <chila/connectionTools/lib/tree/Connector.hpp>
#include <boost/function.hpp>
#include <iostream>
#include <chila/lib/misc/util.hpp>
#include <chila/lib/misc/SinkInserter.hpp>
#include <chila/lib/misc/macrosDef.hpp>

#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE

#define libMisc chila::lib::misc
#define mtLibTree chila::connectionTools::lib::tree
#define PREFIX chila::lib::misc::repeatText(indent, "    ")

DEF_NAMESPACE(3, (chila,connectionTools,docGenerator))
{
    template <typename Container>
    inline std::ostream &operator<<(std::ostream &out, const mtLibTree::Object<Container> &arg)
    {
        return out << arg.getPath().getStringRep();
    }

    template <typename Container>
    struct PrintLink : public chila::lib::misc::SinkInserter< PrintLink<Container> >
    {
        const mtLibTree::Object<Container> &object;
        const bool fullPath;

        PrintLink(const mtLibTree::Object<Container> &object, bool fullPath = false) :
            object(object), fullPath(fullPath) {}

        std::ostream &write(std::ostream &out) const
        {
            return out << "<link linkend='" << object << "'>" <<
                    (fullPath ? object.getPath().getStringRep() : object.getName()) << "</link>";
        }
    };

    template <typename Container>
    inline PrintLink<Container> printLink(const mtLibTree::Object<Container> &object,
            bool fullPath = false)
    {
        return PrintLink<Container>(object, fullPath);
    }

    struct incInd : public chila::lib::misc::SinkInserter<incInd>
    {
        incInd(unsigned &indent) { ++indent; }
        std::ostream &write(std::ostream &out) const { return out; }
    };

    struct decInd : public chila::lib::misc::SinkInserter<decInd>
    {
        decInd(unsigned &indent) { --indent; }
        std::ostream &write(std::ostream &out) const { return out; }
    };

    struct GeneratorBase
    {
        public:
            virtual void generate() = 0;

        protected:
            template <typename Object>
            GeneratorBase(std::ostream &out, const Object &object) : out(out), indent(0)
            {
                modNspPath = object.getPath();
                modNspPath.pop();
            }

            struct ColData
            {
                std::string name, title;
                unsigned width;
                ColData(const std::string &name, unsigned width, const std::string &title) : name(name),
                    width(width), title(title) {}
            };

            struct IncIndent
            {
                unsigned &indent;

                IncIndent(unsigned &indent) : indent(++indent) {}
                ~IncIndent() { assert(indent-- > 0); }
            };

            struct Closer : boost::noncopyable
            {
                typedef boost::function<void()> CloseFun;
                CloseFun closeFun;

                Closer(const CloseFun &closeFun) : closeFun(closeFun) {}
                ~Closer() { if (closeFun) closeFun(); }
            };

            typedef std::vector<ColData> ColDataVec;

            std::ostream &out;
            libMisc::Path modNspPath;
            unsigned indent;

            Closer::CloseFun startSection(const std::string &title, const std::string &extra = "");
            void endSection();

            Closer::CloseFun startTable(const ColDataVec &colDataVec);
            void endTable();

            Closer::CloseFun startTag(const std::string &tag, const std::string &extra = "");
            void endTag(const std::string &tag);

    };

}}}

#undef libMisc
#undef PREFIX
#undef mtLibTree
#undef DEF_NAMESPACE
#include <chila/lib/misc/macrosUndef.hpp>

#endif
