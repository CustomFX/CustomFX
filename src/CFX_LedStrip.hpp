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

#ifndef CFX_LEDSTRIP_H
#define CFX_LEDSTRIP_H

#include <CFX_RGBLed.hpp>
#include "Adafruit_NeoPixel.h"
#ifdef __AVR__
#include "avr/power.h"
#endif

class CFX_LedStrip: public CFX_RGBLed
{
  public:
    CFX_LedStrip(int pinnumber, int leds, int type = NEO_RGB + NEO_KHZ800);

    // additional
    virtual int  GetNrOfOutputs() const;
    virtual const CFX_Color GetPixelColor(int pixel) const;
    virtual long GetPixelColorLong(int pixel) const;
    virtual void SetPixelColor(int led, const CFX_Color& color);
    virtual long GetColorLong() const;
    
    // inherited
    virtual const CFX_Color GetColor() const;
    virtual void SetColor(const CFX_Color& color);
    virtual void SetBrightness(uint8_t brightness);
    virtual void Commit();

  protected:
    CFX_LedStrip();
    void Init();
    
  private:
    int m_type;
    bool m_changed;
    int m_pinnumber;
    int m_nrleds;
    Adafruit_NeoPixel m_pixels;
    uint8_t (*m_pixelcolors)[3];  
    bool m_initialised;
};




#endif // CFX_LEDSTRIP_H
