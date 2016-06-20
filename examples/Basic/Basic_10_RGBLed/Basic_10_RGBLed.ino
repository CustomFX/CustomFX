////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016 Custom FX. All right reserved.
//
// Basic example RGB LED
//
// This example shows how to use an RGB LED and turn it on with a specific color
//
// This file is part of the Custom FX library. This library was developed in 
// order to make Arduino programming as easy as possible. For more information,
// visit our website: http://www.customfx.nl
//
////////////////////////////////////////////////////////////////////////////////

#include <CustomFX.h>

// Connect common anode RGB LED to pin 11 (red), 10 (green) and 9 (blue)
// If you use a common cathode RGB LED, use 'false'
CFX_RGBLed rgbled(11, 10, 9, true);    

void setup()
{
  CFX_Color color1(125, 125, 0); // yellow color
  rgbled.SetColor(color1);
}

void handleInput(int id, int command, int value)
{
}

void loop() 
{
  CFX_InputController::GetInstance()->ReadInputs();
  CFX_AnimationController::GetInstance()->UpdateAnimation();
}
