////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016 Custom FX. All right reserved.
//
// Advanced example 08: Ledstrip Choose Color
//
// This example shows you how to control individual LEDs in a ledstrip. The first
// button generates a new random color. The second button selects the next LED
// in the ledstrip. A blink animation is used to indicate which LED is updated.
//
// This file is part of the Custom FX library. This library was developed in
// order to make Arduino programming as easy as possible. For more information,
// visit our website: http://www.customfx.nl
//
////////////////////////////////////////////////////////////////////////////////

#include <CustomFX.h>

const int max_led = 20;  // use a constant variable to define the number of LEDs
CFX_LedStrip ledstrip(2, max_led);     // Connect ledstrip to pin 2
CFX_LedStripPixel pixel(0, &ledstrip);                  // Create a Pixel from the first LED in the ledstrip. 
CFX_RGBLedAnimationColorBlink blink1(500, 500, &pixel); // The pixel is used for the Blink animation
CFX_Button button1(7, 101); // button 1 is used to pick new random color
CFX_Button button2(8, 102); // button 2 is used to select the next LED in the ledstrip
int led_nr = 0;
CFX_Color newcolor = CFX_Color(random(0, 0xffffff));

void setup()
{
  blink1.SetColor(newcolor); // set the color of the blinking pixel
}

void handleInput(int id, int command, int value)
{
  switch (id)
  {
    case 101:
      switch (command)
      {
        case CFX_CMD_BUTTON_CLICK: // generate new random color
          newcolor = CFX_Color(random(0, 0xffffff));
          blink1.SetColor(newcolor);
          break;
      }
      break;

    case 102:
      switch (command)
      {
        case CFX_CMD_BUTTON_CLICK: // move to next LED in ledstrip
          ledstrip.SetPixelColor(led_nr, newcolor); // set the color to the current color
          led_nr++;
          if (led_nr >= max_led) // when all LEDs are set, move to first LED again
          {
            led_nr = 0;
          }
          CFX_Color previous_color = ledstrip.GetPixelColor(led_nr); // get current color of the LED
          if (previous_color != CFX_Color(0)) // if the LED has a color set, use that color
          {
            newcolor = previous_color;
          }

          pixel.SetPixel(led_nr, &ledstrip); // set blink animation on the next LED
          blink1.SetColor(newcolor);
          break;
      }
      break;
  }
}

void loop()
{
  CFX_InputController::GetInstance()->ReadInputs();
  CFX_AnimationController::GetInstance()->UpdateAnimation();
}
