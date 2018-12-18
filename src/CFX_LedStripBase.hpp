  #ifndef CFX_LedStripBase_H
#define CFX_LedStripBase_H

#include <CFX_LedBase.hpp>
#include <CFX_ColorRange.hpp>

class CFX_LedStripBase: public CFX_LedBase
{
  public:

    virtual uint16_t GetNrOfOutputs() const = 0;
    
    virtual void SetColorRange(const CFX_ColorRange& colorrange, uint16_t index = 0) = 0;

    virtual void SetPixelBrightness(uint16_t pixel, uint8_t brightness) = 0;
    virtual uint8_t GetPixelBrightness(uint16_t pixel) const = 0;

    virtual const CFX_Color GetPixelColor(uint16_t pixel) const = 0;
    virtual void SetPixelColor(uint16_t pixel, const CFX_Color& color) = 0;
    virtual long GetPixelColorLong(uint16_t pixel) const = 0;
    virtual void Commit() = 0;
    // helper functions
    uint16_t NextPixel(const uint16_t pixel, const int increment) const;

};

#endif // CFX_LedStripBase_H

