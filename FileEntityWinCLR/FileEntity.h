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

    WCharString Append(char * arg);

    WCharString Append(wchar_t * arg);

    WCharString Append(string arg);

    WCharString Append(string * arg);

    WCharString Append(const char * arg);

    WCharString Append(const wchar_t * arg);

    WCharString Append(const string * arg);

    WCharString Value(char * arg);

    WCharString Value(wchar_t * arg);

    WCharString Value(string arg);

    WCharString Value(string * arg);

    WCharString Value(const char * arg);

    WCharString Value(const wchar_t * arg);

    WCharString Value(const string * arg);

    unique_ptr<wchar_t> ToWChar();

    string ToString();

    bool WChar_tStartsWith(wchar_t * arg1eval, string arg2test);

    void SysErrWinAPI();

    WCharString();

    ~WCharString();
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

    void SetDirectory(string arg);

    string GetDirectory();

    void SetFileName(string arg);

    string GetFileName();

    void SetFileContents(vector<char> * arg);

    void SetFileContentsClone(vector<char> * arg);

    vector<char> * GetFileContents();

    bool FindFile();

    void ReadPrepare();

    void ReadPrepareText();

    bool IsReadPrepared();

    void WritePrepare();

    bool IsWritePrepared();

    void ReadFile();

    void ReadFileText();

    bool IsReadSuccess();

    void WriteFile();

    bool IsWriteSuccess();

    void DeleteExistingFile();

    bool IsDeleteSuccess();

    FileEntity();

    void Dispose();

    ~FileEntity();
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

    void SetDirectory(string arg);

    string GetDirectoryName();

    string GetFullPath();

    bool RootDirectoryFound();

    void Describe();

    void CreateRootDirectory(string arg);

    void SetDirectories(vector<DirectoryEntity *> * arg);

    vector<DirectoryEntity *> * GetDirectories();

    void AddDirectory(DirectoryEntity * arg);

    void SetFiles(vector<FileEntity *> * arg);

    vector<FileEntity *> * GetFiles();

    void AddFile(FileEntity * arg);

    bool IsCreateSuccess();

    bool IsDeleteSuccess();

    void CreateDir();

    void CreateDir(string arg);

    bool FindDir();

    bool FindDir(string arg);

    void DeleteExistingDir();

    void DeleteExistingDir(string arg);

    void DirCopy(string arg, bool rollback);

    DirectoryEntity();

    void Dispose();

    ~DirectoryEntity();
};