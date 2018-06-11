////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2016 CustomFX. All right reserved.
//
// This file is part of the CustomFX library. This library was developed in 
// order to make Arduino programming as easy as possible. For more information,
// visit our website: http://www.customfx.nl
//
// The CustomFX library is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by the Free
// Software Foundation, either version 3 of the License, or (at your option)
// any later version.
//
// The CustomFX library is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
// or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License 
// for more details.
//
// You should have received a copy of the GNU General Public License along with
// The CustomFX library.  If not, see <http://www.gnu.org/licenses/>.
//
////////////////////////////////////////////////////////////////////////////////

#include <CFX_Potentiometer.hpp>

CFX_Potentiometer::CFX_Potentiometer(int inputPin, int id, uint8_t samples) 
  : CFX_InputBase(id, inputPin, CFX_InputTypeAnalog)
{
  m_minInputRange = 0;
  m_maxInputRange = 1023;
  m_minOutputRange = 0;
  m_maxOutputRange = 1023;
  m_threshold = 5;
  m_signalDirection = 1;
  m_lastRawValue = 0;
  m_samples = samples;
  m_remainingReads = m_samples;
  m_totalValue = 0;
}

void CFX_Potentiometer::SetInputRange(int minRange, int maxRange)
{
  if (minRange >= 0 && minRange < maxRange)
  {
    if (maxRange < 1024)
    {
      m_minInputRange = minRange;
      m_maxInputRange = maxRange;
    }
  }
}

void CFX_Potentiometer::SetOutputRange(int minRange, int maxRange)
{
  if (minRange >= 0 && minRange < maxRange)
  {
    if (maxRange < 1024)
    {
      m_minOutputRange = minRange;
      m_maxOutputRange = maxRange;
    }
  }
}

const CFX_InputEvent* CFX_Potentiometer::GetEvent(unsigned long time)
{
  if (m_remainingReads == 0)
  {
    m_remainingReads = m_samples; // reset samples
  }
  
  m_totalValue += ReadInput();
  m_remainingReads--;
  
  if (m_remainingReads == 0)
  {
    int value = m_totalValue / m_samples;
    m_totalValue = 0;
    
    if (abs(value - m_lastRawValue) > m_threshold)
    {
      m_lastRawValue = value;
      if (value < m_minInputRange) value = m_minInputRange;
      if (value > m_maxInputRange) value = m_maxInputRange;
      
      value = map(value, m_minInputRange, m_maxInputRange, m_minOutputRange, m_maxOutputRange);
      if (GetLastEvent()->value != value)
      {
        SetEvent(CFX_CMD_VALUE_CHANGED, value);
        return GetLastEvent();
      }
      else
      {
        return 0;
      }
    }
    else
    {
      return 0;
    }
  }
  else
  {
    return 0;
  }
}

bool CFX_Potentiometer::IsAnalog() const
{
  return true;
}

uint8_t CFX_Potentiometer::GetRemainingReads() const
{
  return m_remainingReads;
}
