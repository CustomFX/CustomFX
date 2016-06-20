////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016 Custom FX. All right reserved.
//
// Basic example RGBLed Fade
//
// This example shows how to create a fade animation for a single RGB LED. The
// difference with a single color LED is that you can specify the color. 
//
// This file is part of the Custom FX library. This library was developed in 
// order to make Arduino programming as easy as possible. For more information,
// visit our website: http://www.customfx.nl
//
////////////////////////////////////////////////////////////////////////////////

#include <CustomFX.h>

CFX_RGBLed led1(11, 10, 9, true);           // Connect RGB Led to pin 11 (red), 10 (green and 9 (blue)
CFX_RGBLedAnimationFadeInOut fader(&led1);  // Create color fader

void setup() 
{
  CFX_Color color(50,10,125); // create color
  fader.SetColor(color); // set fade color
  // Set timging:
  // fade to color in 2 seconds, stay color for 0 seconds, fade out in 1 second, stay off for 0 seconds
  fader.SetTimes(2000, 0, 1000, 0); 
}

void handleInput(int id, int command, int value)
{
}

void loop() 
{
  CFX_InputController::GetInstance()->ReadInputs();
  CFX_AnimationController::GetInstance()->UpdateAnimation();
}
