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

#ifndef CFX_ServoAnimationMoveToPosition_H
#define CFX_ServoAnimationMoveToPosition_H

#include <CFX_AnimationBase.hpp>
#include <CFX_Servo.hpp>

class CFX_ServoAnimationMoveToPosition: public CFX_AnimationBase
{
  public:
    
    CFX_ServoAnimationMoveToPosition();
    CFX_ServoAnimationMoveToPosition(int newPosition, int duration, CFX_Servo* output);
    
    void MoveToPosition(int newPosition, int duration);
    
    virtual void UpdateAnimation(int timestep);
 
  private:
    CFX_Servo* m_output;
    
    float m_position;      // stores the actual position of the servo
    int m_targetPosition;  // stores the target position to move to
    float m_stepSize;      // the stepsize the servo moves each update. Is determined for each MoveTo action. Can be negative or positive.
};

#endif // CFX_ServoAnimationMoveToPosition_H
