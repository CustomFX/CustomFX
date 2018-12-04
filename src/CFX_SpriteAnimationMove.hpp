////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2016-2018 Custom FX. All right reserved.
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

#ifndef CFX_SpriteAnimationMove_H
#define CFX_SpriteAnimationMove_H

#include <CFX_AnimationBase.hpp>
#include <CFX_Sprite.hpp>

class CFX_SpriteAnimationMove : public CFX_AnimationBase
{
  public:
    CFX_SpriteAnimationMove(int16_t deltaX, int16_t deltaY, uint16_t duration, CFX_Sprite &sprite);
    
    virtual bool InitializeAnimation(int timestep);
    virtual bool FinishAnimation(int timestep);
    virtual bool UpdateAnimation(int timestep);

  private:
    void CalculateSteps();
    
  private:
    uint16_t m_step;
    uint16_t m_totalSteps;

    CFX_Sprite& m_sprite;
    uint16_t m_duration;
    int16_t m_deltaX, m_deltaY;
    float m_incrementX, m_incrementY;

};

#endif // CFX_SpriteAnimationMove_H