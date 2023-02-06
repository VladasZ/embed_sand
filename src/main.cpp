
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>


#include <iostream>
using namespace std;

#define WIFI_SSID "Fergel"
#define WIFI_PASS "******"

ESP8266WebServer server(80);

extern "C" {
    int _write(int fd, char *ptr, int len) {
        (void) fd;
        return Serial.write(ptr, len);
    }
}

void handle_test() {
    cout << "Received test request" << endl;
    server.send(200, "text/html", "Test request received");
}

void connect_to_wifi() {

    cout << "Starting Wifi" << endl;

    WiFi.begin(WIFI_SSID, WIFI_PASS);

    cout << "Wifi began" << endl;

    while (WiFi.status() != WL_CONNECTED) {
        cout << "connecting ..." << endl;
        delay(100);
    }

    cout << "connected!" << endl;

    cout << "local ip: " <<  Serial.println(WiFi.localIP()) << endl;
}

void setup_server() {
    cout << "Server setup" << endl;

    server.on("/test", HTTP_GET, handle_test); // when the server receives a request with /data/ in the string then run the handleSentVar function
    server.begin();
}

void setup() {
    // put your setup code here, to run once:
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600); // open the serial port at 9600 bps:

    connect_to_wifi();
    setup_server();

    cout << "Starting app" << endl;
}

void loop() {
    server.handleClient();
}
