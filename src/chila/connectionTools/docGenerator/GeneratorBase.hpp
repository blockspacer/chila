/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#ifndef CHILA_CONNECTIONTOOLS_DOCGENERATOR__GENERATORBASE_HPP
#define CHILA_CONNECTIONTOOLS_DOCGENERATOR__GENERATORBASE_HPP

//#include <chila/connectionTools/lib/tree/Connector.hpp>
//#include <boost/function.hpp>
//#include <iostream>
//#include <chila/lib/misc/util.hpp>
//#include <chila/lib/misc/SinkInserter.hpp>
//#include <chila/lib/misc/macrosExp.hpp>
//
//#define my_assert CHILA_LIB_MISC__ASSERT
//#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE
//
//#define libMisc chila::lib::misc
//#define cclTree chila::connectionTools::lib::tree
//#define PREFIX chila::lib::misc::repeatText(indent, "    ")
//
//DEF_NAMESPACE(3, (chila,connectionTools,docGenerator))
//{
//    template <typename Container>
//    inline std::ostream &operator<<(std::ostream &out, const cclTree::Object<Container> &arg)
//    {
//        return out << arg.getPath().getStringRep();
//    }
//
//    template <typename Container>
//    struct PrintLink final: public chila::lib::misc::SinkInserter< PrintLink<Container> >
//    {
//        const cclTree::Object<Container> &object;
//        const bool fullPath;
//
//        PrintLink(const cclTree::Object<Container> &object, bool fullPath = false) :
//            object(object), fullPath(fullPath) {}
//
//        std::ostream &write(std::ostream &out) const
//        {
//            return out << "<link linkend='" << object << "'>" <<
//                    (fullPath ? object.getPath().getStringRep() : object.getName()) << "</link>";
//        }
//    };
//
//    template <typename Container>
//    inline PrintLink<Container> printLink(const cclTree::Object<Container> &object,
//            bool fullPath = false)
//    {
//        return PrintLink<Container>(object, fullPath);
//    }
//
//    struct incInd final: public chila::lib::misc::SinkInserter<incInd>
//    {
//        incInd(unsigned &indent) { ++indent; }
//        std::ostream &write(std::ostream &out) const { return out; }
//    };
//
//    struct decInd final: public chila::lib::misc::SinkInserter<decInd>
//    {
//        decInd(unsigned &indent) { --indent; }
//        std::ostream &write(std::ostream &out) const { return out; }
//    };
//
//    struct GeneratorBase
//    {
//        public:
//            virtual void generate() = 0;
//
//        protected:
//            template <typename Object>
//            GeneratorBase(std::ostream &out, const Object &object) : out(out), indent(0)
//            {
//                modNspPath = object.getPath();
//                modNspPath.pop();
//            }
//
//            struct ColData
//            {
//                std::string name, title;
//                unsigned width;
//                ColData(const std::string &name, unsigned width, const std::string &title) : name(name),
//                    width(width), title(title) {}
//            };
//
//            struct IncIndent
//            {
//                unsigned &indent;
//
//                IncIndent(unsigned &indent) : indent(++indent) {}
//                ~IncIndent() { my_assert(indent-- > 0); }
//            };
//
//            struct Closer : boost::noncopyable
//            {
//                typedef boost::function<void()> CloseFun;
//                CloseFun closeFun;
//
//                Closer(const CloseFun &closeFun) : closeFun(closeFun) {}
//                ~Closer() { if (closeFun) closeFun(); }
//            };
//
//            typedef std::vector<ColData> ColDataVec;
//
//            std::ostream &out;
//            libMisc::Path modNspPath;
//            unsigned indent;
//
//            Closer::CloseFun startSection(const std::string &title, const std::string &extra = "");
//            void endSection();
//
//            Closer::CloseFun startTable(const ColDataVec &colDataVec);
//            void endTable();
//
//            Closer::CloseFun startTag(const std::string &tag, const std::string &extra = "");
//            void endTag(const std::string &tag);
//
//    };
//
//}}}
//
//#undef my_assert
//#undef libMisc
//#undef PREFIX
//#undef cclTree
//#undef DEF_NAMESPACE
//
//
//#endif
