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

#ifndef CFX_LedStripAnimationTwinkle_H
#define CFX_LedStripAnimationTwinkle_H

#include <CFX_AnimationBase.hpp>
#include <CFX_LedStripBase.hpp>
#include <CFX_Color.hpp>

class CFX_LedStripAnimationTwinkle: public CFX_AnimationBase
{
  public:
    
    CFX_LedStripAnimationTwinkle();
    CFX_LedStripAnimationTwinkle(const CFX_Color& color, CFX_LedStripBase* output);
    void SetOutputDevice(CFX_LedStripBase* output);

    void SetColor(CFX_Color color);
    void DisableColor();
    void SetBrightness(uint8_t brightness);
    void SetTimes(uint16_t minOnDelay, uint16_t maxOnDelay, uint16_t onTime);
    
    virtual void RestartAnimation();
    virtual bool UpdateAnimation(int timestep);
    virtual bool FinishAnimation(int timestep);
    private:
    void NextStep();
    
  private:
    CFX_LedStripBase* m_output;
    
    CFX_Color m_color;
    bool      m_useColor;
    uint8_t   m_brightness;
    uint16_t  m_minOnDelay;
    uint16_t  m_maxOnDelay;
    uint16_t  m_onTime;

    uint16_t m_step;
    uint16_t m_targetStep;
    bool     m_twinkleOn;
  };

#endif // CFX_LedStripAnimationTwinkle_H
