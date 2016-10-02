////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016 Custom FX. All right reserved.
//
// Basic example 09: LED strip Sweep Change Color
//
// This example shows how to control the color of the sweep animation with a 
// button. Everytime you press the button, the animation will change to a 
// random color.
//
// This file is part of the Custom FX library. This library was developed in 
// order to make Arduino programming as easy as possible. For more information,
// visit our website: http://www.customfx.nl
//
////////////////////////////////////////////////////////////////////////////////

#include <CustomFX.h>

CFX_LedStrip ledstrip(2, 20);    // Connect ledstrip to pin 2
CFX_Color color(12, 25, 115);    // initial color
CFX_LedStripAnimationSweep sweep(color, 20, 350, &ledstrip); // setup sweep, speed 20 msec per led, fade out time is 350 msec
CFX_Button button(7, 101);      // connect button to pin 7

void setup() 
{
}

void handleInput(int id, int command, int value)
{
  if (id == 101)
  {
    if (command == CFX_CMD_BUTTON_CLICK)
    {
      sweep.SetColor(CFX_Color(random(0,0xffffff))); // set new random color
    }
  }
}

void loop() 
{
  CFX_InputController::GetInstance()->ReadInputs();
  CFX_AnimationController::GetInstance()->UpdateAnimation();
}
