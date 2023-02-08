
#include "mem.hpp"
#include "wifi.hpp"
#include <iostream>
#include <ESP8266WiFi.h>
#include <magic_enum.hpp>

using namespace std;


void connect_wifi() {

    cout << "Starting Wifi" << endl;

    auto ssid = read_ssid();

    WiFi.begin(ssid.c_str(), read_pass().c_str());

    cout << "Wifi began" << endl;

    while (WiFi.status() != WL_CONNECTED) {
        cout << "connecting to: " << ssid << " ..." << endl;
        cout << "Password: " << read_pass() << endl;
        cout << "status: " << magic_enum::enum_name(WiFi.status()) << endl;
        delay(1000);
    }

    cout << "connected!" << endl;

    cout << "local ip: " <<  Serial.println(WiFi.localIP()) << endl;
}
