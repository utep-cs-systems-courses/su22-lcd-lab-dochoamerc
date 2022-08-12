#include <msp430.h>
#include <libTimer.h>
#include "switches.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "screenChange.h"

// WARNING: LCD DISPLAY USES P1.0.  Do not touch!!!

#define LED BIT6/* note that bit zero req'd for display */

short redrawScreen = 1;
u_int background = COLOR_MAGENTA;
u_int letters = COLOR_KHAKI;
unsigned char step = 0;
static char colorRotation = 0;

// axis zero for col, axis 1 for row
short drawPos[2] = {1,10}, controlPos[2] = {2, 10};
short colVelocity = 1, colLimits[2] = {1, screenWidth/2};

static int button = 0;
void wdt_c_handler()
{
  static int secCount = 0;

  secCount ++;
  if (secCount >= 25) {/* 10/sec */
    {/* move ball */
      short oldCol = controlPos[0];
      short newCol = oldCol + colVelocity;
      if (newCol <= colLimits[0] || newCol >= colLimits[1])
	colVelocity = -colVelocity;
      else
	controlPos[0] = newCol;
    }

    {// update screen 
      if (switches & SW3) {
	button = 3;
	step = 0;
	clearScreen(background);
      }   
      if (switches & SW2) {
	button = 2;
	step = 0;
	drawString11x16(1,1, "2 IS BAD", COLOR_RED, COLOR_WHITE);
	clearScreen(COLOR_WHITE);
      }   
      if (switches & SW1) {
	button = 1;
	step = 0;
	clearScreen(background);
      }   
      if (step <= 40)
	step ++;
      else
	step = 0;
      secCount = 0;
    }

    if (switches & SW4){
      button = 4;
      step = 0;
      clearScreen(background);
      return;
    }
    redrawScreen = 1;
  }
}

void shape_choice();

static unsigned char row = screenHeight / 2, col = screenWidth / 2;
static char lastStep = 0;
void screen_update_shape()
{
  if (step == 0 || (lastStep > step)) {
    screenChange();
    clearScreen(background);
    lastStep = 0;
  } else {
    shape_choice();
  }
}

void shape_choice()
{
  for (; lastStep <= step; lastStep++) {
    int startCol = col - lastStep;
    int endCol = col + lastStep;
    int width = 1 + endCol - startCol;
    
    switch(button) {
    case 4: 
      drawString5x7(10,20, "Right Arrow", letters, background);    
      // right
      drawRectOutline((startCol+startCol/2), row+lastStep, 1, 1, COLOR_ORANGE); //down-diagonal
      drawRectOutline((startCol+startCol/2), row-lastStep, 1, 1, COLOR_ORANGE); //up-diagonal
      drawRectOutline((startCol+startCol/2)-lastStep, row, 1, 1, COLOR_ORANGE); // horizontal
      break;
    case 3:    
      drawString5x7(10,20, "Down Arrow", letters, background);
      //down
      drawRectOutline((col-lastStep),((row/2)+startCol), 1, 1, COLOR_GREEN); // diagonal-left
      drawRectOutline((col+lastStep),((row/2)+startCol), 1, 1, COLOR_GREEN); // diagonal-right
      drawRectOutline(col,(((row/2)+startCol)-lastStep), 1, 1, COLOR_GREEN); // vertical
      break;
    case 2:
      drawString5x7(10,20, "Up Arrow", letters, background);
      //up
      drawRectOutline(col,((row/2)+(2*lastStep)), 1, 1, COLOR_BLACK); // vertical
      drawRectOutline(col-lastStep,((row/2)+lastStep), 1, 1, COLOR_BLACK); // diagonal-left
      drawRectOutline(col+lastStep,((row/2)+lastStep), 1, 1, COLOR_BLACK); //diagonal-right
      break;
    case 1:
      drawString5x7(10,20, "Left Arrow", letters, background);
      // left
      drawRectOutline((startCol/2)+(2*lastStep), row-lastStep, 1, 1, COLOR_WHITE); //up-diagonal
      drawRectOutline((startCol/2)+(2*lastStep), row+lastStep, 1, 1, COLOR_WHITE); //down-diagonal
      drawRectOutline((startCol/2)+(3*lastStep), row, 1, 1, COLOR_WHITE); // horizontal
      break;
    }
  }
}


void update_shape()
{
  screen_update_shape();
}

void main()
{

  P1DIR |= LED;/**< Green led on when CPU on */
  P1OUT |= LED;
  configureClocks();
  lcd_init();
  switch_init();

  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);              /**< GIE (enable interrupts) */

  clearScreen(background);
  while (1) {/* forever */
    if (redrawScreen) {
      redrawScreen = 0;
      update_shape();
    }
    P1OUT &= ~LED;/* led off */
    or_sr(0x10);/**< CPU OFF */
    P1OUT |= LED;/* led on */
  }
}


