#include "ProcessMemory.hpp"
#include <cstddef>
#include <cstdint>
#include <fmt/core.h>
#include <fstream>
#include <iostream>
#include <locale>
#include <memory>
#include <algorithm>
#include <cstring>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/uio.h>
#include <iconv.h>
#include <limits>
#include <vector>
#include <fmt/format.h>
#include <fmt/xchar.h>
#include <errno.h>
#include <codecvt>

ProcessMemory::ProcessMemory(pid_t pid): pid(pid)
{
    if(pid < 1)
    {
        std::invalid_argument("invalid pid");
    }
};

long ProcessMemory::GetAdressFromBase(long offset)
{
    constexpr long baseAddress = 0x140000000;
    return baseAddress + offset; 
}

std::wstring ProcessMemory::ConvertStringToWstring(const std::string& input)
{
    //codecvt is on it's way out, but I know nothing better
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.from_bytes(input);
}

bool ProcessMemory::DirectRead(size_t address, void* d, size_t sizeToRead) {
    const struct iovec	local = { reinterpret_cast<void*>(d), sizeToRead};
    const struct iovec remote = { reinterpret_cast<void*>(address), sizeToRead};
    constexpr unsigned long oneElement = 1;
	const auto bytesRead = process_vm_readv(pid, &local, oneElement, &remote, oneElement, 0);
	if(bytesRead < 0)
    {
        //critcal error
        int errsv = errno;
        std::string errnoMessage = strerror(errsv);
        std::wcerr << fmt::format(L"Failed read at addr {}. Reason: {}\n", address, ConvertStringToWstring(errnoMessage));
        return false;
    }
    if(static_cast<size_t>(bytesRead) != sizeToRead)
    {
        std::wcerr << fmt::format(L"Partial read at addr {}.Read {} bytes, but wanted {}\n", address, bytesRead, sizeToRead);
		return false;
    }   
	return true;
}
char ProcessMemory::ReadMemoryCharAt(size_t address, const std::vector<size_t>& offsets)
{
    size_t currentAddress = address;
    for(const auto& offset : offsets)
    {
        constexpr ssize_t length = sizeof(char) * 1;
        long tempValue = 0;
        if(!DirectRead(currentAddress, reinterpret_cast<void*>(&tempValue), length))
        {
            throw std::runtime_error("deez char");
        }
        currentAddress = tempValue + offset;
    }
    return currentAddress;
}

int ProcessMemory::ReadMemoryIntAt(size_t address, const std::vector<size_t>& offsets)
{
    size_t currentAddress = address;
    for(const auto& offset : offsets)
    {
        constexpr ssize_t length = sizeof(int) * 1;
        long tempValue = 0;
        if(!DirectRead(currentAddress, reinterpret_cast<void*>(&tempValue), length))
        {
            throw std::runtime_error("deez int");
        }
        currentAddress = tempValue + offset;
    }
    return currentAddress;
}

long ProcessMemory::ReadMemoryLongAt(size_t address, const std::vector<size_t>& offsets)
{
    size_t currentAddress = address;
    for(const auto& offset : offsets)
    {
        constexpr ssize_t length = sizeof(long) * 1;
        long tempValue = 0;
        if(!DirectRead(currentAddress, reinterpret_cast<void*>(&tempValue), length))
        {
            throw std::runtime_error("deez long");
        }
        currentAddress = tempValue + offset;
    }
    return currentAddress;
}

int ProcessMemory::DerefMemory(size_t address, const std::vector<size_t>& offsets)
{
    long ptr = this->ReadMemoryLongAt(address, offsets);
    return this->ReadMemoryIntAt(ptr,{0});
}

bool ProcessMemory::safe_read_utf8(size_t address, size_t length, std::wstring& out) {
    std::vector<char> buf(length, 0);
    if(!this->DirectRead(address, reinterpret_cast<void*>(buf.data()), length))
    {
        return false;
    }
    std::string tempString {buf.data(), length};
    out = this->ConvertStringToWstring(tempString);
    return true;
}

std::wstring ProcessMemory::ReadUtf8String(const size_t addr, const size_t len) {
	std::wstring result;
	if(!safe_read_utf8(addr, len, result))
		throw std::runtime_error("Couldn't find specified address, utf8");
	return result;
}

