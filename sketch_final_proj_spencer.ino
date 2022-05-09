#include <stdbool.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

#include "pins_setup.h"
#include "I2C.h"
#include "encoder.h"
#include "segment.h"
#include "buzzer.h"
#include "state_machine.h"

state_machine_t *state_machine = create_state_machine();

void setup() {
  Serial.begin(9600);
  init_I2C_display(); /* Initialize the I2C display, clearing screen and getting ready for content */
  init_rotary_encoder(); /* Set the a and b pins of encoder */
  init_encoder_button(); /* Set the button pin of the encoder to passive pullup */
  init_buzzer(); /* Initialize the buzzer to the proper pin */
  init_seven_segment(); /* Sets the pinMode for all of the 14 pins on the 7-Segment Display*/
  // Help with interrupts from the Arduino tutorials: https://create.arduino.cc/projecthub/rafitc/interrupts-basics-f475d5
  attachInterrupt(digitalPinToInterrupt(ENCODER_PIN_A), encoder_ISR, CHANGE); /* Attach an interrupt for a change in the encoderA pin, launching the encoder ISR */
}

void loop() {
  state_machine->buttons->button_press = read_button_press();
  switch (state_machine->states->curr_state) {
    case WELCOME:
      I2C_welcome_screen(state_machine);
      break;
    case ABOUT:
      I2C_about_screen(state_machine);
      break;
    case DIFFICULTY_MODE:
      I2C_difficulty_mode_screen(state_machine);
      break;
    case HELP:
      I2C_help_screen(state_machine);
      break;
    case INSTRUCTIONS:
     I2C_instruction_screen(state_machine);
     break;
    case PHOTOCELL_PUZZLE:
      // TODO
      break;
    case RGB_PUZZLE:
      // TODO
      break;
  }
}
