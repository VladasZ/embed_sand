
#include <string>
#include <vector>

class BlinkData {

public:
    BlinkData(uint8_t pin);

    void start_reading();

    std::string to_string();

private:

    bool read();

    uint8_t pin;
    std::vector<bool> data;

};
