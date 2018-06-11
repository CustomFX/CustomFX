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

#include <CFX_Timer.hpp>
 
CFX_Timer::CFX_Timer(int id): CFX_InputBase(id, CFX_InputTypeOther)
{
   m_lastEvent = 0;
   m_timerValue = 0;
   m_recurring = false;
 }
 
void CFX_Timer::SetTimer(unsigned long value, bool recurring)
{
  m_lastEvent = millis();
  m_timerValue = value;
  m_recurring = recurring;
}


const CFX_InputEvent* CFX_Timer::GetEvent(unsigned long time)
{
  static long eventCounter;
  if ((m_timerValue > 0) && (time - m_lastEvent > m_timerValue))
  {
    // timer event occured
    eventCounter++;

    if (m_recurring)
    {
      m_lastEvent = time;
    }
    else
    {
      m_timerValue = 0;
    }
    SetEvent(CFX_CMD_TIMER_EVENT, eventCounter);
    return GetLastEvent();
  }
  else
  {
    return 0;
  }
}

bool CFX_Timer::IsAnalog() const
{
  return false;
}
