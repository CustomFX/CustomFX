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

#include <CFX_RGBLedAnimationFadeInOut.hpp>

CFX_RGBLedAnimationFadeInOut::CFX_RGBLedAnimationFadeInOut()
  : CFX_AnimationBase()
{
  m_output = 0;
  
  m_fadeInStepRed = 0;
  m_fadeInStepGreen = 0;
  m_fadeInStepBlue = 0;
  m_fadeOutStepRed = 0;
  m_fadeOutStepGreen = 0;
  m_fadeOutStepBlue = 0;
  
  m_animationStep = 0;
  m_totalAnimationSteps = 0;
}

CFX_RGBLedAnimationFadeInOut::CFX_RGBLedAnimationFadeInOut(int fadeInTime, int onTime, int fadeOutTime,
  int offTime, CFX_Color color, CFX_RGBLed* output) : CFX_AnimationBase()
{
  m_output = output;

  m_fadeInStepRed = 0;
  m_fadeInStepGreen = 0;
  m_fadeInStepBlue = 0;
  m_fadeOutStepRed = 0;
  m_fadeOutStepGreen = 0;
  m_fadeOutStepBlue = 0;
  
  m_animationStep = 0;
  m_totalAnimationSteps = 0;
  m_color = color;
  SetTimes(fadeInTime, onTime, fadeOutTime, offTime);
}

void CFX_RGBLedAnimationFadeInOut::SetTimes(int fadeInTime, int onTime, int fadeOutTime, int offTime)
{
  m_fadeInSteps = fadeInTime / ANIMATION_UPDATE_INTERVAL;
  m_onSteps = onTime / ANIMATION_UPDATE_INTERVAL;
  m_fadeOutSteps = fadeOutTime / ANIMATION_UPDATE_INTERVAL;
  m_offSteps = offTime / ANIMATION_UPDATE_INTERVAL;
  
  m_totalAnimationSteps = m_fadeInSteps + m_onSteps + m_fadeOutSteps + m_offSteps;
  
  SetStepSizes();
}

void CFX_RGBLedAnimationFadeInOut::SetColor(CFX_Color color)
{
  m_color = color;
  
  SetStepSizes();
}

void CFX_RGBLedAnimationFadeInOut::SetOutputDevice(CFX_RGBLed* output)
{
  m_output = output;
}

void CFX_RGBLedAnimationFadeInOut::SetStepSizes()
{
  if (m_fadeInSteps > 0)
  {
    m_fadeInStepRed = (float)m_color.Red() / m_fadeInSteps;
    m_fadeInStepGreen = (float)m_color.Green() / m_fadeInSteps;
    m_fadeInStepBlue = (float)m_color.Blue() / m_fadeInSteps;
  }
  else
  {
    m_fadeInStepRed = (float)m_color.Red();
    m_fadeInStepGreen = (float)m_color.Green();
    m_fadeInStepBlue = (float)m_color.Blue();
  }
  
  if (m_fadeOutSteps > 0)
  {
    m_fadeOutStepRed = (float)m_color.Red() / m_fadeOutSteps;
    m_fadeOutStepGreen = (float)m_color.Green() / m_fadeOutSteps;
    m_fadeOutStepBlue = (float)m_color.Blue() / m_fadeOutSteps;
    
  }
  else
  {
    m_fadeOutStepRed = (float)m_color.Red();
    m_fadeOutStepGreen = (float)m_color.Green();
    m_fadeOutStepBlue = (float)m_color.Blue();
  }
}

bool CFX_RGBLedAnimationFadeInOut::UpdateAnimation(int timeStep)
{
  bool returnval = false;
  if (m_output)
  {
    if (m_animationStep < m_fadeInSteps)
    {
      m_output->SetColor(CFX_Color(uint8_t(m_animationStep * m_fadeInStepRed), 
                                   uint8_t(m_animationStep * m_fadeInStepGreen),
                                   uint8_t(m_animationStep * m_fadeInStepBlue)));
    }
    else if (m_animationStep < m_onSteps + m_fadeInSteps)
    {
      m_output->SetColor(m_color);
    }
    else if (m_animationStep < m_fadeOutSteps + m_onSteps + m_fadeInSteps)
    {
      uint8_t step = m_animationStep - m_onSteps - m_fadeInSteps;
      m_output->SetColor(CFX_Color(m_color.Red() - step * m_fadeOutStepRed, 
                                   m_color.Green() - step * m_fadeOutStepGreen,
                                   m_color.Blue() - step * m_fadeOutStepBlue));
    }
    else
    {
      m_output->SetColor(CFX_Color(0));
    }
    m_animationStep++;
    if (m_animationStep > m_totalAnimationSteps)
    {
      m_animationStep = 0;
      returnval = true;
    }
  }
  return returnval;
}