#ifndef __SEGMENT_H__
#define __SEGMENT_H__

#include <Arduino.h>
#include <SevSeg.h>

extern SevSeg sevseg;

#define MAX_TIME 999.9
#define EASY_TIME 120
#define MED_TIME 60
#define HARD_TIME 30
#define FREE_TIME 0

/**
 * @brief Sets the seconds to count down from on
 * the 7-Segment Display. Only sets to the hundreds place,
 * with decimal at the decisecond.
 * 
 * @param t unsigned long var for time to set on display.
 */
void timer_set_seconds (unsigned long t);

#endif