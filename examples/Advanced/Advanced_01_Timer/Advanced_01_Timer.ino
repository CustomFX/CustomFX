////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016 Custom FX. All right reserved.
//
// Advanced example 01: Timer
//
// This example will show you how to use a timer. The timer will turn the LED
// on and off. 
//
// This file is part of the Custom FX library. This library was developed in 
// order to make Arduino programming as easy as possible. For more information,
// visit our website: http://www.customfx.nl
//
////////////////////////////////////////////////////////////////////////////////

#include <CustomFX.h>

CFX_Led led(3);              // Connect Led to pin 3
CFX_Timer timer(101);        // create timer with id 101

void setup() 
{
  timer.SetTimer(1000, true); // This timer will turn the LED on
}

void handleInput(int id, int command, int value)
{
  if (id == 101 && command == CFX_CMD_TIMER_EVENT) // timer event
  {  
    if (led.GetBrightness() == 0)
    {
      led.SetBrightness(255); // turn led on
    }
    else
    {
      led.SetBrightness(0); // turn led off
    }
  }
}

void loop() 
{
  CFX_InputController::GetInstance()->ReadInputs();
  CFX_AnimationController::GetInstance()->UpdateAnimation();
}
