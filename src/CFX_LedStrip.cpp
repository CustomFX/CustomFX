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

CFX_LedStrip::CFX_LedStrip(int pinnumber, uint16_t leds, int type) : CFX_LedStripBase()
{
  m_type = type;
  m_pinnumber = pinnumber;
  SetChanged(false);
  m_initialised = false;
  
  uint16_t numBytes = (uint16_t)leds * 4;
  
  if((m_pixelcolors = (uint8_t *)malloc(numBytes))) {
    memset(m_pixelcolors, 0, numBytes);
    m_nrleds = leds;
  } else {
    m_nrleds = 0;
  }

  SetColor(CFX_Color());
  SetBrightness(255);
}

CFX_LedStrip::CFX_LedStrip() : CFX_LedStripBase()
{
  
}

void CFX_LedStrip::Init()
{
  m_initialised = true;
  m_pixels = Adafruit_NeoPixel(m_nrleds, m_pinnumber, m_type);
  m_pixels.begin();
}

uint16_t CFX_LedStrip::GetNrOfOutputs() const
{
  return m_nrleds;
}

const CFX_Color CFX_LedStrip::GetPixelColor(uint16_t pixel) const
{
  uint16_t pix = constrain(pixel, 0, m_nrleds - 1);
  return CFX_Color(m_pixelcolors[pix*4+0], m_pixelcolors[pix*4+1], m_pixelcolors[pix*4+2]);
}

long CFX_LedStrip::GetPixelColorLong(uint16_t pixel) const
{
  return GetPixelColor(pixel).toLong();
}

void CFX_LedStrip::SetPixelColor(uint16_t pixel, const CFX_Color& color)
{
  uint16_t pix = constrain(pixel, 0, m_nrleds - 1);
  m_pixelcolors[pix*4+0] = color.Red();
  m_pixelcolors[pix*4+1] = color.Green();
  m_pixelcolors[pix*4+2] = color.Blue();
  SetChanged(true);
}

const CFX_Color CFX_LedStrip::GetColor() const
{
  if (m_nrleds > 0) return GetPixelColor(0);
  else return CFX_Color(0);
} 

long CFX_LedStrip::GetColorLong() const
{
  if (m_nrleds > 0) return GetPixelColorLong(0);
  else return 0;
} 

void CFX_LedStrip::SetColor(const CFX_Color& color)
{
  for (uint16_t i = 0; i < m_nrleds; i++)
  {
    m_pixelcolors[i*4+0] = color.Red();
    m_pixelcolors[i*4+1] = color.Green();
    m_pixelcolors[i*4+2] = color.Blue();
  }
  SetChanged(true);
}

void CFX_LedStrip::SetColorRange(const CFX_ColorRange& colorrange, uint16_t index)
{
  for (uint16_t i = 0; i < m_nrleds; i++)
  {
    SetPixelColor(i, colorrange.GetColor(i + index));
  }
}

void CFX_LedStrip::SetBrightness(uint8_t brightness)
{
  for (uint16_t i = 0; i < m_nrleds; i++)
  {
    m_pixelcolors[i*4+3] = brightness;
  }
  SetChanged(true);
}

uint8_t CFX_LedStrip::GetBrightness() const
{
  if (m_nrleds > 0) return GetPixelBrightness(0);
  else return 0;
}

void CFX_LedStrip::SetPixelBrightness(uint16_t pixel, uint8_t brightness)
{
  if (m_nrleds > 0) 
  {
    uint16_t pix = constrain(pixel, 0, m_nrleds - 1);
    m_pixelcolors[pix*4+3] = brightness;
    SetChanged(true);
  }
}

uint8_t CFX_LedStrip::GetPixelBrightness(uint16_t pixel) const
{
  if (m_nrleds > 0) 
  {
    uint16_t pix = constrain(pixel, 0, m_nrleds - 1);
    return m_pixelcolors[pix*4+3];
  }
  else
  {
    return 0;
  }
}

void CFX_LedStrip::Commit()
{
  if (!m_initialised) Init();
  
  if (Changed())
  {
    for (uint16_t i = 0; i< m_nrleds; i++)
    {
      //Serial.println(m_pixelcolors[i*4+3]);
      if (m_pixelcolors[i*4+3] == 255)
      {
        m_pixels.setPixelColor(i, m_pixels.Color(m_pixelcolors[i*4+0], m_pixelcolors[i*4+1], 
          m_pixelcolors[i*4+2]));
      }
      else
      {
        m_pixels.setPixelColor(i, m_pixels.Color(
          m_pixelcolors[i*4+0] * ((float)m_pixelcolors[i*4+3] / 255), 
          m_pixelcolors[i*4+1] * ((float)m_pixelcolors[i*4+3] / 255), 
          m_pixelcolors[i*4+2] * ((float)m_pixelcolors[i*4+3] / 255)));
      }
    }

    m_pixels.show();
    SetChanged(false);
  }
}



