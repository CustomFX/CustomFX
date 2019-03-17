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

#ifndef CFX_SpriteAnimationSequence_H
#define CFX_SpriteAnimationSequence_H

#include <CFX_AnimationBase.hpp>
#include <CFX_Sprite.hpp>
#include <CFX_RGBMatrix.hpp>

#include <CFX_List.hpp>

enum CFX_SpriteTransition {CFX_SpriteFadeInOut, CFX_SpriteCrossFade, CFX_SpriteAppear};

struct CFX_SpriteAnimationSequenceStep
{
  CFX_Sprite* sprite;
  uint16_t duration;
  CFX_SpriteTransition transition;
};

class CFX_SpriteAnimationSequence : public CFX_AnimationBase
{
  public:
    CFX_SpriteAnimationSequence(uint16_t steps);//CFX_RGBMatrix* output);
  
    void AddSprite(CFX_Sprite* sprite, uint16_t duration, CFX_SpriteTransition transition);
    void SetSprite(uint16_t step, CFX_Sprite* sprite);
    void SetDuration(uint16_t step, uint16_t duration);
    void SetTransition(uint16_t step, CFX_SpriteTransition transition);

    virtual bool InitializeAnimation(int timestep);
    virtual bool FinishAnimation(int timestep);
    virtual bool UpdateAnimation(int timestep);
    
    
  private:
    void CalculateSteps();

  private:
    CFX_SpriteAnimationSequenceStep* m_steps;
    uint16_t   m_totalSteps;      // the total number of staps in the animation
    uint16_t   m_definedSteps;    // the number of defined (non empty) steps
    uint16_t   m_activeStep;      // the current step in the animation
};

#endif // CFX_SpriteAnimationSequence_H