#ifndef CFX_LedStripSegment_H
#define CFX_LedStripSegment_H

#include <CFX_LedStripBase.hpp>
#include <CFX_LedStrip.hpp>

class CFX_LedStripSegment: public CFX_LedStripBase
{
  public:
    CFX_LedStripSegment(CFX_LedStrip* ledstrip, uint16_t startled, uint16_t length);
    
    // Inherrited
    virtual void SetBrightness(uint8_t brightness);
    virtual uint8_t GetBrightness() const;

    virtual void SetColor(const CFX_Color& color);
    virtual const CFX_Color GetColor() const;
    virtual long GetColorLong() const;
        
    virtual uint16_t GetNrOfOutputs() const;

    virtual void SetColorRange(const CFX_ColorRange& colorrange, uint16_t index = 0);

    virtual void SetPixelBrightness(uint16_t pixel, uint8_t brightness);
    virtual uint8_t GetPixelBrightness(uint16_t pixel) const;

    virtual const CFX_Color GetPixelColor(uint16_t pixel) const;
    virtual void SetPixelColor(uint16_t pixel, const CFX_Color& color);
    virtual long GetPixelColorLong(uint16_t pixel) const;

    virtual void Commit();
    
  private:
    CFX_LedStrip* m_ledstrip;
    uint16_t m_length;
    uint16_t m_startled;

};


#endif //CFX_LedStripSegment_H

