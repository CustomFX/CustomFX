////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2018 Custom FX. All right reserved.
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

// Declare objects here:


void setup() 
{
  // put your setup code here, to run once:
  
}

void handleInput(int id, int command, int value) 
{
  // Handle input events, below is a filled in template that you need to change
  if (id == 1)
  {
    if (command == CFX_CMD_BUTTON_CLICK) 
    {
      
    }
    else if (command == CFX_CMD_BUTTON_DOUBLE_CLICK)
    {
      
    }
    // etc
  }
  else if (id == 2)
  {
    
  }
  // etc
}

void loop() 
{
  // If you stick to the Custom FX library, you do not need to add any code here
  CFX_Run();
}
