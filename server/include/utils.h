#pragma once
#include <string>
#include <vector>
#include "../include/player.h"

namespace utils {
    std::string generate_UUID(bool serv_or_client);

    bool is_UUID(const std::string& UUID);

    bool is_Player(const std::string& UUID, const std::vector<Player*>& players);
}