#ifndef __SEGMENT_H__
#define __SEGMENT_H__

#include <Arduino.h>
#include <SevSeg.h>

#include "state_machine.h"

extern SevSeg sevseg;

#define EASY_TIME 1200
#define MED_TIME 600
#define HARD_TIME 300
#define FREE_TIME 0

/**
 * @brief Sets the seconds to count down from on
 * the 7-Segment Display. Only sets to the hundreds place,
 * with decimal at the decisecond. Updates the state machine
 * struct's member 'time_allotted' to the respective easy, med,
 * hard, or free time.
 * 
 * @param s, pointer to the program's state machine struct
 * to update the time_allotted member.
 */
void timer_set_seconds (state_machine_t *s);

/**
 * @brief 
 * 
 * @param s 
 */
void timer_run (state_machine_t *s);

#endif