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

const byte ball[] PROGMEM = {0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0};

#define CFX_SPRITE_BLACK_WHITE  1
#define CFX_SPRITE_4_COLOR      2
#define CFX_SPRITE_16_COLOR     4
#define CFX_SPRITE_256_COLOR    8

class CFX_Sprite: public CFX_OutputBase
{
  public:
    CFX_Sprite(byte width, byte height, byte color_depth, byte &drawing);
    void Draw(); // TODO pass matrix
    void SetOrigin(signed int newX, signed int newY);

  private:
    byte m_drawing[];
    signed int m_x_position;
    signed int m_y_position;
    byte m_width;
    byte m_height;
    byte m_color_depth;
};

CFX_Sprite::CFX_Sprite(byte width, byte height, byte color_depth, byte &drawing)
 : CFX_OutputBase()
{
  m_width = width;
  m_height = height;
  m_color_depth = color_depth;
  m_x_position = 0;
  m_y_position = 0;
//  m_drawing = drawing;
}

void CFX_Sprite::SetOrigin(signed int newX, signed int newY) {
  m_x_position = newX;
  m_y_position = newY;
}

void CFX_Sprite::Draw() {
  for (int y = 0; y < m_height; y++) {
    for (int x = 0; x < m_width; x++) {
      uint16_t index = y * m_width + x;
      byte pixel = pgm_read_byte_near(m_drawing + index);
      //ledstrip.SetPixelColor(index, color(12, 25, 115))
    }
  }
}

CFX_Sprite sprite(5, 5, CFX_SPRITE_BLACK_WHITE, ball);

void setup() 
{
  // put your setup code here, to run once:
}

void handleInput(int id, int command, int value) 
{
  // Handle input events:
  
}

void loop() 
{
  // If you stick to the Custom FX library, you do not need to add any code here
  CFX_Run();
}
