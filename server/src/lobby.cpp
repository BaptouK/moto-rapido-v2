#include "../include/lobby.h"
#include "../include/utils.h"
#include "../include/player.h"
#include <iostream>
#include <string>


Lobby::Lobby(Player& owner) : lobby_owner{owner}{
    /* créer/rejoidnre une page avec certains
     parametre pour diférencier les games créer*/
    this->UUID = utils::generate_UUID(true); // Créer un uuid de type server
};
Lobby::~Lobby(){
    // Envoyé a tout les clients qu'il faut suppr les UUID des navs
    // Et supprimer le uuid serv  dans la liste globale
    std :: cout << "Lobby fermé" << std::endl;
};

void Lobby::setLobby_owner(){
    // Attendre 1 ou 2 min pour voir si le owner revient
    this->setLobby_owner(players[0]);
};
void Lobby::setLobby_owner(Player& player){
    this->lobby_owner = player;
};

Player Lobby::getLobby_owner(){
    return this->lobby_owner;
};
