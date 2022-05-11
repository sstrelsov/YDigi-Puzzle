#include <SevSeg.h>

#include "init.h"
#include "state_machine.h"
#include "timer.h"

// Create a state_machine struct to navigate the program
state_machine_t *state_machine = create_state_machine();

void setup() {
  // TODO: EXPLAIN THE TIMER INTERRUPT
  // Got from: https://learn.adafruit.com/multi-tasking-the-arduino-part-2/timers
  OCR0A = 0xAF;
  TIMSK0 |= _BV(OCIE0A);
  init_I2C_display(); /* Initialize the I2C display, clearing screen and getting ready for content */
  init_rotary_encoder(); /* Set the a and b pins of encoder */
  init_encoder_button(); /* Set the button pin of the encoder to passive pullup */
  init_buzzer(); /* Initialize the buzzer to the proper pin */
  init_seven_segment(); /* TODO */
  // Help with interrupts from the Arduino tutorials: https://create.arduino.cc/projecthub/rafitc/interrupts-basics-f475d5
  attachInterrupt(digitalPinToInterrupt(ENCODER_PIN_A), encoder_ISR, CHANGE); /* Attach an interrupt for a change in the encoderA pin, launching the encoder ISR */
}

void loop() {
  // Poll the rotary encoder's button for either a single or a long press
  state_machine->buttons->button_press = read_button_press();
  // Switch the current state of the state machine based on user interactions
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
      // TODO screen
      // TODO puzzle function
      break;
    case RGB_PUZZLE:
      // TODO screen
      // TODO puzzle function
      break;
    case COMBO_LOCK_PUZZLE:
      // TODO screen
      // TODO puzzle function
      break;
  }
}

// Refreshes the seven segment display every 1 millisecond through ISR
ISR(TIMER0_COMPA_vect) {
  sevseg.refreshDisplay();
}