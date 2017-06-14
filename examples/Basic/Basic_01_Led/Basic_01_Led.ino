////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016 Custom FX. All right reserved.
//
// Basic example 01: LED
//
// This example shows how to setup a single LED and turn it on.
//
// This file is part of the Custom FX library. This library was developed in 
// order to make Arduino programming as easy as possible. For more information,
// visit our website: http://www.customfx.nl
//
////////////////////////////////////////////////////////////////////////////////

#include <CustomFX.h>

CFX_Led led1(3);                                 // Connect Led to pin 3

void setup() 
{
  led1.SetBrightness(255); // turn led on initially
}

void handleInput(int id, int command, int value)
{
}

void loop() 
{
  CFX_Run();
}
