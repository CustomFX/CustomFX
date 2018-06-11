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

#include <CFX_InputBase.hpp>
#include <CFX_InputController.hpp>

CFX_InputBase::CFX_InputBase(uint8_t id, uint8_t pinnumber, CFX_InputType type)
{
  m_id = id;
  m_pinnumber = pinnumber;
  m_type = type;

  if (type == CFX_InputTypeDigitalHigh)
    pinMode(m_pinnumber, INPUT_PULLUP);
  else if (type == CFX_InputTypeDigitalLow)
    pinMode(m_pinnumber, INPUT);

	CFX_InputController::GetInstance()->RegisterInputDevice(this);
}

CFX_InputBase::CFX_InputBase(uint8_t id, CFX_InputType type)
{
  m_id = id;
  m_pinnumber = 0;
  m_type = type;
	CFX_InputController::GetInstance()->RegisterInputDevice(this);
}

uint8_t CFX_InputBase::GetId() const
{
	return m_id;
}

//
// Protected functions
//

int CFX_InputBase::ReadInput()
{
  if (m_type == CFX_InputTypeDigitalHigh)
    return (digitalRead(m_pinnumber) == HIGH?LOW:HIGH);
  if (m_type == CFX_InputTypeDigitalLow)
    return digitalRead(m_pinnumber);
  if (m_type == CFX_InputTypeAnalog)
    return analogRead(m_pinnumber);
  return 0;
}

uint8_t CFX_InputBase::GetPinNumber()
{
	return m_pinnumber;
}

void CFX_InputBase::SetEvent(uint8_t command, unsigned long value)
{
  m_lastEvent.command = command;
  m_lastEvent.value = value;
}

const CFX_InputEvent* CFX_InputBase::GetLastEvent()
{
  return &m_lastEvent;
}

const CFX_InputType CFX_InputBase::GetType() const
{
  return m_type;
}

uint8_t CFX_InputBase::GetRemainingSamples() const
{
  return 0;
}
