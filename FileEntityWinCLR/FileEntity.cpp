#include "stdafx.h" // ✝

#include "FileEntity.h"

void WCharString::Assign(char * arg)
{
    value.assign(arg);
}

void WCharString::Assign(wchar_t * arg)
{
    wstring castedArg = arg;
    size_t argSize = castedArg.length() + 1;
    size_t cnvSize = 0;
    unique_ptr<char> mbArg(new char[argSize]);
    wcstombs_s(&cnvSize, mbArg.get(), argSize, arg, _TRUNCATE);
    value.assign(mbArg.get());
}

void WCharString::Assign(string arg)
{
    value.assign(arg);
}

void WCharString::Assign(string * arg)
{
    value.assign(*arg);
}

void WCharString::Assign(const char * arg)
{
    value.assign(arg);
}

void WCharString::Assign(const wchar_t * arg)
{
    wstring castedArg = arg;
    size_t argSize = castedArg.length() + 1;
    size_t cnvSize = 0;
    unique_ptr<char> mbArg(new char[argSize]);
    wcstombs_s(&cnvSize, mbArg.get(), argSize, arg, _TRUNCATE);
    value.assign(mbArg.get());
}

void WCharString::Assign(const string * arg)
{
    value.assign(*arg);
}

WCharString WCharString::Append(char * arg)
{
    value.append(arg);
    return *this;
}

WCharString WCharString::Append(wchar_t * arg)
{
    wstring castedArg = arg;
    size_t argSize = castedArg.length() + 1;
    size_t cnvSize = 0;
    unique_ptr<char> mbArg(new char[argSize]);
    wcstombs_s(&cnvSize, mbArg.get(), argSize, arg, _TRUNCATE);
    value.append(mbArg.get());
    return *this;
}

WCharString WCharString::Append(string arg)
{
    value.append(arg);
    return *this;
}

WCharString WCharString::Append(string * arg)
{
    value.append(*arg);
    return *this;
}

WCharString WCharString::Append(const char * arg)
{
    value.append(arg);
    return *this;
}

WCharString WCharString::Append(const wchar_t * arg)
{
    wstring castedArg = arg;
    size_t argSize = castedArg.length() + 1;
    size_t cnvSize = 0;
    unique_ptr<char> mbArg(new char[argSize]);
    wcstombs_s(&cnvSize, mbArg.get(), argSize, arg, _TRUNCATE);
    value.append(mbArg.get());
    return *this;
}

WCharString WCharString::Append(const string * arg)
{
    value.append(*arg);
    return *this;
}

WCharString WCharString::Value(char * arg)
{
    Assign(arg);
    return *this;
}

WCharString WCharString::Value(wchar_t * arg)
{
    Assign(arg);
    return *this;
}

WCharString WCharString::Value(string arg)
{
    Assign(arg);
    return *this;
}

WCharString WCharString::Value(string * arg)
{
    Assign(arg);
    return *this;
}

WCharString WCharString::Value(const char * arg)
{
    Assign(arg);
    return *this;
}

WCharString WCharString::Value(const wchar_t * arg)
{
    Assign(arg);
    return *this;
}

WCharString WCharString::Value(const string * arg)
{
    Assign(arg);
    return *this;
}

unique_ptr<wchar_t> WCharString::ToWChar()
{
    size_t retSize = value.length() + 1;
    size_t cnvSize = 0;
    unique_ptr<wchar_t> ret(new wchar_t[retSize]);
    mbstowcs_s(&cnvSize, ret.get(), retSize, value.c_str(), _TRUNCATE);
    return ret;
}

string WCharString::ToString()
{
    return value;
}

bool WCharString::WChar_tStartsWith(wchar_t * arg1eval, string arg2test)
{
    wstring castedArg1 = arg1eval;
    if (castedArg1.length() < arg2test.length()) {
        return false;
    }
    for (size_t i = 0; i < arg2test.length(); i++) {
        if (castedArg1.at(i) != arg2test.at(i)) {
            return false;
        }
    }
    return true;
}

void WCharString::SysErrWinAPI()
{
    LPVOID msg = NULL;
    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
        NULL,
        GetLastError(),
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&msg,
        0,
        NULL);
    string out = this->Value((const wchar_t *)msg).ToString();
    if (out.substr(out.length() - 2, 2) == string("\r\n")) {
        out = out.substr(0, out.length() - 2);
    }
    cout << out << "\n";
}

WCharString::WCharString()
{
}

WCharString::~WCharString()
{
}

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

void FileEntity::SetFileContents(vector<char> * arg)
{
    fileContents = arg;
}

void FileEntity::SetFileContentsClone(vector<char> * arg)
{
    fileContents = new vector<char>();
    for (size_t i = 0; i < arg->size(); i++) {
        fileContents->push_back(arg->at(i));
    }
}

vector<char> * FileEntity::GetFileContents()
{
    return fileContents;
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

void FileEntity::ReadPrepare()
{
    if (writePrepared) {
        readPrepared = false;
        return;
    }
    if (readPrepared) {
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

void FileEntity::ReadPrepareText()
{
    if (writePrepared) {
        readPrepared = false;
        return;
    }
    if (readPrepared) {
        return;
    }

    string fullPath;
    fullPath.append(directory);
    fullPath.append("\\");
    fullPath.append(fileName);

    ifile = new ifstream(fullPath, ios::in);

    if (ifile) {
        readPrepared = true;
    }
    else {
        readPrepared = false;
    }
}

bool FileEntity::IsReadPrepared()
{
    return readPrepared;
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

bool FileEntity::IsWritePrepared()
{
    return writePrepared;
}

void FileEntity::ReadFile()
{
    readSuccess = false;

    ifile->seekg(0, istream::end);
    streamoff endPos = ifile->tellg();
    ifile->seekg(0, istream::beg);
    streamoff startPos = ifile->tellg();
    int fileSize = (int)(endPos - startPos);

    fileContents = new vector<char>(fileSize);
    unique_ptr<char> readBuffer(new char[fileSize]);
    ifile->read(readBuffer.get(), fileSize);

    for (int i = 0; i < fileSize; i++) {
        fileContents->at(i) = readBuffer.get()[i];
    }

    ifile->close();

    readSuccess = true;
}

void FileEntity::ReadFileText()
{
    readSuccess = false;

    file = new vector<string>();

    while (!ifile->eof()) {
        string line;
        getline(*ifile, line);
        file->push_back(line);
    }

    ifile->close();

    readSuccess = true;
}

bool FileEntity::IsReadSuccess()
{
    return readSuccess;
}

void FileEntity::WriteFile()
{
    writeSuccess = false;

    int iWriteCount = (int)fileContents->size();
    for (int i = 0; i < iWriteCount; i++) {
        ofile->write(&fileContents->at(i), 1);
    }
    ofile->close();

    writeSuccess = true;
}

bool FileEntity::IsWriteSuccess()
{
    return writeSuccess;
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

bool FileEntity::IsDeleteSuccess()
{
    return deleteSuccess;
}

FileEntity::FileEntity()
{
    ifile = nullptr;
    ofile = nullptr;
    fileContents = nullptr;
    disposed = false;
}

void FileEntity::Dispose()
{
    if (readPrepared) {
        ifile->close();
    }
    if (writePrepared) {
        ofile->close();
    }
    delete fileContents;
    disposed = true;
}

FileEntity::~FileEntity()
{
    if (!disposed) {
        Dispose();
    }
}

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
        for (size_t i = 0; i < arg1subDir->GetDirectories()->size(); i++) {
            if (!copySuccess) {
                return;
            }
            DirCopy(arg1subDir->GetDirectories()->at(i), arg2path);
        }
        for (size_t j = 0; j < arg1subDir->GetFiles()->size(); j++) {
            if (!copySuccess) {
                return;
            }
            string filePathFrom = arg1subDir->GetFullPath();
            filePathFrom.append("\\");
            filePathFrom.append(arg1subDir->GetFiles()->at(j)->GetFileName());
            string filePathTo = arg2path;
            filePathTo.append("\\");
            filePathTo.append(arg1subDir->GetFiles()->at(j)->GetFileName());
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
                subDirectories->push_back(Describe(fileInfo, fullPath));
            }
            else {
                FileEntity * addFile = new FileEntity();
                addFile->SetFileName(path.Value(fileInfo->cFileName).ToString());
                files->push_back(addFile);
            }
        } while (FindNextFile(ret, fileInfo));
    }

    delete fileInfo;
}

void DirectoryEntity::SetDirectories(vector<DirectoryEntity *> * arg)
{
    subDirectories = arg;
}

vector<DirectoryEntity *> * DirectoryEntity::GetDirectories()
{
    return subDirectories;
}

void DirectoryEntity::AddDirectory(DirectoryEntity * arg)
{
    subDirectories->push_back(arg);
}

void DirectoryEntity::SetFiles(vector<FileEntity *> * arg)
{
    files = arg;
}

vector<FileEntity *> * DirectoryEntity::GetFiles()
{
    return files;
}

void DirectoryEntity::AddFile(FileEntity * arg)
{
    files->push_back(arg);
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
            subDirectories->push_back(addDir);
        }
    }
}

bool DirectoryEntity::IsCreateSuccess()
{
    return createSuccess;
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

bool DirectoryEntity::IsDeleteSuccess()
{
    return deleteSuccess;
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
    subDirectories = new vector<DirectoryEntity *>();
    files = new vector<FileEntity *>();
    disposed = false;
}

void DirectoryEntity::Dispose()
{
    for (size_t i = 0; i < subDirectories->size(); i++) {
        delete subDirectories->at(i);
    }
    delete subDirectories;
    for (size_t j = 0; j < files->size(); j++) {
        delete files->at(j);
    }
    delete files;
    disposed = true;
}

DirectoryEntity::~DirectoryEntity()
{
    if (!disposed) {
        Dispose();
    }
}