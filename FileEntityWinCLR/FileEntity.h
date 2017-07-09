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

#pragma once

#ifdef FILEENTITY_EXPORTS
#define FILEENTITY_API __declspec(dllexport)
#else
#define FILEENTITY_API __declspec(dllimport)
#endif // FILEENTITY_EXPORTS

#include "stdafx.h"

#include "WCharString.h"

class FileEntity
{
private:

    string directory;

    string fileName;

    int fetchSize;

    ifstream * ifile;

    ofstream * ofile;

    int fileSize;

    vector<char> fileContents;

    bool readPrepared;

    bool writePrepared;

    bool readSuccess;

    bool writeSuccess;

    bool deleteSuccess;

    bool disposed;

    int EvaluateFetchSize();

    int CountFileSize();

    int OptimizedFetchSize();

    void Fetch4();

    void Fetch16();

    void Fetch64();

    void Fetch256();

    void Fetch1024();

public:

    FILEENTITY_API void SetDirectory(string arg);

    FILEENTITY_API string GetDirectory();

    FILEENTITY_API void SetFileName(string arg);

    FILEENTITY_API string GetFileName();

    FILEENTITY_API void SetFetchSize(int arg);

    FILEENTITY_API int GetFetchSize();

    FILEENTITY_API void SetFileContents(vector<char> arg);

    FILEENTITY_API vector<char> GetFileContents();

    FILEENTITY_API bool IsReadPrepared();

    FILEENTITY_API bool IsWritePrepared();

    FILEENTITY_API bool IsReadSuccess();

    FILEENTITY_API bool IsWriteSuccess();

    FILEENTITY_API bool IsDeleteSuccess();

    FILEENTITY_API void ReadPrepare();

    FILEENTITY_API void WritePrepare();

    FILEENTITY_API void ReadFile();

    FILEENTITY_API void WriteFile();

    FILEENTITY_API bool FindFile();

    FILEENTITY_API void DeleteExistingFile();

    FILEENTITY_API FileEntity();

    FILEENTITY_API void Dispose();

    FILEENTITY_API ~FileEntity();
};
