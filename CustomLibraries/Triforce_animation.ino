#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <string.h>
// // Try to keep to a 16x16 icon size!
// '_a_Triforce 0, 250', 16x16px
const unsigned char Triforce_Frame_0 [] PROGMEM = {
	0x01, 0x00, 0x01, 0x00, 0x03, 0x80, 0x03, 0x80, 0x07, 0xc0, 0x07, 0xc0, 0x0f, 0xe0, 0x00, 0x00, 
	0x10, 0x10, 0x10, 0x10, 0x38, 0x38, 0x38, 0x38, 0x7c, 0x7c, 0x7c, 0x7c, 0xfe, 0xfe, 0x00, 0x00
};
// '_a_Triforce 1 Mirror, 250', 16x16px
const unsigned char Triforce_Frame_1_Mirror [] PROGMEM = {
	0x01, 0x00, 0x01, 0x00, 0x03, 0x80, 0x03, 0x80, 0x07, 0xc0, 0x07, 0xc0, 0x0f, 0xe0, 0x00, 0x00, 
	0x10, 0x10, 0x10, 0x10, 0x18, 0x38, 0x38, 0x38, 0x3c, 0x7c, 0x7c, 0x7c, 0x7e, 0xfe, 0x00, 0x02
};
// '_a_Triforce 1, 250', 16x16px
const unsigned char Triforce_Frame_1 [] PROGMEM = {
	0x00, 0x80, 0x00, 0x80, 0x01, 0xc0, 0x01, 0xc0, 0x03, 0xe0, 0x03, 0xe0, 0x07, 0xf0, 0x00, 0x00, 
	0x08, 0x08, 0x08, 0x08, 0x1c, 0x18, 0x1c, 0x1c, 0x3e, 0x3c, 0x3e, 0x3e, 0x7f, 0x7e, 0x40, 0x00
};
// '_a_Triforce 2 Mirror, 250', 16x16px
const unsigned char Triforce_Frame_2_Mirror [] PROGMEM = {
	0x04, 0x00, 0x04, 0x00, 0x0e, 0x00, 0x0e, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x1f, 0x80, 0x00, 0x00, 
	0x20, 0x40, 0x20, 0x40, 0x70, 0xc0, 0x70, 0xe0, 0x71, 0xe0, 0xf1, 0xf0, 0x1b, 0xf0, 0x00, 0xf8
};
// '_a_Triforce 2, 250', 16x16px
const unsigned char Triforce_Frame_2 [] PROGMEM = {
	0x01, 0x00, 0x01, 0x00, 0x03, 0x80, 0x03, 0x80, 0x07, 0x80, 0x07, 0x80, 0x0f, 0xc0, 0x00, 0x00, 
	0x10, 0x20, 0x10, 0x20, 0x18, 0x70, 0x38, 0x70, 0x3c, 0x70, 0x7c, 0x78, 0x7e, 0xc0, 0xf8, 0x00
};
// '_a_Triforce 3 Mirror, 250', 16x16px
const unsigned char Triforce_Frame_3_Mirror [] PROGMEM = {
	0x08, 0x00, 0x08, 0x00, 0x0c, 0x00, 0x0c, 0x00, 0x1c, 0x00, 0x1c, 0x00, 0x1e, 0x00, 0x00, 0x00, 
	0x01, 0x00, 0x21, 0x00, 0x63, 0x00, 0x63, 0x80, 0x73, 0x80, 0x73, 0xc0, 0x17, 0xc0, 0x03, 0xc0
};
// '_a_Triforce 3, 250', 16x16px
const unsigned char Triforce_Frame_3 [] PROGMEM = {
	0x02, 0x00, 0x02, 0x00, 0x06, 0x00, 0x06, 0x00, 0x07, 0x00, 0x07, 0x00, 0x0f, 0x00, 0x00, 0x00, 
	0x10, 0x00, 0x10, 0x80, 0x18, 0xc0, 0x38, 0xc0, 0x39, 0xc0, 0x79, 0xc0, 0x7d, 0x00, 0x78, 0x00
};
// '_a_Triforce 4 Mirror, 250', 16x16px
const unsigned char Triforce_Frame_4_Mirror [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x20, 0x00, 0x30, 0x00, 0x30, 0x00, 0x70, 0x00, 0x00, 0x00, 
	0x08, 0x00, 0x08, 0x00, 0x08, 0x00, 0xc8, 0x00, 0xd8, 0x00, 0xdc, 0x00, 0x1c, 0x00, 0x1c, 0x00
};
// '_a_Triforce 4, 250', 16x16px
const unsigned char Triforce_Frame_4 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x08, 0x00, 0x18, 0x00, 0x18, 0x00, 0x1c, 0x00, 0x00, 0x00, 
	0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x26, 0x00, 0x36, 0x00, 0x76, 0x00, 0x70, 0x00, 0x70, 0x00
};
// '_a_Triforce 5 Mirror, 250', 16x16px
const unsigned char Triforce_Frame_5_Mirror [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa0, 0x00, 0xe0, 0x00, 0x60, 0x00, 0x20, 0x00
};
// '_a_Triforce 5, 250', 16x16px
const unsigned char Triforce_Frame_5 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa0, 0x00, 0xe0, 0x00, 0xc0, 0x00, 0x80, 0x00
};

const unsigned char Triforce_Frame_6 [] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define TOP_BAR_HEIGHT 15 // Height of the top bar, usually a different color than the rest of the screen.
#define MAIN_SCREEN_HEIGHT (SCREEN_HEIGHT - TOP_BAR_HEIGHT)
#define MAIN_SCREEN_START_Y (TOP_BAR_HEIGHT + 1)
#define SCREEN_CENTER_Y (TOP_BAR_HEIGHT + (MAIN_SCREEN_HEIGHT / 2))
#define LINE_HEIGHT 9 // Height of a line of text
#define SERIAL_BAUD_RATE 115200 // Baud rate for the serial monitor
#define Triforce_Frame_allArray_LEN 12

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 528)
const unsigned char* Triforce_Frame_allArray[12] = {
	Triforce_Frame_0,
    Triforce_Frame_1,
    Triforce_Frame_2,
    Triforce_Frame_3,
    Triforce_Frame_4,
    Triforce_Frame_5,
    Triforce_Frame_6,
    Triforce_Frame_5_Mirror,
    Triforce_Frame_4_Mirror,
    Triforce_Frame_3_Mirror,
    Triforce_Frame_2_Mirror,
    Triforce_Frame_1_Mirror
};

void setup() {
    Serial.begin(SERIAL_BAUD_RATE);    
    // Start I2C communication with the Multiplexer
    Wire.begin();
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("SSD1306 allocation failed Port"));
    }
    Serial.println("Starting...");
    display.clearDisplay();
}

void loop() {
  display.clearDisplay();
   for (int i = 0; i < Triforce_Frame_allArray_LEN; i++) {
       display.clearDisplay();
       display.drawBitmap(0, 0, Triforce_Frame_allArray[i], 16, 16, 1);
       display.display();
       delay(100);
   }
}
