#include "../include/player.h"
#include "../include/utils.h"
#include <iostream>
#include <string>

Player::Player(std::string new_name) : name{new_name}{
    this->id = generate_UUID(false);
};

Player::~Player(){};

void Player::setName(std::string new_name){
    this->name = new_name;
};

std::string Player::getName(){
    return this->name;
};

void Player::setID(std::string new_id){
    this->id = new_id;
};

std::string Player::getID(){
    return this->id;
}