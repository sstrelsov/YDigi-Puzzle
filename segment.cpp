#include "segment.h"
int segment_pins[] = {PIN_A,PIN_B,PIN_C,PIN_D,PIN_E,PIN_F,PIN_G,PIN_DEC}; 
int digit_pins[] = {DIGIT_1,DIGIT_2,DIGIT_3,DIGIT_4};

/* Array of 7-segment (+dec point) code for characters 0-9, in order of segment_pins[]. 
   First column is character. */
    //0-9 numbers, 10+ letters/symbols
int segment_digits[10][8] {
            {1,1,1,1,1,1,0,0}, // 0
            {0,1,1,0,0,0,0,0}, // 1
            {1,1,0,1,1,0,1,0}, // 2
            {1,1,1,1,0,0,1,0}, // 3
            {0,1,1,0,0,1,1,0}, // 4
            {1,0,1,1,0,1,1,0}, // 5
            {1,0,1,1,1,1,1,0}, // 6
            {1,1,1,0,0,0,0,0}, // 7
            {1,1,1,1,1,1,1,0}, // 8
            {1,1,1,1,0,1,1,0}, // 9
};

void segment_display_init () {
  pinMode(PIN_A, OUTPUT);
  pinMode(PIN_B, OUTPUT);
  pinMode(PIN_C, OUTPUT);
  pinMode(PIN_D, OUTPUT);
  pinMode(PIN_E, OUTPUT);
  pinMode(PIN_F, OUTPUT);
  pinMode(PIN_G, OUTPUT);
  pinMode(DIGIT_1, OUTPUT);
  pinMode(DIGIT_2, OUTPUT);
  pinMode(DIGIT_3, OUTPUT);
  pinMode(DIGIT_4, OUTPUT);
  pinMode(COM, OUTPUT); // must be included for colon in middle to function
  pinMode(PIN_8, OUTPUT);
  pinMode(PIN_DEC, OUTPUT);
}

void set_easy_time () {
  // TODO
  //digitalWrite(digit_pins[
//  digitalWrite(segment_pins[1],
}

void set_med_time () {
  return;
}

void set_hard_time () {
  return;
}

void light_array_test () {
  for (int i=0; i<10; i++) {
    for (int j=0; j<8; j++) {
      digitalWrite(segment_pins[j], segment_digits[i][j]);
    }
    delay(50);
  }
}

void light_up () {
  digitalWrite(PIN_A, HIGH);
  digitalWrite(PIN_B, HIGH);
  digitalWrite(PIN_C, HIGH);
  digitalWrite(PIN_D, HIGH);
  digitalWrite(PIN_E, HIGH);
  digitalWrite(PIN_F, HIGH);
  digitalWrite(PIN_G, HIGH);
  digitalWrite(DIGIT_1, LOW);
  digitalWrite(DIGIT_2, LOW);
  digitalWrite(DIGIT_3, LOW);
  digitalWrite(DIGIT_4, LOW);
  //analogWrite(COM, LOW);
  analogWrite(PIN_8, 250);  // controls the colon in the middle
  digitalWrite(PIN_DEC, HIGH);
}
