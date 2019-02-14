#include "CFX_RGBMatrix.hpp"

CFX_RGBMatrix::CFX_RGBMatrix(int pinnumber, uint16_t width, uint16_t height, int type)
  :CFX_LedStrip(pinnumber, width * height, type)
{
  m_width = width;
  m_height = height;
}



void CFX_RGBMatrix::SetPixelColor(uint16_t x_pos, uint16_t y_pos, const CFX_Color& color)
{
  if (x_pos >= m_width || y_pos >= m_height)
    return;
  
  CFX_LedStrip::SetPixelColor(CalculatePixel(x_pos, y_pos), color);
}

long CFX_RGBMatrix::GetPixelColorLong(uint16_t x_pos, uint16_t y_pos) const
{
  if (x_pos >= m_width || y_pos >= m_height)
    return 0;

  return CFX_LedStrip::GetPixelColorLong(CalculatePixel(x_pos, y_pos));
}
    
void CFX_RGBMatrix::SetPixelBrightness(uint16_t x_pos, uint16_t y_pos, uint8_t brightness)
{
  if (x_pos >= m_width || y_pos >= m_height)
    return;

  CFX_LedStrip::SetPixelBrightness(CalculatePixel(x_pos, y_pos), brightness);
}

uint8_t CFX_RGBMatrix::GetPixelBrightness(uint16_t x_pos, uint16_t y_pos) const
{
  if (x_pos >= m_width || y_pos >= m_height)
    return 0;

  return CFX_LedStrip::GetPixelBrightness(CalculatePixel(x_pos, y_pos));
}
/*
void CFX_RGBMatrix::DisplayColorSprite(CFX_Sprite& sprite, uint16_t x_pos, uint16_t y_pos)
{
  
  /*
  Check color (palette)
  loop over sprite width
  loop over sprite height
  Getcolor
  setcolor
  */
/*}
  
void CFX_RGBMatrix::DisplayGrayscaleSprite(CFX_Sprite& sprite, uint16_t x_pos, uint16_t y_pos)
{
  /*
  loop over sprite width
  loop over sprite height
  getGrayscale
  setBrightness
  */
/*}*/
 
  
  
// private:
uint16_t CFX_RGBMatrix::CalculatePixel(uint16_t x_pos, uint16_t y_pos) const
{
  return y_pos * m_width + x_pos;
}
