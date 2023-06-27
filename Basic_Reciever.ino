// #include <Wire.h>
// #include <Adafruit_GFX.h>
// #include <Adafruit_SSD1306.h>
// #include <string.h>
// #include <ESP8266WiFi.h>
// #include <IconMapRepository.h>

// // Enter the WiFi credentials
// // const char wifissid[] = "";
// // const char wifipass[] = "";

// #define SCREEN_WIDTH 128 // OLED display width, in pixels
// #define SCREEN_HEIGHT 64 // OLED display height, in pixels
// #define TOP_BAR_HEIGHT 15 // Height of the top bar, usually a different color than the rest of the screen.
// #define MAIN_SCREEN_HEIGHT (SCREEN_HEIGHT - TOP_BAR_HEIGHT)
// #define MAIN_SCREEN_START_Y (TOP_BAR_HEIGHT + 1)
// #define SCREEN_CENTER_Y (TOP_BAR_HEIGHT + (MAIN_SCREEN_HEIGHT / 2))
// #define LINE_HEIGHT 9 // Height of a line of text
// #define SERIAL_BAUD_RATE 115200 // Baud rate for the serial monitor
// #define Triforce_Frame_allArray_LEN 12

// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// int signal_percent[] = {0, 0, 0, 0, 0, 0, 4, 6, 8, 11, 13, 15, 17, 19, 21, 23, 26, 28, 30, 32, 34, 35, 37, 39, 41, 43, 45, 46, 48, 50, 52, 53, 55, 56, 58, 59, 61, 62, 64, 65, 67, 68, 69, 71, 72, 73, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 90, 91, 92, 93, 93, 94, 95, 95, 96, 96, 97, 97, 98, 98, 99, 99, 99, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100};
// int strength = 0;
// int percentage = 0;

// #define MENU_BITMAP_HEIGHT TOP_BAR_HEIGHT
// #define BT_BITMAP_WIDTH 8
// #define WIFI_BITMAP_WIDTH 17

// // 'Bluetooth', 8x15px
// const unsigned char bitmap_Bluetooth [] PROGMEM = {
// 	0x00, 0x18, 0x14, 0x12, 0x91, 0x52, 0x34, 0x18, 0x34, 0x52, 0x91, 0x12, 0x14, 0x18, 0x00
// };
// // 'Bluetooth_False', 8x15px
// const unsigned char bitmap_Bluetooth_False [] PROGMEM = {
// 	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
// };
// // 'Wifi_Full', 17x15px
// const unsigned char bitmap_Wifi_Full [] PROGMEM = {
//   0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x07, 0x00, 0x00, 0x77, 0x00, 0x00, 0x77, 0x00, 0x07, 
//   0x77, 0x00, 0x07, 0x77, 0x00, 0x77, 0x77, 0x00, 0x77, 0x77, 0x00, 0x77, 0x77, 0x00, 0x77, 0x77, 
//   0x00, 0x77, 0x77, 0x00, 0x77, 0x77, 0x00, 0x77, 0x77, 0x00, 0x00, 0x00, 0x00
// };
// // 'Wifi_3_4', 17x15px
// const unsigned char bitmap_Wifi_3_4 [] PROGMEM = {
//   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x70, 0x00, 0x07, 
//   0x70, 0x00, 0x07, 0x70, 0x00, 0x77, 0x70, 0x00, 0x77, 0x70, 0x00, 0x77, 0x70, 0x00, 0x77, 0x70, 
//   0x00, 0x77, 0x70, 0x00, 0x77, 0x70, 0x00, 0x77, 0x70, 0x00, 0x00, 0x00, 0x00
// };
// // 'Wifi_half', 17x15px
// // const unsigned char bitmap_Wifi_half [] PROGMEM = {
// //   0xff, 0xff, 0x80, 0xff, 0xff, 0x80, 0xff, 0xff, 0x80, 0xff, 0xff, 0x80, 0xff, 0xff, 0x80, 0xf8, 
// //   0xff, 0x80, 0xf8, 0xff, 0x80, 0x88, 0xff, 0x80, 0x88, 0xff, 0x80, 0x88, 0xff, 0x80, 0x88, 0xff, 
// //   0x80, 0x88, 0xff, 0x80, 0x88, 0xff, 0x80, 0x88, 0xff, 0x80, 0xff, 0xff, 0x80
// // };
// const unsigned char bitmap_Wifi_half [] PROGMEM = {
//   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
//   0x00, 0x00, 0x07, 0x00, 0x00, 0x77, 0x00, 0x00, 0x77, 0x00, 0x00, 0x77, 0x00, 0x00, 0x77, 0x00, 
//   0x00, 0x77, 0x00, 0x00, 0x77, 0x00, 0x00, 0x77, 0x00, 0x00, 0x00, 0x00, 0x00
// };
// // 'Wifi_quarter', 17x15px
// const unsigned char bitmap_Wifi_quarter [] PROGMEM = {
//   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
//   0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x70, 0x00, 0x00, 0x70, 0x00, 0x00, 0x70, 0x00, 
//   0x00, 0x70, 0x00, 0x00, 0x70, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00
// };

// // Array of wifi icoon bitmaps
// const int bitmap_Wifi_Array_LEN = 4;
// const unsigned char* bitmap_Wifi_Array[4] = {
//     bitmap_Wifi_quarter,
//     bitmap_Wifi_half,
//     bitmap_Wifi_3_4,
//     bitmap_Wifi_Full
// };

// void setup() {
//     for (int i = 0; i <= 100; i++) {
//         signal_percent[i] = i <= 6 ? 0 : (i - 6) * 2;
//     }
//     Serial.begin(115200);

//     // Start I2C communication with the Multiplexer
//     Wire.begin();
//     if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
//         Serial.println(F("SSD1306 allocation failed Port"));
//     }
    
// //    connectToWifi();   
// // Set WiFi to Station Mode
//     WiFi.mode(WIFI_STA);
//     WiFi.disconnect();
//     delay(10);
//     WiFi.begin(wifissid, wifipass);
//     Serial.print("Connecting to WIFI...");

//     display.clearDisplay();
//     display.setTextSize(1);
//     display.setTextColor(WHITE);
//     //Serial.println("SCREEN_CENTER", SCREEN_CENTER);
//     display.setCursor(2, SCREEN_CENTER - 2);
//     display.println("Connecting to WIFI...");
//     display.display();
     

//     // Check if connected to WiFi
//     // while (WiFi.status() != WL_CONNECTED) {
//     //     display.clearDisplay();
//     //     delay(150);
//     //     String connectingMessage = "Connecting to WIFI";
//     //     for (int i = 0; i < 4; i++) {
//     //         delay(150);
//     //         display.clearDisplay();
//     //         display.setCursor(2,SCREEN_CENTER - 2);    
//     //         display.print(connectingMessage);
//     //         display.display();
//     //         connectingMessage += ".";
//     //     }
//     // }
//     display.clearDisplay();
// }
// void loop() {
//     display.clearDisplay();
//     drawTopBar(88, true);

//     display.setCursor(2, TOP_BAR_HEIGHT + 1);
//     display.print(WiFi.RSSI());
//     display.setCursor(2, TOP_BAR_HEIGHT + LINE_HEIGHT + 1);
//     display.print(WiFi.status());
//     Serial.print("WiFi Status:\n");
//     Serial.print("      RSSI: ");
//     Serial.print(WiFi.RSSI());
//     Serial.print(" dBm\n");
//     Serial.print("      Connection Status: ");
//     Serial.print(WiFi.status());
//     Serial.print("\n");
//     Serial.print("      IP Address: ");
//     Serial.print(WiFi.localIP());
//     Serial.print("\n");


//     display.display();
    

    

//     delay(2000);
// }


// //void loop() {
// //    display.clearDisplay();
// //   int wifiStrengthIndex = PrintWifiSignalStrength();
// //   drawTopBar(signal_percent[wifiStrengthIndex], true);
// //    drawConnectionScreen();
// //    display.display();
// //    delay(2000);
// //}



// // int getWifiStrengthAsPercent() {
// //     int rssi = WiFi.RSSI();

// //     int index = -1;
// //     for (int i = 0; i <= 100; i++) {
// //         if (signal_dBM[i] == rssi) {
// //             index = i;
// //             break;
// //         }
// //     }
// //     return index;
// // }
// // void drawWifiStrength() {

// // }


// void drawTopBar(int wifiStrengthPercent, bool hasBluetooth) {
//     int marginRight = 9;
//     const unsigned char *bluetoothBitmap;
//     if (hasBluetooth) {
//         bluetoothBitmap = bitmap_Bluetooth;
//     } else {
//         bluetoothBitmap = bitmap_Bluetooth_False;
//     }
//     display.drawBitmap(SCREEN_WIDTH - marginRight - WIFI_BITMAP_WIDTH - BT_BITMAP_WIDTH, 0, bluetoothBitmap, BT_BITMAP_WIDTH, MENU_BITMAP_HEIGHT, WHITE);

//     const unsigned char *wifiBitmap;
//     if (wifiStrengthPercent <= 25) {
//         wifiBitmap = bitmap_Wifi_quarter;
//     } else if (wifiStrengthPercent <= 50) {
//         wifiBitmap = bitmap_Wifi_half;
//     } else if (wifiStrengthPercent <= 75) {
//         wifiBitmap = bitmap_Wifi_3_4;
//     } else {
//         wifiBitmap = bitmap_Wifi_Full;
//     }
//     display.drawBitmap(SCREEN_WIDTH - WIFI_BITMAP_WIDTH , 0, wifiBitmap, WIFI_BITMAP_WIDTH, MENU_BITMAP_HEIGHT, WHITE);
// }

// void drawConnectionScreen() {
//     display.setCursor(2, TOP_BAR_HEIGHT + 1);
//     display.print("Connected to: ");
//     display.setCursor(10, TOP_BAR_HEIGHT + LINE_HEIGHT + 1);
//     for (int i = 0; i < strlen(wifissid); i++) {
//         display.print(wifissid[i]);
//     }
// }

// //void connectToWifi() {
// //    // Set WiFi to Station Mode
// //    WiFi.mode(WIFI_STA);
// //    WiFi.disconnect();
// //    delay(10);
// //    WiFi.begin(wifissid, wifipass);
// //    Serial.print("Connecting to WIFI...");
// //
// //    display.clearDisplay();
// //    display.setTextSize(1);
// //    display.setTextColor(WHITE);
// //    //Serial.println("SCREEN_CENTER", SCREEN_CENTER);
// //    display.setCursor(2, SCREEN_CENTER - 2);
// //    display.println("Connecting to WIFI...");
// //    display.display();
// //     
// //
// //    // Check if connected to WiFi
// //    int dotCount = 0;
// //    while (WiFi.status() != WL_CONNECTED) {
// //        display.clearDisplay();
// //        delay(150);
// //        String connectingMessage = "Connecting to WIFI";
// //        for (int i = 0; i < 4; i++) {
// //            delay(150);
// //            display.clearDisplay();
// //            display.setCursor(2,SCREEN_CENTER - 2);    
// //            display.print(connectingMessage);
// //            display.display();
// //            connectingMessage += ".";
// //        }
// //    }
// //}

// int PrintWifiSignalStrength(){
//     display.setCursor(2, TOP_BAR_HEIGHT + LINE_HEIGHT * 3);
//     Serial.print(WiFi.RSSI());
//     Serial.print(F(" dBm"));
//     Serial.println();
//     int strength = WiFi.RSSI();
//     int strengthIndex = strength + 100;
//     display.print(strengthIndex);
//     display.print(" dBm");
//     display.setCursor(2, TOP_BAR_HEIGHT + LINE_HEIGHT * 4);
//     display.print(signal_percent[strengthIndex]); 
//     display.print("%");
//     return strengthIndex;
// }


// // #pragma region WIFI Connection

// // #pragma endregion

// const char wifissid[] = "";
// const char wifipass[] = "";

// #define SCREEN_WIDTH 128 // OLED display width, in pixels
// #define SCREEN_HEIGHT 64 // OLED display height, in pixels
// #define TOP_BAR_HEIGHT 15 // Height of the top bar, usually a different color than the rest of the screen.
// #define MAIN_SCREEN_HEIGHT (SCREEN_HEIGHT - TOP_BAR_HEIGHT)
// #define MAIN_SCREEN_START_Y (TOP_BAR_HEIGHT + 1)
// #define SCREEN_CENTER_Y (TOP_BAR_HEIGHT + (MAIN_SCREEN_HEIGHT / 2))
// #define LINE_HEIGHT 9 // Height of a line of text
// #define SERIAL_BAUD_RATE 115200 // Baud rate for the serial monitor
// #define Triforce_Frame_allArray_LEN 12

// // Try to keep to a 16x16 icon size!
// '_a_Triforce 0, 250', 16x16px
// const unsigned char Triforce_Frame_0 [] PROGMEM = {
// 	0x01, 0x00, 0x01, 0x00, 0x03, 0x80, 0x03, 0x80, 0x07, 0xc0, 0x07, 0xc0, 0x0f, 0xe0, 0x00, 0x00, 
// 	0x10, 0x10, 0x10, 0x10, 0x38, 0x38, 0x38, 0x38, 0x7c, 0x7c, 0x7c, 0x7c, 0xfe, 0xfe, 0x00, 0x00
// };
// // '_a_Triforce 1 Mirror, 250', 16x16px
// const unsigned char Triforce_Frame_1_Mirror [] PROGMEM = {
// 	0x01, 0x00, 0x01, 0x00, 0x03, 0x80, 0x03, 0x80, 0x07, 0xc0, 0x07, 0xc0, 0x0f, 0xe0, 0x00, 0x00, 
// 	0x10, 0x10, 0x10, 0x10, 0x18, 0x38, 0x38, 0x38, 0x3c, 0x7c, 0x7c, 0x7c, 0x7e, 0xfe, 0x00, 0x02
// };
// // '_a_Triforce 1, 250', 16x16px
// const unsigned char Triforce_Frame_1 [] PROGMEM = {
// 	0x00, 0x80, 0x00, 0x80, 0x01, 0xc0, 0x01, 0xc0, 0x03, 0xe0, 0x03, 0xe0, 0x07, 0xf0, 0x00, 0x00, 
// 	0x08, 0x08, 0x08, 0x08, 0x1c, 0x18, 0x1c, 0x1c, 0x3e, 0x3c, 0x3e, 0x3e, 0x7f, 0x7e, 0x40, 0x00
// };
// // '_a_Triforce 2 Mirror, 250', 16x16px
// const unsigned char Triforce_Frame_2_Mirror [] PROGMEM = {
// 	0x04, 0x00, 0x04, 0x00, 0x0e, 0x00, 0x0e, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x1f, 0x80, 0x00, 0x00, 
// 	0x20, 0x40, 0x20, 0x40, 0x70, 0xc0, 0x70, 0xe0, 0x71, 0xe0, 0xf1, 0xf0, 0x1b, 0xf0, 0x00, 0xf8
// };
// // '_a_Triforce 2, 250', 16x16px
// const unsigned char Triforce_Frame_2 [] PROGMEM = {
// 	0x01, 0x00, 0x01, 0x00, 0x03, 0x80, 0x03, 0x80, 0x07, 0x80, 0x07, 0x80, 0x0f, 0xc0, 0x00, 0x00, 
// 	0x10, 0x20, 0x10, 0x20, 0x18, 0x70, 0x38, 0x70, 0x3c, 0x70, 0x7c, 0x78, 0x7e, 0xc0, 0xf8, 0x00
// };
// // '_a_Triforce 3 Mirror, 250', 16x16px
// const unsigned char Triforce_Frame_3_Mirror [] PROGMEM = {
// 	0x08, 0x00, 0x08, 0x00, 0x0c, 0x00, 0x0c, 0x00, 0x1c, 0x00, 0x1c, 0x00, 0x1e, 0x00, 0x00, 0x00, 
// 	0x01, 0x00, 0x21, 0x00, 0x63, 0x00, 0x63, 0x80, 0x73, 0x80, 0x73, 0xc0, 0x17, 0xc0, 0x03, 0xc0
// };
// // '_a_Triforce 3, 250', 16x16px
// const unsigned char Triforce_Frame_3 [] PROGMEM = {
// 	0x02, 0x00, 0x02, 0x00, 0x06, 0x00, 0x06, 0x00, 0x07, 0x00, 0x07, 0x00, 0x0f, 0x00, 0x00, 0x00, 
// 	0x10, 0x00, 0x10, 0x80, 0x18, 0xc0, 0x38, 0xc0, 0x39, 0xc0, 0x79, 0xc0, 0x7d, 0x00, 0x78, 0x00
// };
// // '_a_Triforce 4 Mirror, 250', 16x16px
// const unsigned char Triforce_Frame_4_Mirror [] PROGMEM = {
// 	0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x20, 0x00, 0x30, 0x00, 0x30, 0x00, 0x70, 0x00, 0x00, 0x00, 
// 	0x08, 0x00, 0x08, 0x00, 0x08, 0x00, 0xc8, 0x00, 0xd8, 0x00, 0xdc, 0x00, 0x1c, 0x00, 0x1c, 0x00
// };
// // '_a_Triforce 4, 250', 16x16px
// const unsigned char Triforce_Frame_4 [] PROGMEM = {
// 	0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x08, 0x00, 0x18, 0x00, 0x18, 0x00, 0x1c, 0x00, 0x00, 0x00, 
// 	0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x26, 0x00, 0x36, 0x00, 0x76, 0x00, 0x70, 0x00, 0x70, 0x00
// };
// // '_a_Triforce 5 Mirror, 250', 16x16px
// const unsigned char Triforce_Frame_5_Mirror [] PROGMEM = {
// 	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x00, 0x00, 
// 	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa0, 0x00, 0xe0, 0x00, 0x60, 0x00, 0x20, 0x00
// };
// // '_a_Triforce 5, 250', 16x16px
// const unsigned char Triforce_Frame_5 [] PROGMEM = {
// 	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x00, 0x00, 
// 	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa0, 0x00, 0xe0, 0x00, 0xc0, 0x00, 0x80, 0x00
// };

// const unsigned char Triforce_Frame_6 [] PROGMEM = {
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// 	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
// };

// #define SCREEN_WIDTH 128 // OLED display width, in pixels
// #define SCREEN_HEIGHT 64 // OLED display height, in pixels
// #define TOP_BAR_HEIGHT 15 // Height of the top bar, usually a different color than the rest of the screen.
// #define MAIN_SCREEN_HEIGHT (SCREEN_HEIGHT - TOP_BAR_HEIGHT)
// #define MAIN_SCREEN_START_Y (TOP_BAR_HEIGHT + 1)
// #define SCREEN_CENTER_Y (TOP_BAR_HEIGHT + (MAIN_SCREEN_HEIGHT / 2))
// #define LINE_HEIGHT 9 // Height of a line of text
// #define SERIAL_BAUD_RATE 115200 // Baud rate for the serial monitor
// #define Triforce_Frame_allArray_LEN 12

// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


// // Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 528)
// const unsigned char* Triforce_Frame_allArray[12] = {
// 	Triforce_Frame_0,
//     Triforce_Frame_1,
//     Triforce_Frame_2,
//     Triforce_Frame_3,
//     Triforce_Frame_4,
//     Triforce_Frame_5,
//     Triforce_Frame_6,
//     Triforce_Frame_5_Mirror,
//     Triforce_Frame_4_Mirror,
//     Triforce_Frame_3_Mirror,
//     Triforce_Frame_2_Mirror,
//     Triforce_Frame_1_Mirror
// };

// void setup() {
//     Serial.begin(SERIAL_BAUD_RATE);    
//     // Start I2C communication with the Multiplexer
//     Wire.begin();
//     if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
//         Serial.println(F("SSD1306 allocation failed Port"));
//     }
//     Serial.println("Starting...");
//     display.clearDisplay();
// }

// void loop() {
//   display.clearDisplay();
//    for (int i = 0; i < Triforce_Frame_allArray_LEN; i++) {
//        display.clearDisplay();
//        display.drawBitmap(0, 0, Triforce_Frame_allArray[i], 16, 16, 1);
//        display.display();
//        delay(100);
//    }
// }
