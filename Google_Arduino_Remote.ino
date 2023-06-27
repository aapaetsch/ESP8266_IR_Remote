//#include <Arduino.h>
//#include "SimpleReceiver\PinDefinitionsAndMore.h"
//#include <IRremote.hpp>
//
//
//void setup() {
//    Serial.begin(115200);
//    // Just to know which program is running on my Arduino
//    Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));
//
//    // Start the receiver and if not 3. parameter specified, take LED_BUILTIN pin from the internal boards definition as default feedback LED
//    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
//
//    Serial.print(F("Ready to receive IR signals of protocols: "));
//    printActiveIRProtocols(&Serial);
//    Serial.println(F("at pin " STR(IR_RECEIVE_PIN)));
//}
//
//void loop() {
//    
//}
//
//void IRDecodeMode() {
//    if (IrReceiver.decode()) {
//        /*
//         * Print a short summary of received data
//         */
//        IrReceiver.printIRResultShort(&Serial);
//        IrReceiver.printIRSendUsage(&Serial);
//        if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
//            Serial.println(F("Received noise or an unknown (or not yet enabled) protocol"));
//            // We have an unknown protocol here, print more info
//            IrReceiver.printIRResultRawFormatted(&Serial, true);
//        }
//        Serial.println();
//
//        /*
//         * !!!Important!!! Enable receiving of the next value,
//         * since receiving has stopped after the end of the current received data packet.
//         */
//        IrReceiver.resume(); // Enable receiving of the next value
//    }
//}
//
//enum IRCommand {
//    POWER,
//    VOLUME_UP,
//    VOLUME_DOWN,
//    FanPower,
//    FanUp,
//    FanDown,
//    FanOsc,
//    // ComputerOn
//};
//
//unsigned long sendIRCommand(IRCommand command, bool onlyReturnCode = false, int repeat = 1, int delay = 500) {
//    unsigned long powerCode = 0xAB054F;
//    unsigned long fanPowerCode = 0x10D;
//    unsigned long fanUpCode = 0x31D;
//    unsigned long fanOscCode = 0x61D;
//    switch(command) {
//        case IRCommand.POWER:
//            if (!onlyReturnCode) {
//                IrSender.sendPulseDistanceWidth(38, 4100, 3950, 550, 1950, 550, 950, powerCode, 24, PROTOCOL_IS_LSB_FIRST, delay, repeat);
//            }
//            return powerCode;
//        case IRCommand.VOLUME_UP:
//            return;
//        case IRCommand.VOLUME_DOWN:
//            return;
//        case IRCommand.FanPower:
//            if (!onlyReturnCode) {
//                IrSender.sendPulseDistanceWidth(38, 1300, 400, 1300, 400, 400, 1250, fanPowerCode, 11, PROTOCOL_IS_LSB_FIRST, delay, repeat);
//            }
//            return fanPowerCode;
//        case IRCommand.FanUp:
//            if (!onlyReturnCode) {
//                IrSender.sendPulseDistanceWidth(38, 1300, 400, 1300, 350, 450, 1250, fanUpCode, 11, PROTOCOL_IS_LSB_FIRST, delay, repeat);
//            }
//            return fanUpCode;
//        case IRCommand.FanDown:
//            if (!onlyReturnCode) {
//                IrSender.sendPulseDistanceWidth(38, 1300, 400, 1300, 350, 450, 1250, fanUpCode, 11, PROTOCOL_IS_LSB_FIRST, delay, 4 * repeat);
//            }
//            return fanUpCode;
//        case IRCommand.FanOsc:
//        
//            if (!onlyReturnCode) {
//                IrSender.sendPulseDistanceWidth(38, 1350, 350, 1300, 400, 450, 1200, fanOscCode, 11, PROTOCOL_IS_LSB_FIRST, delay, repeat);
//            }
//            return fanOscCode;
//        default:
//            return 0;
//    }
//}
