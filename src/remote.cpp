
#include <IRremote.hpp>

#include "remote.hpp"

void Remote::init() {
    IrReceiver.begin(D0);
    IrSender.begin(D1);
}

void Remote::read_input() {
    if (IrReceiver.decode()) {
        IrReceiver.printIRSendUsage(&Serial);
        IrReceiver.resume();
    }
}

void Remote::power() {
    IrSender.sendNEC(0xE710, 0x46, 1);
}

void Remote::volume_up() {
    IrSender.sendNEC(0xE710, 0x6, 1);
}

void Remote::volume_down() {
    IrSender.sendNEC(0xE710, 0x47, 1);
}
