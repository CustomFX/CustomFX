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
  m_nrOfOutputDevices = 0;
  m_nrOfAnimations = 0;
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
  if (m_nrOfOutputDevices < MAX_OUTPUT_DEVICES - 1)
  {
    m_outputDevices[m_nrOfOutputDevices] = outputDevice;
    m_nrOfOutputDevices++;
  }
}

void CFX_AnimationController::RegisterAnimation(CFX_AnimationBase* animation)
{
  if (m_nrOfAnimations < MAX_ANIMATIONS - 1)
  {
    m_animations[m_nrOfAnimations] = animation;
    m_nrOfAnimations++;
  }
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
    for (int i = 0; i < m_nrOfAnimations; i++)
    {
      m_animations[i]->Animate(timeelapsed);
    }
    for (int i = 0; i < m_nrOfOutputDevices; i++)
    {
      m_outputDevices[i]->Commit();
    }
  }
}