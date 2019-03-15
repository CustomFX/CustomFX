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

#include <CFX_AnimationController.hpp>
static CFX_AnimationController* s_animationController = 0;

CFX_AnimationController::CFX_AnimationController()
{
  m_previousUpdateTime = 0;
  m_timeStep = ANIMATION_UPDATE_INTERVAL;
}

CFX_AnimationController* CFX_AnimationController::GetInstance()
{
  if (!s_animationController)
  {
    s_animationController = new CFX_AnimationController;
  }  
  return s_animationController;
}

void CFX_AnimationController::RegisterOutputDevice(CFX_OutputBase* outputDevice)
{
  m_outputDevices.Add(outputDevice);
}

void CFX_AnimationController::RegisterAnimation(CFX_AnimationBase* animation)
{
  m_animations.Add(animation);
}

void CFX_AnimationController::SetAnimationSpeed(int timeStep)
{
  m_timeStep = timeStep;
}

void CFX_AnimationController::UpdateAnimation()
{
  unsigned long timeelapsed = millis() - m_previousUpdateTime;
  if (timeelapsed > m_timeStep)
  {
    m_previousUpdateTime = millis();
    for (unsigned int i = 0; i < m_animations.Size(); i++)
    {
      CFX_AnimationBase* animation = m_animations.Get(i);
      int event = animation->Animate(timeelapsed);
      if (animation->GetId() > 0)
      { 
        handleInput(animation->GetId(), event, 0);
      }
    }
    for (unsigned int i = 0; i < m_outputDevices.Size(); i++)
    {
      m_outputDevices.Get(i)->Commit();
    }
  }
}