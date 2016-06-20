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
  : CFX_LedStripAnimationSweep(0, 1, color, time_on, fadeouttime, true, true, output)
{
}


CFX_LedStripAnimationSweep::CFX_LedStripAnimationSweep(int startled, int8_t direction, CFX_Color color,
  unsigned long time_on, unsigned long fadeouttime, bool loop, bool repeat, CFX_LedStrip* output) 
  : CFX_AnimationBase()
{
  m_output = output;
  m_color = color;
  m_fadeouttime = fadeouttime;
  m_currentStep = 0;
  m_onSteps = time_on / ANIMATION_UPDATE_INTERVAL;
  if (m_onSteps == 0) m_onSteps = 1;
  
  CalculateFadeOutSteps(fadeouttime);
  m_trailLength = 0; // initially there is no trail

  if (m_output)
  {
    m_activeLed = constrain(startled, 0, m_output->GetNrOfOutputs()); // todo limit
  }
  else
  {
    m_activeLed = 0;
  }
  m_loop = loop;
  m_repeat = repeat;
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
  if (fadeouttime == 0)
  {
    m_fadeOutStepSize[0] = (float)m_color.Red();
    m_fadeOutStepSize[1] = (float)m_color.Green();
    m_fadeOutStepSize[2] = (float)m_color.Blue();
  }
  else
  {
    m_fadeOutStepSize[0] = (float)m_color.Red() / (fadeouttime / ANIMATION_UPDATE_INTERVAL);
    m_fadeOutStepSize[1] = (float)m_color.Green() / (fadeouttime / ANIMATION_UPDATE_INTERVAL);
    m_fadeOutStepSize[2] = (float)m_color.Blue() / (fadeouttime / ANIMATION_UPDATE_INTERVAL);
  }
}


void CFX_LedStripAnimationSweep::UpdateAnimation(int timeStep)
{
  if (m_output)
  {
    if (m_currentStep >= m_onSteps) // progress to next led?
    {
      m_activeLed += m_direction;
      if (m_activeLed >= m_output->GetNrOfOutputs())
      {
        m_activeLed = 0;
      }
      else if (m_activeLed < 0)
      {
        m_activeLed = m_output->GetNrOfOutputs();
      }
      m_currentStep = 0;
      
      // update trail lenght
      m_trailLength++;
      if (m_trailLength >= m_output->GetNrOfOutputs())
      {
        m_trailLength = m_output->GetNrOfOutputs();
      }
    }
    else
    {
      m_currentStep++;
    }
   
    // turn on current led 
    m_output->SetPixelColor(m_activeLed, m_color);

    // set trail
    int trail = m_trailLength;
    int led = m_activeLed;
    while (trail > 0)
    {
      // todo: check direction
      led -= m_direction;
      if (led < 0)
      {
        led = m_output->GetNrOfOutputs() - 1;
      }
      else if (led >= m_output->GetNrOfOutputs())
      {
        led = 0;
      }
      int factor = (m_trailLength - trail) * m_onSteps + m_currentStep;
      CFX_Color colorCorrection(factor * m_fadeOutStepSize[0], 
                                factor * m_fadeOutStepSize[1],
                                factor * m_fadeOutStepSize[2]);
      
      if (colorCorrection.Red() > m_color.Red()) colorCorrection.SetRed(m_color.Red());
      if (colorCorrection.Green() > m_color.Green()) colorCorrection.SetGreen(m_color.Green());
      if (colorCorrection.Blue() > m_color.Blue()) colorCorrection.SetBlue(m_color.Blue());
      
      if (colorCorrection == m_color) m_trailLength--;
      //CFX_Color newColor = m_color - colorCorrection;
      CFX_Color newColor(m_color.Red() - colorCorrection.Red(), 
                         m_color.Green() - colorCorrection.Green(), 
                         m_color.Blue() - colorCorrection.Blue());
      /*Serial.print("m_color: ");
      Serial.print(m_color.toString());
      Serial.print(" color correction: ");
      Serial.print(colorCorrection.toString());
      Serial.print(" new color: ");
      Serial.println(newColor.toString());
      */
      m_output->SetPixelColor(led, newColor);
      trail--;
    }
  }
}
