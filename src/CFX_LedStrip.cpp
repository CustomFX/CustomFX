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

#include <CFX_LedStrip.hpp>

CFX_LedStrip::CFX_LedStrip(int pinnumber, int leds, int type) : CFX_RGBLed()
{
  m_type = type;
  m_pinnumber = pinnumber;
  m_nrleds = 1; // minimum length is 1
  if (leds > 0) m_nrleds = leds;
  m_changed = false;
  m_initialised = false;
  m_pixelcolors = new uint8_t[m_nrleds][3];
  SetColor(CFX_Color());
}

CFX_LedStrip::CFX_LedStrip() : CFX_RGBLed()
{
  
}

void CFX_LedStrip::Init()
{
  m_initialised = true;
  m_pixels = Adafruit_NeoPixel(m_nrleds, m_pinnumber, m_type);

  m_pixels.begin();
}

int CFX_LedStrip::GetNrOfOutputs() const
{
  return m_nrleds;
}

const CFX_Color CFX_LedStrip::GetPixelColor(int pixel) const
{
  return CFX_Color(m_pixels.getPixelColor(pixel));
}

long CFX_LedStrip::GetPixelColorLong(int pixel) const
{
  return m_pixels.getPixelColor(pixel);
}

void CFX_LedStrip::SetPixelColor(int led, const CFX_Color& color)
{
  led = constrain(led, 0, m_nrleds - 1);
  m_pixelcolors[led][0] = color.Red();
  m_pixelcolors[led][1] = color.Green();
  m_pixelcolors[led][2] = color.Blue();
  m_changed = true;
}

const CFX_Color CFX_LedStrip::GetColor() const
{
  return m_pixels.getPixelColor(0);
} 

long CFX_LedStrip::GetColorLong() const
{
  return m_pixels.getPixelColor(0);
} 

void CFX_LedStrip::SetColor(const CFX_Color& color)
{
  for (int i = 0; i < m_nrleds; i++)
  {
    m_pixelcolors[i][0] = color.Red();
    m_pixelcolors[i][1] = color.Green();
    m_pixelcolors[i][2] = color.Blue();
  }
  m_changed = true;
}

void CFX_LedStrip::SetBrightness(uint8_t brightness)
{
  SetColor(CFX_Color(brightness, brightness, brightness));  
}

void CFX_LedStrip::Commit()
{
  if (!m_initialised) Init();
  
  if (m_changed)
  {
    for (int i = 0; i< m_nrleds; i++)
    {
      m_pixels.setPixelColor(i, m_pixels.Color(m_pixelcolors[i][0], m_pixelcolors[i][1], m_pixelcolors[i][2]));
    }

    m_pixels.show();
    m_changed = false;
  }
}

