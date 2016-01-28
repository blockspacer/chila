/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

//
//#include "GeneratorBase.hpp"
//#include <boost/algorithm/string/trim.hpp>
//#include <boost/algorithm/string/case_conv.hpp>
//#include <boost/assign/list_of.hpp>
//#include <chila/lib/misc/RepeatText.hpp>
//#include <boost/bind.hpp>
//#include <chila/connectionTools/lib/tree/namespace.hpp>
//
////@TODO Trimear todo
//
//#include <chila/lib/misc/macrosExp.hpp>
//
//#define cclTree chila::connectionTools::lib::tree
//
//#define DEF_NAMESPACE CHILA_LIB_MISC__DEF_NAMESPACE
//#define PREFIX libMisc::repeatText(indent, "    ")
//#define INC_INDENT IncIndent incIndent(indent)
//
//#define libMisc chila::lib::misc
//
//DEF_NAMESPACE(3, (chila,connectionTools,docGenerator))
//{
//    typedef std::vector<std::string> StringVec;
//
//    GeneratorBase::Closer::CloseFun GeneratorBase::startSection(const std::string &title,
//            const std::string &extra)
//    {
////        out << PREFIX <<   "<section";
////            if (!xmlns.empty()) out << " xmlns='" << xmlns << "'";
////            if (!id.empty()) out << " xml:id='" << id << "'";
////            out << ">\n";
//
//        out << PREFIX << "<section";
//        if (!extra.empty()) out << " " << extra;
//        out << ">\n";
//
//
//        out << PREFIX << "    <title>" << title << "</title>\n";
//
//        indent++;
//
//        return boost::bind(&GeneratorBase::endSection, this);
//    }
//
//    void GeneratorBase::endSection()
//    {
//        indent--;
//        out << PREFIX <<   "</section>\n";
//    }
//
//    GeneratorBase::Closer::CloseFun GeneratorBase::startTable(const ColDataVec &colDataVec)
//    {
//        out << PREFIX << "<informaltable>\n"
//            << PREFIX << "    <tgroup cols='" << colDataVec.size() << "'>\n";
//
//        for (const auto &colData : colDataVec)
//        {
//            out << PREFIX << "        <colspec colwidth='" << colData.width << "' colname='" << colData.name << "'/>\n";
//        }
//
//        out << PREFIX << "        <thead>\n"
//            << PREFIX << "            <row>\n";
//
//        for (const auto &colData : colDataVec)
//        {
//            out <<   PREFIX << "                <entry align='center'>" << colData.title << "</entry>\n";
//        }
//
//        out << PREFIX << "            </row>\n"
//            << PREFIX << "        </thead>\n"
//            << PREFIX << "        <tbody>\n";
//
//        indent += 3;
//        return boost::bind(&GeneratorBase::endTable, this);
//    }
//
//    void GeneratorBase::endTable()
//    {
//        indent -= 3;
//        out << PREFIX << "        </tbody>\n"
//            << PREFIX << "    </tgroup>\n"
//            << PREFIX << "</informaltable>\n";
//    }
//
//    GeneratorBase::Closer::CloseFun GeneratorBase::startTag(const std::string &tag, const std::string &extra)
//    {
//        out << PREFIX << "<" << tag << (extra.empty() ? std::string() : " " + extra) + ">\n";
//        return boost::bind(&GeneratorBase::endTag, this, tag);
//    }
//
//    void GeneratorBase::endTag(const std::string &tag)
//    {
//        out << PREFIX << "</" << tag << ">\n";
//    }
//
//}}}
