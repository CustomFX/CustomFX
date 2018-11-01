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

#include <CFX_LedStripAnimationFadeInOut.hpp>
#include <CustomFX.h>

CFX_LedStripAnimationFadeInOut::CFX_LedStripAnimationFadeInOut()
  : CFX_AnimationBase()
{
  m_output = 0;
}

CFX_LedStripAnimationFadeInOut::CFX_LedStripAnimationFadeInOut(
  unsigned long fadeInTime, unsigned long fadeOutTime, 
  CFX_LedStripBase* output, CFX_FadeType fadetype)
  : CFX_AnimationBase()
{
  m_output = output;
  m_fadeInTime = fadeInTime;
  m_fadeOutTime = fadeOutTime;
  m_step = 1;
  m_brightness = 255;
  m_useColor = false;
  m_type = fadetype;
  
  switch (fadetype)
  {
    case CFX_FadeLeftRight:
      m_startLed = 0;
      m_length = m_output->GetNrOfOutputs();
      break;
    
    case CFX_FadeRightLeft:
      m_startLed = m_output->GetNrOfOutputs() - 1;
      m_length = m_output->GetNrOfOutputs();
      break;
  }  
}

void CFX_LedStripAnimationFadeInOut::SetOutputDevice(CFX_LedStripBase* output)
{
  m_output = output;
  RestartAnimation();
}

void CFX_LedStripAnimationFadeInOut::SetColor(CFX_Color color)
{
  m_color = color;
  m_useColor = true;
}

void CFX_LedStripAnimationFadeInOut::SetBrightness(uint8_t brightness)
{
  m_brightness = brightness;
}

void CFX_LedStripAnimationFadeInOut::SetType(CFX_FadeType type)
{
  m_type = type;
}

void CFX_LedStripAnimationFadeInOut::SetFadeInTime(unsigned long fadeInTime)
{
  m_fadeInTime = fadeInTime;
}

void CFX_LedStripAnimationFadeInOut::RestartAnimation()
{
  m_step = 1;
  switch (m_type)
  {
    case CFX_FadeLeftRight:
      m_startLed = 0;
      break;
    
    case CFX_FadeRightLeft:
      m_startLed = m_output->GetNrOfOutputs() - 1;
      break;
  }
  this->Start();
}

bool CFX_LedStripAnimationFadeInOut::UpdateAnimation(int timeStep)
{
  if (m_output)
  {
    uint32_t totallevels = m_brightness * m_length;
    uint32_t totalsteps = m_fadeInTime / ANIMATION_UPDATE_INTERVAL;
    uint32_t value;
    if (totalsteps == 0)
    {
        value = totallevels;
    }
    else
    {  
      value = m_step * totallevels / totalsteps;
    }
    uint16_t ledsOn = value / m_brightness;
    uint8_t lastBrightness = value % m_brightness;
     
    for (uint16_t led = 0; led < ledsOn; led++)
    {
      uint16_t pixel;
      if (m_startLed == 0)
      {
        pixel = led;
      }
      else
      {
        pixel = m_length - led - 1;
      }
        
      if (m_useColor)
      {
        m_output->SetPixelColor(pixel, m_color);
      }
      m_output->SetPixelBrightness(pixel, m_brightness);
    }
    if (ledsOn == m_length)
    {
      return true; // done
    }
    else
    {
      uint16_t pixel;
      if (m_startLed == 0)
      {
        pixel = ledsOn;
      }
      else
      {
        pixel = m_length - ledsOn - 1;
      }
      if (m_useColor)
      {
        m_output->SetPixelColor(pixel, m_color);
      }
      m_output->SetPixelBrightness(pixel, lastBrightness);
      m_step++;
      return false;
    }
  }
  return false;
}
