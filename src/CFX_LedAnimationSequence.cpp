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
#include <CFX_LedAnimationSequence.hpp>

CFX_LedAnimationSequence::CFX_LedAnimationSequence(uint16_t steps, CFX_LedBase* output, int id)
  : CFX_AnimationBase(id)
{
  m_output = output;
  m_steps = new CFX_LedAnimationSequenceStep[steps];
  
  m_totalSteps = steps;
  m_definedSteps = 0;
  m_activeStep = 0;
  m_startBrightness = 0;
  m_initialBrightness = 0;
  m_stepIncrement = 0;
  m_totalIncrements = 0;
}

void CFX_LedAnimationSequence::AddStep(uint8_t brightness, uint16_t duration, CFX_TransitionType type)
{
  if (m_definedSteps < m_totalSteps)
  {
    m_steps[m_definedSteps].duration = duration;
    m_steps[m_definedSteps].brightness = brightness;
    m_steps[m_definedSteps].type = type;
    m_definedSteps++;
  }
  if (m_definedSteps == 1) // first step defined
  {
    SetStepSizes(0);
  }
}

void CFX_LedAnimationSequence::ChangeStep(uint16_t step, uint8_t brightness, uint16_t duration,
  CFX_TransitionType type)
{
  if (step < m_totalSteps)
  {
    m_steps[step].duration = duration;
    m_steps[step].brightness = brightness;
    m_steps[step].type = type;
  }
}

void CFX_LedAnimationSequence::SetInitialBrightness(uint8_t brightness)
{
  m_initialBrightness = brightness;
}    

bool CFX_LedAnimationSequence::InitializeAnimation(int timestep)
{
  m_activeStep = 0;
  if (m_activeStep < m_definedSteps)
  {
    SetStepSizes(m_activeStep);
    //m_startBrightness = m_initialBrightness;
  }
  return true;
}

bool CFX_LedAnimationSequence::NextStep()
{
  m_activeStep++;
  if (m_activeStep < m_definedSteps)
  {
    SetStepSizes(m_activeStep);
    return false;
  }
  else
  {
    m_activeStep = 0;
    SetStepSizes(m_activeStep);

    return true;
  }
}

void CFX_LedAnimationSequence::SetStepSizes(uint16_t step)
{
  m_totalIncrements = m_steps[step].duration / ANIMATION_UPDATE_INTERVAL;
  if (m_totalIncrements == 0) m_totalIncrements = 1; // a minimum of 1 increment is required
  m_stepIncrement = 0;
  m_startBrightness = m_output->GetBrightness();
}

bool CFX_LedAnimationSequence::UpdateAnimation(int timeStep)
{
  bool returnval = false;
  m_stepIncrement++;
  m_output->SetBrightness(CalculateValue(m_stepIncrement, m_totalIncrements, m_startBrightness,
    m_steps[m_activeStep].brightness, m_steps[m_activeStep].type));

  if (m_stepIncrement >= m_totalIncrements)
  {
    returnval = NextStep();
  }
  return returnval;
}

uint8_t CFX_LedAnimationSequence::CalculateValue(uint16_t increment, uint16_t totalincrements, 
                                                 uint8_t startvalue, uint8_t targetvalue, CFX_TransitionType type)
{
  switch (type)
  {
    case CFX_Transition_Lineair:
      if (increment == totalincrements)
      {
        return targetvalue;
      }
      else
      {
        int value = startvalue + ((float)increment/totalincrements) * ((int)targetvalue - startvalue);
        return value;
      }
    break;
    
    case CFX_Transition_Block:
      if (increment == totalincrements)
      {
        return targetvalue;
      }
      else
      {
        return startvalue;
      }
    break;
    
    case CFX_Transition_Curve:
      if (increment == totalincrements)
      {
        return targetvalue;
      }
      else
      {
        return startvalue + sin((double)increment / totalincrements) * ((int)targetvalue - startvalue);
      }
    break;
    
    case CFX_No_Transition:
      return targetvalue;
    break;
    
  }
  return 0;
}