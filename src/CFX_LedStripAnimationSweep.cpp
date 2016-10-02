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
  unsigned long fadeouttime, CFX_LedStrip* output)
  : CFX_LedStripAnimationSweep(0, 1, color, time_on, fadeouttime, output)
{
}


CFX_LedStripAnimationSweep::CFX_LedStripAnimationSweep(uint8_t startled, int8_t direction, CFX_Color color,
  unsigned long time_on, unsigned long fadeouttime, CFX_LedStrip* output) 
  : CFX_AnimationBase()
{
  m_output = output;
  m_color = color;
  m_fadeouttime = fadeouttime;
  m_currentStep = 0;
  m_stopped = false;
  m_stoppedSteps = 0;
  m_onSteps = time_on / ANIMATION_UPDATE_INTERVAL;
  if (m_onSteps == 0) m_onSteps = 1;
  
  CalculateFadeOutSteps(fadeouttime);
  m_trailLength = 1;

  if (m_output)
  {
    m_activeLed = constrain(startled, 0, m_output->GetNrOfOutputs()); // todo limit
  }
  else
  {
    m_activeLed = 0;
  }
  m_output->SetPixelColor(m_activeLed, m_color);
  m_output->SetPixelBrightness(m_activeLed, 255);

  if (direction == 1) m_direction = 1;
  else m_direction = -1;
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
  m_fadeouttime = fadeouttime;
  m_fadeOutStepSize = (float)255 / (fadeouttime / ANIMATION_UPDATE_INTERVAL);
}

void CFX_LedStripAnimationSweep::Start()
{
  m_stopped = false;
  m_stoppedSteps = 0;
  CFX_AnimationBase::Start();
}

void CFX_LedStripAnimationSweep::Stop(bool fadeout)
{
  m_stopped = true;
  if (!fadeout)
  {
    CFX_AnimationBase::Stop();
  }
}

bool CFX_LedStripAnimationSweep::IsActive() const
{
  return !m_stopped;
}

void CFX_LedStripAnimationSweep::UpdateAnimation(int timeStep)
{
  if (m_output)
  {
    if (!m_stopped)
    {
      if (m_currentStep >= m_onSteps) // progress to next led?
      {
        m_activeLed += m_direction;
        if (m_activeLed - (int8_t) m_output->GetNrOfOutputs() >= 0)
        {
          m_activeLed = 0;
        }
        else if (m_activeLed < 0)
        {
          m_activeLed = m_output->GetNrOfOutputs() - 1;
        }
        
        // turn on current led
        m_output->SetPixelColor(m_activeLed, m_color);
        m_output->SetPixelBrightness(m_activeLed, 255);
        // update trail length
        m_trailLength++;
        if (m_trailLength >= m_output->GetNrOfOutputs())
        {
          m_trailLength = m_output->GetNrOfOutputs();
        }
    
        m_currentStep = 0;
      }
      else
      {
        m_currentStep++;
      }
    }
    else
    {
      m_stoppedSteps++;
    }
    // set trail
    uint8_t trail = m_trailLength;
    int8_t led = m_activeLed;
    uint8_t newbrightness = 255;
    while (trail > 0)
    {
      int elapsedSteps = (m_trailLength - trail) * m_onSteps + m_currentStep + m_stoppedSteps;
      int correction = elapsedSteps * m_fadeOutStepSize;
      if (correction > 255)
      {
        correction = 255;
        m_trailLength--;
      }
      uint8_t currentBrightness = 255;
      if (currentBrightness < correction)
      {
        newbrightness = 0;
      }
      else
      {
        newbrightness = currentBrightness - correction;
      }
      m_output->SetPixelBrightness(led, newbrightness);
      trail--;

      led -= m_direction;
      if (led < 0)
      {
        led = m_output->GetNrOfOutputs() - 1;
      }
      else if (led - (int8_t) m_output->GetNrOfOutputs() >= 0)
      {
        led = 0;
      }
    }
  }
}
