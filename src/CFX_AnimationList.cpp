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

#include <CFX_AnimationList.hpp>

CFX_AnimationList::CFX_AnimationList() : CFX_AnimationBase()
{
  m_currentAnimation = 0;
}

void CFX_AnimationList::Add(CFX_AnimationBase* animation)
{
  m_animations.Add(animation);
  if (m_animations.Size() > 1)
  {
    animation->Stop();
  }
}
    
void CFX_AnimationList::StartNext()
{
  m_animations.Get(m_currentAnimation)->Stop();
  if (m_animations.Size() > m_currentAnimation + 1)
  {
    m_currentAnimation++;
  }
  else
  {
    m_currentAnimation = 0;
  }
  m_animations.Get(m_currentAnimation)->RestartAnimation();  
}

void CFX_AnimationList::StartPrevious()
{
  m_animations.Get(m_currentAnimation)->Stop();
  if (m_currentAnimation >= 1)
  {
    m_currentAnimation--;
  }
  else
  {
    m_currentAnimation = m_animations.Size() - 1;
  }
  m_animations.Get(m_currentAnimation)->RestartAnimation();
}
uint16_t CFX_AnimationList::GetCurrentAnimation() const
{
  return m_currentAnimation;
}

void CFX_AnimationList::RestartAnimation()
{
}

bool CFX_AnimationList::UpdateAnimation(int timeStep)
{
}