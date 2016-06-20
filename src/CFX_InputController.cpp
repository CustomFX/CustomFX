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

// forward declaration of callback function
void handleInput(int id, int command, int value);
static CFX_InputController* s_inputControler = 0;


CFX_InputController::CFX_InputController()
{
  m_nrOfInputDevices = 0;
  m_handleInputFunctionCallback = NULL;
  RegisterHandleInputCallback(handleInput);
  m_previousUpdateTime = 0;
  m_timeStep = INPUT_UPDATE_INTERVAL;
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
  if (m_nrOfInputDevices < MAX_INPUT_DEVICES - 1)
  {
    m_inputDevices[m_nrOfInputDevices] = inputDevice;
    m_nrOfInputDevices++;
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
    for (int i = 0; i < m_nrOfInputDevices; i++)
    {
      const CFX_InputEvent* inputEvent = m_inputDevices[i]->GetEvent(time);
      if (inputEvent)
      {
        m_handleInputFunctionCallback(m_inputDevices[i]->GetId(), inputEvent->command, inputEvent->value);
      }
    }
  }
}


