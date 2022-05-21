#include "init.h"

void init_timer_interrupt () {
  // Set the compare A value to 0xAF, for how often the timer interrupt should be called.
  OCR0A = 0xAF;
  // Sets the timer interrupt mask register to allow for compare A interrupts. Explanation found here: https://stackoverflow.com/questions/8981031/what-is-1ocie0a-in-c
  TIMSK0 |= _BV(OCIE0A);
}

void init_encoder_button () {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void init_rotary_encoder() {
  pinMode(ENCODER_PIN_A, INPUT_PULLUP);
  pinMode(ENCODER_PIN_B, INPUT_PULLUP);
}

// Create instance of Adafruit class called disp.
Adafruit_SSD1306 disp = Adafruit_SSD1306(128, 64, &Wire);

// Code from Lab 3 instructions for I2C setup, beginning, clearing, and displaying the display
void init_I2C_display () {
  disp.begin(SSD1306_SWITCHCAPVCC, 0x3c);  /* 0x3c is the I2C address */
  disp.clearDisplay();
  disp.display();
}

// Name object sevseg
SevSeg sevseg;

#define NUM_DIGITS 4
// Array of digit pins (4 digits on the 7-seg display)
byte digit_pins[] = {DIGIT_1,DIGIT_2,DIGIT_3,DIGIT_4};
// Array of segment pins, from A-G plus the decimal
byte segment_pins[] = {PIN_A,PIN_B,PIN_C,PIN_D,PIN_E,PIN_F,PIN_G,PIN_DEC};

void init_seven_segment () {
  bool resistors_on_segments = true; /* Resistors on segments rather than digits */
  byte hardware_config = COMMON_CATHODE; /* Display mode is common cathode */
  bool update_with_delays = false; /* The display isn't updated using delays */
  bool leading_zeros = false; /* No leading zeros, digit is off if leading digit is zero */
  bool disable_dec_point = false; /* Decimal point used throughout program for deciseconds */

  // Begin display with above parameter configurations, based on the library's specifications
  sevseg.begin(hardware_config, NUM_DIGITS, digit_pins, segment_pins, resistors_on_segments, update_with_delays, leading_zeros, disable_dec_point);
}