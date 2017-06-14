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
// Fade animation
// Fade in in 500 ms, stay on for 1 second, fade out in 250 msec finally stay off for 500 msec
CFX_LedAnimationFadeInOut fader(500, 1000, 250, 500, &led1);  

void setup()
{
}

void handleInput(int id, int command, int value)
{
}

void loop()
{
  CFX_Run();
}
