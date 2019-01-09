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
#include <CFX_ColorPalette.hpp>
#include <CFX_Color.hpp>

CFX_Sprite::CFX_Sprite(byte width, byte height, const byte* drawing, CFX_ColorPalette& palette) : CFX_OutputBase()
{
  m_width = width;
  m_height = height;
  m_palette = palette;
  m_x_position = 0;
  m_y_position = 0;
  m_drawing = drawing;
}

void CFX_Sprite::SetOrigin(signed int newX, signed int newY) {
  m_x_position = newX;
  m_y_position = newY;
}

void CFX_Sprite::Draw(CFX_LedStrip &ledstrip) {
  byte depth = m_palette.GetColorDepth();
  for (int y = 0; y < m_height; y++) {
    for (int x = 0; x < m_width; x++) {
      uint16_t index = y * m_width + x;
      CFX_Color color = GetColor(index, depth);
    }
  }
}

void CFX_Sprite::Commit()
{
  
}

CFX_Color CFX_Sprite::GetColor(uint16_t index, byte depth) {
	if (depth <= 2) {
		return m_palette.GetColor(convert2(index));
	} else if (depth <= 4) {
		return m_palette.GetColor(convert4(index));
	} else if (depth <= 16) {
		return m_palette.GetColor(convert16(index));
	} else {
		return m_palette.GetColor(convert256(index));
	}
}	

byte CFX_Sprite::convert2(uint16_t index) {
  uint16_t arrayIndex = index / 8;
  uint16_t bitIndex = index % 8;
  return (m_drawing[arrayIndex] >> 7 - bitIndex) & 1;
}

byte CFX_Sprite::convert4(uint16_t index) {
  uint16_t arrayIndex = index / 4;
  uint16_t bitIndex = index % 4;
  return (m_drawing[arrayIndex] >> 6 - bitIndex*2) & 3;
}

byte CFX_Sprite::convert16(uint16_t index) {
  uint16_t arrayIndex = index / 2;
  uint16_t bitIndex = index % 2;
  return (m_drawing[arrayIndex] >> 4 - bitIndex*4) & 15;
}
  
byte CFX_Sprite::convert256(uint16_t index) {
  return m_drawing[index];
}
