#include "WifiConnectWrapper.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <string.h>

WifiConnectWrapper::WifiConnectWrapper(
    const char *ssid, 
    const char *password, 
    const unsigned char *wifiNoneAltIcon, 
    const unsigned char *wifiWeakAltIcon, 
    const unsigned char *wifiAvgAltIcon, 
    const unsigned char *wifiStrongAltIcon, 
    const unsigned char *wifiFullAltIcon, 
    int screenWidth, 
    int screenCenter, 
    int mainStartY) {
    this->NETWORK_SSID = ssid;
    this->NETWORK_PASSWORD = password;
    this->WIFI_NONE_ALT_ICON = wifiNoneAltIcon;
    this->WIFI_WEAK_ALT_ICON = wifiWeakAltIcon;
    this->WIFI_AVG_ALT_ICON = wifiAvgAltIcon;
    this->WIFI_STRONG_ALT_ICON = wifiStrongAltIcon;
    this->WIFI_FULL_ALT_ICON = wifiFullAltIcon;
    this->SCREEN_WIDTH = screenWidth;
    this->SCREEN_CENTER = screenCenter;
    this->MAIN_SCREEN_STARTY = mainStartY;
    Serial.println("Ent constructor");
}
// #region Setters
void WifiConnectWrapper::setDisplay(Adafruit_SSD1306 display) {
    this->SCREEN = display;
}
// #endregion Setters
// #region Getters
int* WifiConnectWrapper::getSignalStrengthMap() {
    static int SIGNAL_STRENGTH_MAP[] = { 
        0, 0, 0, 0, 0, 0, 4, 6, 8, 11, 13, 15, 17, 19, 21, 23, 26, 28, 30, 32, 34, 
        35, 37, 39, 41, 43, 45, 46, 48, 50, 52, 53, 55, 56, 58, 59, 61, 62, 64, 65, 
        67, 68, 69, 71, 72, 73, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 
        88, 89, 90, 90, 91, 92, 93, 93, 94, 95, 95, 96, 96, 97, 97, 98, 98, 99, 99, 
        99, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 
        100, 100, 100, 100, 100, 100, 100
    };
    return SIGNAL_STRENGTH_MAP;
}

const char* WifiConnectWrapper::getNetworkSSID() {
    return NETWORK_SSID;
}

int WifiConnectWrapper::getSignalStrength_RSSI() {
    return WiFi.RSSI();
}

int WifiConnectWrapper::getSignalStrengthAsPercent() {
    return this->getSignalStrengthMap()[WiFi.RSSI() + 100];
}

const unsigned char* WifiConnectWrapper::getWifiIconByEnum(WIFI_CONNECT_STRENGTH strength) {
    switch(strength) {
        case WIFI_CONNECT_STRENGTH::NONE:
            return this->WIFI_NONE_ALT_ICON;
        case WIFI_CONNECT_STRENGTH::WEAK:
            return this->WIFI_WEAK_ALT_ICON;
        case WIFI_CONNECT_STRENGTH::AVG:
            return this->WIFI_AVG_ALT_ICON;
        case WIFI_CONNECT_STRENGTH::STRONG:
            return this->WIFI_STRONG_ALT_ICON;
        case WIFI_CONNECT_STRENGTH::FULL:
            return this->WIFI_FULL_ALT_ICON;
        default:
            return this->WIFI_NONE_ALT_ICON;
    }
}

WIFI_CONNECT_STRENGTH WifiConnectWrapper::getWifiStrengthFromSignalPercent(int percent) {
    if (percent <= 1) {
        return WIFI_CONNECT_STRENGTH::NONE;
    } else if (percent <= 30) {
        return WIFI_CONNECT_STRENGTH::WEAK;
    } else if (percent <= 55) {
        return WIFI_CONNECT_STRENGTH::AVG;
    } else if (percent <= 80) {
        return WIFI_CONNECT_STRENGTH::STRONG;
    } else {
        return WIFI_CONNECT_STRENGTH::FULL;
    }
}

wl_status_t WifiConnectWrapper::getConnectionStatus() {
    return WiFi.status();
}

const char* WifiConnectWrapper::getConnectionStatusString(wl_status_t status) {
    switch (status) {
        case WL_IDLE_STATUS:
            return "WL_IDLE_STATUS";
        case WL_NO_SSID_AVAIL:
            return "WL_NO_SSID_AVAIL";
        case WL_SCAN_COMPLETED:
            return "WL_SCAN_COMPLETED";
        case WL_CONNECTED:
            return "WL_CONNECTED";
        case WL_CONNECT_FAILED:
            return "WL_CONNECT_FAILED";
        case WL_CONNECTION_LOST:
            return "WL_CONNECTION_LOST";
        case WL_WRONG_PASSWORD:
            return "WL_WRONG_PASSWORD";
        case WL_DISCONNECTED:
            return "WL_DISCONNECTED";
        default:
            return "Unknown";
    }
}

const char* WifiConnectWrapper::getCurrentConnectionStatusString() {
    return this->getConnectionStatusString(this->getConnectionStatus());
}
// #endregion Getters

void WifiConnectWrapper::connectToWifiAsStationMode() {
    // Set to station mode
    WiFi.mode(WIFI_STA);    
    // Disconnect from any existing network
    WiFi.disconnect();
    delay(10);
    WiFi.begin(NETWORK_SSID, NETWORK_PASSWORD);
    Serial.print("\nConnecting to: ");
    Serial.print(NETWORK_SSID);
    Serial.print("...\n");
    
}

// TODO: Update to not use delay...
void WifiConnectWrapper::waitForWifiConnectionSerial() {
    while (WiFi.status() != WL_CONNECTED) {
        for (int i = 0; i < 5; i++) {
            delay(150);
            Serial.print(".");

        }
    }
    Serial.print("\nConnected to: ");
    Serial.print(NETWORK_SSID);
    Serial.print("\nIP Address: ");
    Serial.print(WiFi.localIP());
    Serial.print("\n");
}
/**
 * Waits for wifi connection and displays the wifi icon + connection text on the oled screen
 * @param cursorX The x position of the wifi icon
 * @param cursorY The y position of the wifi icon
 * @param textY The y position of the text
 * @param textX The x position of the text
*/
void WifiConnectWrapper::waitForWifiConnectionOLED(int cursorX, int cursorY, int textY, int textX) {
    int i = 0;
    while (WiFi.status() != WL_CONNECTED) {

        this->SCREEN.clearDisplay();
        this->SCREEN.drawBitmap(cursorX, cursorY, this->getWifiIconByEnum(static_cast<WIFI_CONNECT_STRENGTH>(i + 1)), 16, 16, WHITE);
        this->SCREEN.setTextColor(WHITE);
        this->SCREEN.setTextSize(1);
        this->SCREEN.setCursor(textX, textY);
        this->SCREEN.print("Connecting");
        for(int j = 0; j < i; j++) {
            this->SCREEN.print(".");
        };
        i++;   
        if (i > 4) {
            i = 0;
        }
        delay(150);

    }
    Serial.println("Before draw top bar current strength wifi icon");
    this->drawTopBarCurrentStrengthWifiIcon();
    Serial.println("After draw top bar current strength wifi icon");
}
/**
 * Represents the current wifi strength as a wifi icon on the oled screen
 * - Drawn in the top right corner of the screen
*/
void WifiConnectWrapper::drawTopBarCurrentStrengthWifiIcon() {
    // TODO: Update to use a variable
    int cursorX = this->SCREEN_WIDTH - 16;
    int cursorY = 0;
    Serial.println("Before get signal strength as percent");
    int signalStrength = this->getSignalStrengthAsPercent();
    Serial.println("Before draw top bar current strength wifi icon");
    this->SCREEN.drawBitmap(cursorX, cursorY, this->getWifiIconByEnum(this->getWifiStrengthFromSignalPercent(signalStrength)), 16, 16, 1);
    Serial.println("After draw top bar current strength wifi icon");
}

/**
 * Initializes the wifi connection
*/
void WifiConnectWrapper::initWifiConnection() {
    Serial.println("Before connect to wifi as station mode");
    this->connectToWifiAsStationMode();
    Serial.println("After connect to wifi as station mode");
    this->waitForWifiConnectionOLED(this->SCREEN_WIDTH - 16, 0, this->SCREEN_CENTER, this->MARGIN_LEFT);
    Serial.println("After wifi connect oled");
}

// #region Wifi Connect Page
void WifiConnectWrapper::displayWifiSettingsPage() {
    Serial.println("Before display wifi settings page");
    this->drawTopBarCurrentStrengthWifiIcon();
    Serial.println("After draw top bar current strength wifi icon");
    this->SCREEN.setTextColor(WHITE);
    this->SCREEN.setTextSize(1);
    this->SCREEN.setCursor(this->MARGIN_LEFT, this->MAIN_SCREEN_STARTY);

    this->SCREEN.print("SSID: ");
    this->SCREEN.println(this->getNetworkSSID());
    this->SCREEN.print("IP: ");
    this->SCREEN.println(WiFi.localIP());
    this->SCREEN.print("Status: ");
    this->SCREEN.println(this->getCurrentConnectionStatusString());
    this->SCREEN.print("Signal Strength: ");
    this->SCREEN.println(this->getSignalStrengthAsPercent());
    this->SCREEN.print("RSSI: ");
    this->SCREEN.println(this->getSignalStrength_RSSI());
}

// #endregion




