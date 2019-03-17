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

//const PROGMEM byte open_eye[] = {0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0};
const PROGMEM byte open_eye[] = {0x6F, 0xF6};
//const PROGMEM byte closing_eye1[] = {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0};
const PROGMEM byte closing_eye1[] = {0x0F, 0xF6};
//const PROGMEM byte closing_eye2[] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0};
const PROGMEM byte closing_eye2[] = {0x00, 0xF0};
//const PROGMEM byte closed_eye[] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0};
const PROGMEM byte closed_eye[] = {0x00, 0xF0 };
const PROGMEM byte line[] = {0x00, 0x0F };




CFX_RGBMatrix matrix(2, 4, 4);
//CFX_ColorPalette palette(255);
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
CFX_Sprite sprite_open_eye(4, 4, open_eye, palette);
CFX_Sprite sprite_closed_eye(4, 4, closed_eye, palette);
CFX_Sprite sprite_closing_eye1(4, 4, closing_eye1, palette);
CFX_Sprite sprite_closing_eye2(4, 4, closing_eye2, palette);


CFX_SpriteAnimationSequence blinking_eyes(7);


//CFX_Sprite eye_sprites[] = { CFX_Sprite(4, 4, closed_eye, palette), CFX_Sprite(4, 4, line, palette_blue) };
CFX_Sprite eye_sprites[] = { sprite_open_eye, sprite_closed_eye, sprite_closing_eye1, sprite_closing_eye2 };

void setup()
{
  Serial.begin(115200);
  Serial.println("Starting...");

  
  palette.SetColor(0, black);
  palette.SetColor(1, pink);

  palette_blue.SetColor(0, black);
  palette_blue.SetColor(1, blue);

  blinking_eyes.AddSprite(&eye_sprites[0], 20, CFX_SpriteAppear);
  blinking_eyes.AddSprite(&eye_sprites[2], 20, CFX_SpriteAppear);
  blinking_eyes.AddSprite(&eye_sprites[3], 20, CFX_SpriteAppear);
  blinking_eyes.AddSprite(&eye_sprites[1], 300, CFX_SpriteAppear);
  blinking_eyes.AddSprite(&eye_sprites[3], 20, CFX_SpriteAppear);
  blinking_eyes.AddSprite(&eye_sprites[2], 20, CFX_SpriteAppear);
  blinking_eyes.AddSprite(&eye_sprites[0], 250, CFX_SpriteAppear);

  blinking_eyes.SetRepetitions(1);
  blinking_eyes.Stop();
  sprite_open_eye.SetActive(false);

  //  sprite.Draw(matrix);
  matrix.SetSprites(eye_sprites, 4);

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
  else if (id == 42) // blink
  {
    blinking_eyes.SetRepetitions(1);
    blinking_eyes.Start();
    blink_timer.SetTimer(random(100, 500) * 10, false);
  }
}

void loop()
{
  // If you stick to the Custom FX library, you do not need to add any code here
  CFX_Run();
}
