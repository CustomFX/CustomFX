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

CFX_Led led1(3);                         // Connect a Led to pin 3
CFX_Led led2(5);                         // Connect second Led to pin 5

void setup()
{
  led1.SetBrightness(75);  // Let it glow
  led2.SetBrightness(255); // Turn second led on
}

void handleInput(int id, int command, int value)
{
}

void loop()
{
  CFX_Run();
}
