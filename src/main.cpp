#include <magic_enum.hpp>

#include <Arduino.h>
#include <IRremote.hpp>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include <iostream>

#include "data.hpp"

using namespace std;

#define WIFI_SSID "Fergel"
#define WIFI_PASS "******"

ESP8266WebServer server(80);

BlinkData blink_data = BlinkData(D0);

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

void handle_blink() {
    static bool on = true;
    digitalWrite(LED_BUILTIN, on);
    on = !on;
    string stat = on ? "on" : "off";
    string message = "The led is - " + stat;
    server.send(200, "text/html", message.c_str());
}

void handle_blink_data() {
    blink_data = BlinkData(D0);
    blink_data.start_reading();
    server.send(200, "text/html", blink_data.to_string().c_str());
}

void handle_power() {
    IrSender.sendNEC(0xE710, 0x46, 1);
    server.send(200, "text/html", "Power on/off");
}

void handle_up() {
    IrSender.sendNEC(0xE710, 0x6, 1);
    server.send(200, "text/html", "Volume up");
}

void handle_down() {
    IrSender.sendNEC(0xE710, 0x47, 1);
    server.send(200, "text/html", "Volume down");
}

void connect_to_wifi() {

    cout << "Starting Wifi" << endl;

    WiFi.begin(WIFI_SSID, WIFI_PASS);

    cout << "Wifi began" << endl;

    while (WiFi.status() != WL_CONNECTED) {
        cout << "connecting ..." << endl;
        cout << "status: " << WiFi.status() << endl;

        auto status_name = magic_enum::enum_name(WiFi.status());

        cout << status_name << endl;

        delay(500);
    }

    cout << "connected!" << endl;

    cout << "local ip: " <<  Serial.println(WiFi.localIP()) << endl;
}

void setup_server() {
    cout << "Server setup" << endl;

    server.on("/test", HTTP_GET, handle_test); // when the server receives a request with /data/ in the string then run the handleSentVar function
    server.on("/blink", HTTP_GET, handle_blink); // when the server receives a request with /data/ in the string then run the handleSentVar function
    server.on("/blink_data", HTTP_GET, handle_blink_data); // when the server receives a request with /data/ in the string then run the handleSentVar function

    server.on("/power", HTTP_GET, handle_power); // when the server receives a request with /data/ in the string then run the handleSentVar function
    server.on("/up", HTTP_GET, handle_up); // when the server receives a request with /data/ in the string then run the handleSentVar function
    server.on("/down", HTTP_GET, handle_down); // when the server receives a request with /data/ in the string then run the handleSentVar function


    server.begin();
}

void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200); // open the serial port at 9600 bps:

    pinMode(LED_BUILTIN, OUTPUT);

    cout << "Starting setup" << endl;

    connect_to_wifi();
    setup_server();

    IrReceiver.begin(D0); // Start the receiver
    IrSender.begin(D1); // Start the receiver


    cout << "Starting app" << endl;
}

void loop() {
    server.handleClient();

    if (IrReceiver.decode()) {
        IrReceiver.printIRSendUsage(&Serial);   // Print the statement required to send this data
        IrReceiver.resume(); // Enable receiving of the next value
    }
}
