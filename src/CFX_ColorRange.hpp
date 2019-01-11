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

#ifndef CFX_ColorRange_H
#define CFX_ColorRange_H

#include <CFX_Color.hpp>

// include core Wiring API
#include "Arduino.h"

// include description files for other libraries used (if any)
#include "HardwareSerial.h"

class CFX_ColorRange
{
  public:
    CFX_ColorRange(int colors);
    bool AddColor(const CFX_Color& color, uint16_t range = 256);
    bool SetColor(int index, const CFX_Color& color, uint16_t range);
    
    CFX_Color GetColor(uint16_t index) const;
    uint16_t GetMaxRange();
    void SetMaxRange(uint16_t maxrange);
    
  private:
    CFX_Color* m_colors;
    uint16_t* m_ranges;
    int m_totalColors;
    int m_definedColors;
    uint16_t m_totalRange;
    uint16_t m_maxRange;
};


#endif // CFX_ColorRange_H
