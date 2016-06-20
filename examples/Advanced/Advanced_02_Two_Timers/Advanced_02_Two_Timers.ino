////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016 Custom FX. All right reserved.
//
// Advanced example 02: Two Timers
//
// This example will show you how to use two timers. The first timer will turn 
// the LED on, the second timer will turn the LED off.
//
// This file is part of the Custom FX library. This library was developed in 
// order to make Arduino programming as easy as possible. For more information,
// visit our website: http://www.customfx.nl
//
////////////////////////////////////////////////////////////////////////////////

#include <CustomFX.h>

CFX_Led led1(3);              // Connect Led to pin 3
CFX_Timer on_timer(101);
CFX_Timer off_timer(102);

void setup() 
{
  on_timer.SetTimer(1004, true); // This timer will turn the LED on
  off_timer.SetTimer(875, true); // This timer will turn the LED off
}

void handleInput(int id, int command, int value)
{
  switch(id)
  {
    case 101: // on_timer event, turn led on
    if (command == CFX_CMD_TIMER_EVENT)
    {
      led1.SetBrightness(255);
    }
    break;

    case 102: // off_timer event, turn led off
    if (command == CFX_CMD_TIMER_EVENT)
    {
      led1.SetBrightness(0);
    }
    break;
  }
}

void loop() 
{
  CFX_InputController::GetInstance()->ReadInputs();
  CFX_AnimationController::GetInstance()->UpdateAnimation();
}
