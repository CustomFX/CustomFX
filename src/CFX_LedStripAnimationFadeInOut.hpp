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

#ifndef CFX_LedStripAnimationFadeInOut_H
#define CFX_LedStripAnimationFadeInOut_H

#include <CFX_AnimationBase.hpp>
#include <CFX_LedStripBase.hpp>

enum CFX_FadeType { CFX_FadeLeftRight, CFX_FadeRightLeft };


class CFX_LedStripAnimationFadeInOut: public CFX_AnimationBase
{
  public:
    
    CFX_LedStripAnimationFadeInOut();
    CFX_LedStripAnimationFadeInOut(unsigned long fadeInTime, unsigned long fadeOutTime,
      CFX_LedStripBase* output, CFX_FadeType fadetype = CFX_FadeLeftRight);
    void SetOutputDevice(CFX_LedStripBase* output);
    
    void SetColor(CFX_Color color);
    void SetBrightness(uint8_t brightness);
    void SetType(CFX_FadeType type);
    void SetFadeInTime(unsigned long fadeInTime);
    
    virtual void RestartAnimation();
    virtual bool UpdateAnimation(int timestep);
    
    private:
    
  private:
    CFX_LedStripBase* m_output;
    
    CFX_Color m_color;
    bool    m_useColor;
    uint8_t m_brightness;
    
    CFX_FadeType m_type;
    uint16_t m_startLed;
    uint16_t m_length;
    
    uint16_t m_step;
    unsigned long m_fadeInTime;
    unsigned long m_fadeOutTime;
    };

#endif // CFX_LedStripAnimationFadeInOut_H