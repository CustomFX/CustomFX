////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016 Custom FX. All right reserved.
//
// Basic example 06: LED strip Blink
//
// This example shows how to create a blink effect for an LED strip using a 
// single constant color
//
// This file is part of the Custom FX library. This library was developed in 
// order to make Arduino programming as easy as possible. For more information,
// visit our website: http://www.customfx.nl
//
////////////////////////////////////////////////////////////////////////////////

#include <CustomFX.h>

CFX_LedStrip ledstrip(2, 20);   // Connect ledstrip to pin 2
CFX_LedAnimationBlink blink1(250, 250, &ledstrip); // blink for 250 milliseconds on and off

void setup() 
{
  CFX_Color color(12, 25, 115);  // create color
  ledstrip.SetColor(color);      // set color
}

void handleInput(int id, int command, int value)
{
}

void loop() 
{
  CFX_Run();
}
