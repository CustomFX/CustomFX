////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016 Custom FX. All right reserved.
//
// Basic example 15: RGBLed Fade to Color
//
// This example shows how to change the color of the RGB Led using a fade effect.
// Each time you press the button, the color will fade to the next random color.
// Double clicking the button will slowly turn off the Led.
//
// This file is part of the Custom FX library. This library was developed in 
// order to make Arduino programming as easy as possible. For more information,
// visit our website: http://www.customfx.nl
//
////////////////////////////////////////////////////////////////////////////////

#include <CustomFX.h>

CFX_RGBLed led1(11, 10, 9, true);             // Connect RGB Led to pin 11 (red), 10 (green and 9 (blue)
CFX_RGBLedAnimationFadeToColor fader(&led1);  // Create animation for fading
CFX_Button button(7, 101);

void setup() 
{
  CFX_Color color(12, 25, 115);   // initial color
  fader.FadeToColor(color, 100);  // Start fader. The Led will fade to the color in 1 second
}

void handleInput(int id, int command, int value)
{
  if (id == 101)
  {
    if (command == CFX_CMD_BUTTON_CLICK)
    {
      fader.FadeToColor(CFX_Color(random(0,0xffffff)), 100); // fade to new random color
    }
    else if (command == CFX_CMD_BUTTON_DOUBLE_CLICK)
    {
      fader.FadeToColor(CFX_Color(0), 1000); // fade out
    }
  }
}

void loop() 
{
  CFX_InputController::GetInstance()->ReadInputs();
  CFX_AnimationController::GetInstance()->UpdateAnimation();
}
