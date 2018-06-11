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

#ifndef CFX_DigitalInput_H
#define CFX_DigitalInput_H

#include <CFX_InputBase.hpp>

#define CFX_CMD_HIGH            1
#define CFX_CMD_LOW             0

// Digital Input
//
class CFX_DigitalInput: public CFX_InputBase
{
  public:
    CFX_DigitalInput(int inputPin, int id, CFX_InputType type = CFX_InputTypeDigitalLow);
    virtual const CFX_InputEvent* GetEvent(unsigned long time);
    virtual bool IsAnalog() const;

  private:
    bool m_state;
  
};




#endif // CFX_DigitalInput_H
