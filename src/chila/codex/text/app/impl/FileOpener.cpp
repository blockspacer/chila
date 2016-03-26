/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "FileOpener.hpp"
#include <boost/thread.hpp>
#include <boost/make_shared.hpp>

#include <chila/lib/misc/util.hpp>
#include <fstream>

#define MODULE_NAME FileOpener

#include "macros.fgen.hpp"

MY_NSP_START
{


    FileOpener::FileOpener(module_args_ex) :
        connection::FileOpener::CProvider(instanceName),
        exFTypeMap(exFTypeMap),
        createFileIdFun(createFileIdFun)
    {
        connector.bindActions(*this);
    }

    std::string FileOpener::getFileType(const bfs::path &fileName) const
    {
        std::string type;
        auto ext = fileName.extension().string();

        if (ext.size())
        {
            auto it = exFTypeMap.find(ext.substr(1));
            if (it != exFTypeMap.end())
                type = it->second;
        }

        return type;
    }

    void FileOpener::MOD_ACTION_SIG(openFile)
    {
        auto it = fileIdMap.find(fileName);

        if (it != fileIdMap.end())
        {
            execute_event(fileAlreadyOpened)(it->second);
            return;
        }

        auto ret = fileIdMap.insert({fileName, createFileIdFun()});
        ct_assert(ret.second);

        auto fileId = ret.first->second;
        ct_assert(fileIterMap.insert({fileId, ret.first}).second);

        std::ifstream str;
        str.exceptions(std::ios::badbit | std::ios::failbit);

        try
        {
            str.open(fileName.c_str());
        }
        catch (const std::ios::failure &ex)
        {
            call_ev_fatal(std::string("error opening file: ") + ex.what());
        }

        execute_event(openingNewFile)(fileId, fileName, getFileType(fileName));

        char buff[65535];
        while (auto size = str.readsome(buff, sizeof(buff)))
        {
            execute_event(textFound)(fileId, BufferRange(buff, buff + size));
        }

        execute_event(fileOpened)(fileId);
    }

    void FileOpener::saveFile(const bfs::path &fileName, const BufferRange &textBuffer)
    {
        std::ofstream str;
        str.exceptions(std::ios::badbit | std::ios::failbit);

        str.open(fileName.string());
        str.write(textBuffer.begin(), textBuffer.size());
    }

    void FileOpener::MOD_ACTION_SIG(saveFile_current) try
    {
        auto it = fileIterMap.find(fileId);
        if (it != fileIterMap.end())
        {
            auto &fileName = it->second->first;
            saveFile(fileName, textBuffer);

            execute_event(fileSaved)(fileId, getFileType(fileName));
        }
        else
        {
            execute_event(savingUnnamedFile)(fileId);
        }
    }
    catch (const std::ios::failure &ex)
    {
        call_ev_fatal(ex.what());
    }

    void FileOpener::MOD_ACTION_SIG(saveFile_as) try
    {
        auto it = fileIterMap.find(fileId);

        if (it != fileIterMap.end())
            fileIdMap.erase(it->second);

        auto ret = fileIdMap.insert({fileName, fileId});
        ct_assert(ret.second);

        if (it != fileIterMap.end())
            it->second = ret.first;
        else
            ct_assert(fileIterMap.insert({fileId, ret.first}).second);

        saveFile(fileName, textBuffer);

        execute_event(fileSaved)(fileId, getFileType(fileName));
    }
    catch (const std::ios::failure &ex)
    {
        call_ev_fatal(ex.what());
    }

    void FileOpener::MOD_ACTION_SIG(fileSelected)
    {
        auto it = fileIterMap.find(fileId);
        if (it == fileIterMap.end())
            return;

        auto &fileName = it->second->first;

        execute_event(fileSelected)(fileId, fileName);
    }

    void FileOpener::MOD_ACTION_SIG(fileClosed)
    {
        auto it = fileIterMap.find(fileId);
        if (it != fileIterMap.end())
        {
            fileIdMap.erase(it->second);
            fileIterMap.erase(it);
        }
    }

    connection::FileOpener::CProviderUPtr connection::FileOpener::create(module_args_ex)
    {
        return std::make_unique<impl::FileOpener>(module_pass_args_ex);
    }
}
MY_NSP_END
