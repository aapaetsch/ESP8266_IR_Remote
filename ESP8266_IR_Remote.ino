#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <string.h>
#include <ESP8266WiFi.h>
// #include "IconMapRepository.h"
#include "WifiConnectWrapper.h"
#include "MainMenu.h"
// #region Menu Icons
const unsigned char IR_Reciever_Icon_13X13 [] PROGMEM = {
    0x00, 0x00, 0x1f, 0xc0, 0x18, 0xc0, 0x15, 0x40, 0x12, 0x40, 0x15, 0x40, 0x18, 0xc0, 0x1f, 0xc0, 
    0x1f, 0xc0, 0x1f, 0xc0, 0x08, 0x80, 0x08, 0x80, 0x08, 0x80, 0x17, 0x40, 0x17, 0x40, 0x16, 0x40
};

const unsigned char IR_Transmitter_Icon_13X13 [] PROGMEM = {
    0x00, 0x00, 0x02, 0x00, 0x07, 0x00, 0x08, 0x80, 0x10, 0x40, 0x12, 0x40, 0x16, 0x40, 0x17, 0x40, 
    0x17, 0x40, 0x3f, 0xe0, 0x08, 0x80, 0x08, 0x80, 0x08, 0x80   
};

const unsigned char Settings_Icon_13X13 [] PROGMEM = {
    0x07, 0x00, 0x05, 0x00, 0x35, 0x60, 0x28, 0xa0, 0x12, 0x40, 0xe7, 0x38, 0x8d, 0x88, 0xe7, 0x38, 
    0x12, 0x40, 0x28, 0xa0, 0x35, 0x60, 0x05, 0x00, 0x07, 0x00
};
// #endregion Menu Icons
// #region Wifi icons Alt
const unsigned char Wifi_None_Alt [] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0d, 0xb0, 0x1d, 0xb8, 0x31, 0x8c, 0x65, 0xa6, 0x4d, 0xb2, 
    0x19, 0x98, 0x11, 0x88, 0x05, 0xa0, 0x04, 0x20, 0x01, 0x80, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00
};

const unsigned char Wifi_Weak_Alt [] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00
};

const unsigned char Wifi_Avg_Alt [] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x03, 0xc0, 0x07, 0xe0, 0x04, 0x20, 0x01, 0x80, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00
};

const unsigned char Wifi_Strong_Alt [] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x0f, 0xf0, 
    0x18, 0x18, 0x13, 0xc8, 0x07, 0xe0, 0x04, 0x20, 0x01, 0x80, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00
};

const unsigned char Wifi_Full_Alt [] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xf0, 0x1f, 0xf8, 0x30, 0x0c, 0x67, 0xe6, 0x4f, 0xf2, 
    0x18, 0x18, 0x13, 0xc8, 0x07, 0xe0, 0x04, 0x20, 0x01, 0x80, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00
};

// const unsigned char* Wifi_Icon_Array[5] = {
//     Wifi_None_Alt,
//     Wifi_Weak_Alt,
//     Wifi_Avg_Alt,
//     Wifi_Strong_Alt,
//     Wifi_Full_Alt
// };
// #endregion Wifi icons Alt
const char wifissid[] = "";
const char wifipass[] = "";

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define SCREEN_CENTER_Y SCREEN_HEIGHT / 2
#define TOP_BAR_HEIGHT 15 // Height of the top bar, usually a different color than the rest of the screen.
#define MAIN_SCREEN_HEIGHT (SCREEN_HEIGHT - TOP_BAR_HEIGHT)
#define MAIN_SCREEN_START_Y (TOP_BAR_HEIGHT + 1)
#define MAIN_SCREEN_CENTER_Y (TOP_BAR_HEIGHT + (MAIN_SCREEN_HEIGHT / 2))
#define LINE_HEIGHT 9 // Height of a line of text

#define KNOB_SWITCH_PIN 13 //
#define KNOB_A_PIN 12 // DT
#define KNOB_B_PIN 14 // CLK

#define SERIAL_BAUD_RATE 115200 // Baud rate for the serial monitor


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
MainMenuDriver mainMenuDriver(
    SCREEN_HEIGHT, 
    SCREEN_WIDTH, 
    MAIN_SCREEN_START_Y, 
    MAIN_SCREEN_HEIGHT, 
    IR_Transmitter_Icon_13X13,
    IR_Reciever_Icon_13X13,
    Settings_Icon_13X13);
WifiConnectWrapper wifiConnect(
    wifissid, 
    wifipass, 
    Wifi_None_Alt, 
    Wifi_Weak_Alt, 
    Wifi_Avg_Alt, 
    Wifi_Strong_Alt, 
    Wifi_Full_Alt, 
    SCREEN_WIDTH, 
    MAIN_SCREEN_CENTER_Y, 
    MAIN_SCREEN_START_Y);
void setupPins() {
    // encoder pins
    pinMode(KNOB_A_PIN, INPUT);
    pinMode(KNOB_B_PIN, INPUT);
    pinMode(KNOB_SWITCH_PIN, INPUT);
}

void onButtonPress() {

}

int lastStateCLK;
void setup() {
    Serial.begin(SERIAL_BAUD_RATE);
    // Start I2C communication with the Multiplexer
    Wire.begin();
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("SSD1306 allocation failed Port"));
    }
    mainMenuDriver.setDisplay(display);
    // wifiConnect.setDisplay(display);
    display.clearDisplay();
    display.setCursor(64/3, SCREEN_CENTER_Y - 2);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    Serial.println("Starting...");
    display.println("Starting...");
    display.display();
    delay(5000);
    display.clearDisplay();
    // wifiConnect.initWifiConnection();


    display.display();

    delay(10000);
    display.clearDisplay();    
    // wifiConnect.displayWifiSettingsPage();
    display.display();
    

    // Initial state of knob_b
    lastStateCLK = digitalRead(KNOB_B_PIN);
    delay(202001);

    // TODO: Then we connect to wifi...

    // TODO: Then we setup the icon topbar...
    // TODO: Draw the main menu...
}

int counter = 0;
int currentStateCLK;
String currentDir ="";
unsigned long lastKnobButtonPress = 0;

void loop() {
  // Check for actions  
  currentStateCLK = digitalRead(KNOB_B_PIN);
  //   Serial.println("Current State: " + String(currentStateCLK) + " | Last State: " + String(lastStateCLK) + " | Counter: " + String(counter) + " | Direction: " + currentDir + " | Button State: " + String(digitalRead(KNOB_SWITCH_PIN)) + " | Last Button Press: " + String(lastButtonPress) + " | Current Time: " + String(millis()) + " | Difference: " + String(millis() - lastButtonPress));

  // If last and current state of CLK are different, then pulse occurred
  // React to only 1 state change to avoid double count
  if (currentStateCLK != lastStateCLK  && currentStateCLK == 1){

    // If the DT state is different than the CLK state then
    // the encoder is rotating CCW so decrement
    if (digitalRead(KNOB_A_PIN) != currentStateCLK) {
      counter --;
      currentDir ="CCW";
    } else {
      // Encoder is rotating CW so increment
      counter ++;
      currentDir ="CW";
    }
    Serial.print("Direction: ");
    Serial.print(currentDir);
    Serial.print(" | Counter: ");
    Serial.println(counter);
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setCursor(4, MAIN_SCREEN_CENTER_Y - 2);
    display.println(counter);
    display.display();
  }

  // Remember last CLK state
  lastStateCLK = currentStateCLK;

  // Read the button state
  int btnState = digitalRead(KNOB_SWITCH_PIN);
  Serial.print("Button State: ");
  Serial.println(btnState);
  //If we detect LOW signal, button is pressed
  if (btnState == LOW) {
    onButtonPress();
    lastKnobButtonPress = millis();
  }
  delay(1);
  // Put in a slight delay to help debounce the reading

  // TODO: Check the wifi signal strength and update the icon if needed...
    // TODO: Check the bluetooth connection and update the icon if needed...? (Maybe not)

    // TODO: Something with either the knob or the buttons... Menu navigation?
    // TODO: Update the screen if needed...

    // TODO: Need some way to setup 
    // TODO: Setup different modes
        // TODO: Settings Mode
            // TODO: Wifi Settings/status screen (put as part of settings? or menu?)
        // TODO: IR Reciever Mode
        // TODO: IR Transmitter Mode
        // TODO: Combo Mode? Maybe allow for it to recieve signals and do something based off of them?
         // Read the current state of CLK
}