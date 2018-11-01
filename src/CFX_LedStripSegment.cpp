#include "CFX_LedStripSegment.hpp"

CFX_LedStripSegment::CFX_LedStripSegment(CFX_LedStrip* ledstrip, uint16_t startled, uint16_t length)
{
  m_length = length;
  m_startled = startled;
  m_ledstrip = ledstrip;
}

void CFX_LedStripSegment::SetBrightness(uint8_t brightness)
{
  if (m_ledstrip)
  {
    for (uint16_t pixel = 0; pixel < m_length; pixel++)
    {
      m_ledstrip->SetPixelBrightness(m_startled + pixel, brightness);
    }
  }
}

uint8_t CFX_LedStripSegment::GetBrightness() const
{
  if (m_ledstrip)
  {
    return m_ledstrip->GetPixelBrightness(m_startled);
  }
  else
  {
    return 0;
  }
}

void CFX_LedStripSegment::SetColor(const CFX_Color& color)
{
  if (m_ledstrip)
  {
    for (uint16_t pixel = 0; pixel < m_length; pixel++)
    {
      m_ledstrip->SetPixelColor(m_startled + pixel, color);
    }
  }
}

const CFX_Color CFX_LedStripSegment::GetColor() const
{
  if (m_ledstrip)
  {
    return m_ledstrip->GetPixelColor(m_startled);
  }
  else
  {
    return 0;
  }
}

long CFX_LedStripSegment::GetColorLong() const
{
  return GetPixelColorLong(m_startled);
}

uint16_t CFX_LedStripSegment::GetNrOfOutputs() const
{
  return m_length;
}

void CFX_LedStripSegment::SetColorRange(const CFX_ColorRange & colorrange, uint16_t index)
{
  for (uint16_t i = 0; i < m_length; i++)
  {
    SetPixelColor(i, colorrange.GetColor(i + index));
  }
}

void CFX_LedStripSegment::SetPixelBrightness(uint16_t pixel, uint8_t brightness)
{
  if ((m_ledstrip) && (pixel < m_length))
  {
    m_ledstrip->SetPixelBrightness(m_startled + pixel, brightness);
  }
}

uint8_t CFX_LedStripSegment::GetPixelBrightness(uint16_t pixel) const
{
  if ((m_ledstrip) && (pixel < m_length))
  {
    return m_ledstrip->GetPixelBrightness(m_startled + pixel);
  }
  else
  {
    return 0;
  }
}

const CFX_Color CFX_LedStripSegment::GetPixelColor(uint16_t pixel) const
{
  if ((m_ledstrip) && (pixel < m_length))
  {
    return m_ledstrip->GetPixelColor(m_startled + pixel);
  }
  else
  {
    return CFX_Color(0);
  }
}

void CFX_LedStripSegment::SetPixelColor(uint16_t pixel, const CFX_Color & color)
{
  if ((m_ledstrip) && (pixel < m_length))
  {
    m_ledstrip->SetPixelColor(m_startled + pixel, color);
  }
}

long CFX_LedStripSegment::GetPixelColorLong(uint16_t pixel) const
{
  if ((m_ledstrip) && (pixel < m_length))
  {
    m_ledstrip->GetPixelColorLong(m_startled + pixel);
  }
  else
  {
    return 0;
  }
}

void CFX_LedStripSegment::Commit()
{
  // The commit is handled by the Ledstrip
}


