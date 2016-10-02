////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016 Custom FX. All right reserved.
//
// Advanced example 03: Button
//
// This example shows hoe to use all commands received from a button:
// - single click: turn LED 1 on
// - double click: turn LED 1 off
// - click and hold: fade LED 1 on and off
// - when pressing and releaseing the button, LED 2 will be turned on and off
//
// This file is part of the Custom FX library. This library was developed in 
// order to make Arduino programming as easy as possible. For more information,
// visit our website: http://www.customfx.nl
//
////////////////////////////////////////////////////////////////////////////////

#include <CustomFX.h>

CFX_Button button1(7, 101);  // Connect button to pin 7 with id 101
CFX_Led led1(3);             // Connect Led to pin 3
CFX_Led led2(5);             // Connect second Led to pin 5
int brightness;              // variable to store the brightness
bool led_on = false;         // led is initially off

void setup() 
{
}

void handleInput(int id, int command, int value)
{
  switch(id)
  {
    case 101: // handle input events from button1
    switch(command)
    {
      case CFX_CMD_BUTTON_PRESSED: // turn led 2 on
      led2.SetBrightness(255);
      break;

      case CFX_CMD_BUTTON_RELEASED: // turn led 2 off
      led2.SetBrightness(0);
      break;
      
      case CFX_CMD_BUTTON_CLICK: // turn led on
      brightness = 255;
      led_on = true;
      break;
      
      case CFX_CMD_BUTTON_DOUBLE_CLICK: // turn led off
      brightness = 0;
      led_on = false;
      break;
      
      case CFX_CMD_BUTTON_CLICK_AND_HOLD: // fade led
      if (led_on)
      {
        // fade out
        brightness--;
        if (brightness < 0)
        {
          brightness = 0;
          led_on = false;
        }
      }
      else
      {
        // fade in
        brightness++;
        if (brightness > 255)
        {
          brightness = 255;
          led_on = true;
        }
      }
      break;
    }
    led1.SetBrightness(brightness);
    break;
  }
}

void loop() 
{
  CFX_InputController::GetInstance()->ReadInputs();
  CFX_AnimationController::GetInstance()->UpdateAnimation();
}
