#ifndef __ENCODER_H__
#define __ENCODER_H__

#include <stdbool.h>
#include <Arduino.h>

#include "state_machine.h"
#include "pins_setup.h"

void encoder_ISR ();
/*
 * Set the encoder pins to input, pulled up to logic 1.
 */

bool state_changed (int curr_state, int *past_state);

void update_curr_button (int a_state, int b_state, state_machine_t *s, int range);

#endif