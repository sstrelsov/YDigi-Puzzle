#include "I2C.h"

/**
 * @brief Each of the following helper functions display the
 * I2C screen for different states of the state machine. Each uses
 * the same naming convention of the I2C screen functions, but contain
 * the word 'static.' Every function displays a static screen except for
 * I2C_confirmation_static, which changes the text displayed on the screen
 * based on the user's difficulty selection.
 * 
 * These functions are necessary because the I2C screen functions are constantly
 * being refreshed and altering based on the user's actions – different buttons are
 * hovered over based on the state of the rotary encoder. The original, static screen
 * needs to constantly be refreshed to create the illusion of the user hovering over buttons
 * on the same screen.
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
void I2C_game_won_static ();
void I2C_game_lost_static ();
void I2C_end_static ();
void I2C_help_static ();
void I2C_instruction_initial_static ();
void I2C_instruction_second_static ();
void I2C_instruction_third_static ();
void I2C_instruction_fourth_static ();
void I2C_instruction_fifth_static ();
void I2C_instruction_sixth_static ();
void I2C_instruction_seventh_static ();
void I2C_instruction_eighth_static ();

/**
 * @brief These functions draw the 'EXIT' and 
 * 'START' buttons at a fixed location on the bottom
 * of the 128x64 I2C display. They take a color parameter
 * that allows them to be dynamically changed for when they're
 * hovered over.
 * 
 * @param color either WHITE or BLACK
 */
void draw_exit (uint16_t color);
void draw_start (uint16_t color);

/**
 * @brief Draws an arrow the acts as a button on
 * either the bottom left or bottom right of the I2C
 * display. The color parameter allows them to be dynamically
 * hovered over, and the 'dir' paramater allows the same function
 * to be reused to create 'next' and 'back' buttons on the I2C display.
 * This is helpful for states like ABOUT and INSTRUCTIONS that contain
 * multiple pages of information that the user can cycle through.
 * 
 * The arrow is draw with the Adafruit_SSD1306 library, using the drawLine
 * function to manually draw each line that creates the arrow.
 * 
 * @param color either WHITE or BLACK, the color of the arrow
 * @param dir either LEFT or RIGHT, the direction the arrow points.
 */
void draw_arrow (uint16_t color, int dir);

/**
 * @brief This helper function is used in many I2C screen functions to
 * simulate the user hovering over a virtual button. It uses the Adafruit_SSD1306
 * library's fillRect function to fill a white rectangle beneath the text to simulate
 * a 'hover.' 
 * 
 * @param str the string of text to hover over with a white rectangle
 * @param text_y the y axis location to set the cursor for writing the text on the I2C screen
 * @param s pointer to a state machine 's'
 */
void hover_text (const char *str, int text_y, state_machine_t *s);

/**
 * @brief Helper function for the static helper functions. Initializes the static 
 * text to include a certain string, size (0,1,2), and y axis cursor. Consolidates
 * multiple lines of code into one. If writing text at the top of the screen, the constant
 * TOP is used for the size parameter, and the display is cleared before writing any text
 * per the Adafruit_SSD1306 library specifications.
 * 
 * @param str the string of text to write on the static I2C screen
 * @param size the size of the text, either 0,1,2
 * @param y_axis the pixel number to begin writing text, from 0-64
 */
void I2C_init_static_text (const char *str, int size, int y_axis);

/**
 * @brief Helper function that consolidates a left arrow, EXIT button,
 * and right arrow into one 'carousel' as a footer to I2C static screens.
 * 
 */
void I2C_carousel_button_footer ();

void I2C_welcome_screen (state_machine_t *s) {
  // Load the static screen before selecting a button to hover over
  I2C_welcome_static();
  // Switch the button to hover over based on the value of current button
  switch (s->buttons->curr_button) {
    case ABOUT_BTN:
      // Hover over the text written in the static helper function
      hover_text("About", 55, s);
      // If the button is pressed, switch states
      state_switch(s, ABOUT);
      break;
    case RIGHT_ARROW:
      // Hover over the drawn arrow
      hover_arrow(RIGHT);
      // Switch states if button is pressed while hovering over the arrow
      state_switch(s, DIFFICULTY_MODE);
      break;
  }
  // Display the updated screen
  disp.display();
}

void I2C_about_screen (state_machine_t *s) {
  // Set the index of the last page (3 pages on the about screen, 0 indexed)
  s->pages->last_page = 2;
  // Switch the current page to different static pages
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
  // Switch page based on button press on left or right arrows, or EXIT button
  page_switch(s);
  // Display the page
  disp.display();
}

void I2C_difficulty_mode_screen (state_machine_t *s) {
  I2C_difficulty_mode_static();
  switch (s->buttons->curr_button) {
    case EASY_BTN:
      // Set the state machine's difficulty mode based on where user hovers
      s->tasks->difficulty_mode = EASY;
      hover_text("Easy", 20, s);
      // Set the 7-segment display's timer to the difficulty mode's allotted time
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
  // Switch to the confirmation state on button press
  state_switch(s, CONFIRM_DIFFICULTY);
  // Display screen
  disp.display();
}

void I2C_confirmation_screen(state_machine_t *s) {
  I2C_confirmation_static(s);
  switch (s->buttons->curr_button) {
    case BACK_ARROW:
      // Hover over the back arrow
      hover_arrow(LEFT);
      // Switch to difficulty selection on button press
      state_switch(s, DIFFICULTY_MODE);
      break;
    case START:
      // Hover over the start button
      hover_start();
      // Switch to the first task on button press
      state_switch(s, TASK_1);
      break;
  }
  disp.display();
}

void I2C_task_1_screen (state_machine_t *s) {
  // Display instructions for the task
  I2C_task_1_static();
  switch (s->tasks->task_status) {
    // Start the task in NOT_STARTED case, setting the timer's seconds
    case NOT_STARTED:
      timer_set_seconds(s);
      // Switch task to the in progress case
      s->tasks->task_status = IN_PROGRESS;
      break;
    case IN_PROGRESS:
      // Run the timer
      timer_run(s);
      /* *** Tanya's TODO: Test for Task Completion *** */
      break;
    case COMPLETE:
      // Hover over the next arrow upon task completion
      hover_arrow(RIGHT);
      // On button press, switch to next task
      state_switch(s, TASK_2);
      break;
    case FAILED:
      // Switch state to the end of the game
      state_switch(s, GAME_LOST);
      break;
  }
  // Display the screen
  disp.display();
}

void I2C_task_2_screen (state_machine_t *s) {
  // Display task 2 instructions
  I2C_task_2_static();
  switch (s->tasks->task_status) {
    case NOT_STARTED:
      timer_set_seconds(s);
      s->tasks->task_status = IN_PROGRESS;
      break;
    case IN_PROGRESS:
      timer_run(s);
      /* *** Tanya's TODO: Test for Task Completion *** */
      break;
    case COMPLETE:
      hover_arrow(RIGHT);
      // Switch to task 3 on button press
      state_switch(s, TASK_3);
      break;
    case FAILED:
      state_switch(s, GAME_LOST);
      break;
  }
  // Display the screen
  disp.display();
}

void I2C_task_3_screen (state_machine_t *s) {
  // Display task 3 instructions
  I2C_task_3_static();
  switch (s->tasks->task_status) {
    case NOT_STARTED:
      timer_set_seconds(s);
      s->tasks->task_status = IN_PROGRESS;
      break;
    case IN_PROGRESS:
      timer_run(s);
      /* *** Tanya's TODO: Test for Task Completion *** */
      break;
    case COMPLETE:
      hover_arrow(RIGHT);
      // On button press, switch to the state for winning the game (congratulations screen)
      state_switch(s, GAME_WON);
      break;
    case FAILED:
      state_switch(s, GAME_LOST);
      break;
  }
  disp.display();
}

void I2C_game_won_screen (state_machine_t *s) {
  // Display the congratulations screen
  I2C_game_won_static();
  // Hover over the EXIT button
  hover_exit();
  // Switch to the end screen
  state_switch(s,END);
  disp.display();
}

void I2C_game_lost_screen (state_machine_t *s) {
  // Display the game over screen
  I2C_game_lost_static();
  // Hover over the TRY AGAIN button at the bottom of the screen
  hover_text("TRY AGAIN", 50, s);
  // Switch to the end screen.
  state_switch(s,END);
  disp.display();
}

void I2C_end_screen (state_machine_t *s) {
  // Display the reset instructions (activating hardward interrupt reset button on Arduino)
  I2C_end_static();
  disp.display();
}

void I2C_help_screen (state_machine_t *s) {
  // Display the help menu
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
    // Resets the program to the WELCOME state
    case RESET_BTN:
      hover_text("Reset", 37, s);
      state_switch(s,WELCOME);
      break;
    // Switch to the previous state before the help interrupt
    case BACK_BTN:
      hover_text("Back", 45, s);
      // Go to the previous state of the machine before it entered the help state.
      state_switch(s,s->states->pre_help_curr_state);
      break;
  }
  // Display the screen with button hover
  disp.display();
}

void I2C_instruction_screen (state_machine_t *s) {
  // Set page count (0-indexed) to correctly switch between 8 pages
  s->pages->last_page = 7;
  // Switch the static screen
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
  // Switch the page using the left, right, and exit arrows
  page_switch(s);
  disp.display();
}

 /*************************************************************************
 *
 *  Static Screen Helper Functions:
 *  - The following are helper functions to make my code more modular.
 *  - Learned about disp.println(); and printing text on display from an
 *    excellent tutorial at https://www.elithecomputerguy.com/2019/07/print-text-to-oled-screen-on-arduino/
 *
 **************************************************************************
 */

void I2C_init_static_text (const char *str, int size, int y_axis) {
  // If the y axis is 0, clear the display to wipe the screen, set the color to WHITE as default color for text
  if (y_axis == TOP) {
    disp.clearDisplay();
    disp.setTextColor(WHITE);
  }
  // Set size, cursor, and print text
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
  // Heading stays same regardless of difficulty selected
  I2C_init_static_text("You selected:", SMALL_TXT, TOP);
  // Switch the body text based on difficulty mode selected
  switch (s->tasks->difficulty_mode) {
    case EASY:
      I2C_init_static_text("EASY", MED_TXT, 20);
      break;
    case MED:
      I2C_init_static_text("MEDIUM", MED_TXT, 20);
      break;
    case HARD:
      I2C_init_static_text("HARD", MED_TXT, 20);
      break;
    case FREE:
      I2C_init_static_text("FREE", MED_TXT, 20);
      break;
  }
  // Include back arrow and start button
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

void I2C_game_won_static () {
  // Congratulations message
  I2C_init_static_text("CONGRATS", MED_TXT, TOP);
  // Body Text
  I2C_init_static_text("You completed all", SMALL_TXT, 20);
  disp.println("the puzzles :)");
  // Include exit button
  draw_exit(WHITE);
}

void I2C_game_lost_static () {
  // Heading
  I2C_init_static_text("GAME OVER", MED_TXT, TOP);
  // Body Text
  I2C_init_static_text("You ran out of time", SMALL_TXT, 20);
  disp.println("to complete");
  disp.println("a puzzle :(");
  // Try again button at bottom of screen
  I2C_init_static_text("TRY AGAIN", SMALL_TXT, 50); 
}

void I2C_end_static () {
  // Heading
  I2C_init_static_text("THANK YOU", MED_TXT, TOP);
  // Body
  I2C_init_static_text("Press reset button", SMALL_TXT, 20);
  disp.println("on Arduino to play");
  disp.println("again.");
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
  I2C_init_static_text("When all done and", SMALL_TXT, 15);
  disp.println("the puzzles are");
  disp.println("fully completed,");
  disp.println("the lid will open.");
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
    disp.drawLine(5, 62, 2, 59, color); /* bottom line */
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
