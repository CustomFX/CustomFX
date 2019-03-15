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

#include <CFX_LedStripAnimationTwinkle.hpp>
#include <CustomFX.h>

CFX_LedStripAnimationTwinkle::CFX_LedStripAnimationTwinkle()
  : CFX_AnimationBase()
{
  m_output = 0;
}

CFX_LedStripAnimationTwinkle::CFX_LedStripAnimationTwinkle(const CFX_Color& color,
  CFX_LedStripBase* output)
  : CFX_AnimationBase()
{
  m_output = output;
  m_brightness = 255;
  m_useColor = true;
  m_color = color;
  m_twinkleOn = false;
  m_minOnDelay = 50;
  m_maxOnDelay = 250;
  m_onTime = 50;
  NextStep();
}

void CFX_LedStripAnimationTwinkle::SetOutputDevice(CFX_LedStripBase* output)
{
  m_output = output;
}

void CFX_LedStripAnimationTwinkle::SetColor(CFX_Color color)
{
  m_useColor = true;
  m_color = color;
}

void CFX_LedStripAnimationTwinkle::DisableColor()
{
  m_useColor = false;
}

void CFX_LedStripAnimationTwinkle::SetBrightness(uint8_t brightness)
{
  m_brightness = brightness;
}

bool CFX_LedStripAnimationTwinkle::InitializeAnimation(int timeStep)
{
  m_twinkleOn = false;
  if (m_output)
  {
    m_output->SetBrightness(0);
  }
  NextStep();
  return true;
}

void CFX_LedStripAnimationTwinkle::SetTimes(uint16_t minOnDelay, uint16_t maxOnDelay, uint16_t onTime)
{
  m_minOnDelay = minOnDelay;
  m_maxOnDelay = maxOnDelay;
  m_onTime = onTime;
}

void CFX_LedStripAnimationTwinkle::NextStep()
{
  if (m_twinkleOn)
  {
    m_targetStep = m_onTime/ANIMATION_UPDATE_INTERVAL; // turn off after 100ms
  }
  else
  {
    m_targetStep = random(m_minOnDelay, m_maxOnDelay)/ANIMATION_UPDATE_INTERVAL; // next twinkle after 100-500ms
  }
  m_step = 0;
}

bool CFX_LedStripAnimationTwinkle::UpdateAnimation(int timeStep)
{
  if (m_output)
  {
    if (m_step >= m_targetStep)
    {
      if (m_twinkleOn)
      {
        m_twinkleOn = false;
        m_output->SetBrightness(0);
      }
      else
      {
        m_twinkleOn = true;
        uint16_t pixel = random(0, m_output->GetNrOfOutputs());
        if (m_useColor)
        {
          m_output->SetPixelColor(pixel, m_color);
        }
        m_output->SetPixelBrightness(pixel, m_brightness);
      }
      NextStep();
    }
    m_step++;
  }
  return false;
}

bool CFX_LedStripAnimationTwinkle::FinishAnimation(int timestep)
{
  if (m_output)
  {
    if (m_step >= m_targetStep)
    {
      if (m_twinkleOn)
      {
        m_twinkleOn = false;
        m_output->SetBrightness(0);
        return true;
      }
    }
    m_step++;
  }
  return false;
}