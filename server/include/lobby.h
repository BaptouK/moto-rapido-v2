#pragma once
#include "../include/player.h"
#include <string>
#include <vector>


class Lobby{
public:
    Lobby() = delete;
    Lobby(Player* owner);
    ~Lobby();

    bool matches(const std::string& id) const;


    void setLobby_owner();
    void setLobby_owner(Player* player);
    Player getLobby_owner() const;

    std::string getID() const;

    void addPlayer(Player* player);
    void removePlayer(Player* player) ;
    std::vector<Player*> getPlayers() const ;
    void clearPlayers();
    int getPlayerCount() const;

    int getMaxPlayers() const ;

    enum class GameStatus { Waiting, Ongoing, Completed };

    std::string statusToString(GameStatus status) const;
    GameStatus getStatus() const;

private:
    Player lobby_owner;
    std::string UUID;
    std::vector <Player*> players;
    int max_players;
    GameStatus status;
};
