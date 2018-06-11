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

#ifndef CFX_RGBLED_H
#define CFX_RGBLED_H

#include <CFX_Led.hpp>
#include <CFX_Color.hpp>

class CFX_RGBLed: public CFX_Led
{
  public:
    CFX_RGBLed(int redpin, int greenpin, int bluepin, bool commonAnode = false);

    // additional
    virtual long     GetColorLong() const;
    virtual const CFX_Color GetColor() const;
    virtual void     SetColor(const CFX_Color& color);
    
    // inherited
    virtual void     Commit();
    
  protected:
    CFX_RGBLed();
    
  private:
    int m_redpin;
    int m_greenpin;
    int m_bluepin;
    
    CFX_Color m_color;
    bool      m_commonAnode;
};


#endif // CFX_RGBLED_H
