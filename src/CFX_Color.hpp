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

#ifndef CFX_Color_H
#define CFX_Color_H

// include core Wiring API
#include "Arduino.h"

// include description files for other libraries used (if any)
#include "HardwareSerial.h"

class CFX_Color
{
  public:
    CFX_Color();
    CFX_Color(uint8_t red, uint8_t green, uint8_t blue);
    CFX_Color(long color);
    
    const String toString() const;
    long toLong() const;
    
    uint8_t Red() const;
    uint8_t Green() const;
    uint8_t Blue() const;

    void SetRed(uint8_t red);
    void SetGreen(uint8_t green);
    void SetBlue(uint8_t blue);
    
    bool operator==(const CFX_Color& color) const;
    bool operator!=(const CFX_Color& color) const;
    
  private:
    uint8_t m_red;
    uint8_t m_green;
    uint8_t m_blue;

};


#endif // CFX_Color_H
