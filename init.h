#ifndef __INIT_H__
#define __INIT_H__

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

#include "SevSeg.h"

// Create extern variable disp to use in other files
extern Adafruit_SSD1306 disp;

/**
 * @brief Utilizes TIMER0, which is the same timer interrupt
 * that millis() uses. Uses the output compare register (OCR0A)
 * and the timer interrupt mask register (TIMSK0, p95 of ATMega 328 datasheet) to enable the 
 * TIMER0 interrupt to be called every millisecond, when the compare A register value hits 0xAF. 
 * Learned about method from https://learn.adafruit.com/multi-tasking-the-arduino-part-2/timers
 * under subheading "Comparison Registers."
 */
void init_timer_interrupt ();

/**
 * @brief Initialize the encoder button pin, pulling it up to HIGH.
 * 
 */
void init_encoder_button ();

/**
 * @brief Initialize the rotary encoder's pins, pulling them up to HIGH
 * 
 */
void init_rotary_encoder ();

/**
 * @brief Initializes the I2C display by clearing the screen, running the
 * 'begin' function, and setting the address of the display.
 * 
 */
void init_I2C_display ();

/**
 * @brief Initialize the 7-Segment Display based on the SevSeg library's configurations.
 * See the GitHub page of the creator, Dean Reading: https://github.com/DeanIsMe/SevSeg
 * Sets the mode to common cathode, assigns the digit and segment pins, and sets the resistor,
 * updating, and leading zeros modes.
 * 
 */
void init_seven_segment ();


// Rotary Encoder
#define ENCODER_PIN_A 2
#define ENCODER_PIN_B 4
#define ENCODER_DEBOUNCE_TIME 10

// Button (on encoder)
#define BUTTON_PIN 3

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

#endif