#include <crow.h>
#include <crow/websocket.h>
#include "../include/lobby.h"
#include "../include/utils.h"
#include "../include/player.h"
#include "../template/findObject.tpp"
#include <mutex>
#include <vector>
#include <thread>
#include <sstream>
#include <iostream>
#include <array>

std::vector <crow::websocket::connection*> connections;
std::vector <Lobby*> lobbies;
std::vector <Player*> players;
std::mutex connections_mutex;

// Handler pour les connexions WebSocket
void open_handler(crow::websocket::connection& conn) {
    std::lock_guard<std::mutex> guard(connections_mutex);
    connections.push_back(&conn);
    conn.send_text("Bienvenue sur le serveur WebSocket!");
}

// Handler pour les messages WebSocket
void message_handler(crow::websocket::connection& conn, const std::string& message) {
    std::stringstream ss(message);
    std::vector<std::string> tokens;
    std::string item;

    while (std::getline(ss, item, '|')) {
        tokens.push_back(item);
    }

    if (tokens[0] == "newName") {
        // Logique pour "newName"
    }

    if (utils::is_UUID(message)) {
        std::cout << "UUID :" << message << std::endl;
    }
    std::cout << "Message :" << message << std::endl;
    conn.send_text("Message recu :" + message);
}

// Handler pour la fermeture de connexion WebSocket
void close_handler(crow::websocket::connection& conn, const std::string& reason) {
    std::lock_guard<std::mutex> guard(connections_mutex);
    connections.erase(std::remove(connections.begin(), connections.end(), &conn), connections.end());
    std::cout << "Connexion fermée: " << reason << std::endl;
}

// Fonction qui permet d'ajouter l'en-tête CORS à toutes les réponses
void add_cors_headers(crow::response& res) {
    res.add_header("Access-Control-Allow-Origin", "*");
    res.add_header("Access-Control-Allow-Methods", "POST, GET, OPTIONS, PUT");
    res.add_header("Access-Control-Allow-Headers", "Content-Type, Authorization, Accept");
}

int main() {
    crow::SimpleApp app;

    // Route pour gérer les requêtes OPTIONS pour CORS (pré-vol)
    CROW_ROUTE(app, "/").methods("OPTIONS"_method)([](const crow::request& req) {
        std::cout << "Requête de pré-vol CORS" << std::endl;
        crow::response res{200};
        add_cors_headers(res); // Ajoute les en-têtes CORS pour la pré-vol
        return res;
    });

    // Route pour gérer les requêtes POST, par exemple, pour créer un joueur
    CROW_ROUTE(app, "/").methods(crow::HTTPMethod::POST)
    ([](const crow::request& req) {
        std::string message = req.body;

        std::cout << "Message reçu: " << message << std::endl;
        if (utils::is_Player(message, players)) {
            crow::response res{200, "Vous êtes déjà connecté"};
            add_cors_headers(res);
            return res;
        }
        else {
            // Créer un joueur et lui attribuer un UUID
            auto* p = new Player{};
            p->setID(utils::generate_UUID());
            players.push_back(p);

            std::cout << "New player created: " << p->getID() << std::endl;

            crow::json::wvalue json_response;
            json_response["playerUUID"] = p->getID();

            crow::response res{201, "application/json", json_response.dump()};
            add_cors_headers(res);


            return res;
        }
    });

    // Route pour modifier le pseudo d'un joueur
    CROW_ROUTE(app, "/setPseudo")
    .methods(crow::HTTPMethod::POST)
    ([](const crow::request& req) {

        crow::json::rvalue body = crow::json::load(req.body);

        std::string UUID = body["UUID"].s();
        std::string pseudo = body["pseudo"].s();

        std::cout << "UUID reçu : " << UUID << std::endl;
        std::cout << "Pseudo reçu : " << pseudo << std::endl;

        if  ( !utils::is_UUID(UUID) || !utils::is_Player(UUID, players) )    {
            crow::response res{400, "application/json", "{\"error\": \"UUID invalide\"}"};
            add_cors_headers(res);
            return res;
        }

        // Mettre à jour le pseudo du joueur
        //utils::search_Player(UUID, players)->setName(pseudo);
        findObject(UUID, players)->setName(pseudo);

        // Réponse JSON
        crow::json::wvalue response;
        response["message"] = "Pseudo mis à jour";
        response["UUID"] = UUID;
        response["pseudo"] = pseudo;

        crow::response res{200,"application/json", response.dump()};
        add_cors_headers(res);
        return res;
    });

    // Route pour modifier le pseudo d'un joueur
    CROW_ROUTE(app, "/games")
    .methods(crow::HTTPMethod::POST)
    ([](const crow::request& req) {

        crow::json::rvalue body = crow::json::load(req.body);

        std::string UUID = body["playerUUID"].s();

        if (!utils::is_UUID(UUID)) {
            crow::response res{409, "la game n'a pas été créée"};
            add_cors_headers(res);
            return res;
        }

        Lobby* lobby {};
        //Créer une nouvelle partie
        //auto p {utils::search_Player(UUID, players)};
        auto p {findObject(UUID, players)};

        lobby = new Lobby{p};
        lobbies.push_back(lobby);
        std::cout << "New game created: " << lobby->getLobby_owner().getID() << std::endl;

        crow::json::wvalue response;
        response["GameUUID"] = lobby->getID();

        crow::response res{200,"application/json", response.dump()};
        add_cors_headers(res);
        return res;
    });

    CROW_ROUTE(app, "/games")
        .methods(crow::HTTPMethod::GET)
        ([](const crow::request& req) {

            std::vector<crow::json::wvalue> game_list;

            for (auto& lobby : lobbies) {
                crow::json::wvalue gameJson;

                gameJson["id"] = lobby->getID();
                gameJson["currentPlayers"] = lobby->getPlayerCount();
                gameJson["maxPlayers"] = lobby->getMaxPlayers();  // Assuming getMaxPlayers() is correct
                gameJson["status"] = lobby->statusToString(lobby->getStatus());

                game_list.push_back(gameJson);
            }

            crow::json::wvalue result;
            result["data"] = crow::json::wvalue(game_list);

            crow::response res{200, "application/json", result.dump()};

            add_cors_headers(res);

            return res;
        });

    CROW_ROUTE(app, "/games/<string>/player/<string>")  // Paramètres de l'ID de la game et du joueur dans l'URL
        .methods(crow::HTTPMethod::Delete)
        ([](const crow::request& req, crow::response& res, const std::string& game, const std::string& player) {

            // Récupération des paramètres gameId et playerId à partir de l'URL
            std::string gameId = game;
            std::string playerId = player;

            //Lobby* game = utils::search_Lobby(gameId, lobbies);
            Lobby* game = findObject(gameId, lobbies);


            if (game==nullptr ) {
                crow::json::wvalue result;
                result["error"] = "La game n'a pas été trouvée";

                crow::response res{404, "application/json", result.dump()};
                add_cors_headers(res);
                return res;
            }

            if (game->getLobby_owner().getID()!=playerId) {
                crow::json::wvalue result;
                result["error"] = "Le joueur n'est pas autorisé à supprimer cette game (pas propriétaire).";

                crow::response res{403, "application/json", result.dump()};
                add_cors_headers(res);
                return res;
            }

            crow::response res{204};
            add_cors_headers(res);
            return res;
        });

    // Route WebSocket
    CROW_WEBSOCKET_ROUTE(app, "/")
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

    // Lancement de l'application sur le port 18080
    app.port(18080).multithreaded().run();
}
