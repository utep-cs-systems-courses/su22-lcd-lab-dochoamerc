/** \file lcddemo.c
 *  \brief A simple demo that draws a string and square
 */

#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"

/** Initializes everything, clears the screen, draws "hello" and a square */
int
main()
{
  configureClocks();
  lcd_init();
  u_char width = screenWidth, height = screenHeight;

  clearScreen(COLOR_BLUE);
  drawString5x7(20,20, "TRIAL", COLOR_RED, COLOR_YELLOW);
  // drawString11x16(30,30, "Test", COLOR_RED, COLOR_YELLOW);
  drawString8x12(30,30, "TRIAL", COLOR_RED, COLOR_YELLOW);

  // fillRectangle(30,30, 60, 60, COLOR_ORANGE);
  /*
  int col = 20, row = 80;
  int step = 1;
  for(int i =-25; i <= 25; i++) {
    drawPixel(col+i, row+i, COLOR_PINK);
    drawPixel(col+i, row-i, COLOR_BLACK);
  }
  */
}
