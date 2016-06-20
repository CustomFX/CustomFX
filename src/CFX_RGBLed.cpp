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

#include <CFX_RGBLed.hpp>

CFX_RGBLed::CFX_RGBLed(int redpin, int greenpin, int bluepin, bool commonAnode) : CFX_Led()
{
  m_redpin = redpin;
  m_greenpin = greenpin;
  m_bluepin = bluepin;
  pinMode(m_redpin, OUTPUT);
  pinMode(m_greenpin, OUTPUT);
  pinMode(m_bluepin, OUTPUT);
  m_commonAnode = commonAnode;
  SetColor(m_color);
  m_changed = true;
  Commit();
}

CFX_RGBLed::CFX_RGBLed() : CFX_Led()
{
  
}

long CFX_RGBLed::GetColorLong() const
{
  return m_color.toLong();
}

const CFX_Color& CFX_RGBLed::GetColor() const
{
  return m_color;
}

void CFX_RGBLed::SetColor(const CFX_Color& color)
{
  m_color = color;
  m_changed = true;
}

void CFX_RGBLed::SetBrightness(uint8_t brightness)
{
  m_color = CFX_Color(brightness, brightness, brightness);
  m_changed = true;  
}

void CFX_RGBLed::Commit()
{
  if (m_changed)
  {
    if (m_commonAnode)
    {
      analogWrite(m_redpin, 255 - m_color.Red());
      analogWrite(m_greenpin, 255 - m_color.Green());
      analogWrite(m_bluepin, 255 - m_color.Blue());
    }
    else
    {
      analogWrite(m_redpin, m_color.Red());
      analogWrite(m_greenpin, m_color.Green());
      analogWrite(m_bluepin, m_color.Blue());
    }
    m_changed = false;
  }
}
