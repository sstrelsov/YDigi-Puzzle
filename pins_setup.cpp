#include "pins_setup.h"

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

void init_seven_segment () {
  pinMode(PIN_A, OUTPUT);
  pinMode(PIN_B, OUTPUT);
  pinMode(PIN_C, OUTPUT);
  pinMode(PIN_D, OUTPUT);
  pinMode(PIN_E, OUTPUT);
  pinMode(PIN_F, OUTPUT);
  pinMode(PIN_G, OUTPUT);
  pinMode(DIGIT_1, OUTPUT);
  pinMode(DIGIT_2, OUTPUT);
  pinMode(DIGIT_3, OUTPUT);
  pinMode(DIGIT_4, OUTPUT);
  pinMode(COM, OUTPUT); // must be included for colon in middle to function
  pinMode(PIN_8, OUTPUT);
  pinMode(PIN_DEC, OUTPUT);
}