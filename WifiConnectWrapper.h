#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <string.h>
#ifndef WifiConnectWrapper_H
#define WifiConnectWrapper_H
enum WIFI_CONNECT_STRENGTH {
    NONE,
    WEAK,
    AVG,
    STRONG,
    FULL
};
// enum WIFI_CONNECTION_STATUS {
//     WL_IDLE_STATUS = 0,
//     WL_NO_SSID_AVAIL = 1,
//     WL_CONNECTED = 3,
//     WL_CONNECT_FAILED = 4,
//     WL_CONNECT_WRONG_PASSWORD = 6,
//     WL_DISCONNECTED = 7
// };

class WifiConnectWrapper {
    private:
        const char *NETWORK_SSID;
        const char *NETWORK_PASSWORD;
        // const unsigned char* WIFI_ICON_ARRAY[5];        
        const unsigned char* WIFI_NONE_ALT_ICON;
        const unsigned char* WIFI_WEAK_ALT_ICON;
        const unsigned char* WIFI_AVG_ALT_ICON;
        const unsigned char* WIFI_STRONG_ALT_ICON;
        const unsigned char* WIFI_FULL_ALT_ICON;
        int WIFI_ICON_COUNT = 5;
        unsigned long LAST_DELAY;
        Adafruit_SSD1306 SCREEN;
        int SCREEN_WIDTH;
        int MARGIN_LEFT = 4;
        int SCREEN_CENTER;
        int MAIN_SCREEN_STARTY;

        const unsigned char* getWifiIconByEnum(WIFI_CONNECT_STRENGTH strength);
        WIFI_CONNECT_STRENGTH getWifiStrengthFromSignalPercent(int percent);        

    public:
        WifiConnectWrapper(
            const char *ssid, 
            const char *password, 
            const unsigned char *wifiNoneAltIcon, 
            const unsigned char *wifiWeakAltIcon, 
            const unsigned char *wifiAvgAltIcon, 
            const unsigned char *wifiStrongAltIcon, 
            const unsigned char *wifiFullAltIcon, 
            int screenWidth, 
            int screenCenter, 
            int mainStartY);
        // #region Setters
        void setDisplay(Adafruit_SSD1306 display);
        // #endregion Setters
        // #region Getters
        int* getSignalStrengthMap();
        const char* getNetworkSSID();
        int getSignalStrength_RSSI();
        int getSignalStrengthAsPercent();
        const char* getConnectionStatusString(wl_status_t status);
        const char* getCurrentConnectionStatusString();
        wl_status_t getConnectionStatus();
        // #endregion Getters
        void initWifiConnection();
        void connectToWifiAsStationMode();
        void waitForWifiConnectionSerial();
        void waitForWifiConnectionOLED(int cursorX, int cursorY, int textX, int textY);
        void drawTopBarCurrentStrengthWifiIcon();
        // #region Wifi Settings Page
        void displayWifiSettingsPage();
        // #endregion Wifi Settings Page
        
};
#endif