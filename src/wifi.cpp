
#include "wifi.hpp"
#include <iostream>
#include <ESP8266WiFi.h>
#include <magic_enum.hpp>

using namespace std;


#define WIFI_SSID "Fergel"
#define WIFI_PASS "******"


void connect_wifi() {

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
