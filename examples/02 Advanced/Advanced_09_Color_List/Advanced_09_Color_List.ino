////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016 Custom FX. All right reserved.
//
// Advanced example : Color list
//
// This example shows how to create a list of colors and use this to change
// the color of an RGB LED.
//
// This file is part of the Custom FX library. This library was developed in 
// order to make Arduino programming as easy as possible. For more information,
// visit our website: http://www.customfx.nl
//
////////////////////////////////////////////////////////////////////////////////

#include <CustomFX.h>

CFX_RGBLed led1(11, 10, 9, true);                 // Connect RGB Led to pin 11 (red), 10 (green) and 9 (blue)
CFX_RGBLedAnimationFadeToColor colorfade(&led1);  // fade animation
CFX_Timer timer(101);                             // create a time with id 101
int color = 0;            // variable to indicate the current color
const int maxcolors = 8;  // constant to indicate the total number of colors
// create an array of colors
CFX_Color colors[maxcolors] = { CFX_Color(   0,   0,   0 ), 
                                CFX_Color( 255,   0,   0 ),
                                CFX_Color( 125, 125,   0 ),
                                CFX_Color( 255, 255,   0 ),
                                CFX_Color(   0, 255, 255 ),
                                CFX_Color(   0,   0, 255 ),
                                CFX_Color( 255,   0, 255 ),
                                CFX_Color( 255, 255, 255 )};

void setup() 
{
  timer.SetTimer(2000, true); // set timer to 2 second interval, repeating
  colorfade.FadeToColor(colors[color], 0); // set first color
}

void handleInput(int id, int command, int value)
{
  switch (id)
  {
    case 101:
      // timer went off, set new color
      color++;
      if (color >= maxcolors) color = 0; // start with the start of the list if the end is reached
      colorfade.FadeToColor(colors[color], 2000); // set next color
    break;
  }
}

void loop() 
{
  CFX_Run();
}
