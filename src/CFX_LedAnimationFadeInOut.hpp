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
#include <CFX_LedBase.hpp>
#include <CustomFX.h>

class CFX_LedAnimationFadeInOut: public CFX_LedAnimationSequence
{
  public:
    
    CFX_LedAnimationFadeInOut(uint16_t fadeInTime, uint16_t onTime, uint16_t fadeOutTime, 
      uint16_t offTime, CFX_LedBase* output);
    
    void SetTimes(uint16_t fadeInTime, uint16_t onTime, uint16_t fadeOutTime, uint16_t offTime);
    void SetBrightness(uint8_t brightness);
 
  private: // private member variables
    uint8_t m_brightness;
    uint16_t m_fadeInTime;
    uint16_t m_onTime;
    uint16_t m_offTime;
    uint16_t m_fadeOutTime;
};

#endif // CFX_LEDANIMATIONFADEINOUT_H
