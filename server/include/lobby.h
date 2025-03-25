#pragma once
#include "../include/player.h"
#include <string>
#include <vector>


class Lobby{
public:
    Lobby() = delete;
    Lobby(Player& owner);
    ~Lobby();

    void setLobby_owner();
    void setLobby_owner(Player& player);
    Player getLobby_owner();

private:
    Player lobby_owner;
    std::string UUID;
    std::vector <Player> players;

};
