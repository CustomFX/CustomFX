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

#ifndef CFX_ServoAnimationSweep_H
#define CFX_ServoAnimationSweep_H

#include <CFX_AnimationBase.hpp>
#include <CFX_Servo.hpp>

class CFX_ServoAnimationSweep: public CFX_AnimationBase
{
  public:
    
    CFX_ServoAnimationSweep();
    CFX_ServoAnimationSweep(int minAngle, int maxAngle, int duration, int offset, CFX_Servo* output);
    
    virtual bool UpdateAnimation(int timestep);
 
  private:
    CFX_Servo* m_output;
    int m_minAngle;
    int m_maxAngle;
    int m_duration;
    int m_offset;
    bool m_directionUp;
     
    int m_angle;
    int m_stepsize;
};

#endif // CFX_ServoAnimationSweep_H
