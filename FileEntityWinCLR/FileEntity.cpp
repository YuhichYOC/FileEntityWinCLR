/*
*
* FileEntity.cpp
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

#include "FileEntity.h"

void FileEntity::SetDirectory(string arg)
{
    directory.assign(arg);
}

string FileEntity::GetDirectory()
{
    return directory;
}

void FileEntity::SetFileName(string arg)
{
    fileName.assign(arg);
}

string FileEntity::GetFileName()
{
    return fileName;
}

void FileEntity::SetFetchSize(int arg)
{
    fetchSize = arg;
}

int FileEntity::GetFetchSize()
{
    return fetchSize;
}

void FileEntity::SetFileContents(vector<char> arg)
{
    fileContents = arg;
}

vector<char> FileEntity::GetFileContents()
{
    return fileContents;
}

bool FileEntity::IsReadPrepared()
{
    return readPrepared;
}

bool FileEntity::IsWritePrepared()
{
    return writePrepared;
}

bool FileEntity::IsReadSuccess()
{
    return readSuccess;
}

bool FileEntity::IsWriteSuccess()
{
    return writeSuccess;
}

bool FileEntity::IsDeleteSuccess()
{
    return deleteSuccess;
}

int FileEntity::EvaluateFetchSize()
{
    fileSize = CountFileSize();
    if (fetchSize <= 0) {
        return OptimizedFetchSize();
    }
    else if (fetchSize <= 4) {
        return 4;
    }
    else if (fetchSize <= 16) {
        return 16;
    }
    else if (fetchSize <= 64) {
        return 64;
    }
    else if (fetchSize <= 256) {
        return 256;
    }
    else {
        return 1024;
    }
}

int FileEntity::CountFileSize()
{
    ifile->seekg(0, istream::end);
    streamoff endPos = ifile->tellg();
    ifile->seekg(0, istream::beg);
    streamoff startPos = ifile->tellg();

    return (int)(endPos - startPos);
}

int FileEntity::OptimizedFetchSize()
{
    int mod4 = fileSize % 4;
    int mod16 = fileSize % 16;
    int mod64 = fileSize % 64;
    int mod256 = fileSize % 256;
    int mod1024 = fileSize % 1024;

    int div4 = (int)ceil((float)fileSize / 4);
    int div16 = (int)ceil((float)fileSize / 16);
    int div64 = (int)ceil((float)fileSize / 64);
    int div256 = (int)ceil((float)fileSize / 256);
    int div1024 = (int)ceil((float)fileSize / 1024);

    float score4 = (float)mod4 + (float)(div4 * div4) - (float)(0.25);
    float score16 = (float)mod16 + (float)(div16 * div16) - (float)(0.0625);
    float score64 = (float)mod64 + (float)(div64 * div64) - (float)(0.015625);
    float score256 = (float)mod256 + (float)(div256 * div256) - (float)(0.00390625);
    float score1024 = (float)mod1024 + (float)(div1024 * div1024) - (float)(0.0009765625);

    vector<float> scores;
    scores.push_back(score4);
    scores.push_back(score16);
    scores.push_back(score64);
    scores.push_back(score256);
    scores.push_back(score1024);

    sort(scores.begin(), scores.end());
    if (scores.at(0) == score4) {
        return 4;
    }
    else if (scores.at(0) == score16) {
        return 16;
    }
    else if (scores.at(0) == score64) {
        return 64;
    }
    else if (scores.at(0) == score256) {
        return 256;
    }
    else {
        return 1024;
    }
}

void FileEntity::Fetch4()
{
    char readBuffer[4];
    while (!ifile->eof()) {
        memset(readBuffer, 0, 4);
        ifile->read(readBuffer, 4);
        int iLoopCount = 4;
        if (iLoopCount > fileSize) {
            iLoopCount = fileSize;
        }
        for (int i = 0; i < iLoopCount; i++) {
            fileContents.push_back(readBuffer[i]);
        }
        fileSize -= 4;
    }
}

void FileEntity::Fetch16()
{
    char readBuffer[16];
    while (!ifile->eof()) {
        memset(readBuffer, 0, 16);
        ifile->read(readBuffer, 16);
        int iLoopCount = 16;
        if (iLoopCount > fileSize) {
            iLoopCount = fileSize;
        }
        for (int i = 0; i < iLoopCount; i++) {
            fileContents.push_back(readBuffer[i]);
        }
        fileSize -= 16;
    }
}

void FileEntity::Fetch64()
{
    char readBuffer[64];
    while (!ifile->eof()) {
        memset(readBuffer, 0, 64);
        ifile->read(readBuffer, 64);
        int iLoopCount = 64;
        if (iLoopCount > fileSize) {
            iLoopCount = fileSize;
        }
        for (int i = 0; i < iLoopCount; i++) {
            fileContents.push_back(readBuffer[i]);
        }
        fileSize -= 64;
    }
}

void FileEntity::Fetch256()
{
    char readBuffer[256];
    while (!ifile->eof()) {
        memset(readBuffer, 0, 256);
        ifile->read(readBuffer, 256);
        int iLoopCount = 256;
        if (iLoopCount > fileSize) {
            iLoopCount = fileSize;
        }
        for (int i = 0; i < iLoopCount; i++) {
            fileContents.push_back(readBuffer[i]);
        }
        fileSize -= 256;
    }
}

void FileEntity::Fetch1024()
{
    char readBuffer[1024];
    while (!ifile->eof()) {
        memset(readBuffer, 0, 1024);
        ifile->read(readBuffer, 1024);
        int iLoopCount = 1024;
        if (iLoopCount > fileSize) {
            iLoopCount = fileSize;
        }
        for (int i = 0; i < iLoopCount; i++) {
            fileContents.push_back(readBuffer[i]);
        }
        fileSize -= 1024;
    }
}

void FileEntity::ReadPrepare()
{
    if (writePrepared) {
        readPrepared = false;
        return;
    }

    string fullPath;
    fullPath.append(directory);
    fullPath.append("\\");
    fullPath.append(fileName);

    ifile = new ifstream(fullPath, ios::in | ios::binary);

    if (ifile) {
        readPrepared = true;
    }
    else {
        readPrepared = false;
    }
}

void FileEntity::WritePrepare()
{
    if (readPrepared) {
        writePrepared = false;
        return;
    }

    string fullPath;
    fullPath.append(directory);
    fullPath.append("\\");
    fullPath.append(fileName);

    ofile = new ofstream(fullPath, ios::out | ios::binary);

    if (ofile) {
        writePrepared = true;
    }
    else {
        writePrepared = false;
    }
}

void FileEntity::ReadFile()
{
    readSuccess = false;

    switch (EvaluateFetchSize())
    {
    case 4:
        Fetch4();
        break;
    case 16:
        Fetch16();
        break;
    case 64:
        Fetch64();
        break;
    case 256:
        Fetch256();
        break;
    default:
        Fetch1024();
        break;
    }
    ifile->close();

    readSuccess = true;
}

void FileEntity::WriteFile()
{
    writeSuccess = false;

    int iWriteCount = (int)fileContents.size();
    for (int i = 0; i < iWriteCount; i++) {
        ofile->write(&fileContents.at(i), 1);
    }
    ofile->close();

    writeSuccess = true;
}

bool FileEntity::FindFile()
{
    WCharString path;
    unique_ptr<wchar_t> filePath = move(path.Value(directory).Append("\\").Append(fileName).ToWChar());
    if (PathFileExists((LPCWSTR)filePath.get())) {
        return true;
    }
    else {
        return false;
    }
}

void FileEntity::DeleteExistingFile()
{
    deleteSuccess = false;

    WCharString path;
    unique_ptr<wchar_t> filePath = move(path.Value(directory).Append("\\").Append(fileName).ToWChar());
    if (FindFile()) {
        int ret = DeleteFile((LPCWSTR)filePath.get());
        if (ret != 0) {
            deleteSuccess = true;
        }
    }
}

FileEntity::FileEntity()
{
    fetchSize = -1;
    ifile = nullptr;
    ofile = nullptr;
    disposed = false;
}

void FileEntity::Dispose()
{
    if (readPrepared) {
        ifile->close();
        delete ifile;
    }
    if (writePrepared) {
        ofile->close();
        delete ofile;
    }
    disposed = true;
}

FileEntity::~FileEntity()
{
    if (!disposed) {
        Dispose();
    }
}