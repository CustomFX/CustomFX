////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016 Custom FX. All right reserved.
//
// Advanced example 04: Button and Blink
//
// This example will show you how use animations and input in one program. The
// button is uses as follows:
// - single click, turn LED on and off
// - double click, start blinking
// - click and hold, fade in and out
//
// This file is part of the Custom FX library. This library was developed in
// order to make Arduino programming as easy as possible. For more information,
// visit our website: http://www.customfx.nl
//
////////////////////////////////////////////////////////////////////////////////

#include <CustomFX.h>

CFX_Button button1(7, 101, CFX_Low_Input);  // Connect button to pin 10 with id 101
CFX_Led led(3);              // Connect Led to pin 3
CFX_LedAnimationBlink blink1(500, 250, &led); // blink animation
CFX_LedAnimationFadeInOut fader(1000, 500, 1000, 500, &led);

void setup()
{
  blink1.Stop(); // the blink animation is initially off
  fader.Stop();  // the fade animation is also initially off
}

void handleInput(int id, int command, int value)
{
  if (id == 101)
  {
    if (command == CFX_CMD_BUTTON_PRESSED)
    {
      blink1.Stop(); // stop blink animation is it was running
    }
    else if (command == CFX_CMD_BUTTON_RELEASED)
    {
      fader.Stop(); // stop the fader once you release the button
    }
    else if (command == CFX_CMD_BUTTON_CLICK)
    {
      // toggle the led brightness
      if (led.GetBrightness() == 0)
      {
        led.SetBrightness(255);
      }
      else // turn led off
      {
        led.SetBrightness(0);
      }
    }
    else if (command == CFX_CMD_BUTTON_DOUBLE_CLICK)
    {
      blink1.Start(); // start blinking on doubleclick
    }
    else if (command == CFX_CMD_BUTTON_CLICK_AND_HOLD)
    {
      if (!fader.IsActive()) // start the fade animation if it hasn't already started
      {
        fader.Start();
      }
    }
  }
}

void loop()
{
  CFX_Run();
}
