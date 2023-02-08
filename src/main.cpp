
#include "wifi.hpp"
#include "remote.hpp"
#include "web_server.hpp"

#include <iostream>
#include <Arduino.h>


using namespace std;


extern "C" {
    int _write(int fd, char *ptr, int len) {
        (void) fd;
        return Serial.write(ptr, len);
    }
}

void setup() {

    Serial.begin(115200);

    cout << endl;
    cout << "Starting setup" << endl;

    pinMode(LED_BUILTIN, OUTPUT);

    connect_wifi();
    WebServer::init();
    Remote::init();

    cout << "Starting app" << endl;
}

void loop() {
    WebServer::handle();
    // Remote::read_input();
}
