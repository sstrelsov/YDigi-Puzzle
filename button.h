#ifndef __BUTTON_H__
#define __BUTTON_H__

#include <stdbool.h>
#include <Arduino.h>
#include "state_machine.h"
#include "init.h"

// Button press type constants
#define NONE   0
#define SINGLE 1
#define LONG   2

/**
 * @brief Determines whether the button
 * on the rotary encoder was pressed along with
 * the type of press. Debounces button presses. If
 * the button was pressed for more than 400 ms, then
 * it is considered a LONG press. If it is a normal
 * press, it is SINGLE.
 * 
 * @return int, the type of button press. Returns SINGLE
 * (1), NONE (0), LONG (2).
 */
int read_button_press ();

#endif