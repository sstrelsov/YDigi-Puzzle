#include "encoder.h"
#include "I2C.h"

int num_options_on_screen(state *curr_state);

void encoder_init() {
  pinMode(ENCODER_PIN_A, INPUT_PULLUP);
  pinMode(ENCODER_PIN_B, INPUT_PULLUP);
}

bool state_changed(int curr_state, int *past_state) {
  if (curr_state != *past_state) {
    *past_state = curr_state;
    return true;
  }
  return false;
}

void update_selector(int pin_a_state, int pin_b_state, int *selector, int range) {
  int upper = range - 1;
  // Update the value at the address of the selector.
  if (pin_a_state != pin_b_state) {
    // Loop back to the first option if 
    if  (*selector == upper) {
      *selector = 0;
    } else {
      *selector += 1;      
    }
  }
  else if (*selector == 0) {
    *selector = upper;
  }
  // Select the previous option
  else {
      *selector -= 1;
  }
}

int num_options_on_screen (state *curr_state) {
  switch (*curr_state) {
    case HELP:
      return 4;
      break;
    case WELCOME:
      return 2;
      break;
    case ABOUT:
      return 3;
      break;
    case DIFFICULTY_MODE:
      return 4;
      break;
    case INSTRUCTIONS:
      return 3;
      break;
  }
}

/* The interrupt service handler's body is only run with a break of 10 milliseconds, which
 *  is the debouncing time we selected for the rotary encoder. If the state of the rotary encoder
 *  changes, we update the value at the address of the selector depending on the direction
 *  the encoder turned. Print the value of the selector to Serial and update the past value
 *  of the 'A' pin for the next interrupt.
 */

int pin_a_prev_state = HIGH; /* Declare the current value of a as 'a_now'*/
unsigned long last_encoder_interrupt = 0; /* Set the previous interrupt to 0ms, to be updated with millis() after each ISR runs*/

void encoder_ISR() {
  unsigned long encoder_time_stamp = millis(); /* Time stamp the currently elapsed time of the program */
  // Make sure that the encoder is debounced before updating the state change
  if (encoder_time_stamp - last_encoder_interrupt > ENCODER_DEBOUNCE_TIME) {
    int pin_a_state = digitalRead(ENCODER_PIN_A); 
    int pin_b_state = digitalRead(ENCODER_PIN_B);
    int selector_range = num_options_on_screen(&current_state);
    // Update the selector of the highlighted text if state changed
    if (state_changed(pin_a_state, &pin_a_prev_state)) {
      update_selector(pin_a_state, pin_b_state, &selector, selector_range);
      Serial.println(selector);
      last_encoder_interrupt = millis();
    }
  } 
}
