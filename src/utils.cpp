#include "utils.h"
#include <string>
#include <fstream>
#include <filesystem>
#include <iostream>

pid_t utils::find_mhw_pid(void) {
    const std::filesystem::path procDir{"/proc"};
    if(!std::filesystem::exists(procDir))
    {
		throw std::runtime_error("Can't find MH:W pid - '/proc' doesn't seem to exist");
    }
    for (auto const& dir_entry : std::filesystem::directory_iterator{procDir})
    {
        if(!dir_entry.is_directory())
        {
            continue;
        }
        const auto folderName = dir_entry.path().stem().string();
        //PID folders only contain digits - checking the first char is enough
        if(!std::isdigit(folderName.front()))
        {
            continue;
        }
        const std::filesystem::path processDir = dir_entry.path() / "cmdline";
        if(!std::filesystem::exists(processDir))
        {
            continue;
        }
        std::ifstream file(processDir);
		std::string	line;
		if(!std::getline(file, line))
        {
            continue;
        }
        const auto startPos = line.find("\\MonsterHunterWorld.exe");
        if(startPos == std::string::npos)
        {
            //not our process
            continue;
        }
        return std::atoi(folderName.c_str());
    }
    throw std::runtime_error("Can't find MH:W pid");
}
