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

#ifndef CFX_LedAnimationSequence_H
#define CFX_LedAnimationSequence_H

#include <CFX_AnimationBase.hpp>

enum CFX_TransitionType { CFX_Transition_Block, CFX_Transition_Lineair, CFX_Transition_Curve, CFX_No_Transition };
// struct for step definitions
struct CFX_LedAnimationSequenceStep
{
  uint16_t duration;
  uint8_t brightness;
  CFX_TransitionType type;// interpolation/transition
};

class CFX_LedAnimationSequence: public CFX_AnimationBase
{
  public:
    CFX_LedAnimationSequence(uint16_t steps, CFX_LedBase* output);
    
    void AddStep(uint8_t brightness, uint16_t duration, CFX_TransitionType type = CFX_Transition_Lineair);
    void ChangeStep(uint16_t step, uint8_t brightness, uint16_t duration, CFX_TransitionType type);
    void SetInitialBrightness(uint8_t brightness);
    
    virtual bool InitializeAnimation(int timestep);
    virtual bool UpdateAnimation(int timestep);

  private:
    bool NextStep();
    void SetStepSizes(uint16_t step);
    uint8_t CalculateValue(uint16_t increment, uint16_t totalincrements, 
                   uint8_t startvalue, uint8_t targetvalue, CFX_TransitionType type);
 
  private:
    CFX_LedBase* m_output;
    CFX_LedAnimationSequenceStep* m_steps;
    uint16_t   m_totalSteps;      // the total number of staps in the animation
    uint16_t   m_definedSteps;    // the number of defined (non empty) steps
    uint16_t   m_activeStep;      // the current step in the animation
    uint8_t m_startBrightness;
    uint8_t m_initialBrightness;
    uint16_t m_stepIncrement;
    uint16_t m_totalIncrements;
};

#endif // CFX_LedAnimationSequence_H
