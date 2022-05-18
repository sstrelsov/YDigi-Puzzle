#include "encoder_ISR.h"

bool state_changed(int curr_state, int *past_state) {
  if (curr_state != *past_state) {
    *past_state = curr_state;
    return true;
  }
  return false;
}

void update_curr_button(int pin_a_state, int pin_b_state, state_machine_t *s) {
  int upper = s->buttons->num_buttons - 1;
  // Update the value at the address of the selector.
  if (pin_a_state != pin_b_state) {
    // Loop back to the first option if 
    if  (s->buttons->curr_button == upper) {
      s->buttons->curr_button = 0;
    } else {
        s->buttons->curr_button += 1;      
    }
  }
  else if (s->buttons->curr_button  == 0) {
    s->buttons->curr_button = upper;
  }
  // Select the previous option
  else {
    s->buttons->curr_button -= 1;
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
    // Update the selector of the highlighted text if state changed
    if (state_changed(pin_a_state, &pin_a_prev_state)) {
      update_curr_button(pin_a_state, pin_b_state, state_machine);
      last_encoder_interrupt = millis();
    }
  } 
}
