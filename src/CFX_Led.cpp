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

#include <CFX_Led.hpp>

CFX_Led::CFX_Led(uint8_t pinnumber):  CFX_LedBase()
{
  m_pin = pinnumber;
  pinMode(pinnumber, OUTPUT);
  m_brightness = 0;
  SetChanged(true);
  Commit();
}

CFX_Led::CFX_Led():  CFX_LedBase()
{
  }

void CFX_Led::SetBrightness(uint8_t brightness)
{
  m_brightness = brightness;
  SetChanged(true);
}

uint8_t CFX_Led::GetBrightness() const
{
  return m_brightness;
}

void CFX_Led::SetColor(const CFX_Color& color)
{
}

long CFX_Led::GetColorLong() const
{
  return 0;
}

const CFX_Color CFX_Led::GetColor() const
{
    return CFX_Color(0);
}

void CFX_Led::Commit()
{
  
  if (Changed())
  {
    analogWrite(m_pin, m_brightness);
    SetChanged(false);
  }
}
