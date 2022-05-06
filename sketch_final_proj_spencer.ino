#include <stdbool.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

#include "pins.h"
#include "I2C.h"
#include "encoder.h"
#include "segment.h"
#include "buzzer.h"
#include "states.h"

int selector = 0;
int button_pin_prev = HIGH;
int button_press;

state current_state = WELCOME;
state prev_state = WELCOME;
state prev_prev_state;
page page_no = PAGE_ZERO;

void setup() {
  Serial.begin(9600);
  I2C_init_display(); /* Initialize the I2C display, clearing screen and getting ready for content */
  encoder_init(); /* Set the a and b pins of encoder */
  button_init(); /* Set the button pin of the encoder to passive pullup */
  buzzer_init(); /* Initialize the buzzer to the proper pin */
  segment_display_init(); /* Sets the pinMode for all of the 14 pins on the 7-Segment Display*/
  // Help with interrupts from the Arduino tutorials: https://create.arduino.cc/projecthub/rafitc/interrupts-basics-f475d5
  attachInterrupt(digitalPinToInterrupt(ENCODER_PIN_A), encoder_ISR, CHANGE); /* Attach an interrupt for a change in the encoderA pin, launching the encoder ISR */
}

void loop() {
  button_press = read_button_press();
  switch (current_state) {
    case WELCOME:
      I2C_welcome_screen(selector, button_press, &current_state, &prev_state);
      switch_to_help(button_press, &current_state, &prev_state);
   //   light_array_test();
      break;
    case ABOUT:
      I2C_about_screen(selector, button_press, &current_state, &prev_state, &page_no);
      switch_to_help(button_press, &current_state, &prev_state);
      break;
    case DIFFICULTY_MODE:
      I2C_difficulty_mode_screen(selector, button_press, &current_state, &prev_state);
      switch_to_help(button_press, &current_state, &prev_state);
      break;
    case HELP:
      I2C_help_screen(&selector, button_press, &current_state, &prev_state, &page_no);
      break;
    // TODO
    case INSTRUCTIONS:
     I2C_instruction_selection_0(selector);
     break;
  }
}
