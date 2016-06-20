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

// Declare objects here:


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
  CFX_InputController::GetInstance()->ReadInputs();
  CFX_AnimationController::GetInstance()->UpdateAnimation();
}
