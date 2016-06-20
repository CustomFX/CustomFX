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

#ifndef CFX_SERVO_H
#define CFX_SERVO_H

#include <CFX_OutputBase.hpp>
#include <Servo.h>

class CFX_Servo: public CFX_OutputBase
{
  public:
    CFX_Servo(int pinnumber);
    
    // additional
    virtual void SetRange(int minAngle, int maxAngle);
    virtual void SetPulseRange(int minPulse, int maxPulse);
    virtual void SetAngle(int angle);
    virtual int  GetAngle() const;
    virtual int  GetPulse() const;
        
    // inherited
    virtual void Commit();
    
  protected:
    CFX_Servo();
    void Init();

  private:
    bool     m_changed;
    int      m_pin;
    Servo    m_servo;
    int      m_minAngle;
    int      m_maxAngle;
    int      m_minpulse;
    int      m_maxpulse;
    int      m_newAngle;
    bool     m_initialised;
};





#endif // CFX_SERVO_H

