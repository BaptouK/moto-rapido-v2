#include "../include/player.h"
#include "../include/utils.h"
#include <iostream>
#include <string>

Player::Player(){
    this->id = utils::generate_UUID();
};

Player::~Player() {
    //Suprimer les UUID Coté clients et coté serveur
};

bool Player::matches(const std::string& id) const {
    return id == this->id;
}

void const Player::setName(std::string new_name){
    this->name = new_name;
};

std::string Player::getName(){
    return this->name;
};

void const Player::setID(std::string new_id){
    this->id = new_id;
};

std::string Player::getID() const{
    return this->id;
}