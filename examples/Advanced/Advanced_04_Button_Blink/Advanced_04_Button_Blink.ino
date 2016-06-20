////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016 Custom FX. All right reserved.
//
// Advanced example 04: Button and Blink
//
// This example will show you how use animations and input in one program. The
// button is uses as follows:
// - single click, turn LED on and off
// - double click, start blinking
// - click and hold, fade in and out
//
// This file is part of the Custom FX library. This library was developed in 
// order to make Arduino programming as easy as possible. For more information,
// visit our website: http://www.customfx.nl
//
////////////////////////////////////////////////////////////////////////////////

#include <CustomFX.h>

CFX_Button button1(7, 101);  // Connect button to pin 10 with id 101
CFX_Led led(3);              // Connect Led to pin 3
CFX_LedAnimationBlink blink1(500, 250, &led); // blink animation
int brightness;
bool led_on = false;

void setup() 
{
  blink1.Stop(); // the blink animation is initially off
}

void handleInput(int id, int command, int value)
{
  switch(id)
  {
    case 101: // handle input events from button1
    switch(command)
    {
      case CFX_CMD_BUTTON_CLICK: 
      blink1.Stop(); // stop blink animation is it was running
      if (led_on) // turn led on
      {
        brightness = 0;
        led_on = false;
      }
      else // turn led off
      {
        brightness = 255;
        led_on = true;
      }
    break;
      
      case CFX_CMD_BUTTON_DOUBLE_CLICK: // blink
      blink1.Start();
      break;
      
      case CFX_CMD_BUTTON_CLICK_AND_HOLD: // fade led
      blink1.Stop(); // stop blink animation is it was running
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
    led.SetBrightness(brightness);
    break;
  }
}

void loop() 
{
  CFX_InputController::GetInstance()->ReadInputs();
  CFX_AnimationController::GetInstance()->UpdateAnimation();
}
