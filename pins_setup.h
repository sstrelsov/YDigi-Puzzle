#ifndef __PINS_SETUP_H__
#define __PINS_SETUP_H__

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

extern Adafruit_SSD1306 disp;
void init_encoder_button ();
void init_buzzer ();
void init_rotary_encoder ();
/**
 * @brief Initializes the I2C display
 * by clearing the screen, running the
 * 'begin' function, and setting the address of
 * the display.
 */
void init_I2C_display ();

void init_seven_segment ();


// Rotary Encoder
#define ENCODER_PIN_A 2
#define ENCODER_PIN_B 4
#define ENCODER_DEBOUNCE_TIME 10

// Button (on encoder)
#define BUTTON_PIN 3
#define BUTTON_DEBOUNCE_TIME 50

// Buzzer
#define BUZZER_PIN 5

// Seven Segment Display
#define PIN_A 51
#define PIN_B 43
#define PIN_C 46
#define PIN_D 50
#define PIN_E 52
#define PIN_F 49
#define PIN_G 44
#define PIN_DEC 48

#define DIGIT_1 53
#define DIGIT_2 47
#define DIGIT_3 45
#define DIGIT_4 42

#define COM A0 
#define PIN_8 A1

// Motor

#endif