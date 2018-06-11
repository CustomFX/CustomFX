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

#ifndef CFX_AnimationBase_H
#define CFX_AnimationBase_H

// include core Wiring API
#include "Arduino.h"

// include description files for other libraries used (if any)
#include "HardwareSerial.h"

enum CFX_Animation_State {
  cfx_animation_initializing, 
  cfx_animation_running, 
  cfx_animation_shuttingdown,
  cfx_animation_stopped};

class CFX_AnimationBase
{
  public:
    CFX_AnimationBase();

    // initialize animation
    virtual bool InitializeAnimation(int timestep);
    
    // finish animation
    virtual bool FinishAnimation(int timestep);
    
    // update animation. Returns true if animation reached the end
    virtual bool UpdateAnimation(int timestep) = 0;
    
    void Animate(int timestep);
    
    void SetDelay(long delay);
    void SetRepetitions(int16_t repetitions);
    
    virtual void Start();
    virtual void Stop();
    bool IsActive() const;
    virtual void RestartAnimation() = 0;
    
  private:
    CFX_Animation_State m_state;
    long m_delay;
    int16_t m_repetitions;
};




#endif // CFX_AnimationBase_H
