#include "timer.h"

#define INCREMENT 1
#define DECREMENT -1

/**
 * @brief Helper function for timer_run() that increments or
 * decrements the current time every 100 milliseconds. Code inspired
 * from example by Dean Reading, the creator of the SevSeg library used
 * in this program: https://wokwi.com/arduino/libraries/SevSeg/SevSeg_Counter.
 * Since the library doesn't work with the delay() function (the timer interrupt
 * interferes with delay()), the workaround is to use a time stamp and time buffer.
 * 
 * @param dir either INCREMENT or DECREMENT, depending whether user selected free mode
 * @param s pointer to state machine 's'
 */
void change_time (int dir, state_machine_t *s);

void timer_set_seconds (state_machine_t *s) {
  // Call built-in .setNumber function for the respective allotted time
  switch (s->tasks->difficulty_mode) {
    case EASY:
      sevseg.setNumber(EASY_TIME,1);
      // Set the time remaining, which will change once the timer_run() function is called
      s->tasks->time_remaining = EASY_TIME;
      break;
    case MED:
      sevseg.setNumber(MED_TIME,1);
      s->tasks->time_remaining = MED_TIME;
      break;
    case HARD:
      sevseg.setNumber(HARD_TIME,1);
      s->tasks->time_remaining = HARD_TIME;
      break;
    case FREE:
      sevseg.setNumber(FREE_TIME,1);
      s->tasks->time_remaining = FREE_TIME;
      break;
  }
}

void timer_run (state_machine_t *s) {
  // If the difficulty mode is not free, decrement the time by 1 decisecond
  if (s->tasks->difficulty_mode != FREE) {
    while (s->tasks->time_remaining != 0) {
      change_time(DECREMENT,s);
      /* *** Tanya's TODO: If puzzle solved, change s->tasks->task_status to COMPLETE and return. Otherwise set to FAILED. *** */
    }
    /* *** In the interim, I set the status to COMPLETE when timer runs out *** */
    s->tasks->task_status = COMPLETE;
  }
  else {
    // Increment until task COMPLETE if difficult mode is set to free
    change_time(INCREMENT,s);
  }
}

void change_time (int dir, state_machine_t *s) {
  // Create buffer of 100 milliseconds after the current time is stamped
  if (millis() - curr_time >= 100) {
    // If in free mode, count upwards from 0 rather than downwards
    if (dir == INCREMENT) {
      s->tasks->time_remaining++;
      // In the event of overflow in free mode, reset the timer to 0
      if (s->tasks->time_remaining == 10000) {
        s->tasks->time_remaining = 0;
      }
    }
    // Otherwise count down from the respective allotted time
    else {
      s->tasks->time_remaining--;
    }
    // Update the 7-Seg display with the time remaining and increment the current time by 100 millis
    sevseg.setNumber(s->tasks->time_remaining, 1);
    // Update the value of the buffer by 100 milliseconds (10 deciseconds)
    curr_time += 100;
  }
}

// Refreshes the seven segment display every 1 millisecond through the built-in ISR and TIMER0_COMPA_vect. This must be called to display anything on the 7-seg.
ISR(TIMER0_COMPA_vect) {
  sevseg.refreshDisplay();
}