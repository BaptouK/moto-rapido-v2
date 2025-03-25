#include <crow.h>
#include <crow/websocket.h>
#include "../include/lobby.h"
#include "../include/utils.h"
#include <mutex>
#include <vector>
#include <thread>

std::vector <crow::websocket::connection*> connections;
std::mutex connections_mutex;

void open_handler(crow::websocket::connection& conn) {

    std::lock_guard<std::mutex> guard(connections_mutex);
    connections.push_back(&conn);


    std::cout << "Connexion ouverte :" << generate_UUID(false) << std::endl;
    std::cout << "Connexion ouverte :" << generate_UUID(true)<< std::endl;

    conn.send_text("Bienvenue sur le serveur WebSocket!");
}

void message_handler(crow::websocket::connection& conn, const std::string& message) {
    std::cout << "Message " << message << std::endl;
    conn.send_text("Message recu :" + message);
}

void close_handler(crow::websocket::connection& conn, const std::string& reason) {
    std::lock_guard<std::mutex> guard(connections_mutex);
    connections.erase(std::remove(connections.begin(), connections.end(), &conn), connections.end());

    std::cout << "Connexion fermée: " << reason << std::endl;
}

int main() {
    crow::SimpleApp app;

    CROW_WEBSOCKET_ROUTE(app,"/")
    .onopen([&](crow::websocket::connection& conn){
            open_handler(conn);
            })
    .onclose([&](crow::websocket::connection& conn, const std::string& reason, uint16_t){
            close_handler(conn, reason);
            })
    .onmessage([&](crow::websocket::connection& conn, const std::string& data, bool is_binary){
                if (is_binary)
                    message_handler(conn, data);
                else
                    message_handler(conn, data);
            });


    app.port(18080).multithreaded().run();

}

