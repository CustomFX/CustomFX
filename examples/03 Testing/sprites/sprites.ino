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
const byte ball4[] PROGMEM = {0,1,1,0, 1,1,1,1, 1,1,1,1, 0,1,1,0};


CFX_RGBMatrix matrix(2, 4, 4);
CFX_ColorPalette palette(2);
CFX_Color blue(0,0,255);
CFX_Color black(0,0,0);

//
//CFX_Sprite sprite(5, 5, ball, palette);
CFX_Sprite sprite(4, 4, ball4, palette);

void setup() 
{
  Serial.begin(115200);
  
  // put your setup code here, to run once:
  palette.SetColor(0, black);
  palette.SetColor(1, blue);
  
  sprite.Draw(matrix);
  matrix.SetBrightness(100);
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
