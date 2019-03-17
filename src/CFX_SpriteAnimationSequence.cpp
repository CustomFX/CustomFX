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
#include <CFX_SpriteAnimationSequence.hpp>

CFX_SpriteAnimationSequence::CFX_SpriteAnimationSequence(uint16_t steps)//, CFX_RGBMatrix* output)
  : CFX_AnimationBase()
{
  m_steps = new CFX_SpriteAnimationSequenceStep[steps];
  
  m_totalSteps = steps;
  m_definedSteps = 0;
  m_activeStep = 0;
}

void CFX_SpriteAnimationSequence::AddSprite(CFX_Sprite* sprite, uint16_t duration, CFX_SpriteTransition transition)
{
  if (m_definedSteps < m_totalSteps)
  {
    m_steps[m_definedSteps].duration = duration;
    m_steps[m_definedSteps].sprite = sprite;
    m_steps[m_definedSteps].transition = transition;
    m_definedSteps++;
    sprite->SetActive(false);
  }
}

void CFX_SpriteAnimationSequence::SetSprite(uint16_t step, CFX_Sprite* sprite)
{
  if (step < m_totalSteps)
  {
    m_steps[step].sprite = sprite;
  }
}

void CFX_SpriteAnimationSequence::SetDuration(uint16_t step, uint16_t duration)
{
  if (step < m_totalSteps)
  {
    m_steps[step].duration = duration;
  }
}

void CFX_SpriteAnimationSequence::SetTransition(uint16_t step, CFX_SpriteTransition transition)
{
  if (step < m_totalSteps)
  {
    m_steps[step].transition = transition;
  }
}

bool CFX_SpriteAnimationSequence::InitializeAnimation(int timestep)
{
  m_activeStep = 0;
  if (m_activeStep < m_definedSteps)
  {
    m_steps[m_activeStep].sprite->SetActive(true);
    this->SetDelay(m_steps[m_activeStep].duration);
  }
  return true;
}


bool CFX_SpriteAnimationSequence::FinishAnimation(int timestep)
{
  return true;
}


bool CFX_SpriteAnimationSequence::UpdateAnimation(int timeStep)
{
  bool returnval = false;
  
  // disable current sprite
  if (m_activeStep < m_definedSteps)
  {
    m_steps[m_activeStep].sprite->SetActive(false);
  }

  // enable next sprite
  m_activeStep++;
  if (m_activeStep == m_definedSteps)
  {
    returnval = true;
    m_activeStep = 0;
  }
  if (m_activeStep < m_definedSteps)
  {
    m_steps[m_activeStep].sprite->SetActive(true);
    this->SetDelay(m_steps[m_activeStep].duration);
  }
  
  return returnval;
}
