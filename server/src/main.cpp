#include <crow.h>
#include <crow/websocket.h>
#include "../include/lobby.h"
#include "../include/utils.h"
#include "../include/player.h"
#include <mutex>
#include <vector>
#include <thread>
#include <sstream>
#include <iostream>

std::vector <crow::websocket::connection*> connections;
std::vector <Lobby> lobbies;
std::vector <Player*> players;
std::mutex connections_mutex;

void open_handler(crow::websocket::connection& conn) {

    std::lock_guard<std::mutex> guard(connections_mutex);
    connections.push_back(&conn);

    conn.send_text("Bienvenue sur le serveur WebSocket!");
}

void message_handler(crow::websocket::connection& conn, const std::string& message) {

    std::stringstream ss(message);
    std::vector<std::string> tokens;
    std::string item;

    while (std::getline(ss,item, '|')) {
        tokens.push_back(item);
    }

    if (tokens[0] == "newName") {

    }

    if (utils::is_UUID(message)) {
        std::cout << "UUID :" << message << std::endl;
    }
    std::cout << "Message :" << message << std::endl;
    conn.send_text("Message recu :" + message);
}

void close_handler(crow::websocket::connection& conn, const std::string& reason) {
    std::lock_guard<std::mutex> guard(connections_mutex);
    connections.erase(std::remove(connections.begin(), connections.end(), &conn), connections.end());

    std::cout << "Connexion fermée: " << reason << std::endl;
}

// Fonction qui permet d'ajouter l'en-tête CORS à toutes les réponses
void add_cors_headers(crow::response& res) {
    res.add_header("Access-Control-Allow-Origin", "*"); // Permet l'accès depuis n'importe quelle origine
    res.add_header("Access-Control-Allow-Methods", "POST, GET, OPTIONS, PUT"); // Permet les méthodes HTTP requises
    res.add_header("Access-Control-Allow-Headers", "Content-Type"); // Permet l'en-tête Content-Type
}

int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/").methods(crow::HTTPMethod::Post)
    ([](const crow::request& req)
    {
        std::string message = req.body;

        std::cout << "prout : "<< utils::is_UUID("USR_d00adbc3-7b60-5432-f9e9-e9e73fb13878") << std::endl;
        std::cout << "message : " << message <<utils::is_UUID(message) << std::endl;
        if (utils::is_Player(message, players)) {
            // Lui donnez son pseudo, le mettre dans la game ou dans la page de lobby

            crow::response res{200, "Vous êtes déjà connecté"};
            add_cors_headers(res);
            return res;
        }
        else {
            // Créer un joueur, lui donnez son uuid et qu'il le mette dans le localstorage
            Player* p = new Player{};  // Allocate on heap so it persists
            p->setID(utils::generate_UUID(false));

            players.push_back(p);

            std::cout << "New player create :" << p->getID() << std::endl;

            crow::json::wvalue json_response;
            json_response["playerUUID"] = p->getID();

            crow::response res{200, "application/json", json_response.dump()};
            add_cors_headers(res);
            return res;
        }
    });


    CROW_WEBSOCKET_ROUTE(app,"/")
    .onopen([&](crow::websocket::connection& conn){
            open_handler(conn);
            })
    .onclose([&](crow::websocket::connection& conn, const std::string& reason, uint16_t){
            close_handler(conn, reason);
            })
    .onmessage([&](crow::websocket::connection& conn, const std::string& data, const bool is_binary){
                if (is_binary)
                    message_handler(conn, data);
                else
                    message_handler(conn, data);
            });


    app.port(18080).multithreaded().run();

}

