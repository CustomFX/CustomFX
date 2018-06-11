////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016 Custom FX. All right reserved.
//
// Basic example 08: LED strip Sweep and button
//
// This example shows how to start and continue an animation. The LED strip is
// setup with a sweep animation. By pressing the button, you can start and stop
// the animation. If you double click animation will stop with a fade out
//
// This file is part of the Custom FX library. This library was developed in
// order to make Arduino programming as easy as possible. For more information,
// visit our website: http://www.customfx.nl
//
////////////////////////////////////////////////////////////////////////////////

#include <CustomFX.h>

CFX_LedStrip ledstrip(2, 20);    // Connect ledstrip to pin 2
CFX_Color color(12, 25, 115);    // create color
CFX_LedStripAnimationSweep sweep(color, 20, 350, &ledstrip); // setup sweep, speed 20 msec per led, fade out time is 350 msec
CFX_Button button(7, 101);       // connect a button to pin 7

void setup()
{
}

void handleInput(int id, int command, int value)
{
  if (id == 101)
  {
    if (command == CFX_CMD_BUTTON_CLICK)
    {
      if (sweep.IsActive())
      {
        sweep.Stop();
      }
      else
      {
        sweep.Start();
      }
    }
    else if (command == CFX_CMD_BUTTON_DOUBLE_CLICK)
    {
      sweep.Stop(true); // fade out and stop
    }
  }
}

void loop()
{
  CFX_Run();
}
