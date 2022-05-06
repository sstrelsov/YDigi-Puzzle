#ifndef STATES_H
#define STATES_H

// Enumeration of all the different states
typedef enum {
  WELCOME,
  ABOUT,
  DIFFICULTY_MODE,
  INSTRUCTIONS,
  HELP
} state;

// Enumeration of different pages for certain states (ie multiplate pages of INSTRUCTIONS or ABOUT states)
typedef enum {
  PAGE_ZERO,
  PAGE_ONE,
  PAGE_TWO
} page;

#include "I2C.h"
#include "button.h"
#include "encoder.h"
#include <arduino.h>

// TODO:
/* Insert helper function to clean up code for switching states, reduce errors.
 *  1. clearing and initializing display
 *  2. getting to the help screen
*/

/*
 * Reads the button_press. If it's a long press, regardless of what screen the
 * user is on, it will take them to the help screen. Switches state to HELP and
 * does all necessary bookkeeping, like clearing the display and saving the previous
 * state.
 */
void switch_to_help (int button_press, state *curr_state, state *prev_state);

void instructions_sub_state_machine(int button_press, int selector);

#endif
