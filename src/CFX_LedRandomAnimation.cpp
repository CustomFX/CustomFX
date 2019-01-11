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

#include <CustomFX.h>
#include <CFX_LedRandomAnimation.hpp>

CFX_LedRandomAnimation::CFX_LedRandomAnimation(uint8_t minvalue, uint8_t maxvalue, 
  uint16_t mindelay, uint16_t maxdelay, CFX_LedBase* output) : CFX_AnimationBase()
{
  m_output = output;
  
  m_minvalue = minvalue;
  m_maxvalue = maxvalue;
  m_mindelay = mindelay;
  m_maxdelay = maxdelay;
}

void CFX_LedRandomAnimation::SetBrightness(uint8_t minvalue, uint8_t maxvalue)
{
  m_minvalue = minvalue;
  m_maxvalue = maxvalue;
}

void CFX_LedRandomAnimation::SetTimes(uint16_t mindelay, uint16_t maxdelay)
{
  m_mindelay = mindelay;
  m_maxdelay = maxdelay;
}

void CFX_LedRandomAnimation::NextStep()
{
  SetStepSizes(random(m_minvalue, m_maxvalue), random(m_mindelay, m_maxdelay));
}

void CFX_LedRandomAnimation::SetStepSizes(uint8_t brightness, uint16_t duration)
{
  m_totalIncrements = duration / ANIMATION_UPDATE_INTERVAL;
  if (m_totalIncrements == 0) m_totalIncrements = 1; // a minimum of 1 increment is required
  m_stepIncrement = 0;

  m_brightnessIncrement = 
    (float)(brightness - m_output->GetBrightness()) / m_totalIncrements;
}

void CFX_LedRandomAnimation::RestartAnimation()
{
  m_stepIncrement = 0;
  m_brightness = m_output->GetBrightness();
}

bool CFX_LedRandomAnimation::UpdateAnimation(int timeStep)
{
  bool returnval = false;
  m_stepIncrement++;
  m_brightness += m_brightnessIncrement;
  if (m_brightness > 255)
  {
    m_output->SetBrightness(255);
  }
  else if (m_brightness < 0)
  {
    m_output->SetBrightness(0);
  }
  else
  {
    m_output->SetBrightness(m_brightness);
  }

  if (m_stepIncrement >= m_totalIncrements)
  {
    NextStep();
    returnval = true;
  }
  return returnval;
}