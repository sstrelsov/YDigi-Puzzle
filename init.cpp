#include "init.h"

void init_encoder_button () {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void init_buzzer () {
  pinMode(BUZZER_PIN, OUTPUT);
}

void init_rotary_encoder() {
  pinMode(ENCODER_PIN_A, INPUT_PULLUP);
  pinMode(ENCODER_PIN_B, INPUT_PULLUP);
}

Adafruit_SSD1306 disp = Adafruit_SSD1306(128, 64, &Wire);

void init_I2C_display () {
  disp.begin(SSD1306_SWITCHCAPVCC, 0x3c);  /* 0x3c is the I2C address */
  disp.clearDisplay();
  disp.display();
}

// Name object sevseg
SevSeg sevseg;
#define NUM_DIGITS 4
byte digit_pins[] = {DIGIT_1,DIGIT_2,DIGIT_3,DIGIT_4};
byte segment_pins[] = {PIN_A,PIN_B,PIN_C,PIN_D,PIN_E,PIN_F,PIN_G,PIN_DEC};

void init_seven_segment () {
  bool resistorsOnSegments = true;
  byte hardwareConfig = COMMON_CATHODE; // We have a common cathode seven segment display
  bool updateWithDelays = false; // The display isn't updated using delays.
  bool leadingZeros = false;
  bool disableDecPoint = false;

  // Begin display with above parameter configurations 
  sevseg.begin(hardwareConfig, NUM_DIGITS, digit_pins, segment_pins, resistorsOnSegments, updateWithDelays, leadingZeros, disableDecPoint);
}