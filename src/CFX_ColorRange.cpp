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

#include <CFX_ColorRange.hpp>

CFX_ColorRange::CFX_ColorRange(int colors)
{
  if (colors <= 0)
  {
    colors = 1;
  }
  
  m_colors = new CFX_Color[colors];
  m_ranges = new uint16_t[colors];
  m_totalColors = colors;
  m_definedColors = 0;
  m_totalRange = 0;
  m_maxRange = 0;
}

bool CFX_ColorRange::AddColor(const CFX_Color& color, uint16_t range)
{
  if (m_definedColors < m_totalColors)
  {
    m_colors[m_definedColors] = color;
    m_ranges[m_definedColors] = range;
    m_totalRange += range;
    m_definedColors++;
    return true;
  }
  else
  {
    return false;
  }
}

bool CFX_ColorRange::SetColor(int index, const CFX_Color& color, uint16_t range)
{
  if (index < m_totalColors)
  {
    m_colors[index] = color;
    // adjust range
    m_totalRange -= m_ranges[index];
    // Set new range
    m_ranges[index] = range;
    m_totalRange += range;
    return true;
  }
  else
  {
    return false;
  }
}

CFX_Color CFX_ColorRange::GetColor(uint16_t index) const
{
  uint16_t newindex = index;
  if (m_definedColors > 0)
  {
    if (m_maxRange > 0)
    {
      newindex = ((float)newindex/m_maxRange) * m_totalRange;
    }
    newindex = newindex % m_totalRange;
    
    // find segment
    if (newindex < m_ranges[0]) // first segment
    {
      float factor = (float)newindex / m_ranges[0];
      return m_colors[0] * factor;
    }
    else if (newindex >= m_totalRange) // last segment
    {
      return m_colors[m_definedColors - 1];
    }
    else
    {
      int first = 0;
      int second = 0;
      uint16_t range = m_ranges[0];
      for (int i = 1; i < m_definedColors; i++)
      {
        range += m_ranges[i];
        if (newindex < range)
        {
          first = i-1;
          second = i;
          break;
        }
      }

      // find the color
      if (range == newindex)
      {
        return m_colors[first];
      }
      else
      {
        float factor = ((float)(newindex) + m_ranges[second] - range) / m_ranges[second];
        int red = factor * ((int)m_colors[second].Red() - (int)m_colors[first].Red()) + 
                    (int)m_colors[first].Red();
        int green = factor * ((int)m_colors[second].Green() - (int)m_colors[first].Green()) + 
                    (int)m_colors[first].Green();
        int blue = factor * ((int)m_colors[second].Blue() - (int)m_colors[first].Blue()) + 
                    (int)m_colors[first].Blue();
        return CFX_Color(red, green, blue);
      }
    }
  }
  else
  {
    return CFX_Color(0);
  }
}

uint16_t CFX_ColorRange::GetMaxRange()
{
  if (m_maxRange ==0)
  {
    return m_maxRange;
  }
  else
  {
    return m_totalRange;
  }
}

void CFX_ColorRange::SetMaxRange(uint16_t maxrange)
{
  m_maxRange = maxrange;
}
