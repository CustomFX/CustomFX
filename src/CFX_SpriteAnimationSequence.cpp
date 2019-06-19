////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2016-2019 Custom FX. All right reserved.
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

CFX_SpriteAnimationSequence::CFX_SpriteAnimationSequence(uint16_t steps, CFX_Sprite* sprite, int id)
  : CFX_AnimationBase(id)
{
  m_sprite = sprite;
  m_steps = new CFX_SpriteAnimationSequenceStep[steps];
  
  m_totalSteps = steps;
  m_definedSteps = 0;
  m_activeStep = 0;
}

void CFX_SpriteAnimationSequence::AddBitmap(const byte* bitmap, uint16_t duration, CFX_SpriteTransition transition)
{
  if (m_definedSteps < m_totalSteps)
  {
    m_steps[m_definedSteps].duration = duration;
    m_steps[m_definedSteps].bitmap = bitmap;
    m_steps[m_definedSteps].transition = transition;
    m_definedSteps++;
  }
}

void CFX_SpriteAnimationSequence::SetBitmap(uint16_t step, const byte* bitmap)
{
  if (step < m_totalSteps)
  {
    m_steps[step].bitmap = bitmap;
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
    m_sprite->SetBitmap(m_steps[m_activeStep].bitmap);
    this->SetDelay(m_steps[m_activeStep].duration);
  }
  return true;
}

void CFX_SpriteAnimationSequence::RestartAnimation()
{

}

bool CFX_SpriteAnimationSequence::FinishAnimation(int timestep)
{
  return true;
}


bool CFX_SpriteAnimationSequence::UpdateAnimation(int timeStep)
{
  bool returnval = false;
  if (m_activeStep < m_definedSteps)
  {
    m_sprite->SetBitmap(m_steps[m_activeStep].bitmap);
    this->SetDelay(m_steps[m_activeStep].duration);
  }
  
  m_activeStep++;
  if (m_activeStep == m_definedSteps)
  {
    returnval = true;
    m_activeStep = 0;
  }
  
  return returnval;
}
