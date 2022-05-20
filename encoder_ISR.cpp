#include "encoder_ISR.h"

/**
 * @brief Helper function for encoder_ISR() that determines whether
 * the state of the encoder has changed. It takes the encoder's pin A
 * and compares its current state to its past state, returning true if
 * the state changed.
 * 
 * @param curr_state, the current state of the rotary encoder's pin A, either HIGH or LOW.
 * @param past_state, pointer to pin A of the encoder's past state.
 * @return true if the state changed
 * @return false if it's the same
 */
bool state_changed (int curr_state, int *past_state);

/**
 * @brief Helper function for encoder_ISR() that updates the value of the state_machine's
 * curr_button member. If the helper function state_changed() returns true, then the current
 * button that the user is hovering over on the I2C display changes as well. This function
 * determines the direction the rotary encoder is turning and makes sure that the buttons that
 * the user hovers over loop back around. For example, turning the encoder left when the user
 * is hovering over the I2C's virtual button that is the left-most option results in hovering
 * over the right-most option.
 * 
 * @param a_state the state of the encoder's pin A 
 * @param b_state the state of the encoder's pin B
 * @param s pointer to a state_machine s
 * @param range the number of buttons on the current I2C screen (arrows, 'exit,' 'next,' etc).
 */
void update_curr_button (int a_state, int b_state, state_machine_t *s, int range);

bool state_changed(int curr_state, int *past_state) {
  if (curr_state != *past_state) {
    *past_state = curr_state;
    return true;
  }
  return false;
}

void update_curr_button(int pin_a_state, int pin_b_state, state_machine_t *s) {
  int upper = s->buttons->num_buttons - 1;
  // Check if the rotary encoder was turned to the right
  if (pin_a_state != pin_b_state) {
    // Check if the encoder is at the upper bound of options on the screen, resetting to 0 if it is.
    if  (s->buttons->curr_button == upper) {
      s->buttons->curr_button = 0;
    } else {
        s->buttons->curr_button += 1;      
    }
  }
  // Check if encoder is at the lower bound of options on the screen, looping it around to the upper.
  else if (s->buttons->curr_button  == 0) {
    s->buttons->curr_button = upper;
  }
  // Decrease the number of the option to hover over
  else {
    s->buttons->curr_button -= 1;
  }
}

int pin_a_prev_state = HIGH; /* Initialize the encoder's pin A previous state to HIGH*/
unsigned long last_encoder_interrupt = 0; /* Set the previous interrupt to 0ms, to be updated with millis() after each ISR runs*/

void encoder_ISR() {
  unsigned long encoder_time_stamp = millis(); /* Time stamp the currently elapsed time of the program */
  // Make sure that the encoder is debounced before updating the state change
  if (encoder_time_stamp - last_encoder_interrupt > ENCODER_DEBOUNCE_TIME) {
    // Read the pin A and pin B states
    int pin_a_state = digitalRead(ENCODER_PIN_A); 
    int pin_b_state = digitalRead(ENCODER_PIN_B);
    // Update the state machine's curr_button if state changed
    if (state_changed(pin_a_state, &pin_a_prev_state)) {
      update_curr_button(pin_a_state, pin_b_state, state_machine);
      // Time stamp the last successful encoder state change
      last_encoder_interrupt = millis();
    }
  } 
}
