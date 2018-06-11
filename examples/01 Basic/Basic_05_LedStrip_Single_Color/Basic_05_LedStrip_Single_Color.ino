////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016 Custom FX. All right reserved.
//
// Basic example 05: LED strip single color
//
// This example shows how to setup a LED strip and give it a single constant color
//
// This file is part of the Custom FX library. This library was developed in 
// order to make Arduino programming as easy as possible. For more information,
// visit our website: http://www.customfx.nl
//
////////////////////////////////////////////////////////////////////////////////

#include <CustomFX.h>

CFX_LedStrip ledstrip(2, 20);   // Connect ledstrip to pin 2
CFX_Color color(12, 25, 115);   // Create color

void setup() 
{
  ledstrip.SetColor(color); // set color
}

void handleInput(int id, int command, int value)
{
}

void loop() 
{
  CFX_Run();
}
