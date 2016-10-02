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

#include <CFX_LedAnimationFadeInOut.hpp>

   

CFX_LedAnimationFadeInOut::CFX_LedAnimationFadeInOut()
  : CFX_AnimationBase()
{
  m_output = 0;
  m_brightness = 0;
  m_fadeInStep = 0;
  m_fadeOutStep = 0;
  m_animationStep = 0;
  m_totalAnimationSteps = 0;
}


CFX_LedAnimationFadeInOut::CFX_LedAnimationFadeInOut(int fadeInTime, int onTime, 
  int fadeOutTime, int offTime, CFX_Led* output) : CFX_AnimationBase()
{
  m_output = output;
  m_brightness = 255; // default brightness
  m_fadeInStep = 0;
  m_fadeOutStep = 0;
  m_animationStep = 0;
  m_totalAnimationSteps = 0;
  SetTimes(fadeInTime, onTime, fadeOutTime, offTime);
}

void CFX_LedAnimationFadeInOut::SetTimes(int fadeInTime, int onTime, int fadeOutTime, int offTime)
{
  m_fadeInSteps = fadeInTime / ANIMATION_UPDATE_INTERVAL;
  m_onSteps = onTime / ANIMATION_UPDATE_INTERVAL;
  m_fadeOutSteps = fadeOutTime / ANIMATION_UPDATE_INTERVAL;
  m_offSteps = offTime / ANIMATION_UPDATE_INTERVAL;
  
  m_totalAnimationSteps = m_fadeInSteps + m_onSteps + m_fadeOutSteps + m_offSteps;
  
  SetStepSizes();
}

void CFX_LedAnimationFadeInOut::SetBrightness(uint8_t brightness)
{
  m_brightness = brightness;
  
  SetStepSizes();
}

void CFX_LedAnimationFadeInOut::SetOutputDevice(CFX_Led* output)
{
  m_output = output;
}

void CFX_LedAnimationFadeInOut::SetStepSizes()
{
  if (m_fadeInSteps > 0)
  {
    m_fadeInStep = (float)m_brightness / m_fadeInSteps;
  }
  else
  {
    m_fadeInStep = (float)m_brightness;
  }
  
  if (m_fadeOutSteps > 0)
  {
    m_fadeOutStep = (float)m_brightness / m_fadeOutSteps;
  }
  else
  {
    m_fadeOutStep = (float)m_brightness;
  }
}

void CFX_LedAnimationFadeInOut::UpdateAnimation(int timeStep)
{
  if (m_output)
  {
    if (m_animationStep < m_fadeInSteps)
    {
      m_output->SetBrightness(uint8_t(m_animationStep * m_fadeInStep));
    }
    else if (m_animationStep < m_onSteps + m_fadeInSteps)
    {
      m_output->SetBrightness(m_brightness);
    }
    else if (m_animationStep < m_fadeOutSteps + m_onSteps + m_fadeInSteps)
    {
      m_output->SetBrightness(m_brightness - uint8_t((m_animationStep - m_onSteps - m_fadeInSteps) * m_fadeInStep));
    }
    else
    {
      m_output->SetBrightness(0);
    }
    m_animationStep++;
    if (m_animationStep > m_totalAnimationSteps)
    {
      m_animationStep = 0;
    }
  }
}