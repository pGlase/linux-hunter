#pragma once
#include <string>
#include <vector>
#include "PartyMemberStructure.hpp"
#include "ProcessMemory.hpp"

class PlayerDataLookup
{
    public:
    explicit PlayerDataLookup(ProcessMemory& processMemory);
    std::wstring GetFormattedPartyMemberString();
    size_t LoadPartyInformationPointer();
    std::vector<PartyMemberStructure> ReadPartyMemberStructure(long address, int count);
    std::vector<PartyMemberStructure> LoadPartyMembers();
    private:
    ProcessMemory* processMemory = nullptr;
};

