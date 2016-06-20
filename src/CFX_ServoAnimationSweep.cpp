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

#include <CFX_ServoAnimationSweep.hpp>

CFX_ServoAnimationSweep::CFX_ServoAnimationSweep()
  : CFX_AnimationBase()
{
  m_output = 0;

  m_minAngle = 0;
  m_maxAngle = 0;
  m_duration = 0;
  m_offset = 0;
  m_angle = 0;
  m_stepsize = 0;
  m_directionUp = true;
}


CFX_ServoAnimationSweep::CFX_ServoAnimationSweep(int minAngle, int maxAngle, int duration, int offset, CFX_Servo* output)
  : CFX_AnimationBase()
{
  m_output = output;
  if (minAngle < maxAngle)
  {
    m_minAngle = minAngle;
    m_maxAngle = maxAngle;
  }
  else
  {
    m_minAngle = maxAngle;
    m_maxAngle = minAngle;
  }
  m_duration = duration;
  m_stepsize = 2;
  m_offset = constrain(offset, m_minAngle, m_maxAngle);
  m_angle = m_offset;
  m_directionUp = true;
  m_repeat = true;
}

void CFX_ServoAnimationSweep::UpdateAnimation(int timeStep)
{
  if (m_output)
  {
    if (m_directionUp)
    {
      if (m_angle < m_maxAngle)
      {
        if (m_angle < m_offset)
        {
          m_angle += m_stepsize;
          if (!m_repeat && m_angle >= m_offset)
          {
            // check if with this step the animations reaches the startingpoint
            Stop();
          }
        }
        else
        {
          m_angle += m_stepsize;
        }
      }
      else
      {
        m_directionUp = false;
        m_angle -= m_stepsize;
      }
    }
    else
    {
      if (m_angle > m_minAngle)
      {
        m_angle -= m_stepsize;
      }
      else
      {
        m_directionUp = true;
        m_angle += m_stepsize;
      }
    }
    m_output->SetAngle(m_angle);
  }
}