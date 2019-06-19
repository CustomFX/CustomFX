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

#include <CFX_SpriteContainer.hpp>

CFX_SpriteContainer::CFX_SpriteContainer() : CFX_Sprite()
{
	m_x_position = 0;
	m_y_position = 0;
}

void CFX_SpriteContainer::AddSprite(CFX_Sprite* sprite)
{
  m_sprites.Add(sprite);
}

void CFX_SpriteContainer::Draw(CFX_RGBMatrix* matrix)
{
	// TODO Z-order of sprite relative to container
  if (this->IsActive())
  {
    for (uint16_t i = 0; i < m_sprites.Size(); i++)
    {
      CFX_Sprite* sprite = m_sprites.Get(i);
      sprite->Draw(matrix);
    }
  }
}

void CFX_SpriteContainer::SetOrigin(signed int newX, signed int newY)
{
  // calculate relative movement
  Move(newX - m_x_position, newY - m_y_position);
}

void CFX_SpriteContainer::Move(signed int horizontal, signed int vertical)
{
  for (uint16_t i = 0; i < m_sprites.Size(); i++)
  {
    CFX_Sprite* sprite = m_sprites.Get(i);
    sprite->Move(horizontal, vertical);
  }
	m_x_position += horizontal;
	m_y_position += vertical;
}

void CFX_SpriteContainer::Commit()
{
  // nothing to do here. Thes sprites are drawn with draw memberfunction
}
