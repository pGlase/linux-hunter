/*
    This file is part of linux-hunter.

    linux-hunter is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    linux-hunter is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with linux-hunter.  If not, see <https://www.gnu.org/licenses/>.
 * */

#pragma once

/*
 * Taken from https://github.com/sir-wilhelm/SmartHunter/blob/master/SmartHunter/Game/Helpers/MhwHelper.cs
 */

namespace offsets {
	namespace PlayerNameCollection {
        constexpr uint32_t IDLength = 12;
        constexpr uint32_t PlayerNameLength = 32;
        constexpr uint32_t FirstPlayerName = 0x532ED;//0x53305,
        constexpr uint32_t SessionID = FirstPlayerName + 0xF43;
        constexpr uint32_t SessionHostPlayerName = SessionID + 0x3F;
        constexpr uint32_t LobbyID = FirstPlayerName + 0x463;
        constexpr uint32_t LobbyHostPlayerName = LobbyID + 0x29;
        constexpr uint32_t NextLobbyHostName = 0x2F;
	}

	namespace PlayerDamageCollection {
		constexpr uint32_t MaxPlayerCount = 4;
		constexpr uint32_t FirstPlayerPtr = 0x48;
		constexpr uint32_t NextPlayerPtr = 0x58;
		constexpr uint32_t Damage = 0x48;
	}

	namespace Monster {
        constexpr uint32_t	PreviousMonsterOffset = 0x10;
        constexpr uint32_t	NextMonsterOffset = 0x18;
        constexpr uint32_t	MonsterStartOfStructOffset = 0x40;
        constexpr uint32_t	MonsterHealthComponentOffset = 0x7670;
        constexpr uint32_t	MonsterNumIDOffset = 0x12280;
        constexpr uint32_t	MonsterSizeScale = 0x188;
        constexpr uint32_t	MonsterScaleModifier = 0x7730;
	}

	namespace MonsterModel {
		constexpr uint32_t IdLength = 32; // 64?
		constexpr uint32_t IdOffset = 0x179;
	}

	namespace MonsterHealthComponent {
		constexpr uint32_t	MaxHealth = 0x60;
		constexpr uint32_t CurrentHealth = 0x64;
	}
}

