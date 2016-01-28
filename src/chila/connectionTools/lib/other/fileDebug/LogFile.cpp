/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "LogFile.hpp"
#include <boost/foreach.hpp>
#include <chila/lib/misc/SinkInserter.hpp>
#include <chila/lib/misc/exceptions.hpp>
#include <boost/filesystem.hpp>
#include <chila/lib/misc/ThreadPool.hpp>
#include <chila/lib/misc/util.hpp>

#define SHOW          CHILA_LIB_MISC__SHOW
#define THREAD_NAME_SIZE 10

#include "macros.fgen.hpp"

MY_NSP_START
{
    struct LogFile::Indent
    {
        LogFile &logFile;
        const unsigned value;

        Indent(LogFile &logFile) : logFile(logFile), value(getNextValue())
        {
        }

        unsigned getNextValue()
        {
            auto ret = logFile.indent.get();
            if (!ret)
            {
                ret = new unsigned(0);
                logFile.indent.reset(ret);
            }

            return ++*ret;
        }

        ~Indent()
        {

            auto ptr = logFile.indent.get();
            --*ptr;
        }
    };

    LogFile::LogFile(const boost::filesystem::path &path, unsigned tNameMaxSize, unsigned maxOldFiles, unsigned maxFileSizeKB, bool append) :
        path(path),
        tNameMaxSize(tNameMaxSize),
        maxOldFiles(maxOldFiles),
        maxFileSizeKB(maxFileSizeKB),
        pid(::getpid()),
        append(append)
    {
        if (!boost::filesystem::exists(path.parent_path()))
            BOOST_THROW_EXCEPTION(chila::lib::misc::InvalidPath("does not exists") <<
                    chila::lib::misc::ExceptionInfo::FilePath(path));

        if (!boost::filesystem::is_directory(path.parent_path()))
            BOOST_THROW_EXCEPTION(chila::lib::misc::InvalidPath("is not a directory") <<
                    chila::lib::misc::ExceptionInfo::FilePath(path));

        my_assert(maxOldFiles > 1);

        file.exceptions(std::ios::badbit | std::ios::failbit);

        openNewFile();
    }

    void LogFile::write(const std::string &text, const Function &fun)
    {
        const std::string *tName = chila::lib::misc::ThreadPool::getThreadNamePtr();
        const std::string &threadName = tName ? *tName : std::string("unknown");

        LogFile::Indent indent(*this);
        WritePrefix prefix(pid, threadName, indent.value, tNameMaxSize);

        FileLock lock(fileMutex);
        file << prefix << "---> " << text << std::endl;

        if (fun)
        {
            lock.unlock();
            fun();
        }
    }

    void LogFile::writeFunEx(const Function &fun, const ContFun &contFun)
    {
        const std::string *tName = chila::lib::misc::ThreadPool::getThreadNamePtr();
        const std::string &threadName = tName ? *tName : std::string("unknown");

        LogFile::Indent indent(*this);
        WritePrefix prefix(pid, threadName, indent.value, tNameMaxSize);

        FileLock lock(fileMutex);
        contFun(file, prefix);

        if (!fun)
        {
            file << prefix << "  |---> (no function)" << std::endl;
            checkFile();
        }
        else
        {
            checkFile();

            lock.unlock();
            fun();
        }
    }

    void LogFile::writeFunction(const std::string &name, const ArgMap &args, bool showArguments,
        const std::string &comments, const Function &fun)
    {
        const std::string *tName = chila::lib::misc::ThreadPool::getThreadNamePtr();
        const std::string &threadName = tName ? *tName : std::string("unknown");

        LogFile::Indent indent(*this);
        WritePrefix prefix(pid, threadName, indent.value, tNameMaxSize);

        FileLock lock(fileMutex);
        file << prefix << "---> " << name;

        if (!comments.empty()) file << " (" << comments << ")";

        file << std::endl;

        if (showArguments)
        {
            for (const auto &vt : args)
            {
                file << prefix << "  |--- " << vt.first << ": [" << vt.second << "]" << std::endl;
            }
        }

        if (!fun)
        {
            file << prefix << "  |---> (no function)" << std::endl;
            checkFile();
        }
        else
        {
            checkFile();

            lock.unlock();
            fun();
        }
    }

    void LogFile::checkFile()
    {
        if (file.tellp() > maxFileSizeKB * 1024)
        {
            file << "\n--------------------------------------------------------------------------------- creating new file "
                    "---------------------------------------------------------------------------------" << std::endl;

            closeFile();
            removeLastFiles();
            openNewFile();
        }
    }

    void LogFile::removeLastFiles()
    {
        boost::filesystem::directory_iterator it(path.parent_path()), end;

        std::set<boost::filesystem::path> files;

        for (; it != end; ++it)
        {
            auto filePath = it->path();

            if (filePath.stem().stem() == "debug")
                my_assert(files.insert(filePath).second);
        }

        if (files.size() > maxOldFiles)
        {
            unsigned delCount = files.size() - maxOldFiles;
            for (unsigned i = 0; i < delCount; ++i)
            {
                auto begin = files.begin();
                boost::filesystem::remove(*begin);
                files.erase(begin);
            }
        }
    }

    void LogFile::openNewFile()
    {
        file.open(path.c_str(), append ? std::ios::app : std::ios::trunc);
    }

    void LogFile::closeFile()
    {
        std::stringstream str;
        str << chila::lib::misc::dateTimeInserter(boost::posix_time::second_clock::local_time());

        auto pathToRename = path;
        pathToRename.replace_extension(str.str() + path.extension().string());

        file.close();

        boost::filesystem::rename(path, pathToRename);
    }

}
MY_NSP_END

