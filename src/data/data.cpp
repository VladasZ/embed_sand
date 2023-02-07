
#include <Arduino.h>

#include "data.hpp"

using namespace std;

BlinkData::BlinkData(uint8_t pin) : pin(pin) {
    data.reserve(1000);
}

void BlinkData::start_reading() {
    while (!read()) {}
    int zero_count = 0;
    while (zero_count < 1000) {
        bool val = read();
        if (val) {
            zero_count = 0;
        } else {
            zero_count++;
        }
        data.push_back(read());
    }
}

string BlinkData::to_string() {

    string result = "[";

    for (bool val : data) {
        result += string(val ? "1" : "0") + ",";
    }

    result.pop_back();

    return result + "]";
}

bool BlinkData::read() {
    return !digitalRead(pin);
}
