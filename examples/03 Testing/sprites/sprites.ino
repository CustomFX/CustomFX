////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016 Custom FX. All right reserved.
//
// Custom FX Empty Template
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

//const PROGMEM byte ball[]  = {0,1,1,1,0,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,0,1,1,1, 0};
//const PROGMEM byte ball2[]  = {119, 255, 247, 0};
const PROGMEM byte open_eye[] = {0,1,1,0, 1,0,0,1, 1,0,0,1, 0,1,1,0};
const PROGMEM byte closing_eye1[] = {0,0,0,0, 0,1,1,0, 1,0,0,1, 0,1,1,0};
const PROGMEM byte closing_eye2[] = {0,0,0,0, 0,0,0,0, 0,1,1,0, 0,1,1,0};
const PROGMEM byte closed_eye[] = {0,0,0,0, 0,0,0,0, 0,1,1,0, 0,0,0,0};
//const PROGMEM byte l[] = {112};
//const PROGMEM byte u[] = {112};


CFX_RGBMatrix matrix(2, 4, 4);
CFX_ColorPalette palette(255);
CFX_Color blue(0, 0, 255);
CFX_Color black(0, 0, 0);
CFX_Color pink(255,20,147);

CFX_Button button_right(7, 100, CFX_Low_Input);
CFX_Button button_left(8, 101, CFX_Low_Input);

CFX_SpriteAnimationSequence blinking_eyes(6, &matrix);

//
//CFX_Sprite sprite(2, 2, l, palette);
CFX_Sprite sprite_open_eye(4, 4, open_eye, palette);
CFX_Sprite sprite_closed_eye(4, 4, closed_eye, palette);
CFX_Sprite sprite_closing_eye1(4, 4, closing_eye1, palette);
CFX_Sprite sprite_closing_eye2(4, 4, closing_eye2, palette);

void setup()
{
  Serial.begin(115200);
  
  palette.SetColor(0, black);
  palette.SetColor(1, pink);

  blinking_eyes.AddSprite(&sprite_open_eye, 2000, CFX_SpriteAppear);
  blinking_eyes.AddSprite(&sprite_closing_eye1, 50, CFX_SpriteAppear);
  blinking_eyes.AddSprite(&sprite_closing_eye2, 50, CFX_SpriteAppear);
  blinking_eyes.AddSprite(&sprite_closed_eye, 500, CFX_SpriteAppear);
  blinking_eyes.AddSprite(&sprite_closing_eye2, 50, CFX_SpriteAppear);
  blinking_eyes.AddSprite(&sprite_closing_eye1, 50, CFX_SpriteAppear);

//  sprite.Draw(matrix);
  matrix.SetBrightness(20);
}

void handleInput(int id, int command, int value)
{
  // Handle input events:
  if (id == 100) // right
  {
    if (command == CFX_CMD_BUTTON_PRESSED)
    {
      // move one pixel to right
    }
  }
  else if (id == 101) // left
  {
    if (command == CFX_CMD_BUTTON_PRESSED)
    {
      // Move one pixel to the left
    }
  }
}

void loop()
{
  // If you stick to the Custom FX library, you do not need to add any code here
  CFX_Run();
}
