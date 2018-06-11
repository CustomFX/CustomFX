////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016 Custom FX. All right reserved.
//
// Basic example 04: LED and Button
//
// This example shows how to use a button to turn a LED on and off. Press the 
// button once will turn on the LED. Pressing it again will turn the LED off.
//
// This file is part of the Custom FX library. This library was developed in 
// order to make Arduino programming as easy as possible. For more information,
// visit our website: http://www.customfx.nl
//
////////////////////////////////////////////////////////////////////////////////

#include <CustomFX.h>

CFX_Led led1(3);           // connect LED to pin 3
CFX_Button button(7, 101); // connect button to pin 7
int led_on = false;        // led is initially off

void setup() 
{
}

void handleInput(int id, int command, int value)
{
  if (id == 101)
  {
    if (command == CFX_CMD_BUTTON_CLICK)
    {
      if (led_on)
      {
        led1.SetBrightness(0);
        led_on = false;
      }
      else
      {
        led1.SetBrightness(255);
        led_on = true;
      }
    }
  }
}

void loop() 
{
  CFX_Run();
}
