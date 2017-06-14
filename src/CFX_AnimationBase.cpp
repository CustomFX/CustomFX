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

#include <CFX_AnimationBase.hpp>
#include <CFX_AnimationController.hpp>

CFX_AnimationBase::CFX_AnimationBase()
{
 	CFX_AnimationController::GetInstance()->RegisterAnimation(this);
  //m_active = true;
  m_state = cfx_animation_initializing;
  m_repetitions = -1;
  m_delay = 0;
}

void CFX_AnimationBase::Animate(int timestep)
{
  if (m_delay > 0)
  {
    if (m_delay - timestep > 0)
    {
      m_delay -= timestep;
    }
    else
    {
      m_delay = 0;
      Serial.print(millis());
      Serial.println(" start...");
    }
  }
  else
  {
    switch (m_state)
    {
      case cfx_animation_initializing:
        if (InitializeAnimation(timestep) == true)
        {
          m_state = cfx_animation_running;
        }
      break;
      
      case cfx_animation_running:
        if (UpdateAnimation(timestep) == true)
        {
          if (m_repetitions > 0)
          {
            m_repetitions--;
            if (m_repetitions == 0)
            {
              m_state = cfx_animation_shuttingdown;
            }
          }
        }
      break;
      
      case cfx_animation_shuttingdown:
        if (FinishAnimation(timestep) == true)
        {
          m_state = cfx_animation_stopped;
        }
      break;
      
      case cfx_animation_stopped:
        // do nothing
      break;
    }
  }
}

bool CFX_AnimationBase::InitializeAnimation(int timestep)
{
  return true;
}

bool CFX_AnimationBase::FinishAnimation(int timestep)
{
  return true;
}

void CFX_AnimationBase::SetDelay(long delay)
{
  m_delay = delay;
}

void CFX_AnimationBase::SetRepetitions(int repetitions)
{
  m_repetitions = repetitions;
}

void CFX_AnimationBase::Start()
{
  //m_active = true;
  m_state = cfx_animation_initializing;
}

void CFX_AnimationBase::Stop()
{
  //m_active = false;
  m_state = cfx_animation_shuttingdown;
}

bool CFX_AnimationBase::IsActive() const
{
  return m_state != cfx_animation_stopped;
}
