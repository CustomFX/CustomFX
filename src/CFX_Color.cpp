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

#include <CFX_Color.hpp>

CFX_Color::CFX_Color()
{
  m_red = 0;
  m_green = 0;
  m_blue = 0;
}

CFX_Color::CFX_Color(uint8_t red, uint8_t green, uint8_t blue)
{
  m_red = red;
  m_green = green;
  m_blue = blue;
}

CFX_Color::CFX_Color(long color)
{
  m_red = color >> 16;
  m_green = color >> 8;
  m_blue = color;
}

void CFX_Color::SetRed(uint8_t red)
{
  m_red = red;
}

void CFX_Color::SetGreen(uint8_t green)
{
  m_green = green;
}

void CFX_Color::SetBlue(uint8_t blue)
{
  m_blue = blue;
}

const String CFX_Color::toString() const
{
  return String(m_red) + "," + String(m_green) + "," + String(m_blue);
}

long CFX_Color::toLong() const
{
  return (long)m_red << 16 | (long)m_green << 8 | (long)m_blue;
}

uint8_t CFX_Color::Red() const
{
  return m_red;
}

uint8_t CFX_Color::Green() const
{
  return m_green;
}

uint8_t CFX_Color::Blue() const
{
  return m_blue;
}

bool CFX_Color::operator==(const CFX_Color& color) const
{
  if (this == &color)
  {
    return true;
  }
  else if (m_red == color.m_red && m_green == color.m_green && m_blue == color.m_blue)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool CFX_Color::operator!=(const CFX_Color& color) const
{
  return !(*this == color);
}
