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

#ifndef CFX_SPRITE_H
#define CFX_SPRITE_H

#include <CFX_OutputBase.hpp>
#include <CFX_RGBMatrix.hpp>
#include <CFX_ColorPalette.hpp>
#include <CFX_Color.hpp>

#define CFX_SPRITE_BLACK_WHITE  1
#define CFX_SPRITE_4_COLOR      2
#define CFX_SPRITE_16_COLOR     4
#define CFX_SPRITE_256_COLOR    8

class CFX_Sprite: public CFX_OutputBase
{
  public:
    CFX_Sprite(byte width, byte height, const byte* drawing, CFX_ColorPalette& palette);
    void Draw(CFX_RGBMatrix &matrix); // TODO pass matrix
    void SetOrigin(signed int newX, signed int newY);
    
    void Commit();

  private:
    const byte* m_drawing;
    signed int m_x_position;
    signed int m_y_position;
    byte m_width;
    byte m_height;
    CFX_ColorPalette m_palette;
	CFX_Color GetColor(uint16_t index, byte depth);
	byte convert2(uint16_t index);
	byte convert4(uint16_t index);
	byte convert16(uint16_t index);
	byte convert256(uint16_t index);
	
	
};

#endif // CFX_SPRITE_H