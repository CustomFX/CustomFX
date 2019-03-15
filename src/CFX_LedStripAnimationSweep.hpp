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

#ifndef CFX_LEDSTRIPANIMATIONSWEEP_H
#define CFX_LEDSTRIPANIMATIONSWEEP_H

#include <CFX_AnimationBase.hpp>
#include <CFX_LedStripBase.hpp>

class CFX_LedStripAnimationSweep: public CFX_AnimationBase
{
  public:
    
    CFX_LedStripAnimationSweep();
    CFX_LedStripAnimationSweep(CFX_Color color, unsigned long time_on, unsigned long fadeouttime,
      CFX_LedStripBase* output, int id = 0);
    CFX_LedStripAnimationSweep(uint16_t startled, int8_t direction, CFX_Color color, unsigned long time_on, 
      unsigned long fadeouttime, CFX_LedStripBase* output, int id = 0);
      
    void SetOutputDevice(CFX_LedStripBase* output);

    void SetTimes(unsigned long time_on, unsigned long fadeouttime);
    void SetColor(CFX_Color color);
    void DisableColor();
    void SetDirection(int8_t direction);
    int8_t GetDirection() const;
    
    virtual bool InitializeAnimation(int timeStep);
    virtual bool FinishAnimation(int timeStep);

    virtual void RestartAnimation();
    virtual bool UpdateAnimation(int timeStep);

    private:
    bool UpdateHead(int timeStep);
    bool UpdateTrail(int timeStep);
    void CalculateFadeOutSteps(unsigned long fadeouttime);
 
  private:
    CFX_LedStripBase* m_output;
    CFX_Color m_color;
    bool m_useColor;
    int8_t m_direction;           // indicates the direction of the sweep. 1 or -1
    unsigned long m_fadeouttime;
    
    uint16_t m_startled;
    int16_t m_activeLed;          // the index of the led that is the first in the sweep
    unsigned long m_stoppedSteps;
    unsigned long m_onSteps;      // the number of animationsteps a led is on before the next led turns on
    unsigned long m_currentStep;  // the step index of the active led
    float m_fadeOutStepSize;
    uint16_t m_trailLength;       // the length in #leds of the trail
};

#endif // CFX_LEDSTRIPANIMATIONSWEEP_H
