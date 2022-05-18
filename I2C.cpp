#include "I2C.h"

/**
 * @brief 
 * 
 */
void I2C_welcome_static ();
void I2C_about_initial_static ();
void I2C_about_second_static ();
void I2C_about_third_static ();
void I2C_difficulty_mode_static ();
void I2C_confirmation_static (state_machine_t *s);
void I2C_task_1_static ();
void I2C_task_2_static ();
void I2C_task_3_static ();
void I2C_help_static ();
void I2C_instruction_initial_static ();
void I2C_instruction_second_static ();
void I2C_instruction_third_static ();
void I2C_instruction_fourth_static ();
void I2C_instruction_fifth_static ();
void I2C_instruction_sixth_static ();
void I2C_instruction_seventh_static ();
void I2C_instruction_eighth_static ();

// Screen object helpers
/**
 * @brief 
 * 
 * @param color 
 */
void draw_exit (uint16_t color);
void draw_start (uint16_t color);

/**
 * @brief 
 * 
 * @param color 
 * @param dir 
 */
void draw_arrow (uint16_t color, int dir);

/**
 * @brief 
 * 
 * @param str 
 * @param text_y 
 * @param s 
 */
void hover_text (const char *str, int text_y, state_machine_t *s);

// Text display helpers
/**
 * @brief 
 * 
 * @param str 
 * @param size 
 * @param y_axis 
 */
void I2C_init_static_text (const char *str, int size, int y_axis);

/**
 * @brief 
 * 
 */
void I2C_carousel_button_footer ();

void I2C_welcome_screen (state_machine_t *s) {
  I2C_welcome_static();
  switch (s->buttons->curr_button) {
    case ABOUT_BTN:
      hover_text("About", 55, s);
      state_switch(s, ABOUT);
      break;
    case RIGHT_ARROW:
      hover_arrow(RIGHT);
      state_switch(s, DIFFICULTY_MODE);
      break;
  }
  disp.display();
}

void I2C_about_screen (state_machine_t *s) {
  s->pages->last_page = 2;
  switch (s->pages->curr_page) {
    case 0:
      I2C_about_initial_static();
      break;
    case 1:
      I2C_about_second_static();
      break;
    case 2:
      I2C_about_third_static();
      break;  
    }
  page_switch(s);
  disp.display();
}

void I2C_difficulty_mode_screen (state_machine_t *s) {
  // Call the generic selection screen, with no highlighted buttons. Simulates buttons hovering over a normal screen.
  I2C_difficulty_mode_static();
  switch (s->buttons->curr_button) {
    case EASY_BTN:
      s->tasks->difficulty_mode = EASY;
      hover_text("Easy", 20, s);
      timer_set_seconds(s);
      break;
    case MED_BTN:
      s->tasks->difficulty_mode = MED;
      hover_text("Medium", 29, s);
      timer_set_seconds(s);
      break;
    case HARD_BTN:
      s->tasks->difficulty_mode = HARD;
      hover_text("Hard", 37, s);
      timer_set_seconds(s);
      break;
    case FREE_MODE_BTN:
      s->tasks->difficulty_mode = FREE;
      hover_text("Free Mode", 45, s);
      timer_set_seconds(s);
      break;
  }
  state_switch(s, CONFIRM_DIFFICULTY);
  // Display the screen with button hover
  disp.display();
}

void I2C_confirmation_screen(state_machine_t *s) {
  I2C_confirmation_static(s);
  switch (s->buttons->curr_button) {
    case BACK_ARROW:
      hover_arrow(LEFT);
      state_switch(s, DIFFICULTY_MODE);
      break;
    case START:
      hover_start();
      state_switch(s, TASK_1);
      break;
  }
  disp.display();
}

void I2C_task_1_screen (state_machine_t *s) {
  I2C_task_1_static();
  switch (s->tasks->task_status) {
    case NOT_STARTED:
      timer_set_seconds(s);
      s->tasks->task_status = IN_PROGRESS;
      break;
    case IN_PROGRESS:
      timer_run(s);
      // TODO: Test for Task Completion
      break;
    case COMPLETE:
      hover_arrow(RIGHT);
      state_switch(s, TASK_2);
      break;
    case FAILED:
      state_switch(s, GAME_OVER);
      break;
  }
  disp.display();
}

void I2C_task_2_screen (state_machine_t *s) {
  I2C_task_2_static();
  switch (s->tasks->task_status) {
    case NOT_STARTED:
      timer_set_seconds(s);
      s->tasks->task_status = IN_PROGRESS;
      break;
    case IN_PROGRESS:
      timer_run(s);
      // TODO: Test for Task Completion
      break;
    case COMPLETE:
      hover_arrow(RIGHT);
      state_switch(s, TASK_3);
      break;
    case FAILED:
      state_switch(s, GAME_OVER);
      break;
  }
  disp.display();
}

void I2C_task_3_screen (state_machine_t *s) {
  I2C_task_3_static();
  switch (s->tasks->task_status) {
    case NOT_STARTED:
      timer_set_seconds(s);
      s->tasks->task_status = IN_PROGRESS;
      break;
    case IN_PROGRESS:
      timer_run(s);
      // TODO: Test for Task Completion
      break;
    case COMPLETE:
      hover_arrow(RIGHT);
      state_switch(s, PUZZLES_COMPLETE);
      break;
    case FAILED:
      state_switch(s, GAME_OVER);
      break;
  }
  disp.display();
}

void I2C_help_screen (state_machine_t *s) {
  I2C_help_static();
  switch (s->buttons->curr_button) {
    case ABOUT_BTN:
      hover_text("About", 20, s);
      state_switch(s,ABOUT);
      break;
    case INSTR_BTN:
      hover_text("Instructions", 29, s);
      state_switch(s,INSTRUCTIONS);
      break; 
    case RESET_BTN:
      hover_text("Reset", 37, s);
      state_switch(s,WELCOME);
      break;
    case BACK_BTN:
      hover_text("Back", 45, s);
      state_switch(s,s->states->pre_help_curr_state);
      break;
  }
  // Display the screen with button hover
  disp.display();
}

void I2C_instruction_screen (state_machine_t *s) {
  // Set page count (0-indexed) to correctly switch pages
  s->pages->last_page = 7;
  // Switch the static screen, all include the left, exit, and right arrow buttons at bottom
  switch (s->pages->curr_page) {
    case 0:
      I2C_instruction_initial_static();
      break;
    case 1:
      I2C_instruction_second_static();
      break;
    case 2:
      I2C_instruction_third_static();
      break;
    case 3:
      I2C_instruction_fourth_static();
      break;
    case 4:
      I2C_instruction_fifth_static();
      break;
    case 5:
      I2C_instruction_sixth_static();
      break;
    case 6:
      I2C_instruction_seventh_static();
      break;
    case 7:
      I2C_instruction_eighth_static();
      break;
    }
  // Switches page based on which button was pressed
  page_switch(s);
  disp.display();
}
 /*************************************************************************
 *
 *  Static Screen Helper Functions:
 *  - The following are helper functions to make our code more modular.
 *  - Learned about disp.println(); and printing text on display from an
 *    excellent tutorial at
 *    https://www.elithecomputerguy.com/2019/07/print-text-to-oled-screen-on-arduino/
 *
 **************************************************************************
 */

void I2C_init_static_text (const char *str, int size, int y_axis) {
  if (y_axis == TOP) {
    disp.clearDisplay();
    disp.setTextColor(WHITE);
  }
  disp.setTextSize(size);
  disp.setCursor(LEFT_INDENT,y_axis);
  disp.println(str);
}

void I2C_welcome_static () {
  // Welcome header text
  I2C_init_static_text("Welcome to", SMALL_TXT, TOP);
  disp.println("YDigi Puzzle Box!");
  // "About" and arrow buttons
  draw_arrow(RIGHT,WHITE);
  I2C_init_static_text("About", SMALL_TXT, 55);
}

void I2C_about_initial_static () {
  // About heading
  I2C_init_static_text("ABOUT (1/3)", SMALL_TXT, TOP);
  // About text
  I2C_init_static_text("YDigi Puzzle is a", SMALL_TXT, 14);
  disp.println("project for CPSC 338");
  disp.println("by Tanya Shibu and");
  disp.println("Spencer Strelsov.");
  // Left arrow, EXIT, and right arrow buttons
  I2C_carousel_button_footer();
}

void I2C_about_second_static () {
  // About (2/3) heading
  I2C_init_static_text("ABOUT (2/3)", SMALL_TXT, TOP);
  // About text
  I2C_init_static_text("YDigi stands for Yale", SMALL_TXT, 14);
  disp.println("Digital Systems. Our");
  disp.println("project is a puzzle");
  disp.println("box!");
  // Left arrow, EXIT, and right arrow buttons
  I2C_carousel_button_footer();
}

void I2C_about_third_static () {
  // About (3/3) heading
  I2C_init_static_text("ABOUT (3/3)", SMALL_TXT, TOP);
  // About Text
  I2C_init_static_text("To reach the help", SMALL_TXT, 13);
  disp.println("screen at any time,");
  disp.println("do a long button");
  disp.println("press on the rotary");
  disp.println("encoder!");
  // Left arrow, EXIT, and right arrow buttons
  I2C_carousel_button_footer();
}

void I2C_difficulty_mode_static () {
  // "Select difficulty" heading
  I2C_init_static_text("Select difficulty:", SMALL_TXT, TOP);
  // Puzzle box difficulty buttons
  I2C_init_static_text("Easy", SMALL_TXT, 20);
  disp.println("Medium");
  disp.println("Hard");
  disp.println("Free Mode");
}

void I2C_confirmation_static (state_machine_t *s) {
  // Write heading
  I2C_init_static_text("You selected:", SMALL_TXT, TOP);
  switch (s->tasks->time_remaining) {
    case EASY_TIME:
      I2C_init_static_text("EASY", MED_TXT, 20);
      break;
    case MED_TIME:
      I2C_init_static_text("MEDIUM", MED_TXT, 20);
      break;
    case HARD_TIME:
      I2C_init_static_text("HARD", MED_TXT, 20);
      break;
    case FREE_TIME:
      I2C_init_static_text("FREE", MED_TXT, 20);
      break;
  }
  // Include back button
  draw_arrow(WHITE,LEFT);
  draw_start(WHITE);
}

void I2C_task_1_static () {
  // Heading
  I2C_init_static_text("TASK 1", MED_TXT, TOP);
  // Task instructions
  I2C_init_static_text("Cover photocells in", SMALL_TXT, 20);
  disp.println("the following order");
  I2C_init_static_text("2 1 3 5 4 6", SMALL_TXT, 40);
}

void I2C_task_2_static () {
  // Heading
  I2C_init_static_text("TASK 2", MED_TXT, TOP);
  // Task instructions
  I2C_init_static_text("Flip the switches", SMALL_TXT, 20);
  disp.println("to get RGB pattern");
  I2C_init_static_text("R B B", SMALL_TXT, 40);
}

void I2C_task_3_static () {
  // Heading
  I2C_init_static_text("TASK 3", MED_TXT, TOP);
  // Task instructions
  I2C_init_static_text("Use rotary encoder", SMALL_TXT, 20);
  disp.println("to enter the numbers");
  disp.println("on the 7-Seg Display.");
  I2C_init_static_text("4 1 3 2", SMALL_TXT, 50);
}

void I2C_help_static () {
  // HELP heading
  I2C_init_static_text("HELP", MED_TXT, TOP);
  // Help buttons
  I2C_init_static_text("About", SMALL_TXT, 20);
  disp.println("Instructions");
  disp.println("Reset");
  disp.println("Back");
}

void I2C_instruction_initial_static () {
  // Instruction heading
  I2C_init_static_text("INSTRUCTIONS (1/8)", SMALL_TXT, TOP);
  // Instruction content  
  I2C_init_static_text("Solve 3 puzzles to", SMALL_TXT, 13);
  disp.println("open the box. There");
  disp.println("are 3 difficulty");
  disp.println("modes + a free mode.");
  // Left arrow, EXIT, and right arrow buttons
  I2C_carousel_button_footer();
}

void I2C_instruction_second_static () {
  // Instruction heading
  I2C_init_static_text("INSTRUCTIONS (2/8)", SMALL_TXT, TOP);
  // Instruction content
  I2C_init_static_text("The 7-seg time", SMALL_TXT, 13);
  disp.println("has 2 purposes: show");
  disp.println("remaining time and");
  disp.println("combo lock entry.");
  // Left arrow, EXIT, and right arrow buttons
  I2C_carousel_button_footer();
}

void I2C_instruction_third_static () {
  // Instruction heading
  I2C_init_static_text("INSTRUCTIONS (3/8)", SMALL_TXT, TOP);
  // Instruction content
  I2C_init_static_text("Easy mode gives users", SMALL_TXT, 16);
  disp.println("120 seconds total to");
  disp.println("complete each puzzle.");
  // Left arrow, EXIT, and right arrow buttons
  I2C_carousel_button_footer();
}

void I2C_instruction_fourth_static () {
  // Instruction heading
  I2C_init_static_text("INSTRUCTIONS (4/8)", SMALL_TXT, TOP);
  // Instruction content
  I2C_init_static_text("Med mode gives users", SMALL_TXT, 16);
  disp.println("90 seconds total to");
  disp.println("complete each puzzle.");
  // Left arrow, EXIT, and right arrow buttons
  I2C_carousel_button_footer();
}

void I2C_instruction_fifth_static () {
  // Instruction heading
  I2C_init_static_text("INSTRUCTIONS (5/8)", SMALL_TXT, TOP);
  // Instruction content
  I2C_init_static_text("Hard mode gives users", SMALL_TXT, 16);
  disp.println("30 seconds total to");
  disp.println("complete each puzzle.");
  // Left arrow, EXIT, and right arrow buttons
  I2C_carousel_button_footer();
}

void I2C_instruction_sixth_static () {
  // Instruction heading
  I2C_init_static_text("INSTRUCTIONS (6/8)", SMALL_TXT, TOP);
  // Instruction content
  I2C_init_static_text("Free mode sets no", SMALL_TXT, 15);
  disp.println("time limit for");
  disp.println("completing puzzles.");
  disp.println("It counts upwards.");
  // Left arrow, EXIT, and right arrow buttons
  I2C_carousel_button_footer();
}

void I2C_instruction_seventh_static () {
  // Instruction heading
  I2C_init_static_text("INSTRUCTIONS (7/8)", SMALL_TXT, TOP);
  // Instruction content
  I2C_init_static_text("When all done,", SMALL_TXT, 15);
  disp.println("the buzzer will");
  disp.println("sound and the");
  disp.println("lid will open.");
  // Left arrow, EXIT, and right arrow buttons
  I2C_carousel_button_footer();
}

void I2C_instruction_eighth_static () {
  // Instruction heading
  I2C_init_static_text("INSTRUCTIONS (8/8)", SMALL_TXT, TOP);
  // Instruction content
  I2C_init_static_text("That's it!", SMALL_TXT, 16);
  disp.println("Good luck! :)");
  // Left arrow, EXIT, and right arrow buttons
  I2C_carousel_button_footer();
}

 /*************************************************************************
 *
 *  Animation Helper Functions:
 *  - The following are helper functions to help animate button clicks,
 *    hovers, and symbols like arrows.
 *
 **************************************************************************
 */

void hover_text(const char *str, int text_y, state_machine_t *s) {
  // Set the text to BLACK to allow for WHITE rectangle underneath it.
  disp.setTextColor(BLACK);
  // Maintain the location for writing text when hovering
  disp.setCursor(LEFT_INDENT, text_y);
  // Fill a white rectangle behind the text
  disp.fillRect(LEFT_INDENT, text_y-1, s->buttons->hover_length, s->buttons->hover_height, WHITE);
  // Write the text over the white rectangle
  disp.println(str);
}

void hover_arrow (int dir) {
  // Depending on direction of arrow, fill white rectangle on either left or right
  if (dir == RIGHT) {
    disp.fillRect(115, 55, 13, 9, WHITE);
  } else if (dir == LEFT) {
    disp.fillRect(0, 55, 14, 9, WHITE);
  }
  // Make the arrow black
  draw_arrow(BLACK, dir);
}

void draw_arrow (uint16_t color, int dir) {
  if (dir == RIGHT) {
    disp.drawLine(123, 62, 126, 59, color); /* bottom line */
    disp.drawLine(123, 56, 126, 59, color); /* top line */
    disp.drawLine(116, 59, 126, 59, color); /* middle line */
  } else {
    disp.drawLine(5, 62, 2, 59, color); /*bottom line */
    disp.drawLine(5, 56, 2, 59, color); /* top line */
    disp.drawLine(12, 59, 2, 59, color); /* middle line */
  }
}

void draw_exit(uint16_t color) {
  disp.setTextSize(SMALL_TXT);
  disp.setTextColor(color); /* Allows us to dynamically set the color, helpful for hovering */
  disp.setCursor(52, 55); /* Set on the bottom middle of screen */
  disp.println("EXIT");
}

void hover_exit () {
  disp.setCursor(52,55); 
  disp.fillRect(51, 54, 25, 10, WHITE);
  draw_exit(BLACK);
}

void draw_start(uint16_t color) {
  disp.setTextSize(SMALL_TXT);
  disp.setTextColor(color);
  disp.setCursor(95,55);
  disp.println("START");
}

void hover_start() {
  disp.setCursor(95,55);
  disp.fillRect(94, 54, 32, 10, WHITE);
  draw_start(BLACK);
}

void I2C_carousel_button_footer () {
  draw_arrow(WHITE,LEFT);
  draw_exit(WHITE);
  draw_arrow(RIGHT,WHITE);
}
