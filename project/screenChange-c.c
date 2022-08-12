#include <msp430.h>
#include <libTimer.h>
#include "screenChange.h"
#include "lcdutils.h"

void screenChange() {
   static char colorRotation = 0;
    switch(colorRotation){
    case 0:
      colorRotation++;
      background = COLOR_RED;
      letters = COLOR_DEEP;
      break;
    case 1:
      colorRotation++;
      background = COLOR_DARK_GREEN;
      letters = COLOR_LIME_GREEN;
      break;
    case 2:
      colorRotation++;
      background = COLOR_BLUE;
      letters = COLOR_AQUAMARINE;
      break;
    case 3:
      colorRotation = 0;
      background = COLOR_PURPLE;
      letters = COLOR_HOT_PINK;
      break;
    default:
      colorRotation = 0;
      break;
    }
 }
