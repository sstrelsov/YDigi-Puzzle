#ifndef __SEGMENT_H__
#define __SEGMENT_H__

#include <Arduino.h>
#include <SevSeg.h>

#include "state_machine.h"

// Let sevseg be used in other files
extern SevSeg sevseg;

// Set the timer in deciseconds (base units of counting, 1 decimal place after the seconds)
#define EASY_TIME 1200
#define MED_TIME 600
#define HARD_TIME 300
#define FREE_TIME 0

/**
 * @brief Sets the seconds to count down from on
 * the 7-Segment Display. Only sets to the tens place,
 * with decimal at the decisecond. Updates the state machine
 * struct's member 'time_remaining' to the respective easy, med,
 * hard, or free time.
 * 
 * @param s pointer to state machine 's'
 */
void timer_set_seconds (state_machine_t *s);

/**
 * @brief Runs the timer by either decrementing or incrementing by
 * 1 decisecond, depending on whether the user selects free mode. If
 * the user selects free mode, increment. All other modes decrement from
 * different allotted times. Utilizes Dean Reading's example for creating a
 * timer that decrements every decisecond without using delay(), found at
 * https://wokwi.com/arduino/libraries/SevSeg/SevSeg_Counter.
 * 
 * Updates the time_remaining member until it reaches 0.0 if decrementing, or
 * 10,000 deciseconds while incrementing (when it resets).
 * 
 * @param s pointer to state machine 's'
 */
void timer_run (state_machine_t *s);

#endif