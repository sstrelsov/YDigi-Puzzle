#include "timer.h"

#define INCREMENT 1
#define DECREMENT -1

/**
 * @brief 
 * 
 * @param dir 
 * @param s 
 */
void change_time (int dir, state_machine_t *s);

void timer_set_seconds (state_machine_t *s) {
  // Call built-in .setNumber function for the respective allotted time
  switch (s->tasks->difficulty_mode) {
    case EASY:
      sevseg.setNumber(EASY_TIME,1);
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
  if (s->tasks->difficulty_mode != FREE) {
    while (s->tasks->time_remaining != 0) {
      change_time(DECREMENT,s);
      // TODO: If puzzle solved, change s->tasks->task_status to COMPLETE and return
    }
    // For testing all the screens, setting to COMPLETE. Should be set to FAILED if it gets here
    s->tasks->task_status = COMPLETE;
  }
  else {
    // Increment until task COMPLETE
    change_time(INCREMENT,s);

    // TODO: If task COMPLETE, set s->tasks->task_status to COMPLETE
  }
}

void change_time (int dir, state_machine_t *s) {
  // Learned how to change the timer by 1 decisecond from Dean Reading's (SevSeg library author) tutorial: https://wokwi.com/arduino/libraries/SevSeg/SevSeg_Counter
  static unsigned long curr_time = millis();
  if (millis() - curr_time >= 100) {
    // If in free mode, count upwards from 0 rather than downwards
    if (dir == INCREMENT) {
      s->tasks->time_remaining++;
      // In the event of overflow in free mode, reset the timer to 0
      if (s->tasks->time_remaining == 1000) {
        s->tasks->time_remaining = 0;
      }
    }
    // Otherwise count down from the respective allotted time
    else {
      s->tasks->time_remaining--;
    }
    // Update the 7-Seg display with the time remaining and increment the current time by 100 millis
    sevseg.setNumber(s->tasks->time_remaining, 1);
    curr_time += 100;
  }
}

// Refreshes the seven segment display every 1 millisecond through ISR
ISR(TIMER0_COMPA_vect) {
  sevseg.refreshDisplay();
}