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

#ifndef CFX_LEDANIMATIONFADEINOUT_H
#define CFX_LEDANIMATIONFADEINOUT_H

#include <CFX_AnimationBase.hpp>
#include <CFX_Led.hpp>
#include <CustomFX.h>

class CFX_LedAnimationFadeInOut: public CFX_AnimationBase
{
  public:
    
    CFX_LedAnimationFadeInOut();
    CFX_LedAnimationFadeInOut(int fadeInTime, int onTime, int fadeOutTime, int offTime, CFX_Led* output);
    
    void SetTimes(int fadeInTime, int onTime, int fadeOutTime, int offTime);
    void SetBrightness(uint8_t brightness);
    void SetOutputDevice(CFX_Led* output);

    virtual void UpdateAnimation(int timestep);

  private: // private functions
    void SetStepSizes();
  
  private: // private member variables
    CFX_Led* m_output;
    uint8_t m_brightness;
    
    int m_fadeInSteps;
    int m_onSteps;
    int m_fadeOutSteps;
    int m_offSteps;
    
    float m_fadeInStep;
    float m_fadeOutStep;
        
    int m_animationStep; // counter to keep track of the current step in the animation
    int m_totalAnimationSteps;
};

#endif // CFX_LEDANIMATIONFADEINOUT_H
