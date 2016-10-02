////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016 Custom FX. All right reserved.
//
// Advanced example 10: RGB Led Double animation
//
// This example shows how to use two animations on one output. The Color blink
// animates the color. The FadeImOut animations animates the brightness.
//
// This file is part of the Custom FX library. This library was developed in
// order to make Arduino programming as easy as possible. For more information,
// visit our website: http://www.customfx.nl
//
////////////////////////////////////////////////////////////////////////////////

#include <CustomFX.h>

CFX_RGBLed led1(11, 10, 9, true);             // Connect RGB Led to pin 11 (red), 10 (green and 9 (blue)
CFX_Color color(12, 25, 115);
CFX_RGBLedAnimationColorBlink colorblink(250, 250, color, &led1);  // blink animation
CFX_LedAnimationFadeInOut fade(1000, 0, 1000, 0, &led1);           // fade animation

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
