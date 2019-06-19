////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2016-2019 Custom FX. All right reserved.
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

class CFX_Sprite; // forward declaration

#include <CFX_OutputBase.hpp>
#include <CFX_RGBMatrix.hpp>
#include <CFX_ColorPalette.hpp>
#include <CFX_Color.hpp>

#define CFX_SPRITE_BLACK_WHITE  1
#define CFX_SPRITE_4_COLOR      2
#define CFX_SPRITE_16_COLOR     4
#define CFX_SPRITE_256_COLOR    8

class CFX_Sprite//: public CFX_OutputBase
{
  public:
    CFX_Sprite(byte width, byte height, const byte* drawing, CFX_ColorPalette& palette);
    CFX_Sprite();
    void SetBitmap(const byte* drawing);
    virtual void Draw(CFX_RGBMatrix* matrix); 
    virtual void SetOrigin(signed int newX, signed int newY);
	  virtual void SetOrigin(CFX_Sprite originalSprite);
    virtual void Move(signed int horizontal, signed int vertical);
    virtual void Mirror();
    virtual void Flip();
    
    virtual signed int GetXPosition() const;
    virtual signed int GetYPosition() const;
	      
    void SetActive(bool active);
    bool IsActive() const;
	
    void Commit();

  private: // private functions
    CFX_Color GetColor(uint16_t index, byte depth);
    byte convert2(uint16_t index);
    byte convert4(uint16_t index);
    byte convert16(uint16_t index);
    byte convert256(uint16_t index);
  
  private: // private members
    bool m_active;
    const byte* m_drawing;
    signed int m_x_position;
    signed int m_y_position;
    byte m_width;
    byte m_height;
    CFX_ColorPalette m_palette;
    bool m_mirrorred;
    bool m_flipped;
	
	
};

#endif // CFX_SPRITE_H