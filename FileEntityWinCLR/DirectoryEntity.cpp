/*
*
* DirectoryEntity.cpp
*
* Copyright 2016 Yuichi Yoshii
*     吉井雄一 @ 吉井産業  you.65535.kir@gmail.com
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
*/

#include "stdafx.h"

#include "DirectoryEntity.h"

DirectoryEntity * DirectoryEntity::Describe(LPWIN32_FIND_DATA parentFileInfo, string parentPath)
{
    WCharString path;

    DirectoryEntity * addDir = new DirectoryEntity();
    addDir->SetDirectory(path.Value(parentPath).Append("\\").Append(parentFileInfo->cFileName).ToString());

    HANDLE ret;
    LPWIN32_FIND_DATA fileInfo = new WIN32_FIND_DATA();

    unique_ptr<wchar_t> findPath = move(path.Value(parentPath).Append("\\").Append(parentFileInfo->cFileName).Append("\\*.*").ToWChar());
    ret = FindFirstFile((LPCWSTR)findPath.get(), fileInfo);
    if (ret != INVALID_HANDLE_VALUE) {
        do {
            if (fileInfo->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                if (path.WChar_tStartsWith(fileInfo->cFileName, string(".\0")) || path.WChar_tStartsWith(fileInfo->cFileName, string(".."))) {
                    continue;
                }
                addDir->AddDirectory(Describe(fileInfo, addDir->GetFullPath()));
            }
            else {
                FileEntity * addFile = new FileEntity();
                addFile->SetFileName(path.Value(fileInfo->cFileName).ToString());
                addDir->AddFile(addFile);
            }
        } while (FindNextFile(ret, fileInfo));
    }

    delete fileInfo;
    return addDir;
}

void DirectoryEntity::DirCopy(DirectoryEntity * arg1subDir, string arg2path)
{
    arg2path.append("\\");
    arg2path.append(arg1subDir->GetDirectoryName());

    WCharString path;
    unique_ptr<wchar_t> dirPath = move(path.Value(arg2path).ToWChar());
    int ret = CreateDirectory((LPCWSTR)dirPath.get(), nullptr);

    if (ret != 0) {
        for (size_t i = 0; i < arg1subDir->GetDirectories().size(); i++) {
            if (!copySuccess) {
                return;
            }
            DirCopy(arg1subDir->GetDirectories().at(i), arg2path);
        }
        for (size_t j = 0; j < arg1subDir->GetFiles().size(); j++) {
            if (!copySuccess) {
                return;
            }
            string filePathFrom = arg1subDir->GetFullPath();
            filePathFrom.append("\\");
            filePathFrom.append(arg1subDir->GetFiles().at(j)->GetFileName());
            string filePathTo = arg2path;
            filePathTo.append("\\");
            filePathTo.append(arg1subDir->GetFiles().at(j)->GetFileName());
            unique_ptr<wchar_t> from = move(path.Value(filePathFrom).ToWChar());
            unique_ptr<wchar_t> to = move(path.Value(filePathTo).ToWChar());
            int ret = CopyFile((LPCWSTR)from.get(), (LPCWSTR)to.get(), true);
            if (ret == 0) {
                copySuccess = false;
            }
        }
    }
    else {
        copySuccess = false;
    }
}

void DirectoryEntity::SetDirectory(string arg)
{
    rootDirectoryFound = false;
    if (FindDir(arg)) {
        fullPath.assign(arg);
        directoryName = arg.substr(arg.find_last_of("\\") + 1, arg.length() - (arg.find_last_of("\\") + 1));
        rootDirectoryFound = true;
    }
}

string DirectoryEntity::GetDirectoryName()
{
    return directoryName;
}

string DirectoryEntity::GetFullPath()
{
    return fullPath;
}

bool DirectoryEntity::RootDirectoryFound()
{
    return rootDirectoryFound;
}

void DirectoryEntity::Describe()
{
    if (!rootDirectoryFound) {
        return;
    }

    HANDLE ret;
    LPWIN32_FIND_DATA fileInfo = new WIN32_FIND_DATA();

    WCharString path;
    unique_ptr<wchar_t> findPath = move(path.Value(fullPath).Append("\\*.*").ToWChar());
    ret = FindFirstFile((LPCWSTR)findPath.get(), fileInfo);
    if (ret != INVALID_HANDLE_VALUE) {
        do {
            if (fileInfo->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                if (path.WChar_tStartsWith(fileInfo->cFileName, string(".\0")) || path.WChar_tStartsWith(fileInfo->cFileName, string(".."))) {
                    continue;
                }
                subDirectories.push_back(Describe(fileInfo, fullPath));
            }
            else {
                FileEntity * addFile = new FileEntity();
                addFile->SetFileName(path.Value(fileInfo->cFileName).ToString());
                files.push_back(addFile);
            }
        } while (FindNextFile(ret, fileInfo));
    }

    delete fileInfo;
}

void DirectoryEntity::CreateRootDirectory(string arg)
{
    createSuccess = false;

    if (!FindDir(arg)) {
        WCharString path;
        unique_ptr<wchar_t> dirPath = move(path.Value(arg).ToWChar());
        int ret = CreateDirectory((LPCWSTR)dirPath.get(), nullptr);
        if (ret != 0) {
            createSuccess = true;
            fullPath.assign(arg);
            directoryName = arg.substr(arg.find_last_of("\\") + 1, arg.length() - (arg.find_last_of("\\") + 1));
        }
    }
}

void DirectoryEntity::SetDirectories(vector<DirectoryEntity *> arg)
{
    subDirectories = arg;
}

vector<DirectoryEntity *> DirectoryEntity::GetDirectories()
{
    return subDirectories;
}

void DirectoryEntity::AddDirectory(DirectoryEntity * arg)
{
    subDirectories.push_back(arg);
}

void DirectoryEntity::SetFiles(vector<FileEntity *> arg)
{
    files = arg;
}

vector<FileEntity *> DirectoryEntity::GetFiles()
{
    return files;
}

void DirectoryEntity::AddFile(FileEntity * arg)
{
    files.push_back(arg);
}

bool DirectoryEntity::IsCreateSuccess()
{
    return createSuccess;
}

bool DirectoryEntity::IsDeleteSuccess()
{
    return deleteSuccess;
}

void DirectoryEntity::CreateDir()
{
    createSuccess = false;

    if (!FindDir()) {
        WCharString path;
        unique_ptr<wchar_t> dirPath = move(path.Value(fullPath).ToWChar());
        int ret = CreateDirectory((LPCWSTR)dirPath.get(), nullptr);
        if (ret != 0) {
            createSuccess = true;
        }
    }
}

void DirectoryEntity::CreateDir(string arg)
{
    createSuccess = false;

    if (!FindDir()) {
        WCharString path;
        unique_ptr<wchar_t> dirPath = move(path.Value(fullPath).Append("\\").Append(arg).ToWChar());
        int ret = CreateDirectory((LPCWSTR)dirPath.get(), nullptr);
        if (ret != 0) {
            createSuccess = true;
            DirectoryEntity * addDir = new DirectoryEntity();
            addDir->SetDirectory(arg);
            subDirectories.push_back(addDir);
        }
    }
}

bool DirectoryEntity::FindDir()
{
    WCharString path;
    unique_ptr<wchar_t> dirPath = move(path.Value(fullPath).ToWChar());
    if (PathFileExists((LPCWSTR)dirPath.get())) {
        return true;
    }
    else {
        return false;
    }
}

bool DirectoryEntity::FindDir(string arg)
{
    if (fullPath.empty()) {
        WCharString path;
        unique_ptr<wchar_t> dirPath = move(path.Value(arg).ToWChar());
        if (PathFileExists((LPCWSTR)dirPath.get())) {
            return true;
        }
    }
    else {
        WCharString path;
        unique_ptr<wchar_t> dirPath = move(path.Value(fullPath).Append("\\").Append(arg).ToWChar());
        if (PathFileExists((LPCWSTR)dirPath.get())) {
            return true;
        }
    }
    return false;
}

void DirectoryEntity::DeleteExistingDir()
{
    deleteSuccess = false;

    if (FindDir()) {
        WCharString path;
        unique_ptr<wchar_t> dirPath = move(path.Value(fullPath).ToWChar());
        int ret = RemoveDirectory((LPCWSTR)dirPath.get());
        if (ret != 0) {
            deleteSuccess = true;
        }
    }
}

void DirectoryEntity::DeleteExistingDir(string arg)
{
    deleteSuccess = false;

    if (FindDir(arg)) {
        WCharString path;
        unique_ptr<wchar_t> dirPath = move(path.Value(fullPath).Append("\\").Append(arg).ToWChar());
        int ret = RemoveDirectory((LPCWSTR)dirPath.get());
        if (ret != 0) {
            deleteSuccess = true;
        }
    }
}

void DirectoryEntity::DirCopy(string arg, bool rollback)
{
    copySuccess = true;

    useCopyRollback = rollback;
    dirCopyTo = arg;

    if (FindDir(arg)) {
        copySuccess = false;
        return;
    }
    WCharString path;
    unique_ptr<wchar_t> createDirPath = move(path.Value(arg).ToWChar());
    int ret = CreateDirectory((LPCWSTR)createDirPath.get(), nullptr);
    if (ret != 0) {
        DirCopy(this, arg);
    }
    else {
        copySuccess = false;
    }
}

DirectoryEntity::DirectoryEntity()
{
    disposed = false;
}

void DirectoryEntity::Dispose()
{
    for (size_t i = 0; i < subDirectories.size(); i++) {
        delete subDirectories.at(i);
    }
    for (size_t j = 0; j < files.size(); j++) {
        delete files.at(j);
    }
    disposed = true;
}

DirectoryEntity::~DirectoryEntity()
{
    if (!disposed) {
        Dispose();
    }
}