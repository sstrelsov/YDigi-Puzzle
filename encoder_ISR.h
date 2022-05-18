#ifndef __ENCODER_ISR_H__
#define __ENCODER_ISR_H__

#include <stdbool.h>
#include <Arduino.h>

#include "state_machine.h"
#include "init.h"

/**
 * @brief 
 * 
 */
void encoder_ISR ();

/**
 * @brief 
 * 
 * @param curr_state 
 * @param past_state 
 * @return true 
 * @return false 
 */
bool state_changed (int curr_state, int *past_state);

/**
 * @brief 
 * 
 * @param a_state 
 * @param b_state 
 * @param s 
 * @param range 
 */
void update_curr_button (int a_state, int b_state, state_machine_t *s, int range);

#endif