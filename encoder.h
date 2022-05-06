#include <stdbool.h>
#include <arduino.h>
#include "states.h"
#include "pins.h"

extern int selector;
extern bool option_selected;
extern bool settings_screen;
extern int button_pin_prev;

extern state current_state;

void encoder_ISR ();
/*
 * Set the encoder pins to input, pulled up to logic 1.
 */
void encoder_init ();

bool state_changed (int curr_state, int *past_state);

void update_selector (int a_state, int b_state, int *selector, int range);
