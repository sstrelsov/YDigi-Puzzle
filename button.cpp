#include "button.h"

/*
 * Debounces a button press, ensuring that successive presses are less than
 * the BUTTON_DEBOUNCE_TIME constant defined in button.h. Returns true if
 * a button press was accurately read, false if it was noise.
 */

/**
 * @brief 
 * 
 * @param prev_time 
 * @param curr_time 
 * @param debounce_time 
 * @return true 
 * @return false 
 */
bool debounce (unsigned long prev_time, unsigned long curr_time, unsigned long debounce_time);

unsigned long press_time = 0;
unsigned long release_time;
unsigned long last_press = 0; /* Equivalent of last_encoder_interrupt, for debouncing the button*/

int read_button_press () {
  bool long_press = false;
  int button_state = digitalRead(BUTTON_PIN);
  if ((button_state == HIGH) || (button_state == LOW && !debounce(last_press, millis(), BUTTON_DEBOUNCE_TIME))) {
    return NONE;
  }
  if (button_state == LOW) {
    press_time = millis();
  }
  while (digitalRead(BUTTON_PIN) == LOW) {
    if (millis() - press_time > LONG_PRESS_TIME) {
      long_press = true;
    }
  }
  press_time = 0;
  last_press = millis();
  if (long_press == true) {
    return LONG;
  }
  return SINGLE;
  }

bool debounce (unsigned long prev_time, unsigned long curr_time, unsigned long debounce_time) {
  if (curr_time - prev_time > debounce_time) {
    return true;
  }
  return false;
}

// RENAME TO GENERIC_PRESS
bool any_kind(int button_press) {
  if (button_press == SINGLE || button_press == LONG) {
    return true;
  }
  return false;
}
