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

#include <CFX_DigitalInput.hpp>

CFX_DigitalInput::CFX_DigitalInput(int inputPin, int id, CFX_InputType type)
 : CFX_InputBase(id, inputPin, type)
{
  m_state = false;
}

const CFX_InputEvent* CFX_DigitalInput::GetEvent(unsigned long time)
{
  int value = ReadInput();
  if (value == HIGH && m_state == false)
  {
    m_state = true;
    SetEvent(CFX_CMD_HIGH, 0);
    return GetLastEvent();
  }
  else if (value == LOW && m_state == true)
  {
    m_state = false;
    SetEvent(CFX_CMD_LOW, 0);
    return GetLastEvent();
  }
  else
  {
    return 0;
  }
}

bool CFX_DigitalInput::IsAnalog() const
{
  return false;
}