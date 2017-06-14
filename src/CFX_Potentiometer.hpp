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
//
//
//

// events
// Increasing
// Decreading
//const uint_8 CFX_EVENT_

#define CFX_CMD_VALUE_CHANGED 30

class CFX_Potentiometer : public CFX_InputBase
{
  public:
    CFX_Potentiometer(int inputPin, int id);
    void SetInputRange(int minRange, int maxRange);
    void SetOutputRange(int minRange, int maxRange);
    virtual const CFX_InputEvent* GetEvent(unsigned long time);

  private:
    int m_lastRawValue;
    
    int m_minInputRange;
    int m_maxInputRange;
    int m_minOutputRange;
    int m_maxOutputRange;
    int m_threshold;
    int m_signalDirection;
};



#endif // CFX_Potentiometer_H
