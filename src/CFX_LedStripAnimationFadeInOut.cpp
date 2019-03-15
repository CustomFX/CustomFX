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
  CFX_LedStripBase* output, CFX_FadeType fadeInType, CFX_FadeType fadeOutType)
  : CFX_LedStripAnimationFadeInOut(fadeInTime, fadeOutTime, output, fadeInType, 
  fadeOutType, CFX_Color(0), 255)
{
  m_useColor = false;
}

CFX_LedStripAnimationFadeInOut::CFX_LedStripAnimationFadeInOut(
  unsigned long fadeInTime, unsigned long fadeOutTime, 
  CFX_LedStripBase* output, CFX_FadeType fadeInType, 
      CFX_FadeType fadeOutType, CFX_Color color, uint8_t brightness)
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

void CFX_LedStripAnimationFadeInOut::DisableColor(bool disable)
{
  m_useColor = !disable;
}

void CFX_LedStripAnimationFadeInOut::SetTimes(unsigned long fadeInTime, unsigned long fadeOutTime)
{
  m_fadeInTime = fadeInTime;
  m_fadeOutTime = fadeOutTime;
}

bool CFX_LedStripAnimationFadeInOut::InitializeAnimation(int timestep)
{
  if (m_output)
  {
    m_totallevels = m_brightness * m_output->GetNrOfOutputs();
    m_totalsteps = m_fadeInTime / ANIMATION_UPDATE_INTERVAL;
    Serial.print("m_totallevels: ");
    Serial.println(m_totallevels);
    Serial.print("m_totalsteps: ");
    Serial.println(m_totalsteps);
    
    if (m_totalsteps == 0)
    { 
      m_totalsteps = 1;
    }
    
    m_step = 0;
    m_fadingIn = true;
  }
  return true;
}

bool CFX_LedStripAnimationFadeInOut::UpdateAnimation(int timestep)
{
  if (m_output)
  {
    m_step++;
    
    if (m_fadingIn)
    {
      if (UpdateFadeIn(timestep))
      {
        // Finished fading in, calculate fade out steps
        m_totalsteps = m_fadeOutTime / ANIMATION_UPDATE_INTERVAL;
        m_fadingIn = false;
      }
    }
    else
    {
      if (UpdateFadeOut(timestep))
      {
        // fade out complete, calculate fade in steps for next repetition
        m_totalsteps = m_fadeInTime / ANIMATION_UPDATE_INTERVAL;
        m_fadingIn = true;
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
  uint32_t value = m_step * m_totallevels / m_totalsteps;
  uint8_t  lastBrightness = value % m_brightness;
  uint16_t ledsOn = value / m_brightness;


  if (m_fadeInType == CFX_FadeLeftRight)
  {
    UpdatePixels(0, ledsOn, m_brightness, lastBrightness);
  }
  else if (m_fadeInType == CFX_FadeLeftRight)
  {
    UpdatePixels(m_output->GetNrOfOutputs() - ledsOn, ledsOn, lastBrightness, m_brightness);
  }
  else if (m_fadeInType == CFX_FadeCenterOut)
  {
    
  }
  else if (m_fadeInType == CFX_FadeOutCenter)
  {
    
  }
  
  if (ledsOn == m_output->GetNrOfOutputs())
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool CFX_LedStripAnimationFadeInOut::UpdateFadeOut(int timestep)
{
  uint32_t value = m_step * m_totallevels / m_totalsteps;
  uint8_t  lastBrightness = m_brightness - value % m_brightness;
  uint16_t ledsOff = value / m_brightness;

  Serial.print("value: ");
  Serial.println(value);
  Serial.print("lastBrightness: ");
  Serial.println(lastBrightness);
  Serial.print("ledsOff: ");
  Serial.println(ledsOff);

  if (m_fadeInType == CFX_FadeLeftRight)
  {
    UpdatePixels(0, ledsOff, 0, lastBrightness);
  }
  else if (m_fadeInType == CFX_FadeLeftRight)
  {//m_output->GetNrOfOutputs() - ledsOff
    UpdatePixels(0, ledsOff, lastBrightness, 0);
  }
  else if (m_fadeInType == CFX_FadeCenterOut)
  {
    
  }
  else if (m_fadeInType == CFX_FadeOutCenter)
  {
    
  }

  if (ledsOff == m_output->GetNrOfOutputs())
  {
    return true;
  }
  else
  {
    return false;
  }
}

void CFX_LedStripAnimationFadeInOut::UpdatePixels(uint16_t first_led, uint16_t length, 
  uint8_t firstBrightness, uint8_t lastBrightness)
{
  Serial.print(first_led);
  Serial.print(" - ");
  Serial.println(firstBrightness);
  m_output->SetPixelBrightness(first_led, firstBrightness);
  for (uint16_t pixel = first_led + 1; pixel < length + first_led; pixel++)
  {
  Serial.print(pixel);
  Serial.print(" - ");
  Serial.println(m_brightness);
    if (m_useColor)
    {
      m_output->SetPixelColor(pixel, m_color);
    }
    m_output->SetPixelBrightness(pixel, m_brightness);
  }
  
  Serial.print(first_led + length);
  Serial.print(" - ");
  Serial.println(lastBrightness);
  m_output->SetPixelBrightness(first_led + length, lastBrightness);
}
