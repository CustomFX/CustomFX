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

#ifndef CFX_LedRandomAnimation_H
#define CFX_LedRandomAnimation_H

#include <CFX_AnimationBase.hpp>

class CFX_LedRandomAnimation: public CFX_AnimationBase
{
  public:
    CFX_LedRandomAnimation(uint8_t minvalue, uint8_t maxvalue, 
      uint16_t mindelay, uint16_t maxdelay, CFX_Led* output);
    
    virtual void RestartAnimation();
    virtual bool UpdateAnimation(int timestep);

  private:
    void NextStep();
    void SetStepSizes(uint8_t brightness, uint16_t duration);
 
  private:
    CFX_Led* m_output;
    uint8_t m_minvalue;
    uint8_t m_maxvalue;
    uint16_t m_mindelay;
    uint16_t m_maxdelay;
    
    float m_brightness;      // stores the actual brightrness of the LED
    
    uint16_t m_stepIncrement;
    uint16_t m_totalIncrements;
    float m_brightnessIncrement;
};

#endif // CFX_LedRandomAnimation_H
