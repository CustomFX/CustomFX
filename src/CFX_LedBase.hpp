#ifndef CFX_LedBase_H
#define CFX_LedBase_H

#include <CFX_OutputBase.hpp>
#include <CFX_Color.hpp>

class CFX_LedBase: public CFX_OutputBase
{
  public:
    virtual void SetBrightness(uint8_t brightness) = 0;
    virtual uint8_t GetBrightness() const = 0;

    virtual void SetColor(const CFX_Color& color) = 0;
    virtual const CFX_Color GetColor() const = 0;
    virtual long GetColorLong() const = 0;
    virtual void Commit() = 0;
};

#endif //CFX_LedBase_H

