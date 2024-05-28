#include "PlayerDataLookup.hpp"
#include "PartyMemberStructure.hpp"
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <vector>
#include "QuestState.hpp"
#include "WeaponId.hpp"

PlayerDataLookup::PlayerDataLookup(ProcessMemory& processMemory) : processMemory(&processMemory)
{
    if(this->processMemory == nullptr)
    {
        throw std::invalid_argument("processMemory is null");
    }
}

std::wstring PlayerDataLookup::GetFormattedPartyMemberString()
{
    std::wstringstream ss;
    const auto partyMembers = this->LoadPartyMembers();
    int slot = 0;
    for(const auto& member : partyMembers)
    {
        std::wstring playerName = this->processMemory->ReadUtf8String(member.Address + 0x49, 32);
	    if((playerName.empty()))
         {
             playerName = L"N/A";
        }
        char weaponId = this->processMemory->ReadMemoryCharAt(member.Address + 0x7C, {0x0});
        ss << "Slot:" << slot << ", Player: " << playerName << ", Weapon: " << GetShortname(static_cast<WeaponId>(weaponId)).c_str() << "(" << static_cast<int>(weaponId) << ")" <<"\n";
        slot++;
    }
    return ss.str();
}

std::vector<PartyMemberStructure> PlayerDataLookup::LoadPartyMembers()
{
    const auto partyInformationPointer = this->LoadPartyInformationPointer();
    if(partyInformationPointer == 0)
    {
        return{};
    }
    constexpr long sessionOffset = 0x051C2478;
    const long sessionDataAddress = this->processMemory->GetAdressFromBase(sessionOffset);
    const std::vector<size_t> sessionPartyOffsets {0x258,0x10,0x6574};
    const int partyCount = this->processMemory->DerefMemory(sessionDataAddress, sessionPartyOffsets);
    std::wcerr << "Found " << partyCount << " players\n";

    return ReadPartyMemberStructure(partyInformationPointer, partyCount);
}

size_t PlayerDataLookup::LoadPartyInformationPointer()
{
    constexpr long questDataOffset = 0x050112F0;
    const long questDataAddress = this->processMemory->GetAdressFromBase(questDataOffset);
    const std::vector<size_t> questDataOffsets{0x54};
    const long questInformation = this->processMemory->ReadMemoryLongAt(questDataAddress, questDataOffsets);
    QuestState state = static_cast<QuestState>(questInformation);

    //we might read garbage unless in quest
    if(IsQuestFinished(state))
    {
        std::wcerr << "quest finished\n";
        return 0;
    }
    constexpr long partyDataOffset = 0x050112F0;
    const long partyAddressInfoPtr = this->processMemory->GetAdressFromBase(partyDataOffset);
    const std::vector<size_t> partyInfoOffsets{0x1AB0};
    const long partyInformationPointer = this->processMemory->ReadMemoryLongAt(partyAddressInfoPtr, partyInfoOffsets);
    if(partyInformationPointer == 0)
    {
        throw std::runtime_error("party pointer is bad");
        return 0;
    }
    return partyInformationPointer;
}

std::vector<PartyMemberStructure> PlayerDataLookup::ReadPartyMemberStructure(long address, int count)
{
    std::vector<PartyMemberStructure> results;
    constexpr uint32_t structSize = sizeof(PartyMemberStructure) * 1;
    for(int i=0; i<count; i++)
    {
        PartyMemberStructure data;
        this->processMemory->DirectRead((address + i*structSize), reinterpret_cast<void*>(&data), structSize);
        results.emplace_back(data);
    }
    return results;
}

