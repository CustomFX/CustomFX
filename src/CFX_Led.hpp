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

#ifndef CFX_LED_H
#define CFX_LED_H

#include <CFX_LedBase.hpp>

//
// The Led class represents a single led connected directly to the Arduino using a resistor
//
class CFX_Led: public CFX_LedBase
{
  public:
    CFX_Led(uint8_t pinnumber);
    
    // additional
    virtual void SetBrightness(uint8_t brightness);
    virtual uint8_t GetBrightness() const;
    
    // inherited
    virtual void SetColor(const CFX_Color& color);
    virtual const CFX_Color GetColor() const;
    virtual long GetColorLong() const;
    virtual void Commit();
    
  protected:
    CFX_Led();

  private:
    uint8_t  m_pin;
    uint8_t  m_brightness;
    uint8_t*  m_brightnessref;
};





#endif // CFX_LED_H

