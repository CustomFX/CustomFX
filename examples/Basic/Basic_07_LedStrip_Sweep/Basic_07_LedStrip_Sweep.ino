////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016 Custom FX. All right reserved.
//
// Basic example LED strip Sweep
//
// This example shows how to create a sweep animation with a LED strip with 
// 20 LEDs
//
// This file is part of the Custom FX library. This library was developed in 
// order to make Arduino programming as easy as possible. For more information,
// visit our website: http://www.customfx.nl
//
////////////////////////////////////////////////////////////////////////////////

#include <CustomFX.h>

CFX_LedStrip ledstrip(2, 20);    // Connect ledstrip to pin 2
CFX_Color color(12, 25, 115);    // create color
CFX_LedStripAnimationSweep sweep(color, 20, 350, &ledstrip); // setup sweep, speed 20 msec per led, trail is 350 msec

void setup() 
{
}

void handleInput(int id, int command, int value)
{
}

void loop() 
{
  CFX_InputController::GetInstance()->ReadInputs();
  CFX_AnimationController::GetInstance()->UpdateAnimation();
}
