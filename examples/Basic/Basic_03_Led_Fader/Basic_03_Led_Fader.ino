////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016 Custom FX. All right reserved.
//
// Basic example 03: LED Fader
//
// This example shows the fade in and fade out animation for a single LED.
//
// This file is part of the Custom FX library. This library was developed in 
// order to make Arduino programming as easy as possible. For more information,
// visit our website: http://www.customfx.nl
//
////////////////////////////////////////////////////////////////////////////////

#include <CustomFX.h>

CFX_Led led1(3);                         // Connect Led to pin 3
CFX_LedAnimationFadeInOut fader(&led1);  // Fade animation

void setup()
{
  // Set timging:
  // Fade in in 500 ms, stay on for 1 second, fade out in 250 msec finally stay off for 500 msec
  fader.SetTimes(500, 1000, 250, 500);
  fader.SetBrightness(255);  // The brightness when LED is on
}

void handleInput(int id, int command, int value)
{
}

void loop()
{
  CFX_InputController::GetInstance()->ReadInputs();
  CFX_AnimationController::GetInstance()->UpdateAnimation();
}
