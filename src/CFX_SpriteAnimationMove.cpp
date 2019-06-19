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
#include <CFX_SpriteAnimationMove.hpp>

CFX_SpriteAnimationMove::CFX_SpriteAnimationMove(float deltaX, float deltaY, CFX_Sprite* sprite)
  : CFX_AnimationBase()
{
  // delta's are per second
  m_deltaX = (deltaX * ANIMATION_UPDATE_INTERVAL) / 1000; 
  m_deltaY = (deltaY * ANIMATION_UPDATE_INTERVAL) / 1000; 
  m_sprite = sprite;
}

void CFX_SpriteAnimationMove::Move(float deltaX, float deltaY)
{
  m_deltaX = (deltaX * ANIMATION_UPDATE_INTERVAL) / 1000; 
  m_deltaY = (deltaY * ANIMATION_UPDATE_INTERVAL) / 1000; 
}

bool CFX_SpriteAnimationMove::InitializeAnimation(int timestep)
{
  if (m_sprite)
  {
    m_xpos = m_sprite->GetXPosition();
    m_ypos = m_sprite->GetYPosition();
  }
  return true;
}


bool CFX_SpriteAnimationMove::FinishAnimation(int timestep)
{
  return true;
}


bool CFX_SpriteAnimationMove::UpdateAnimation(int timeStep)
{
  bool returnval = false;

  if (m_sprite)
  {
    m_xpos += m_deltaX;
    m_ypos += m_deltaY;
    m_sprite->SetOrigin((signed int)m_xpos, (signed int)m_ypos);
  }
  
  return returnval;
}
