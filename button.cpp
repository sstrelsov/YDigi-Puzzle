#include "button.h"

#define BUTTON_DEBOUNCE_TIME 50
#define LONG_PRESS_TIME 400

/**
 * @brief Debounces the rotary encoder's button press. Ensures
 * that the constant BUTTON_DEBOUNCE_TIME is the minimum elapsed
 * time between real button presses.
 * 
 * @param prev_time, the previous time that a button press was read.
 * @param curr_time, the current time in the program. millis() passed as param.
 * @param debounce_time, the minimum time between real presses that the function will return as true.
 * @return true if a user's button press was read.  
 * @return false if the detected button press was just noise.
 */
bool debounce (unsigned long prev_time, unsigned long curr_time, unsigned long debounce_time);

unsigned long press_time = 0; /* The time stamp of a debounced button press */
unsigned long last_press = 0; /* Equivalent of last_encoder_interrupt, for debouncing the button */

int read_button_press () {
  // Reset long_press flag to false 
  bool long_press = false;
  int button_state = digitalRead(BUTTON_PIN);
  // Debounce button press, return NONE if not pressed or noise
  if ((button_state == HIGH) || (button_state == LOW && !debounce(last_press, millis(), BUTTON_DEBOUNCE_TIME))) {
    return NONE;
  }
  // If debounced button press, time stamp the press
  if (button_state == LOW) {
    press_time = millis();
  }
  // If the button's state is LOW for longer than the LONG_PRESS_TIME, read it as a long press
  while (digitalRead(BUTTON_PIN) == LOW) {
    if (millis() - press_time > LONG_PRESS_TIME) {
      long_press = true;
    }
  }
  // Reset the press time, time stamp the just-read press
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