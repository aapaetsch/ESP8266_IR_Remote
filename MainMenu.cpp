#include <Arduino.h>
#include <string.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include "MainMenu.h"

// int MainMenuOptions = 3;

MainMenuDriver::MainMenuDriver(int screenHeight, int screenWidth, int initialY, int windowHeight, const unsigned char *menuIcon1, const unsigned char *menuIcon2, const unsigned char *menuIcon3) {
    this->SCREEN_HEIGHT = screenHeight;
    this->SCREEN_WIDTH = screenWidth;
    this->WINDOW_HEIGHT = windowHeight;
    this->MENU_TAB_LEFT = 4;
    this->MENU_TAB_RIGHT = 10;
    this->MENU_TEXT_INDENT = 19;
    this->MENU_TOP_Y = initialY;
    this->MENU_ITEM_FIRST_HEIGHT = 17;
    this->MENU_ICON_WIDTH_HEIGHT = 13;

    this->IR_TRANSMITTER_ICON = menuIcon2;
    this->IR_RECIEVER_ICON = menuIcon1;
    this->SETTINGS_ICON = menuIcon3;

    this->SELECTED_MODE = MainMenuMode::IR_TRANSMITTER_MODE;
}

// #region Setters
/**
 * Sets the display, must happen before any other methods are called.
 * @param display The initialized display object.
*/
void MainMenuDriver::setDisplay(Adafruit_SSD1306 display) {
    this->SCREEN = display;
}
// #endregion Setters
// #region Getters
/**
 * @returns the currently selected mode
*/
MainMenuMode MainMenuDriver::getSelectedMode() {
    return this->SELECTED_MODE;
}

/**
 * Returns the next mode based off of the currently selected mode enum.
 * If the currently selected mode is the last mode, it will return the first mode
 * @returns The next mode
*/
MainMenuMode MainMenuDriver::getNextMode() {
    int nextModeIndex = static_cast<int>(this->getSelectedMode()) + 1;
    if (nextModeIndex >= MainMenuOptions) {
        nextModeIndex = 0;
    }
    MainMenuMode nextMode = static_cast<MainMenuMode>(nextModeIndex);
    return nextMode;
}

/**
 * Returns the previous mode based off of the currently selected mode enum.
 * If the 
*/
MainMenuMode MainMenuDriver::getPreviousMode() {
    int previousModeIndex = static_cast<int>(this->getSelectedMode()) - 1;
    if (previousModeIndex < 0) {
        previousModeIndex = MainMenuOptions - 1;
    }
    MainMenuMode previousMode = static_cast<MainMenuMode>(previousModeIndex);
    return previousMode;
}

/**
 * @param mode
 * @returns The mode label
 */
const char *MainMenuDriver::getModeText(MainMenuMode mode) {
    switch(mode) {
        case MainMenuMode::IR_TRANSMITTER_MODE:
            return "IR Transmitter";
        case MainMenuMode::IR_RECIEVER_MODE:
            return "IR Reciever";
        case MainMenuMode::SETTINGS:
            return "Settings";
        default:
            return "Unknown";
    }
}

/**
 * @param mode
 * @returns the mode icon
*/
const unsigned char *MainMenuDriver::getModeIcon(MainMenuMode mode) {
    switch(mode) {
        case MainMenuMode::IR_TRANSMITTER_MODE:
            return this->IR_TRANSMITTER_ICON;
        case MainMenuMode::IR_RECIEVER_MODE:
            return this->IR_RECIEVER_ICON;
        case MainMenuMode::SETTINGS:
            return this->SETTINGS_ICON;
        default:
            return this->IR_RECIEVER_ICON;
    }
}
// #endregion Getters
// #region Display Methods
void MainMenuDriver::displayMainMenuScreen(MainMenuMode mode, bool isPressed) {
    this->SCREEN.clearDisplay();
    Serial.println("Displaying Main Menu Screen");
    this->displayMenuIcons(mode, isPressed);
    this->displayScrollBar();
    this->SCREEN.display();
}
// #region Menu Icon Display Methods
// Private Method
void MainMenuDriver::displayMenuIcon(const char *menuLabel, int y, const unsigned char *menuIcon) {
    this->SCREEN.drawBitmap(this->MENU_TAB_LEFT, y, menuIcon, this->MENU_ICON_WIDTH_HEIGHT, this->MENU_ICON_WIDTH_HEIGHT, WHITE);
    this->SCREEN.setCursor(this->MENU_TEXT_INDENT, y + this->MENU_ICON_WIDTH_HEIGHT / 2 - 2);
    this->SCREEN.setTextColor(WHITE);
    this->SCREEN.setTextSize(1);
    Serial.print("Displaying Menu Label:");
    Serial.print(menuLabel);
    Serial.print(" at x:");
    Serial.print(this->MENU_TEXT_INDENT);
    Serial.print(" at y:");
    Serial.println(y);


    this->SCREEN.println(menuLabel);
}

// Private Method
void MainMenuDriver::displayTopMenuIcon(const char *menuLabel, const unsigned char *menuIcon) {
    this->displayMenuIcon(menuLabel, this->MENU_TOP_Y, menuIcon);
}

// Private Method
void MainMenuDriver::displayMiddleMenuIcon(const char *menuLabel, const unsigned char *menuIcon) {
    this->displayMenuIcon(menuLabel, this->MENU_TOP_Y + this->MENU_ITEM_FIRST_HEIGHT - 1, menuIcon);
}

// Private method
void MainMenuDriver::displayBottomMenuIcon(const char *menuLabel, const unsigned char *menuIcon) {
    this->displayMenuIcon(menuLabel, this->SCREEN_HEIGHT - this->MENU_ICON_WIDTH_HEIGHT - 1, menuIcon);
}
// #endregion

void MainMenuDriver::displaySelectedMenuIndicator(bool isPressed) {
    // top line
    Serial.println("Displaying Selected Menu Indicator");
    this->SCREEN.drawFastHLine(this->MENU_TAB_LEFT, 31, this->SCREEN_WIDTH - this->MENU_TAB_RIGHT - 1, WHITE);
    Serial.println("After Top line");
    // bottom line
    this->SCREEN.drawFastHLine(this->MENU_TAB_LEFT, 48, this->SCREEN_WIDTH - this->MENU_TAB_RIGHT - 1, WHITE);
    Serial.println("After Bottom line");
    this->SCREEN.drawFastHLine(this->MENU_TAB_LEFT - 1, 47, this->SCREEN_WIDTH - this->MENU_TAB_RIGHT, WHITE);
    Serial.println("After Bottom line 2");
    // left side 
    this->SCREEN.drawFastVLine(this->MENU_TAB_LEFT - 2, 33, 14, WHITE);
    Serial.println("After Left side");
    this->SCREEN.drawPixel(this->MENU_TAB_LEFT - 1, 32, WHITE);
    Serial.println("After Left side 2");
    // right side
    this->SCREEN.drawFastVLine(this->SCREEN_WIDTH - this->MENU_TAB_RIGHT + 4, 33, 14, WHITE);
    Serial.println("After Right side");
    this->SCREEN.drawFastVLine(this->SCREEN_WIDTH - this->MENU_TAB_RIGHT + 3, 32, 16, WHITE);
    Serial.println("After Right side 2");

    if (isPressed) {
        // Fill the indicator
        this->SCREEN.fillRect(4, 32, 16, 33, WHITE);
    }
}

/**
 * Displays a menu state based off of the mode passed in
 * @param mode The mode to display as the middle selected icon
 * @param isPressed If the selected indicator should be filled in
*/
void MainMenuDriver::displayMenuIcons(MainMenuMode mode, bool isPressed) {
    Serial.println("Displaying Menu Icons");
    this->displaySelectedMenuIndicator(isPressed);
    MainMenuMode topMode = this->getPreviousMode();
    this->displayTopMenuIcon(this->getModeText(topMode), this->getModeIcon(topMode));
    if (!isPressed) {
        this->displayMiddleMenuIcon(this->getModeText(mode), this->getModeIcon(mode));
    } else {
        Serial.println("Press, not displaying Middle Menu Icon");
    }

    this->SELECTED_MODE = mode;
    MainMenuMode bottomMode = this->getNextMode();
    this->displayBottomMenuIcon(this->getModeText(bottomMode), this->getModeIcon(bottomMode));
    Serial.println("Finished displaying menu icons.");

}

void MainMenuDriver::displayScrollBar() {
    for(int i = 0; i < this->SCREEN_HEIGHT; i += 4) {
        this->SCREEN.drawPixel(this->SCREEN_WIDTH - 2, i + this->MENU_TOP_Y, WHITE);
        this->SCREEN.drawPixel(this->SCREEN_WIDTH - 2, i + this->MENU_TOP_Y + 1, WHITE);
    }
}
void MainMenuDriver::displayScrollBarThumbByMode(MainMenuMode mode) {
    int y = 0;
    int height = 0;
    switch(mode) {
        case MainMenuMode::IR_TRANSMITTER_MODE:
            y = this->MENU_TOP_Y + this->MENU_ITEM_FIRST_HEIGHT;
            height = this->MENU_ITEM_FIRST_HEIGHT;
            break;
        case MainMenuMode::IR_RECIEVER_MODE:
            y = this->MENU_TOP_Y + this->MENU_ITEM_FIRST_HEIGHT * 2;
            height = this->MENU_ITEM_FIRST_HEIGHT;
            break;
        case MainMenuMode::SETTINGS:
            y = this->SCREEN_HEIGHT - this->MENU_ICON_WIDTH_HEIGHT;
            height = this->MENU_ITEM_FIRST_HEIGHT;
            break;
        default:
            y = this->MENU_TOP_Y;
            height = this->MENU_ITEM_FIRST_HEIGHT;
            break;
    }
    this->displayScrollBarThumb(height, y);
}
void MainMenuDriver::displayScrollBarThumb(int height, int y) {
    this->SCREEN.fillRect(this->SCREEN_WIDTH - 2, y, 2, height, WHITE);
}
// #endregion
// #region Mode Methods




// #endregion