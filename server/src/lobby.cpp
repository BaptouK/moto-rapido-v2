#include "../include/lobby.h"
#include "../include/utils.h"
#include "../include/player.h"
#include <iostream>
#include <string>


Lobby::Lobby(Player* owner) : lobby_owner{*owner}{
    this->UUID = utils::generate_UUID();
    this->max_players = 10;
    this->status = GameStatus::Waiting;
    std::cout << "Une game a été créée avec l'UUID :" << this->UUID << std::endl;
};
Lobby::~Lobby(){
    // Envoyé a tout les clients qu'il faut suppr les UUID des navs
    // Et supprimer le uuid serv  dans la liste globale
    std :: cout << "Lobby fermé" << std::endl;
};

bool Player::matches(const std::string& id) const {
    return id == this->id;
}

void Lobby::setLobby_owner(){
    // Attendre 1 ou 2 min pour voir si le owner revient
    this->setLobby_owner(players[0]);
};
void Lobby::setLobby_owner(Player* player){
    this->lobby_owner = *player;
};

Player Lobby::getLobby_owner() const{
    return this->lobby_owner;
};

std::string Lobby::getID() const {
    return this->UUID;
};

void Lobby::addPlayer(Player* player) {
    players.push_back(player);
}

void Lobby::removePlayer(Player* player) {
    for (auto it = players.begin(); it != players.end(); ++it) {
        if (*it == player) {
            players.erase(it);
            break;
        }
    }
}

std::vector<Player*> Lobby::getPlayers() const {
    return players;
}

void Lobby::clearPlayers() {
    players.clear();
}
int Lobby::getPlayerCount() const {
    return players.size();
}

int Lobby::getMaxPlayers() const {
    return max_players;
}


std::string Lobby::statusToString(GameStatus status) const {
    switch (status) {
        case GameStatus::Waiting:   return "waiting";
        case GameStatus::Ongoing:   return "ongoing";
        case GameStatus::Completed: return "completed";
        default: return "unknown";
    }
}

Lobby::GameStatus Lobby::getStatus() const {
    return status;
}

