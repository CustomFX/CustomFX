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

#ifndef CFX_LEDANIMATIONBLINK_H
#define CFX_LEDANIMATIONBLINK_H

#include <CFX_Led.hpp>
#include <CFX_AnimationBase.hpp>

class CFX_LedAnimationBlink: public CFX_AnimationBase
{
  public:

    CFX_LedAnimationBlink();
    CFX_LedAnimationBlink(unsigned long onTime, unsigned long offTime, CFX_Led* output);
    
    void SetTimes(unsigned long onTime, unsigned long offTime);
    void SetOutputDevice(CFX_Led* output);
    void SetBrightness(uint8_t brightness);

    void UpdateAnimation(int timeStep);

private:
    // private variables for function blink
    unsigned long m_previousUpdateTime;
    unsigned long m_blinkOnTime;
    unsigned long m_blinkOffTime;
    CFX_Led* m_output;
    bool m_blinkon;
    uint8_t m_brightness;
};

#endif // CFX_ANIMATIONBLINK_H
