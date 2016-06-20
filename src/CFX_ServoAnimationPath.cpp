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
#include <CFX_ServoAnimationPath.hpp>

CFX_ServoAnimationPath::CFX_ServoAnimationPath(int pathSegments, CFX_Servo* output)
  : CFX_AnimationBase()
{
  m_output = output;
  m_path = new int[pathSegments][2];
  m_pathSegments = pathSegments;
  m_definedSegments = 0;
  m_activeSegment = 0;
  m_position = (float)output->GetAngle();
  m_targetPosition = 0;
  m_stepSize = 0;
}

void CFX_ServoAnimationPath::AddPosition(int position, int duration)
{
  if (m_definedSegments < m_pathSegments)
  {
    m_path[m_definedSegments][0] = position;
    m_path[m_definedSegments][1] = duration;
    m_definedSegments++;
  }
}

void CFX_ServoAnimationPath::RestartAnimation()
{
  m_activeSegment = 0;
  if (m_activeSegment < m_definedSegments)
  {
    MoveToPosition(m_path[m_activeSegment][0], m_path[m_activeSegment][1]);
  }
  this->Start();
}

void CFX_ServoAnimationPath::MoveToPosition(int newPosition, int duration)
{
  m_targetPosition = newPosition;
  int timeStep = ANIMATION_UPDATE_INTERVAL;
  m_position = (float)m_output->GetAngle();
  
  int distance = abs(m_targetPosition - (int)m_position);
  m_stepSize = (float)distance / (duration / timeStep);
  
  if (m_targetPosition < m_position)
  {
    m_stepSize = -1 * m_stepSize;
  }
}

void CFX_ServoAnimationPath::UpdateAnimation(int timeStep)
{
  if (m_output)
  {
    if (fabs((float)m_targetPosition - m_position) < fabs(m_stepSize))
    {
      m_activeSegment++;
      if (m_activeSegment < m_definedSegments)
      {
        MoveToPosition(m_path[m_activeSegment][0], m_path[m_activeSegment][1]);
      }
      else
      {
        this->Stop();
      }
    }
    else
    {
      m_position += m_stepSize;
      m_output->SetAngle((int)m_position);
    }
    
  }
}