#include "buzzer.h"

void buzzer_init() {
  pinMode(BUZZER_PIN, OUTPUT);
}

void buzz() {
  tone(BUZZER_PIN, FREQ);
  noTone(BUZZER_PIN);
  delay(500);
  tone(BUZZER_PIN, FREQ);
}
