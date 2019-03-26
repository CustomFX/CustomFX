////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2016-2019 Custom FX. All right reserved.
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

CFX_LedStripAnimationFadeInOut::CFX_LedStripAnimationFadeInOut(int id)
  : CFX_AnimationBase(id)
{
  m_output = 0;
}

CFX_LedStripAnimationFadeInOut::CFX_LedStripAnimationFadeInOut(
  unsigned long fadeTime,  
  CFX_LedStripBase* output, CFX_FadeType fadetype, int id)
  : CFX_AnimationBase(id)
{
  m_useColor = false;
  m_output = output;
  m_fadeInTime = fadeTime;
  m_fadeOutTime = fadeTime;
  m_step = 1;
  m_brightness = 255;
  m_fadeInType = fadetype;
  m_fadeOutType = fadetype;
}

CFX_LedStripAnimationFadeInOut::CFX_LedStripAnimationFadeInOut(
  unsigned long fadeInTime, unsigned long fadeOutTime, 
  CFX_LedStripBase* output, CFX_FadeType fadeInType, 
  CFX_FadeType fadeOutType, CFX_Color color, uint8_t brightness, int id)
  : CFX_AnimationBase(id)
{
  m_output = output;
  m_fadeInTime = fadeInTime;
  m_fadeOutTime = fadeOutTime;
  m_step = 1;
  m_brightness = brightness;
  m_color = color;
  m_useColor = true;
  m_fadeInType = fadeInType;
  m_fadeOutType = fadeOutType;
  m_fadeoutDelay = 0;
}

void CFX_LedStripAnimationFadeInOut::SetOutputDevice(CFX_LedStripBase* output)
{
  m_output = output;
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

void CFX_LedStripAnimationFadeInOut::DisableColor(bool disable)
{
  m_useColor = !disable;
}

void CFX_LedStripAnimationFadeInOut::SetTimes(unsigned long fadeInTime, unsigned long fadeOutTime)
{
  m_fadeInTime = fadeInTime;
  m_fadeOutTime = fadeOutTime;
}

void CFX_LedStripAnimationFadeInOut::SetFadeTypes(CFX_FadeType fadeintype, CFX_FadeType fadeouttype)
{
  m_fadeInType = fadeintype;
  m_fadeOutType = fadeouttype;
}

void CFX_LedStripAnimationFadeInOut::SetFadeoutDelay(uint16_t delay)
{
  m_fadeoutDelay = delay;
}

bool CFX_LedStripAnimationFadeInOut::InitializeAnimation(int timestep)
{
  if (m_output)
  {
    if (m_fadeInType == CFX_FadeCenterOut || m_fadeInType == CFX_FadeCenterIn)
    {
      m_totallevels = (m_brightness + 1) * m_output->GetNrOfOutputs() / 2;
    }
    else
    {
      m_totallevels = (m_brightness + 1) * m_output->GetNrOfOutputs();
    }
    m_totalsteps = m_fadeInTime / ANIMATION_UPDATE_INTERVAL;
    
    if (m_totalsteps == 0)
    { 
      m_totalsteps = 1;
    }
    
    m_step = 0;
    if (m_useColor)
    {
      m_output->SetColor(m_color);
    }
    m_output->SetBrightness(0);
    m_fadingIn = true;
  }
  return true;
}

bool CFX_LedStripAnimationFadeInOut::UpdateAnimation(int timestep)
{
  if (m_output)
  {
    if (m_fadingIn)
    {
      m_step++;
      if (UpdateFadeIn(timestep))
      {
        // Finished fading in, calculate fade out steps
        if (m_fadeOutType == CFX_FadeCenterOut || m_fadeOutType == CFX_FadeCenterIn)
        {
          m_totallevels = (m_brightness + 1) * m_output->GetNrOfOutputs() / 2;
        }
        else
        {
          m_totallevels = (m_brightness + 1) * m_output->GetNrOfOutputs();
        }
        m_totalsteps = m_fadeOutTime / ANIMATION_UPDATE_INTERVAL;
        if (m_totalsteps == 0)
        { 
          m_totalsteps = 1;
        }
        m_fadingIn = false;
        m_step = m_totalsteps;
        this->SetDelay(m_fadeoutDelay);
      }
    }
    else
    {
      m_step--;
      if (UpdateFadeOut(timestep))
      {
        // fade out complete, calculate fade in steps for next repetition
        if (m_fadeInType == CFX_FadeCenterOut || m_fadeInType == CFX_FadeCenterIn)
        {
          m_totallevels = (m_brightness + 1) * m_output->GetNrOfOutputs() / 2;
        }
        else
        {
          m_totallevels = (m_brightness + 1) * m_output->GetNrOfOutputs();
        }
        m_totalsteps = m_fadeInTime / ANIMATION_UPDATE_INTERVAL;
        m_fadingIn = true;
        if (m_totalsteps == 0)
        { 
          m_totalsteps = 1;
        }
        m_step = 0;
        return true;
      }
    }
    return false;
  }
  else
  {
    return true;
  }
}

bool CFX_LedStripAnimationFadeInOut::UpdateFadeIn(int timestep)
{
  bool returnval = false;
  uint32_t value = m_step * m_totallevels / m_totalsteps;
  uint8_t  lastBrightness = value % (m_brightness + 1);
  uint16_t ledsOn = value / (m_brightness + 1);

  if (ledsOn == m_output->GetNrOfOutputs())
  {
    lastBrightness = m_brightness;
    ledsOn = m_output->GetNrOfOutputs() - 1;
    returnval = true;
  }

  if (m_fadeInType == CFX_FadeLeftRight)
  {
    SetPixels(0, ledsOn, m_brightness);
    SetPixels(ledsOn, 1, lastBrightness);
    SetPixels(ledsOn + 1, m_output->GetNrOfOutputs() - 1 - ledsOn, 0);
  }
  else if (m_fadeInType == CFX_FadeRightLeft)
  {
    SetPixels(0, m_output->GetNrOfOutputs() - 1 - ledsOn, 0);
    SetPixels(m_output->GetNrOfOutputs() - 1 - ledsOn, 1, lastBrightness);
    SetPixels(m_output->GetNrOfOutputs() - ledsOn, ledsOn, m_brightness);
  }
  else if (m_fadeInType == CFX_FadeCenterOut)
  {
    uint16_t centerpixel = m_output->GetNrOfOutputs() / 2;
    if (ledsOn == centerpixel)
    {
      lastBrightness = m_brightness;
      ledsOn = centerpixel - 1;
      returnval = true;
    }
    
    SetPixels(0, centerpixel - 1 - ledsOn, 0);
    SetPixels(centerpixel - 1 - ledsOn, 1, lastBrightness);
    SetPixels(centerpixel - ledsOn, ledsOn, m_brightness);
    
    SetPixels(centerpixel, ledsOn, m_brightness);
    SetPixels(centerpixel + ledsOn, 1, lastBrightness);
    SetPixels(centerpixel + ledsOn + 1, centerpixel - ledsOn - 1, 0);
  }
  else if (m_fadeInType == CFX_FadeCenterIn)
  {
    uint16_t centerpixel = m_output->GetNrOfOutputs() / 2;
    if (ledsOn == centerpixel)
    {
      lastBrightness = m_brightness;
      ledsOn = centerpixel - 1;
      returnval = true;
    }
    SetPixels(0, ledsOn, m_brightness);
    SetPixels(ledsOn, 1, lastBrightness);
    SetPixels(ledsOn + 1, centerpixel - 1 - ledsOn, 0);

    SetPixels(centerpixel, centerpixel - ledsOn, 0);
    SetPixels(m_output->GetNrOfOutputs() - ledsOn - 1, 1, lastBrightness);
    SetPixels(m_output->GetNrOfOutputs() - ledsOn, ledsOn, m_brightness);
    
  }
  
  return returnval;
}

bool CFX_LedStripAnimationFadeInOut::UpdateFadeOut(int timestep)
{
  bool returnval = false;
  uint32_t value = (m_step * m_totallevels) / m_totalsteps;
  uint8_t  lastBrightness = value % (m_brightness + 1);
  uint16_t ledsOn = value / (m_brightness + 1);
  
  if (ledsOn == 0  && lastBrightness == 0)
  {
    returnval = true;
  }
  else if (ledsOn == m_output->GetNrOfOutputs())
  {
    ledsOn = m_output->GetNrOfOutputs() - 1;
  }

  if (m_fadeOutType == CFX_FadeLeftRight)
  {
    SetPixels(0, m_output->GetNrOfOutputs() - 1 - ledsOn, 0);
    SetPixels(m_output->GetNrOfOutputs() - 1 - ledsOn, 1, lastBrightness);
    SetPixels(m_output->GetNrOfOutputs() - ledsOn, ledsOn, m_brightness);
  }
  else if (m_fadeOutType == CFX_FadeRightLeft)
  {
    SetPixels(0, ledsOn, m_brightness);
    SetPixels(ledsOn, 1, lastBrightness);
    SetPixels(ledsOn + 1, m_output->GetNrOfOutputs() - 1 - ledsOn, 0);
  }
  else if (m_fadeOutType == CFX_FadeCenterOut)
  {
    uint16_t centerpixel = m_output->GetNrOfOutputs() / 2;

    SetPixels(0, ledsOn, m_brightness);
    SetPixels(ledsOn, 1, lastBrightness);
    SetPixels(ledsOn + 1, centerpixel - 1 - ledsOn, 0);

    SetPixels(centerpixel, centerpixel - ledsOn, 0);
    SetPixels(m_output->GetNrOfOutputs() - ledsOn - 1, 1, lastBrightness);
    SetPixels(m_output->GetNrOfOutputs() - ledsOn, ledsOn, m_brightness);
  }
  else if (m_fadeOutType == CFX_FadeCenterIn)
  {
    uint16_t centerpixel = m_output->GetNrOfOutputs() / 2;
    
    SetPixels(0, centerpixel - 1 - ledsOn, 0);
    SetPixels(centerpixel - 1 - ledsOn, 1, lastBrightness);
    SetPixels(centerpixel - ledsOn, ledsOn, m_brightness);
    
    SetPixels(centerpixel, ledsOn, m_brightness);
    SetPixels(centerpixel + ledsOn, 1, lastBrightness);
    SetPixels(centerpixel + ledsOn + 1, centerpixel - ledsOn - 1, 0);
  }

  return returnval;
}

void CFX_LedStripAnimationFadeInOut::SetPixels(uint16_t start, uint16_t length, uint8_t brightness)
{
  for (uint16_t pixel = start; pixel < start + length; pixel++)
  {
    m_output->SetPixelBrightness(pixel, brightness);
  }
}