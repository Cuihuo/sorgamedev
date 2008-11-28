#pragma once

class FileReader
{
public:
    FileReader(std::wstring fileName);
    ~FileReader();

    void* GetFileData(int &size);

private:
    std::wstring m_FileName;
};
