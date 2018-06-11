////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016 Custom FX. All right reserved.
//
// Basic example 14: RGBLed Color Rotation
//
// This example shows how to change the color of the RGB Led by pressing a
// button. With each press the color will change to the next random color. 
// Double clicking the button will turn the Led off.
//
// This file is part of the Custom FX library. This library was developed in 
// order to make Arduino programming as easy as possible. For more information,
// visit our website: http://www.customfx.nl
//
////////////////////////////////////////////////////////////////////////////////

#include <CustomFX.h>

CFX_RGBLed led1(11, 10, 9, true);  // Connect RGB Led to pin 11 (red), 10 (green and 9 (blue)
CFX_Button button(7, 101);         // Connect button to pin 7

void setup() 
{
  CFX_Color color(0,94,255); // create color
  led1.SetColor(color);      // Set color
}

void handleInput(int id, int command, int value)
{
  if (id == 101)
  {
    if (command == CFX_CMD_BUTTON_CLICK)
    {
      led1.SetColor(CFX_Color(random(0,0xffffff))); // set new random color
    }
    else if (command == CFX_CMD_BUTTON_DOUBLE_CLICK)
    {
      led1.SetColor(CFX_Color(0)); // turn Led off
    }
  }
}

void loop() 
{
  CFX_Run();
}
