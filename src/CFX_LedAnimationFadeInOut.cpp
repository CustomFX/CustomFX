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

   

CFX_LedAnimationFadeInOut::CFX_LedAnimationFadeInOut(uint16_t fadeInTime, uint16_t onTime, 
  uint16_t fadeOutTime, uint16_t offTime, CFX_LedBase* output) : CFX_LedAnimationSequence(4, output)
{
  m_fadeInTime = fadeInTime;
  m_onTime = onTime;
  m_offTime = offTime;
  m_fadeOutTime = fadeOutTime;
  m_brightness = 255; // default brightness

  AddStep(m_brightness, m_fadeInTime, CFX_Transition_Lineair);
  AddStep(m_brightness, m_onTime, CFX_Transition_Block);
  AddStep(0, m_fadeOutTime, CFX_Transition_Lineair);
  AddStep(0, m_offTime, CFX_Transition_Block);
}

void CFX_LedAnimationFadeInOut::SetTimes(uint16_t fadeInTime, uint16_t onTime, uint16_t fadeOutTime,
  uint16_t offTime)
{
  m_fadeInTime = fadeInTime;
  m_onTime = onTime;
  m_offTime = offTime;
  m_fadeOutTime = fadeOutTime;

  ChangeStep(0, m_brightness, m_fadeInTime, CFX_Transition_Lineair);
  ChangeStep(1, m_brightness, m_onTime, CFX_Transition_Block);
  ChangeStep(2, 0, m_fadeOutTime, CFX_Transition_Lineair);
  ChangeStep(3, 0, m_offTime, CFX_Transition_Block);  
}

void CFX_LedAnimationFadeInOut::SetBrightness(uint8_t brightness)
{
  m_brightness = brightness;
  ChangeStep(0, m_brightness, m_fadeInTime, CFX_Transition_Lineair);
  ChangeStep(1, m_brightness, m_onTime, CFX_Transition_Block);
}

