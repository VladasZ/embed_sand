
#include <ESP8266WebServer.h>

#include "web_server.hpp"
#include "remote.hpp"

#include <iostream>

using namespace std;


ESP8266WebServer server(80);

void handle_test() {
    cout << "Received test request" << endl;
    server.send(200, "text/html", "Test request received");
}

void handle_blink() {
    static bool on = true;
    digitalWrite(LED_BUILTIN, on);
    on = !on;
    string stat = on ? "on" : "off";
    string message = "The led is - " + stat;
    server.send(200, "text/html", message.c_str());
}

void handle_power() {
    Remote::power();
    server.send(200, "text/html", "Power on/off");
}

void handle_up() {
    Remote::volume_up();
    server.send(200, "text/html", "Volume up");
}

void handle_down() {
    Remote::volume_down();
    server.send(200, "text/html", "Volume down");
}

void handle_identify() {
    server.send(200, "text/html", "OK");
}

void WebServer::init() {

    cout << "Server init" << endl;

    server.on("/test", HTTP_GET, handle_test); // when the server receives a request with /data/ in the string then run the handleSentVar function
    server.on("/blink", HTTP_GET, handle_blink); // when the server receives a request with /data/ in the string then run the handleSentVar function

    server.on("/power", HTTP_GET, handle_power); // when the server receives a request with /data/ in the string then run the handleSentVar function
    server.on("/up", HTTP_GET, handle_up); // when the server receives a request with /data/ in the string then run the handleSentVar function
    server.on("/down", HTTP_GET, handle_down); // when the server receives a request with /data/ in the string then run the handleSentVar function

    server.on("/identify_remote_board", HTTP_GET, handle_identify); // when the server receives a request with /data/ in the string then run the handleSentVar function

    server.begin();
}

void WebServer::handle() {
    server.handleClient();
}