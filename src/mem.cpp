
#include <mem.hpp>
#include <EEPROM.h>
#include <array>
#include <iostream>

using namespace std;

#define MAX_SSID_SIZE 32 + 1
#define MAX_PASSWORD_SIZE 64

#define SSID_ADDRESS 0
#define PASSWORD_ADDRESS (SSID_ADDRESS + MAX_SSID_SIZE)

template<class T>
string array_to_string(const T& arr) {
    string result = "[";
    for (auto a : arr) {
        result += to_string((char)a) + ", ";
    }
    result.pop_back();
    result.pop_back();
    return result + "]";
}

template<uint8_t size>
array<char, size> str_to_buffer(const string& str) {
    array<char, size> result = { 0 };
    for (size_t i = 0; i < str.length() + 1; i++) {
        result[i] = str[i];
    }
    return result;
}

void init() {
    static bool ok = false;
    if (ok) {
        return;
    }
    EEPROM.begin(512);
    ok = true;
}

void write_ssid(const string& ssid) {
    init();
    auto buff = str_to_buffer<MAX_SSID_SIZE>(ssid);
    EEPROM.put(SSID_ADDRESS, buff);
    EEPROM.commit();
}

string read_ssid() {
    init();
    array<char, MAX_SSID_SIZE> buff = { 0 };
    buff = EEPROM.get(SSID_ADDRESS, buff);
    return &buff[0];
}

void write_pass(const string& pass) {
    init();
    auto buff = str_to_buffer<MAX_PASSWORD_SIZE>(pass);
    EEPROM.put(PASSWORD_ADDRESS, buff);
    EEPROM.commit();
}

string read_pass() {
    init();
    array<char, MAX_PASSWORD_SIZE> buff = { 0 };
    EEPROM.get(PASSWORD_ADDRESS, buff);
    return &buff[0];
}
