#pragma once
#include <string>
#include <sys/types.h>
#include <vector>
#include <cstdint>
#include <ostream>

class ProcessMemory
{
    public:
        explicit ProcessMemory(pid_t pid);
        long GetAdressFromBase(long offset);
        int  DerefMemory(size_t address, const std::vector<size_t>& offsets);
        bool DirectRead(size_t address, void* d, size_t sizeToRead);
        char ReadMemoryCharAt(size_t address, const std::vector<size_t>& offsets);
        int  ReadMemoryIntAt(size_t address, const std::vector<size_t>& offsets);
        long ReadMemoryLongAt(size_t address, const std::vector<size_t>& offsets);
		std::wstring ReadUtf8String(size_t address, size_t len);
    private:
        std::wstring ConvertStringToWstring(const std::string& input);
		bool safe_read_utf8(size_t address, size_t len, std::wstring& out);
        pid_t pid;
};

