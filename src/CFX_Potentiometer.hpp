////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2016 CustomFX. All right reserved.
//
// This file is part of the CustomFX library. This library was developed in 
// order to make Arduino programming as easy as possible. For more information,
// visit our website: http://www.customfx.nl
//
// The CustomFX library is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by the Free
// Software Foundation, either version 3 of the License, or (at your option)
// any later version.
//
// The CustomFX library is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
// or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License 
// for more details.
//
// You should have received a copy of the GNU General Public License along with
// The CustomFX library.  If not, see <http://www.gnu.org/licenses/>.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef CFX_Potentiometer_H
#define CFX_Potentiometer_H

#include <CFX_InputBase.hpp>

// events
#define CFX_CMD_VALUE_CHANGED 30

class CFX_Potentiometer : public CFX_InputBase
{
  public:
    CFX_Potentiometer(int inputPin, int id, uint8_t samples = 1);
    void SetInputRange(int minRange, int maxRange);
    void SetOutputRange(int minRange, int maxRange);
    virtual const CFX_InputEvent* GetEvent(unsigned long time);
    virtual bool IsAnalog() const;
    virtual uint8_t GetRemainingReads() const;

  private:
    int m_lastRawValue;
    
    unsigned int m_minInputRange;
    unsigned int m_maxInputRange;
    unsigned int m_minOutputRange;
    unsigned int m_maxOutputRange;
    unsigned int m_threshold;
    int m_signalDirection;
    
    uint8_t m_samples;         // defines the number of samples to average
    uint8_t m_remainingReads;  // remaining samples to take before returning the value
    unsigned int m_totalValue;          // buffer to hold the samples
};



#endif // CFX_Potentiometer_H
