////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016 Custom FX. All right reserved.
//
// Advanced example 04: Button Parameters
//
// This example demonstrates disabling the double click option for a CFX_Button
// to eliminate the lag. The example shows a sweep animation on a LED strip. the
// example uses two buttons to control the animation. Both buttons can be used to
// stop and start the animation. Button 1 has the double click function disabled,
// button 2 has the double click function enabled. When using the buttons to start
// and stop the animation, the lag in button 2 is very noticable.
// Double clicking button 2 changes the color of the animation.
//
// This file is part of the Custom FX library. This library was developed in
// order to make Arduino programming as easy as possible. For more information,
// visit our website: http://www.customfx.nl
//
////////////////////////////////////////////////////////////////////////////////

#include <CustomFX.h>

CFX_Button button1(7, 101);   // Connect a button to pin 7 with id 101
CFX_Button button2(8, 102);   // Connect a second button to pin 8 with id 102
CFX_LedStrip ledstrip(2, 20); // Connect Led to pin 2
CFX_Color color(12, 25, 115);
CFX_LedStripAnimationSweep sweep(color, 50, 500, &ledstrip);

void setup()
{
  button1.DisableDoubleClick(true); // disable the double click function for button 1
}

void handleInput(int id, int command, int value)
{
  if (id == 101) // input from button 1
  {
    if (command == CFX_CMD_BUTTON_CLICK)
    {
      if (sweep.IsActive())
      {
        sweep.Stop(); // stop sweep
      }
      else
      {
        sweep.Start(); // start sweep
      }
    }
  }
  else if (id == 102) // input from button 2
  {
    if (command == CFX_CMD_BUTTON_CLICK)
    {
      if (sweep.IsActive())
      {
        sweep.Stop(); // stop sweep
      }
      else
      {
        sweep.Start(); // start sweep
      }
    }
    else if (command == CFX_CMD_BUTTON_DOUBLE_CLICK)
    {
      color = CFX_Color(random(0, 0xffffff)); // generate new color
      sweep.SetColor(color); // set new color
    }
  }
}

void loop()
{
  CFX_Run();
}
