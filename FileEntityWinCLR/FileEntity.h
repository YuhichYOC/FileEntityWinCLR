/*
*
* FileEntity.h
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

#ifdef FILEENTITY_EXPORTS
#define FILEENTITY_API __declspec(dllexport)
#else
#define FILEENTITY_API __declspec(dllimport)
#endif // FILEENTITY_EXPORTS

#pragma once

#include "stdafx.h" // ✝

class WCharString
{
private:

    string value;

    void Assign(char * arg);

    void Assign(wchar_t * arg);

    void Assign(string arg);

    void Assign(string * arg);

    void Assign(const char * arg);

    void Assign(const wchar_t * arg);

    void Assign(const string * arg);

public:

    FILEENTITY_API WCharString __stdcall Append(char * arg);

    FILEENTITY_API WCharString __stdcall Append(wchar_t * arg);

    FILEENTITY_API WCharString __stdcall Append(string arg);

    FILEENTITY_API WCharString __stdcall Append(string * arg);

    FILEENTITY_API WCharString __stdcall Append(const char * arg);

    FILEENTITY_API WCharString __stdcall Append(const wchar_t * arg);

    FILEENTITY_API WCharString __stdcall Append(const string * arg);

    FILEENTITY_API WCharString __stdcall Value(char * arg);

    FILEENTITY_API WCharString __stdcall Value(wchar_t * arg);

    FILEENTITY_API WCharString __stdcall Value(string arg);

    FILEENTITY_API WCharString __stdcall Value(string * arg);

    FILEENTITY_API WCharString __stdcall Value(const char * arg);

    FILEENTITY_API WCharString __stdcall Value(const wchar_t * arg);

    FILEENTITY_API WCharString __stdcall Value(const string * arg);

    FILEENTITY_API unique_ptr<wchar_t> __stdcall ToWChar();

    FILEENTITY_API string __stdcall ToString();

    FILEENTITY_API bool __stdcall WChar_tStartsWith(wchar_t * arg1eval, string arg2test);

    FILEENTITY_API void __stdcall SysErrWinAPI();

    FILEENTITY_API __stdcall WCharString();

    FILEENTITY_API __stdcall ~WCharString();
};

class FileEntity
{
private:

    string directory;

    string fileName;

    ifstream * ifile;

    ofstream * ofile;

    int fileSize;

    vector<char> * fileContents;

    vector<string> * file;

    bool readPrepared;

    bool writePrepared;

    bool readSuccess;

    bool writeSuccess;

    bool deleteSuccess;

    bool disposed;

public:

    FILEENTITY_API void __stdcall SetDirectory(string arg);

    FILEENTITY_API string __stdcall GetDirectory();

    FILEENTITY_API void __stdcall SetFileName(string arg);

    FILEENTITY_API string __stdcall GetFileName();

    FILEENTITY_API void __stdcall SetFileContents(vector<char> * arg);

    FILEENTITY_API void __stdcall SetFileContentsClone(vector<char> * arg);

    FILEENTITY_API vector<char> * __stdcall GetFileContents();

    FILEENTITY_API vector<string> * __stdcall GetFile();

    FILEENTITY_API bool __stdcall FindFile();

    FILEENTITY_API void __stdcall ReadPrepare();

    FILEENTITY_API void __stdcall ReadPrepareText();

    FILEENTITY_API bool __stdcall IsReadPrepared();

    FILEENTITY_API void __stdcall WritePrepare();

    FILEENTITY_API bool __stdcall IsWritePrepared();

    FILEENTITY_API void __stdcall ReadFile();

    FILEENTITY_API void __stdcall ReadFileText();

    FILEENTITY_API bool __stdcall IsReadSuccess();

    FILEENTITY_API void __stdcall WriteFile();

    FILEENTITY_API bool __stdcall IsWriteSuccess();

    FILEENTITY_API void __stdcall DeleteExistingFile();

    FILEENTITY_API bool __stdcall IsDeleteSuccess();

    FILEENTITY_API __stdcall FileEntity();

    FILEENTITY_API void __stdcall Dispose();

    FILEENTITY_API __stdcall ~FileEntity();
};

class DirectoryEntity
{
private:

    string directoryName;

    string fullPath;

    vector<DirectoryEntity *> * subDirectories;

    vector<FileEntity *> * files;

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

    FILEENTITY_API void __stdcall SetDirectory(string arg);

    FILEENTITY_API string __stdcall GetDirectoryName();

    FILEENTITY_API string __stdcall GetFullPath();

    FILEENTITY_API bool __stdcall RootDirectoryFound();

    FILEENTITY_API void __stdcall Describe();

    FILEENTITY_API void __stdcall CreateRootDirectory(string arg);

    FILEENTITY_API void __stdcall SetDirectories(vector<DirectoryEntity *> * arg);

    FILEENTITY_API vector<DirectoryEntity *> * __stdcall GetDirectories();

    FILEENTITY_API void __stdcall AddDirectory(DirectoryEntity * arg);

    FILEENTITY_API void __stdcall SetFiles(vector<FileEntity *> * arg);

    FILEENTITY_API vector<FileEntity *> * __stdcall GetFiles();

    FILEENTITY_API void __stdcall AddFile(FileEntity * arg);

    FILEENTITY_API bool __stdcall IsCreateSuccess();

    FILEENTITY_API bool __stdcall IsDeleteSuccess();

    FILEENTITY_API void __stdcall CreateDir();

    FILEENTITY_API void __stdcall CreateDir(string arg);

    FILEENTITY_API bool __stdcall FindDir();

    FILEENTITY_API bool __stdcall FindDir(string arg);

    FILEENTITY_API void __stdcall DeleteExistingDir();

    FILEENTITY_API void __stdcall DeleteExistingDir(string arg);

    FILEENTITY_API void __stdcall DirCopy(string arg, bool rollback);

    FILEENTITY_API __stdcall DirectoryEntity();

    FILEENTITY_API void __stdcall Dispose();

    FILEENTITY_API __stdcall ~DirectoryEntity();
};