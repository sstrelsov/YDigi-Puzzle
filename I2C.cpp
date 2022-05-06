#include <stdbool.h>
#include "I2C.h"
#include "encoder.h"

Adafruit_SSD1306 disp(128, 64, &Wire);

void I2C_welcome_static ();
void I2C_about_initial_static ();
void I2C_about_second_static ();
void I2C_about_third_static ();
void I2C_difficulty_mode_static ();
void I2C_help_static ();
void I2C_about_initial_static ();
void I2C_instruction_initial_static ();

// Multi-page screen helpers
void exit_state (int button_press, state *curr_state, state *prev_state, page *page_no);

void blink_animation (int text_y, int selector);
void hover_text (const char *str, int text_y, int highlight_length, int highlight_height, uint16_t hover_color);
void display_text (int selector);
void I2C_init_text (int text_size);
void draw_arrow (uint16_t color, int dir);
void hover_arrow (int dir);
void draw_exit (uint16_t color);
void hover_exit ();

void I2C_init_text (int text_size, int y) {
  disp.setTextSize(text_size);
  disp.setTextColor(WHITE);
  disp.setCursor(LEFT_INDENT,y);
}

void I2C_init_display () {
  disp.begin(SSD1306_SWITCHCAPVCC, 0x3c);  /* 0x3c is the I2C address */
  disp.clearDisplay();
  disp.display();
}

void I2C_welcome_screen (int selector, int button_press, state *curr_state, state *prev_state) {
  I2C_welcome_static();
  switch (selector) {
    case ABOUT_BTN:
      hover_text("About", ABOUT_CURSOR, ABOUT_HOVER_LENGTH, ABOUT_HOVER_HEIGHT, WHITE);
      if (button_press == SINGLE) {
        *curr_state = ABOUT;
        *prev_state = WELCOME;
      }
      break;
    case NEXT_ARROW:
      hover_arrow(RIGHT);
      if (button_press == SINGLE) {
        *curr_state = DIFFICULTY_MODE;
        *prev_state = WELCOME;
      }
      break;
  }
  disp.display();
}

void I2C_about_screen (int selector, int button_press, state *curr_state, state *prev_state, page *page_no) {
  switch (*page_no) {
    case PAGE_ZERO:
      I2C_about_initial_static();
      switch (selector) {
        case LEFT_ARROW:
          hover_arrow(LEFT);
          if (button_press == SINGLE) {
            *page_no = PAGE_TWO;
          }
          break;
        case EXIT_BTN:
          exit_state(button_press, curr_state, prev_state, page_no);
          break;
        case RIGHT_ARROW:
          hover_arrow(RIGHT);
          if (button_press == SINGLE) {
            *page_no = PAGE_ONE;            
          }
          break;
      }
      break;
    case PAGE_ONE:
      I2C_about_second_static();
      switch (selector) {
        case LEFT_ARROW:
          hover_arrow(LEFT);
          if (button_press == SINGLE) {
            *page_no = PAGE_ZERO;            
          }
          break;
        case EXIT_BTN:
          exit_state(button_press, curr_state, prev_state, page_no);
        break;
        case RIGHT_ARROW:
        hover_arrow(RIGHT);
        if (button_press == SINGLE) {
          *page_no = PAGE_TWO;
        }
        break;
     }
     break;
    case PAGE_TWO:
      I2C_about_third_static();
      switch (selector) {
        case LEFT_ARROW:
          hover_arrow(LEFT);
          if (button_press == SINGLE) {
            *page_no = PAGE_ONE;
          }
          break;
        case EXIT_BTN:
          exit_state(button_press, curr_state, prev_state, page_no);
          break;
        case RIGHT_ARROW:
          hover_arrow(RIGHT);
          if (button_press == SINGLE) {
            *page_no = PAGE_ZERO;
          }
          break;
      }
      break;  
    }
  disp.display();
}

void I2C_difficulty_mode_screen (int selector, int button_press, state *curr_state, state *prev_state) {
  // Call the generic selection screen, with no highlighted figures
  I2C_difficulty_mode_static();
  switch (selector) {
    case EASY_BTN:
      hover_text("Easy", EASY_CURSOR, DIFFICULTY_MODE_HOVER_LENGTH, DIFFICULTY_MODE_HOVER_HEIGHT, WHITE);
      break;
    case MED_BTN:
      hover_text("Medium", MED_CURSOR, DIFFICULTY_MODE_HOVER_LENGTH, DIFFICULTY_MODE_HOVER_HEIGHT, WHITE);
      break;
    case HARD_BTN:
      hover_text("Hard", HARD_CURSOR, DIFFICULTY_MODE_HOVER_LENGTH, DIFFICULTY_MODE_HOVER_HEIGHT, WHITE);
      break;
    case FREE_MODE_BTN:
      hover_text("Free Mode", FREE_MODE_CURSOR, DIFFICULTY_MODE_HOVER_LENGTH, DIFFICULTY_MODE_HOVER_HEIGHT, WHITE);
      break;
  }
  // Display the newly selected option
  disp.display();
}

void I2C_help_screen (int *selector, int button_press, state *curr_state, state *prev_state, page *page_no) {
  I2C_help_static();
  switch (*selector) {
    case ABOUT_BTN:
      hover_text("About", ABOUT_HELP_CURSOR, HELP_HOVER_LENGTH, HELP_HOVER_HEIGHT, WHITE);
      if (button_press == SINGLE) {
        *curr_state = ABOUT;
        *page_no = PAGE_ZERO;
      }
      break; 
    case RESET_BTN:
      hover_text("Reset", RESET_CURSOR, HELP_HOVER_LENGTH, HELP_HOVER_HEIGHT, WHITE);
      if (button_press == SINGLE) {
        *curr_state = WELCOME;
        *prev_state = WELCOME;
        *page_no = PAGE_ZERO;
        *selector = 0;
      }
      break;
    case INSTR_BTN:
      hover_text("Instructions", INSTR_CURSOR, HELP_HOVER_LENGTH, HELP_HOVER_HEIGHT, WHITE);
      if (button_press == SINGLE) {
        *curr_state = INSTRUCTIONS;
      }
      break;
    case BACK_BTN:
      hover_text("Back", BACK_CURSOR, HELP_HOVER_LENGTH, HELP_HOVER_HEIGHT, WHITE);
      if (button_press == SINGLE) {
        *curr_state = *prev_state;
      }
      break;
  }
  disp.display();
}

void I2C_instruction_selection_0 (int selector) {
 // if (selector == EXIT
 // switch (page_no)
//  I2C_instruction_initial_static();
  // TODO: Switch statement to switch between next, back, and exit buttons
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

void I2C_welcome_static () {
  // Welcome header text
  disp.clearDisplay();
  I2C_init_text(SMALL_TXT,TOP);
  disp.println("Welcome to");
  disp.println("YDigi Puzzle Box!");
  // "About" and arrow buttons
  draw_arrow(RIGHT,WHITE);
  I2C_init_text(SMALL_TXT, 55);
  disp.println("About");
}

void I2C_about_initial_static () {
  disp.clearDisplay();
  // About heading
  I2C_init_text(SMALL_TXT,TOP);
  disp.println("ABOUT (1/3)");
  // About text
  I2C_init_text(SMALL_TXT, 14);
  disp.println("YDigi Puzzle is a");
  disp.println("project for CPSC 338");
  disp.println("by Tanya Shibu and");
  disp.println("Spencer Strelsov.");
  draw_arrow(WHITE,LEFT);
  draw_exit(WHITE);
  draw_arrow(RIGHT,WHITE);
}

void I2C_about_second_static () {
  disp.clearDisplay();
  // About (2/3) heading
  I2C_init_text(SMALL_TXT,TOP);
  disp.println("ABOUT (2/3)");
  // About text
  I2C_init_text(SMALL_TXT, 14);
  disp.println("YDigi stands for Yale");
  disp.println("Digital Systems. Our");
  disp.println("project is a puzzle");
  disp.println("box!");
  draw_arrow(WHITE, LEFT);
  draw_exit(WHITE);
  draw_arrow(WHITE,RIGHT);
}

void I2C_about_third_static () {
  disp.clearDisplay();
  // About (3/3) heading
  I2C_init_text(SMALL_TXT,TOP);
  disp.println("ABOUT (3/3)");
  // About Text
  I2C_init_text(SMALL_TXT, 13);
  disp.println("To reach the help");
  disp.println("screen at any time,");
  disp.println("do a long button");
  disp.println("press on the rotary");
  disp.println("encoder!");
  draw_arrow(WHITE,LEFT);
  draw_exit(WHITE);
  draw_arrow(WHITE,RIGHT);
}

void I2C_difficulty_mode_static () {
  disp.clearDisplay();
  // "Select difficulty" heading
  I2C_init_text(SMALL_TXT,TOP);
  disp.println("Select difficulty:");
  // Puzzle box difficulty buttons
  I2C_init_text(SMALL_TXT,20);
  disp.println("Easy");
  disp.println("Medium");
  disp.println("Hard");
  disp.println("Free Mode");
}

void I2C_help_static () {
  disp.clearDisplay();
  // HELP heading
  I2C_init_text(MED_TXT,TOP);
  disp.println("HELP");
  // Help buttons
  I2C_init_text(SMALL_TXT,20);
  disp.println("About");
  disp.println("Instructions");
  disp.println("Reset");
  disp.println("Back");
}

void I2C_instruction_initial_static () {
  disp.clearDisplay();
  I2C_init_text(SMALL_TXT,TOP);
  disp.println("YDigi stands for Yale");
  disp.println("Digital Systems. Our");
  disp.println("project is a puzzle");
  disp.println("box, so that's where");
  disp.println("our name comes from!");
 // disp.println("selecting the difficulty level, your goal");
// disp.println("will be to solve each puzzle. After every puzzle");
 // disp.println("you solve, you will unlock a digit of the box's");
//  disp.println("combination lock. Once you get the 3-digit code, enter");
//  disp.println("it using the rotary encoder to open the lid of the box!");
  draw_arrow(WHITE,LEFT);
  draw_exit(WHITE);
  draw_arrow(WHITE,RIGHT);
  disp.display();
}
 /*************************************************************************
 *
 *  Multi-Page Screen Helper Functions:
 *  - The following are helper functions to help modulate code for paginated
 *    screens like ABOUT and INSTRUCTIONS.
 *
 **************************************************************************
 */

 void exit_state (int button_press, state *curr_state, state *prev_state, page *page_no) {
  // Hover over the exit button
  hover_exit();
  if (button_press == SINGLE) {
    // If the prev_state == curr_state, then we are coming back from the HELP screen after clicking the "back" button.
    if (*prev_state == *curr_state) {
      // We must compensate by going back to the Welcome screen
      *curr_state = WELCOME;
      *prev_state = WELCOME;
    } else {
      // Exit back to 
      *curr_state = *prev_state;
    }
    *page_no = PAGE_ZERO; 
  }
 }


 /*************************************************************************
 *
 *  Animation Helper Functions:
 *  - The following are helper functions to help animate button clicks,
 *    hovers, and symbols like arrows.
 *
 **************************************************************************
 */


void blink_animation(int text_y, int selector) {
 //   I2C_selection_screen();
//  hover_text(text_y, selector, BLACK);
  delay(300);
//  hover_text(text_y, selector, WHITE);
  delay(300);
 //// hover_text(text_y, selector, BLACK);
  delay(300);
 // hover_text(text_y, selector, WHITE);
}

void hover_text(const char *str, int text_y, int highlight_length, int highight_height, uint16_t hover_color) {
  // Set the text to the opposite color of the hover_color. Useful for blinking text.
  if (hover_color == WHITE) {
    disp.setTextColor(BLACK);
  } else {
    disp.setTextColor(WHITE);
  }
  // Maintain the location for writing text when hovering
  disp.setCursor(LEFT_INDENT, text_y);
  // Fill a white rectangle behind the text
  disp.fillRect(LEFT_INDENT, text_y-1, highlight_length, highight_height, hover_color);
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
