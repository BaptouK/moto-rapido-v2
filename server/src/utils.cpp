#include <string>
#include <random>
#include <sstream>
#include <iomanip>
#include <regex>
#include <vector>
#include "../include/utils.h"

#include "../include/lobby.h"
#include "../include/player.h"

std::string utils::generate_UUID() {

	std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 15);

    std::stringstream UUID;
    UUID << std::hex;
    for (int i = 0; i < 36; ++i) {
        if (i == 8 || i == 13 || i == 18 || i == 23) {
            UUID << "-";
        } else {
            UUID << dis(gen);
        }
    }
	std::string const UUID_str =UUID.str();

    return UUID_str;
}

bool utils::is_UUID(const std::string& UUID) {
    // Regex to match either SRV_ or USR_ prefix followed by UUID pattern
    std::regex const uuid_pattern("[0-9a-f]{8}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{12}");

    // Check if the string matches the pattern
    return std::regex_match(UUID, uuid_pattern);
}

bool utils::is_Player(const std::string& UUID , const std::vector<Player*>& players) {

    // Check if the uuid is in the game or the players lists
    for (const auto* player : players) {
        if (player->getID() == UUID) {
            return true;
        }
    }

    return false;
}

Player* utils::search_Player(const std::string& UUID, const std::vector<Player*>& players) {
    for (Player* player : players) {
        if (player->getID() == UUID) {
            return player;
        }
    }
    return nullptr;
}

Lobby* utils::search_Lobby(const std::string& UUID, const std::vector<Lobby*>& lobbies) {
    for (Lobby* lobby : lobbies) {
        if (lobby->getID() == UUID) {
            return lobby;
        }
    }
    return nullptr;
}

