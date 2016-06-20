////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016 Custom FX. All right reserved.
//
// Advanced example 06: RGB Led fade
//
// This example uses a timer and a fader to change the color of an RGB LED.
// After the LED has faded in and out, a new color will be generated. 
//
// This file is part of the Custom FX library. This library was developed in 
// order to make Arduino programming as easy as possible. For more information,
// visit our website: http://www.customfx.nl
//
////////////////////////////////////////////////////////////////////////////////

#include <CustomFX.h>

CFX_RGBLed led1(11, 10, 9, true);           // Connect RGB Led to pin 11 (red), 10 (green and 9 (blue)
CFX_RGBLedAnimationFadeToColor fader(&led1);  // Create animation for fading
CFX_Timer timer(101);
bool led_on = false;
CFX_Color no_color(0,0,0);

void setup() 
{
  CFX_Color color(12, 25, 115);     // initial color
  timer.SetTimer(1000, true);       // 1 second timer to start fade in and out with changing colors
}

void handleInput(int id, int command, int value)
{
  if (id == 101)
  {
    if (command == CFX_CMD_TIMER_EVENT)
    {
      if (led_on)
      {
        fader.FadeToColor(no_color, 900);
        led_on = false;
      }
      else
      {
        fader.FadeToColor(CFX_Color(random(0,0xffffff)), 900);
        led_on = true;
      }
    }
  }
}

void loop() 
{
  CFX_InputController::GetInstance()->ReadInputs();
  CFX_AnimationController::GetInstance()->UpdateAnimation();
}
