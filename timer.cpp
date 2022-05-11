#include "timer.h"


void timer_set_seconds (unsigned long t) {
  // Call built-in .setNumber function as long as seconds less than the thousands place
  if (t <= MAX_TIME) {
    sevseg.setNumber(t, 1);
  }
}