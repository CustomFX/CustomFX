////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016 Custom FX. All right reserved.
//
// Advanced example 07: Button RGB fader
//
// After clicking the button, a new color will be generated and a fade in
// and fade out will start using that color.
//
// This file is part of the Custom FX library. This library was developed in
// order to make Arduino programming as easy as possible. For more information,
// visit our website: http://www.customfx.nl
//
////////////////////////////////////////////////////////////////////////////////

#include <CustomFX.h>

CFX_RGBLed led1(11, 10, 9, true);             // Connect RGB Led to pin 11 (red), 10 (green and 9 (blue)
CFX_RGBLedAnimationFadeToColor fader(&led1);  // Create animation for fading
CFX_Timer timer(101);                         // create timer with id 101
CFX_Button button1(7, 102);                   // Connect button to pin 10 with id 101
CFX_Color no_color(0, 0, 0);

void setup()
{
}

void handleInput(int id, int command, int value)
{
  switch (id)
  {
    case 101: // timer
      if (command == CFX_CMD_TIMER_EVENT)
      {
        fader.FadeToColor(no_color, 900);
      }
      break;

    case 102:
      if (command == CFX_CMD_BUTTON_CLICK)
      {
        fader.FadeToColor(CFX_Color(random(0, 0xffffff)), 900); // set new color
        timer.SetTimer(1000, false);       // start timer to fade out the LED
      }
      break;
  }
}

void loop()
{
  CFX_InputController::GetInstance()->ReadInputs();
  CFX_AnimationController::GetInstance()->UpdateAnimation();
}
