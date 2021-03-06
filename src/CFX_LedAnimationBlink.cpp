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

#include <CFX_LedAnimationBlink.hpp>

CFX_LedAnimationBlink::CFX_LedAnimationBlink(unsigned long onTime, unsigned long offTime, 
  CFX_LedBase* output) : CFX_LedAnimationBlink(onTime, offTime, 0, output)
{
}

CFX_LedAnimationBlink::CFX_LedAnimationBlink(unsigned long onTime, unsigned long offTime, 
  unsigned long startdelay, CFX_LedBase* output) : CFX_LedAnimationSequence(2, output)
{
  m_blinkOnTime = onTime;
  m_blinkOffTime = offTime;
  m_brightness = 255;
  m_minbrightness = 0;
  AddStep(m_brightness, m_blinkOnTime, CFX_No_Transition);
  AddStep(m_minbrightness, m_blinkOffTime, CFX_No_Transition);
  SetDelay(startdelay);
}

void CFX_LedAnimationBlink::SetBrightness(uint8_t brightness)
{
  m_brightness = brightness;
  ChangeStep(0, m_brightness, m_blinkOnTime, CFX_No_Transition);
}

void CFX_LedAnimationBlink::SetMinBrightness(uint8_t brightness)
{
  m_minbrightness = brightness;
  ChangeStep(1, m_minbrightness, m_blinkOffTime, CFX_No_Transition);
}

void CFX_LedAnimationBlink::SetTimes(unsigned long onTime, unsigned long offTime)
{
  m_blinkOnTime = onTime;
  m_blinkOffTime = offTime;
  ChangeStep(0, m_brightness, m_blinkOnTime, CFX_No_Transition);
  ChangeStep(1, m_minbrightness, m_blinkOffTime, CFX_No_Transition);
}