////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016 Custom FX. All right reserved.
//
// Basic example 13: RGB Simple Fade
//
// This example demonstrates the fade animation in combination with a button
// Pressing the button will fade the LED on or off.
//
// This file is part of the Custom FX library. This library was developed in 
// order to make Arduino programming as easy as possible. For more information,
// visit our website: http://www.customfx.nl
//
////////////////////////////////////////////////////////////////////////////////

#include <CustomFX.h>

CFX_RGBLed rgbled(11, 10, 9, true);
CFX_RGBLedAnimationFadeToColor fader(&rgbled);
CFX_Button button(7, 100);
bool faded_in = false;
CFX_Color color(125, 125, 0); // target color to fade to

void setup() 
{
  fader.FadeToColor(CFX_Color(0), 0);
}

void handleInput(int id, int command, int value)
{
  if (id == 100 && command == CFX_CMD_BUTTON_CLICK)
  {
    if (faded_in)
    {
      // fade to 0 in 2 seconds
      fader.FadeToColor(CFX_Color(0, 0, 0), 2000);
      faded_in = false;
    }
    else
    {
      // fade to color in 2 seconds
      fader.FadeToColor(color, 2000);
      faded_in = true;
    }
  }
}

void loop() 
{
  CFX_InputController::GetInstance()->ReadInputs();
  CFX_AnimationController::GetInstance()->UpdateAnimation();
}
