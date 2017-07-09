/*
*
* DirectoryEntity.h
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

#pragma once

#ifdef FILEENTITY_EXPORTS
#define FILEENTITY_API __declspec(dllexport)
#else
#define FILEENTITY_API __declspec(dllimport)
#endif // FILEENTITY_EXPORTS

#include "stdafx.h"

#include "WCharString.h"

#include "FileEntity.h"

#pragma comment(lib, "ShLwApi.Lib")

class DirectoryEntity
{
private:

    string directoryName;

    string fullPath;

    vector<DirectoryEntity *> subDirectories;

    vector<FileEntity *> files;

    bool rootDirectoryFound;

    bool createSuccess;

    bool deleteSuccess;

    string dirCopyTo;

    bool useCopyRollback;

    bool copySuccess;

    bool disposed;

    DirectoryEntity * Describe(LPWIN32_FIND_DATA fileInfo, string parentPath);

    void DirCopy(DirectoryEntity * arg1subDir, string arg2path);

public:

    FILEENTITY_API void SetDirectory(string arg);

    FILEENTITY_API string GetDirectoryName();

    FILEENTITY_API string GetFullPath();

    FILEENTITY_API bool RootDirectoryFound();

    FILEENTITY_API void Describe();

    FILEENTITY_API void CreateRootDirectory(string arg);

    FILEENTITY_API void SetDirectories(vector<DirectoryEntity *> arg);

    FILEENTITY_API vector<DirectoryEntity *> GetDirectories();

    FILEENTITY_API void AddDirectory(DirectoryEntity * arg);

    FILEENTITY_API void SetFiles(vector<FileEntity *> arg);

    FILEENTITY_API vector<FileEntity *> GetFiles();

    FILEENTITY_API void AddFile(FileEntity * arg);

    FILEENTITY_API bool IsCreateSuccess();

    FILEENTITY_API bool IsDeleteSuccess();

    FILEENTITY_API void CreateDir();

    FILEENTITY_API void CreateDir(string arg);

    FILEENTITY_API bool FindDir();

    FILEENTITY_API bool FindDir(string arg);

    FILEENTITY_API void DeleteExistingDir();

    FILEENTITY_API void DeleteExistingDir(string arg);

    FILEENTITY_API void DirCopy(string arg, bool rollback);

    FILEENTITY_API DirectoryEntity();

    FILEENTITY_API void Dispose();

    FILEENTITY_API ~DirectoryEntity();
};