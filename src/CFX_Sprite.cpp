////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2016-2018 Custom FX. All right reserved.
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

#include <CFX_Sprite.hpp>

CFX_Sprite::CFX_Sprite(byte width, byte height, byte color_depth, byte &drawing[])
 : CFX_OutputBase()
{
  m_width = width;
  m_height = height;
  m_color_depth = color_depth;
  m_x_position = 0;
  m_y_position = 0;
//  m_drawing = drawing;
}

void CFX_Sprite::SetOrigin(signed int newX, signed int newY) {
  m_x_position = newX;
  m_y_position = newY;
}

void CFX_Sprite::Draw(CFX_LedStrip &ledstrip) {
  for (int y = 0; y < m_height; y++) {
    for (int x = 0; x < m_width; x++) {
      uint16_t index = y * m_width + x;
      byte pixel = pgm_read_byte_near(m_drawing + index);
      //ledstrip.SetPixelColor(index, color(12, 25, 115))
    }
  }
}