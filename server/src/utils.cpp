#include <string>
#include <iostream>
#include <random>
#include <sstream>
#include <iomanip>
#include "../include/utils.h"

std::string generate_UUID(bool serv_or_client) {

	std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 15);

    std::stringstream UUID;
    UUID << std::hex;
    for (int i = 0; i < 36; ++i) {
        if (i == 8 || i == 13 || i == 18 || i == 23) {
            UUID << "-";
        } else {
            UUID << dis(gen);
        }
    }
	std::string UUID_str =UUID.str();

    std::string prefix = serv_or_client ? "SRV_" : "USR_";
    return prefix + UUID_str;
}