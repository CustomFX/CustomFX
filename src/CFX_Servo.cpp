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

#include <CFX_Servo.hpp>

CFX_Servo::CFX_Servo(int pinnumber) : CFX_OutputBase()
{
  m_pin = pinnumber;
  
  m_newAngle = 90;
  m_minAngle = 0;
  m_minpulse = 544;
  m_maxpulse = 2400;
  m_maxAngle = 180;
  m_changed = false;
  m_initialised = false;
}

CFX_Servo::CFX_Servo() : CFX_OutputBase()
{
  m_newAngle = 90;
  m_minAngle = 0;
  m_minpulse = 544;
  m_maxpulse = 2400;
  m_maxAngle = 180;
}

void CFX_Servo::Init()
{
  m_servo.attach(m_pin);
  m_initialised = true;
}

void CFX_Servo::SetRange(int minAngle, int maxAngle)
{
  m_minAngle = minAngle;
  m_maxAngle = maxAngle;
}

void CFX_Servo::SetPulseRange(int minPulse, int maxPulse)
{
  m_minpulse = minPulse;
  m_maxpulse = maxPulse;
}

void CFX_Servo::SetAngle(int angle)
{
  angle = constrain(angle, m_minAngle, m_maxAngle);
  if (angle != m_newAngle)
  {
    m_newAngle = angle;
    m_changed = true;
  }
}

int CFX_Servo::GetAngle() const
{
  return m_newAngle;
}

int CFX_Servo::GetPulse() const
{
  unsigned long pulse = ((unsigned long)(m_maxpulse - m_minpulse)*m_newAngle)/180 + m_minpulse;
  return pulse;
}

void CFX_Servo::Commit()
{
  if (!m_initialised) 
  {
    Init();
  }
  
  if (m_changed)
  {
    m_servo.write(m_newAngle);
    m_changed = false;
  }
}
