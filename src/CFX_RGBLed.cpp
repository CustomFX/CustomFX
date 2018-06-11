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
  SetBrightness(255);
  SetChanged(true);
  Commit();
}

CFX_RGBLed::CFX_RGBLed() : CFX_Led()
{
  
}

long CFX_RGBLed::GetColorLong() const
{
  return m_color.toLong();
}

const CFX_Color CFX_RGBLed::GetColor() const
{
  return m_color;
}

void CFX_RGBLed::SetColor(const CFX_Color& color)
{
  m_color = color;
  SetChanged(true);
}

void CFX_RGBLed::Commit()
{
  if (Changed())
  {
    CFX_Color newcolor;
    
    uint8_t brightness = GetBrightness();
    if (brightness == 255)
    {
      newcolor = m_color;
    }
    else
    {
      float factor = (float)brightness/255;
      newcolor = m_color * factor;
    }
    
    if (m_commonAnode)
    {
      analogWrite(m_redpin, 255 - newcolor.Red());
      analogWrite(m_greenpin, 255 - newcolor.Green());
      analogWrite(m_bluepin, 255 - newcolor.Blue());
    }
    else
    {
      analogWrite(m_redpin, newcolor.Red());
      analogWrite(m_greenpin, newcolor.Green());
      analogWrite(m_bluepin, newcolor.Blue());
    }
    SetChanged(false);
  }
}
