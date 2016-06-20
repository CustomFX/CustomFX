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

CFX_InputBase::CFX_InputBase(int id)
{
  m_id = id;
	CFX_InputController::GetInstance()->RegisterInputDevice(this);
}

int CFX_InputBase::GetId()
{
	return m_id;
}

//
// Protected functions
//
int CFX_InputBase::GetPinNumber()
{
	return m_pinnumber;
}

void CFX_InputBase::SetPinNumber(int pinnumber)
{
	m_pinnumber = pinnumber;
}

void CFX_InputBase::SetEvent(int command, unsigned long value)
{
  m_lastEvent.command = command;
  m_lastEvent.value = value;
}

const CFX_InputEvent* CFX_InputBase::GetLastEvent()
{
  return &m_lastEvent;
}
