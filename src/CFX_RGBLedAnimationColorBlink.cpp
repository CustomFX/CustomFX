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

#include <CFX_RGBLedAnimationColorBlink.hpp>

CFX_RGBLedAnimationColorBlink::CFX_RGBLedAnimationColorBlink() : CFX_AnimationBase()
{
  m_blinkOnTime = 0;
  m_blinkOffTime = 0;
  m_output = 0;
  m_previousUpdateTime = 0;
  m_blinkon = false;
}

CFX_RGBLedAnimationColorBlink::CFX_RGBLedAnimationColorBlink(unsigned long onTime, unsigned long offTime, CFX_RGBLed* output)
  : CFX_AnimationBase()
{
  m_blinkOnTime = onTime;
  m_blinkOffTime = offTime;
  m_output = output;
  m_previousUpdateTime = 0;
  m_blinkon = false;
}

void CFX_RGBLedAnimationColorBlink::SetColor(const CFX_Color& color)
{
  m_color = color;
}

void CFX_RGBLedAnimationColorBlink::SetTimes(unsigned long onTime, unsigned long offTime)
{
  m_blinkOnTime = onTime;
  m_blinkOffTime = offTime;
}

void CFX_RGBLedAnimationColorBlink::SetOutputDevice(CFX_RGBLed* output)
{
  m_output = output;
}

void CFX_RGBLedAnimationColorBlink::UpdateAnimation(int timeStep)
{
  if (m_output)
  {
    if ((!m_blinkon) && (millis() - m_previousUpdateTime >= m_blinkOffTime))
    {
      m_previousUpdateTime = millis();
      m_output->SetColor(m_color);
      m_blinkon = true;
    }
    else if (millis() - m_previousUpdateTime >= m_blinkOnTime)
    {
      m_previousUpdateTime = millis();
      m_output->SetColor(CFX_Color(0));
      m_blinkon = false;
    }
  }
}
    
