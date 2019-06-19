////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016-2019 Custom FX. All right reserved.
//
//
// Use this template to build you Custom FX project from scratch.
//
// Happy coding!
//
// This file is part of the Custom FX library. This library was developed in
// order to make Arduino programming as easy as possible. For more information,
// visit our website: http://www.customfx.nl
//
////////////////////////////////////////////////////////////////////////////////
#include <CustomFX.h>
#include <CFX_SpriteAnimationSequence.hpp>

//const PROGMEM byte open_eye[] = {0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0};
//const PROGMEM byte open_eye[] = {0x6F, 0xF6};
//const PROGMEM byte closing_eye1[] = {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0};
//const PROGMEM byte closing_eye1[] = {0x0F, 0xF6};
//const PROGMEM byte closing_eye2[] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0};
//const PROGMEM byte closing_eye2[] = {0x00, 0xF6};
//const PROGMEM byte closed_eye[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1};
//const PROGMEM byte closed_eye[] = {0x00, 0x0F };

const PROGMEM byte open_eye[] = {0x27, 0x77, 0x77, 0x77, 0x77, 0x20};
const PROGMEM byte mouth[] = {0x8B, 0x80};
const PROGMEM byte mouthopen[] = {0x5F, 0xFE, 0x80};
const PROGMEM byte closing_eye1[] = {0x0F, 0x77, 0x77, 0x77, 0x77, 0x20};
//const PROGMEM byte closing_eye2[] = {0x00, 0xF7, 0x77, 0x77, 0x77, 0x20};
const PROGMEM byte closing_eye2[] = {0x00, 0x0F, 0x77, 0x77, 0x77, 0x20};
const PROGMEM byte closed_eye[]   = {0x00, 0x00, 0x00, 0x00, 0x05, 0x20};

//CFX_RGBMatrix matrix(2, 4, 4, NEO_GRB + NEO_KHZ800, true);
CFX_RGBMatrix matrix(13, 31, 15);
CFX_ColorPalette palette(2);
CFX_ColorPalette palette_blue(2);

CFX_Color blue(0, 0, 255);
CFX_Color black(0, 0, 0);
CFX_Color pink(255, 20, 147);

CFX_Button button_right(7, 100, CFX_Low_Input);
CFX_Button button_left(8, 101, CFX_Low_Input);

CFX_Timer blink_timer(42);

//
//CFX_Sprite sprite(2, 2, l, palette);
CFX_Sprite sprite_eye(4, 11, open_eye, palette);
CFX_Sprite sprite_eye2(4, 11, open_eye, palette);
CFX_SpriteAnimationSequence blinking_eyes(7, &sprite_eye);
CFX_SpriteAnimationSequence blinking_eyes2(7, &sprite_eye2);

void setup()
{
  Serial.begin(115200);
  Serial.println("Starting...");

  palette.SetColor(0, black);
  palette.SetColor(1, pink);

  palette_blue.SetColor(0, black);
  palette_blue.SetColor(1, blue);

  blinking_eyes.AddBitmap(open_eye, 20, CFX_SpriteAppear);
  blinking_eyes.AddBitmap(closing_eye1, 20, CFX_SpriteAppear);
  blinking_eyes.AddBitmap(closing_eye2, 20, CFX_SpriteAppear);
  blinking_eyes.AddBitmap(closed_eye, 300, CFX_SpriteAppear);
  blinking_eyes.AddBitmap(closing_eye2, 20, CFX_SpriteAppear);
  blinking_eyes.AddBitmap(closing_eye1, 20, CFX_SpriteAppear);
  blinking_eyes.AddBitmap(open_eye, 250, CFX_SpriteAppear);

  blinking_eyes.SetRepetitions(1);
  blinking_eyes.Stop();

  blinking_eyes2.AddBitmap(open_eye, 20, CFX_SpriteAppear);
  blinking_eyes2.AddBitmap(closing_eye1, 20, CFX_SpriteAppear);
  blinking_eyes2.AddBitmap(closing_eye2, 20, CFX_SpriteAppear);
  blinking_eyes2.AddBitmap(closed_eye, 300, CFX_SpriteAppear);
  blinking_eyes2.AddBitmap(closing_eye2, 20, CFX_SpriteAppear);
  blinking_eyes2.AddBitmap(closing_eye1, 20, CFX_SpriteAppear);
  blinking_eyes2.AddBitmap(open_eye, 250, CFX_SpriteAppear);

  blinking_eyes2.SetRepetitions(1);
  blinking_eyes2.Stop();

  matrix.AddSprite(&sprite_eye);
  matrix.AddSprite(&sprite_eye2);

  sprite_eye.SetOrigin(10, 2);
  sprite_eye2.SetOrigin(17, 2);
  matrix.SetBrightness(20);
  blink_timer.SetTimer(1500, false);
}

void handleInput(int id, int command, int value)
{
  // Handle input events:
  if (id == 100) // right
  {
    if (command == CFX_CMD_BUTTON_PRESSED)
    {
      sprite_eye.Move(1, 0); // move one pixel to right
    }
  }
  else if (id == 101) // left
  {
    if (command == CFX_CMD_BUTTON_PRESSED)
    {
      sprite_eye.Move(-1, 0); // Move one pixel to the left
    }
  }
  else if (id == 42) // blink
  {
    blinking_eyes.SetRepetitions(1);
    blinking_eyes.Start();
    blinking_eyes2.SetRepetitions(1);
    blinking_eyes2.Start();
    blink_timer.SetTimer(random(100, 500) * 10, false);
  }
}

void loop()
{
  // If you stick to the Custom FX library, you do not need to add any code here
  CFX_Run();
}
