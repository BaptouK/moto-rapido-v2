#include "crow.h"
//#include "crow_all.h"

int main() {
    crow::SimpleApp app; //define your crow application

    //define your endpoint at the root directory
    CROW_ROUTE(app, "/")([]() {
        return "Hello world";
    });

    CROW_WEBSOCKET_ROUTE(app, "/ws")
            .onopen([&](crow::websocket::connection &conn) {
                CROW_LOG_INFO << "WebSocket connection opened";
            })
            .onclose([&](crow::websocket::connection &conn, const std::string &reason, uint16_t) {
                CROW_LOG_INFO << "WebSocket connection closed: " << reason;
            })
            .onmessage([&](crow::websocket::connection &conn, const std::string &data, bool is_binary) {
                if (is_binary) {
                    CROW_LOG_INFO << "Received binary data of size: " << data.size();
                    conn.send_binary(data); // Echo de la même donnée
                } else {
                    CROW_LOG_INFO << "Received text data: " << data;
                }
            });

    //set the port, set the app to run on multiple threads, and run the app
    app.port(8080).multithreaded().run();
}
