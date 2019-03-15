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

#include <CFX_LedStripAnimationSweep.hpp>
#include <CustomFX.h>

CFX_LedStripAnimationSweep::CFX_LedStripAnimationSweep()
  : CFX_AnimationBase()
{
  m_output = 0;
}

CFX_LedStripAnimationSweep::CFX_LedStripAnimationSweep(CFX_Color color, unsigned long time_on, 
  unsigned long fadeouttime, CFX_LedStripBase* output, int id)
  : CFX_LedStripAnimationSweep(0, 1, color, time_on, fadeouttime, output, id)
{
}


CFX_LedStripAnimationSweep::CFX_LedStripAnimationSweep(uint16_t startled, int8_t direction, CFX_Color color,
  unsigned long time_on, unsigned long fadeouttime, CFX_LedStripBase* output, int id) 
  : CFX_AnimationBase(id)
{
  m_output = output;
  m_color = color;
  m_useColor = true;
  m_fadeouttime = fadeouttime;
  m_currentStep = 0;
  m_stoppedSteps = 0;
  m_onSteps = time_on / ANIMATION_UPDATE_INTERVAL;
  if (m_onSteps == 0) m_onSteps = 1;
  m_startled = startled;
  m_activeLed = startled;
  CalculateFadeOutSteps(fadeouttime);

  if (direction == 1) m_direction = 1;
  else m_direction = -1;
}

void CFX_LedStripAnimationSweep::SetOutputDevice(CFX_LedStripBase* output)
{
  m_output = output;
  RestartAnimation();
}

void CFX_LedStripAnimationSweep::SetTimes(unsigned long time_on, unsigned long fadeouttime)
{
  m_onSteps = time_on / ANIMATION_UPDATE_INTERVAL;  
  if (m_onSteps == 0) m_onSteps = 1;
  CalculateFadeOutSteps(fadeouttime);
}

void CFX_LedStripAnimationSweep::SetColor(CFX_Color color)
{
  m_color = color;
  CalculateFadeOutSteps(m_fadeouttime);
  m_useColor = true;
}

void CFX_LedStripAnimationSweep::DisableColor()
{
  m_useColor = false;
}

void CFX_LedStripAnimationSweep::SetDirection(int8_t direction)
{
  if (direction == 1) m_direction = 1;
  else m_direction = -1;
}

int8_t CFX_LedStripAnimationSweep::GetDirection() const
{
  return m_direction;
}

void CFX_LedStripAnimationSweep::CalculateFadeOutSteps(unsigned long fadeouttime)
{
  if (fadeouttime == 0)
  {
    m_fadeouttime = 1;
  }
  else
  {
    m_fadeouttime = fadeouttime;
  }
  
  m_fadeOutStepSize = 255 / ((float)m_fadeouttime / ANIMATION_UPDATE_INTERVAL);
}

bool CFX_LedStripAnimationSweep::InitializeAnimation(int timestep)
{  
  m_trailLength = 0;
  m_stoppedSteps = 0;
  m_currentStep = 0;

  if (m_output)
  {
    m_output->SetBrightness(0);
    m_activeLed = constrain(m_startled, 0, m_output->GetNrOfOutputs());
  }
  return true;
}

bool CFX_LedStripAnimationSweep::FinishAnimation(int timeStep)
{
  if (m_output)
  {
    m_stoppedSteps++;
    return UpdateTrail(timeStep);
  }
  else
  {
    return true;
  }
}

void CFX_LedStripAnimationSweep::RestartAnimation()
{
  m_activeLed = 0;
  this->Start();
}

bool CFX_LedStripAnimationSweep::UpdateAnimation(int timeStep)
{
  bool returnValue;
  if (m_output)
  {
    returnValue = UpdateHead(timeStep);
    UpdateTrail(timeStep);
    return returnValue;
  }
  else
  {
    return true;
  }
}

bool CFX_LedStripAnimationSweep::UpdateHead(int timeStep)
{
  if (m_currentStep >= m_onSteps) // progress to next led?
  {
    m_activeLed = m_output->NextPixel(m_activeLed, m_direction);
   
    // update trail length
    m_trailLength++;
    if (m_trailLength >= m_output->GetNrOfOutputs())
    {
      m_trailLength = m_output->GetNrOfOutputs();
    }

    m_currentStep = 0;
    if (m_activeLed == m_startled)
    {
      return true;
    }
  }
  else
  {
    m_currentStep++;

    if (m_useColor)
    {
      m_output->SetPixelColor(m_activeLed, m_color);
    }
    m_output->SetPixelBrightness(m_activeLed, (uint8_t)(((float)(m_currentStep) / m_onSteps) * 255));
  }
  return false;
}

bool CFX_LedStripAnimationSweep::UpdateTrail(int timeStep)
{ 
  if (m_trailLength > 0)
  {
    for (uint16_t trail = 1; trail <= m_trailLength; trail++)
    {
      int elapsedSteps = trail * m_onSteps + m_currentStep + m_stoppedSteps;
      int newbrightness = 255 - elapsedSteps * m_fadeOutStepSize;
      if (newbrightness < 0)
      {
        newbrightness = 0;
        m_trailLength--;
      }
      m_output->SetPixelBrightness(m_output->NextPixel(m_activeLed, trail * -m_direction), (uint8_t)newbrightness);
    } 
    return false;
  }
  else if (m_stoppedSteps > 0 && m_currentStep > 0)
  {
    m_currentStep--;
    m_output->SetPixelBrightness(m_activeLed, (uint8_t)(((float)(m_currentStep) / m_onSteps) * 255));
    return false;
  }
  else
  {
    return true;
  }
}

