////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016 Custom FX. All right reserved.
//
// Basic example RGB Blink
//
// This example shows how to create a blink animation for a single RGB LED. The
// difference with a single color LED is that you can specify the color. 
//
// This file is part of the Custom FX library. This library was developed in 
// order to make Arduino programming as easy as possible. For more information,
// visit our website: http://www.customfx.nl
//
////////////////////////////////////////////////////////////////////////////////

#include <CustomFX.h>

CFX_RGBLed led1(11, 10, 9, true);                // Connect RGB Led to pin 11 (red), 10 (green and 9 (blue)
CFX_LedAnimationBlink blink1(1000, 500, &led1);  // Blink led for 1 second on and 0,5 seconds off

void setup() 
{
  CFX_Color color(0x005eff); // define color using hexadecimal representation. Alternatively use 3 color components (0,94,255)
  led1.SetColor(color);  // Set color of the led
}

void handleInput(int id, int command, int value)
{
}

void loop() 
{
  CFX_InputController::GetInstance()->ReadInputs();
  CFX_AnimationController::GetInstance()->UpdateAnimation();
}
