
#include "mem.hpp"
#include "wifi.hpp"
#include <iostream>
#include <ESP8266WiFi.h>
#include <magic_enum.hpp>

using namespace std;


void connect_wifi() {

    cout << "Starting WiFi" << endl;

    auto ssid = read_ssid();

    WiFi.hostname("ESP");
    WiFi.begin(ssid.c_str(), read_pass().c_str());

    while (WiFi.status() != WL_CONNECTED) {
        cout << "connecting to: " << ssid << " ..." << endl;
        cout << "status: " << magic_enum::enum_name(WiFi.status()) << endl;
        delay(1000);
    }

    cout << "status: " << magic_enum::enum_name(WiFi.status()) << endl;

    cout << "local ip: " <<  WiFi.localIP().toString().c_str() << endl;

}

static WiFiServer server(80);

void start_ap() {
    cout << "Starting WiFi AP" << endl;

    WiFi.softAP("ESP-board");

    cout << "AP ip: " <<  WiFi.softAPIP().toString().c_str() << endl;

    server.begin();
}

String header;


void handle_ap() {
    WiFiClient client = server.available();   // Listen for incoming clients

    if (client) {                             // If a new client connects,
        Serial.println("New Client.");          // print a message out in the serial port
        String currentLine = "";                // make a String to hold incoming data from the client
        while (client.connected()) {            // loop while the client's connected
            if (client.available()) {             // if there's bytes to read from the client,
                char c = client.read();             // read a byte, then
                Serial.write(c);                    // print it out the serial monitor
                header += c;
                if (c == '\n') {                    // if the byte is a newline character
                    // if the current line is blank, you got two newline characters in a row.
                    // that's the end of the client HTTP request, so send a response:
                    if (currentLine.length() == 0) {
                        // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
                        // and a content-type so the client knows what's coming, then a blank line:
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-type:text/html");
                        client.println("Connection: close");
                        client.println();

                        // turns the GPIOs on and off
                        if (header.indexOf("GET /26/on") >= 0) {
                            Serial.println("GPIO 26 on");
                        } else if (header.indexOf("GET /26/off") >= 0) {
                            Serial.println("GPIO 26 off");
                        } else if (header.indexOf("GET /27/on") >= 0) {
                            Serial.println("GPIO 27 on");
                        } else if (header.indexOf("GET /27/off") >= 0) {
                            Serial.println("GPIO 27 off");
                        }

                        // Display the HTML web page
                        client.println("<!DOCTYPE html><html>");
                        client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
                        client.println("<link rel=\"icon\" href=\"data:,\">");
                        // CSS to style the on/off buttons
                        // Feel free to change the background-color and font-size attributes to fit your preferences
                        client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
                        client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
                        client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
                        client.println(".button2 {background-color: #555555;}</style></head>");

                        // Web Page Heading
                        client.println("<body><h1>ESP32 Web Server</h1>");

                        // Display current state, and ON/OFF buttons for GPIO 26
                        // If the output26State is off, it displays the ON button
                        client.println("<p><a href=\"/26/off\"><button class=\"button button2\">OFF</button></a></p>");


                        // Display current state, and ON/OFF buttons for GPIO 27
                        // If the output27State is off, it displays the ON button
                        client.println("<p><a href=\"/27/off\"><button class=\"button button2\">OFF</button></a></p>");
                        client.println("</body></html>");

                        // The HTTP response ends with another blank line
                        client.println();
                        // Break out of the while loop
                        break;
                    } else { // if you got a newline, then clear currentLine
                        currentLine = "";
                    }
                } else if (c != '\r') {  // if you got anything else but a carriage return character,
                    currentLine += c;      // add it to the end of the currentLine
                }
            }
        }
        // Clear the header variable
        header = "";
        // Close the connection
        client.stop();
        Serial.println("Client disconnected.");
        Serial.println("");
    }
}
