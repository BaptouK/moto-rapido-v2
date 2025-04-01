#pragma once
#include <string>

class Player{
public:
    Player();
    ~Player();

    void const setName(std::string new_name);
    std::string getName();

    void setID(std::string new_id);
    std::string getID() const;
private:
    std::string name;
    std::string id;
};
