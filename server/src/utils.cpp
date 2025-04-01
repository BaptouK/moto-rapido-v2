#include <string>
#include <random>
#include <sstream>
#include <iomanip>
#include <regex>
#include <vector>
#include "../include/utils.h"
#include "../include/player.h"

std::string utils::generate_UUID(const bool serv_or_client) {

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

    std::string const prefix = serv_or_client ? "SRV_" : "USR_";
    return prefix + UUID_str;
}

bool utils::is_UUID(const std::string& UUID) {
    // Regex to match either SRV_ or USR_ prefix followed by UUID pattern
    std::regex const uuid_pattern("(SRV_|USR_)[0-9a-f]{8}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{12}");

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