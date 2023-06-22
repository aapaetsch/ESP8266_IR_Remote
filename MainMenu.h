#include <Wire.h>
#include <Arduino.h>
#include <string.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#ifndef MAIN_MENU_DRIVER
#define MAIN_MENU_DRIVER
#define MainMenuOptions 3
enum MainMenuMode {
    IR_RECIEVER_MODE,
    IR_TRANSMITTER_MODE,
    SETTINGS
};
class MainMenuDriver {
    private:
        Adafruit_SSD1306 SCREEN;
        int SCREEN_HEIGHT;
        int SCREEN_WIDTH;
        int WINDOW_HEIGHT;
        int MENU_TAB_LEFT;
        int MENU_TAB_RIGHT;
        int MENU_TEXT_INDENT;
        int MENU_TOP_Y;
        int MENU_ITEM_FIRST_HEIGHT;
        int MENU_ICON_WIDTH_HEIGHT;
        const unsigned char *IR_TRANSMITTER_ICON;
        const unsigned char *IR_RECIEVER_ICON;
        const unsigned char *SETTINGS_ICON;
        MainMenuMode SELECTED_MODE;

        void displayTopMenuIcon(const char *menuLabel, const unsigned char *menuIcon);
        void displayMiddleMenuIcon(const char *menuLabel, const unsigned char *menuIcon);
        void displayBottomMenuIcon(const char *menuLabel, const unsigned char *menuIcon);
        void displayMenuIcon(const char *menuLabel, int y, const unsigned char *menuIcon);
    public:
        MainMenuDriver(int screenHeight, int screenWidth, int initialY, int windowHeight, const unsigned char *menuItem1, const unsigned char *menuItem2, const unsigned char *menuItem3);
        // #region Setters
        void setDisplay(Adafruit_SSD1306 display);
        // #endregion Setters
        // #region Getters
        MainMenuMode getSelectedMode();
        MainMenuMode getNextMode();
        MainMenuMode getPreviousMode();
        const char *getModeText(MainMenuMode mode);
        const unsigned char *getModeIcon(MainMenuMode mode);
        // #endregion Getters
        // #region Display Methods
        void displayMainMenuScreen(MainMenuMode mode, bool isPressed);
        void displaySelectedMenuIndicator(bool isPressed);
        void displayMenuIcons(MainMenuMode mode, bool isPressed);
        void displayScrollBar();
        void displayScrollBarThumbByMode(MainMenuMode mode);
        void displayScrollBarThumb(int height, int y);
        // #endregion Display Methods
};
#endif

// #include <Wire.h>
// #include <Adafruit_GFX.h>
// #include <Adafruit_SSD1306.h>
// #include <string.h>
// // // Try to keep to a 16x16 icon size!
// #define SCREEN_WIDTH 128 // OLED display width, in pixels
// #define SCREEN_HEIGHT 64 // OLED display height, in pixels
// #define TOP_BAR_HEIGHT 15 // Height of the top bar, usually a different color than the rest of the screen.
// #define MAIN_SCREEN_HEIGHT (SCREEN_HEIGHT - TOP_BAR_HEIGHT)
// #define MAIN_SCREEN_START_Y (TOP_BAR_HEIGHT + 1)
// #define SCREEN_CENTER_Y (TOP_BAR_HEIGHT + (MAIN_SCREEN_HEIGHT / 2))
// #define LINE_HEIGHT 9 // Height of a line of text
// #define SERIAL_BAUD_RATE 115200 // Baud rate for the serial monitor
// // #define Triforce_Frame_allArray_LEN 12
// #define MENU_ITEM_FIRST_HEIGHT 17
// #define MENU_ICON_HEIGHT_WIDTH 13
// #define MENU_TAB_WIDTH 4
// #define MENU_TEXT_INDENT 17

// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


// // #endregion Display Menu
// // #region Display
// // TODO: Update to use an array?
// MainMenuDriver mainMenu(SCREEN_HEIGHT, SCREEN_WIDTH, MAIN_SCREEN_START_Y, MAIN_SCREEN_HEIGHT, IR_Transmitter_Icon_13X13, IR_Reciever_Icon_13X13, Settings_Icon_13X13);

// void setup() {
//     Serial.begin(SERIAL_BAUD_RATE);    
//     Wire.begin();
//     if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
//         Serial.println(F("SSD1306 allocation failed Port"));
//     }
//     Serial.println("Starting...");
//     mainMenu.setDisplay(display);
//     display.clearDisplay();
//     display.setTextSize(1);
//     display.setTextColor(WHITE);
//     delay(10);
// }

// unsigned long lastUpdateTime = 0;
// const unsigned long refreshScreen = 3000; // 1 second
// // int i = 1;

// void loop() {
//     unsigned long currentTime = millis();
//     bool hasUpdatedScreen = false;
//     if (currentTime - lastUpdateTime > refreshScreen) {
//         lastUpdateTime = currentTime;
//         // display.clearDisplay();
//         mainMenu.displayMainMenuScreen(MainMenuMode::IR_TRANSMITTER_MODE, false);
//         hasUpdatedScreen = true;
//     }
//     if (hasUpdatedScreen) {
//         display.display();
//     }
//     // i++;
//     // delay(1);
// }