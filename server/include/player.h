#pragma once
#include <string>

class Player{
public:
    Player() = delete;
    Player(std::string new_name);
    ~Player();

    void setName(std::string new_name);
    std::string getName();

    void setID(std::string new_id);
    std::string getID();
private:
    std::string name;
    std::string id;
};
