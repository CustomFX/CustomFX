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

#include <CFX_LedBase.hpp>
#include <CFX_LedAnimationSequence.hpp>

class CFX_LedAnimationBlink: public CFX_LedAnimationSequence
{
  public:

    CFX_LedAnimationBlink(unsigned long onTime, unsigned long offTime, CFX_LedBase* output);
    CFX_LedAnimationBlink(unsigned long onTime, unsigned long offTime, 
      unsigned long startdelay, CFX_LedBase* output);
    
    void SetTimes(unsigned long onTime, unsigned long offTime);
    void SetBrightness(uint8_t brightness);

private:
    // private variables for function blink
    uint16_t m_blinkOnTime;
    uint16_t m_blinkOffTime;
    uint8_t m_brightness;
};

#endif // CFX_ANIMATIONBLINK_H
