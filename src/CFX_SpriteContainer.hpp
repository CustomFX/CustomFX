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

#ifndef CFX_SPRITECONTAINER_H
#define CFX_SPRITECONTAINER_H

#include <CFX_Sprite.hpp>
#include <CFX_RGBMatrix.hpp>
#include <CFX_Color.hpp>


class CFX_SpriteContainer: public CFX_Sprite
{
  public:
    CFX_SpriteContainer();
    void AddSprite(CFX_Sprite* sprite);
    void Draw(CFX_RGBMatrix* matrix); 
    void SetOrigin(signed int newX, signed int newY);
    void Move(signed int horizontal, signed int vertical);
    void Commit();

  private: // private functions
    
    
  private: // private members
    CFX_List<CFX_Sprite*> m_sprites;
    signed int m_x_position;
    signed int m_y_position;	
	
};

#endif // CFX_SPRITECONTAINER_H