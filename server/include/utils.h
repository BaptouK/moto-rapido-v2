#pragma once
#include <string>
#include <vector>
#include "../include/player.h"
#include "../include/lobby.h"

namespace utils {
    std::string generate_UUID();

    bool is_UUID(const std::string& UUID);

    bool is_Player(const std::string& UUID, const std::vector<Player*>& players);

    Player* search_Player(const std::string& UUID, const std::vector<Player*>& players);

    Lobby* search_Lobby(const std::string& UUID, const std::vector<Lobby*>& lobbies);


}