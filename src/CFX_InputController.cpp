////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2016 Custom FX. All right reserved.
//
// This file is part of the Custom FX library. This library was developed in 
// order to make Arduino programming as easy as possible. For more information,
// visit our website: http://www.customfx.nl
//
// The Custom FX library is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by the Free
// Software Foundation, either version 3 of the License, or (at your option)
// any later version.
//
// The Custom FX library is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
// or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License 
// for more details.
//
// You should have received a copy of the GNU General Public License along with
// The Custom FX library. If not, see <http://www.gnu.org/licenses/>.
//
////////////////////////////////////////////////////////////////////////////////

#include <CFX_InputController.hpp>
#include <limits.h>

// forward declaration of callback function
void handleInput(int id, int command, int value);

static CFX_InputController* s_inputControler = 0;

CFX_InputController::CFX_InputController()
{
  m_handleInputFunctionCallback = NULL;
  RegisterHandleInputCallback(handleInput);
  m_previousUpdateTime = 0;
  m_timeStep = INPUT_UPDATE_INTERVAL;
  m_analogDevice = 0;
}

CFX_InputController* CFX_InputController::GetInstance()
{
  if (!s_inputControler)
  {
    s_inputControler = new CFX_InputController;
  }  
  return s_inputControler;
}

void CFX_InputController::RegisterInputDevice(CFX_InputBase* inputDevice)
{
  if (inputDevice->GetType() == CFX_Analog_Input)
  {
    m_analogInputList.Add(inputDevice);
  }
  else
  {
    m_digitalInputList.Add(inputDevice);
  }
}

void CFX_InputController::RegisterHandleInputCallback(void (*callback)(int, int, int))
{
  m_handleInputFunctionCallback = callback;
}

void CFX_InputController::ReadInputs()
{
  unsigned long time = millis();
  if (time - m_previousUpdateTime > m_timeStep)
  {
    m_previousUpdateTime = time;

    // handle all digital inputs
    for (int i = 0; i < m_digitalInputList.Size(); i++)
    {
      CFX_InputBase* input = m_digitalInputList.Get(i);
      if (input)
      {
        const CFX_InputEvent* inputEvent = input->GetEvent(time);
        if (inputEvent)
        {
          m_handleInputFunctionCallback(input->GetId(), inputEvent->command, inputEvent->value);
        }
      }
    }
    
    // handle next analog input
    if (m_analogInputList.Size() > 0)
    {
      CFX_InputBase* input = m_analogInputList.Get(m_analogDevice);
      if (input)
      {
        const CFX_InputEvent* inputEvent = input->GetEvent(time);
        if (inputEvent)
        {
          m_handleInputFunctionCallback(input->GetId(), inputEvent->command, inputEvent->value);
        }
      
        // check if enough samples have been read
        if (input->GetRemainingSamples() == 0)
        {
          m_analogDevice++;  // proceed to the next analog input
          if (m_analogDevice  >= m_analogInputList.Size())
          {
            m_analogDevice = 0;
          }
        }
      }
    }
  }
}


