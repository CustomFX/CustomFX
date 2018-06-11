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

#ifndef CFX_RGBLEDANIMATIONCOLORBLINK_H
#define CFX_RGBLEDANIMATIONCOLORBLINK_H

#include <CFX_LedBase.hpp>
#include <CFX_AnimationBase.hpp>

class CFX_RGBLedAnimationColorBlink: public CFX_AnimationBase
{
  public:

    CFX_RGBLedAnimationColorBlink();
    CFX_RGBLedAnimationColorBlink(unsigned long onTime, unsigned long offTime, 
      CFX_Color color, CFX_LedBase* output);
    CFX_RGBLedAnimationColorBlink(unsigned long onTime, unsigned long offTime, 
      unsigned long startdelay, CFX_Color color, CFX_LedBase* output);
    void SetColor(const CFX_Color& color);
    void DisableColor();
    
    void SetTimes(unsigned long onTime, unsigned long offTime);
    void SetOutputDevice(CFX_LedBase* output);

    virtual void RestartAnimation();
    virtual bool UpdateAnimation(int timeStep);

private:
    // private variables for function blink
    unsigned long m_previousUpdateTime;
    unsigned long m_blinkOnTime;
    unsigned long m_blinkOffTime;
    unsigned long m_startDelay;
    CFX_LedBase* m_output;
    
    bool m_blinkon;
    CFX_Color m_color;
    bool m_useColor;
};




#endif // CFX_ANIMATIONBLINK_H
