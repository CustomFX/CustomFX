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

#include <CFX_LedStripPixel.hpp>

CFX_LedStripPixel::CFX_LedStripPixel(unsigned int pixel, CFX_LedStrip* ledstrip) : CFX_RGBLed()
{
  m_pixel = pixel;
  m_ledstrip = ledstrip;
}

CFX_LedStripPixel::CFX_LedStripPixel() : CFX_RGBLed()
{  
}

void CFX_LedStripPixel::SetPixel(unsigned int pixel, CFX_LedStrip* ledstrip)
{
  m_pixel = pixel;
  m_ledstrip = ledstrip;  
}

long CFX_LedStripPixel::GetColorLong() const
{
  return m_ledstrip->GetPixelColor(m_pixel).toLong();
}

const CFX_Color CFX_LedStripPixel::GetColor() const
{
  return m_ledstrip->GetPixelColor(m_pixel);
}

void CFX_LedStripPixel::SetColor(const CFX_Color& color)
{
  m_ledstrip->SetPixelColor(m_pixel, color);
}

void CFX_LedStripPixel::SetBrightness(uint8_t brightness)
{
  m_ledstrip->SetPixelColor(m_pixel, CFX_Color(brightness, brightness, brightness));
}

void CFX_LedStripPixel::Commit()
{
  // The commit is handled by the Ledstrip
}
