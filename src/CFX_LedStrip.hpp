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

#include <CFX_LedStripBase.hpp>
#include <CFX_ColorRange.hpp>

#include "Adafruit_NeoPixel.h"
#ifdef __AVR__
#include "avr/power.h"
#endif

class CFX_LedStrip: public CFX_LedStripBase
{
  public:
    CFX_LedStrip(int pinnumber, uint16_t leds, int type = NEO_GRB + NEO_KHZ800);

    // additional
    virtual uint16_t GetNrOfOutputs() const;
    virtual const CFX_Color GetPixelColor(uint16_t pixel) const;
    virtual void SetPixelColor(uint16_t pixel, const CFX_Color& color);
    virtual long GetPixelColorLong(uint16_t pixel) const;
    
    virtual void SetPixelBrightness(uint16_t pixel, uint8_t brightness);
    virtual uint8_t GetPixelBrightness(uint16_t pixel) const;
  
    
    // inherited
    virtual const CFX_Color GetColor() const;
    virtual long GetColorLong() const;
    virtual void SetColor(const CFX_Color& color);
    virtual void SetColorRange(const CFX_ColorRange& colorrange, uint16_t index = 0);
    virtual void SetBrightness(uint8_t brightness);
    virtual uint8_t GetBrightness() const;
    virtual void Commit();

  protected:
    CFX_LedStrip();
    void Init();
    
  private:
    int m_type;
    int m_pinnumber;
    uint16_t m_nrleds;
    Adafruit_NeoPixel m_pixels;
    uint8_t *m_pixelcolors; 
    bool m_initialised;
};




#endif // CFX_LEDSTRIP_H
