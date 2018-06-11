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

#ifndef CFX_INPUTBASE_H
#define CFX_INPUTBASE_H

// include core Wiring API
#include "Arduino.h"

// include description files for other libraries used (if any)
#include "HardwareSerial.h"

//
// Base class for all input classes
//
struct CFX_InputEvent
{
  uint8_t command;
  unsigned long value;
};
enum CFX_InputType {CFX_InputTypeAnalog, CFX_InputTypeDigitalHigh, 
CFX_InputTypeDigitalLow, CFX_InputTypeOther};

class CFX_InputBase
{
  public:
    CFX_InputBase(uint8_t id, uint8_t pinnumber, CFX_InputType type);
    CFX_InputBase(uint8_t id, CFX_InputType type);
    virtual const CFX_InputEvent* GetEvent(unsigned long time) = 0;
    
    virtual uint8_t GetId() const;
    const CFX_InputType GetType() const;
    virtual uint8_t GetRemainingSamples() const;
	
  protected:
    int      ReadInput();
    uint8_t  GetPinNumber();
    void SetEvent(uint8_t command, unsigned long value);
    const CFX_InputEvent* GetLastEvent();
	
  private:
    uint8_t m_pinnumber;
    uint8_t m_id;
    CFX_InputType m_type;
    CFX_InputEvent m_lastEvent;
};

#endif // CFX_INPUTBASE_H
