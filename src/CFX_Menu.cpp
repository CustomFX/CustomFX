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

#include <CFX_Menu.hpp>

CFX_Menu::CFX_Menu()
{
  m_opened = false;
}

void CFX_Menu::AddMenuItem(CFX_MenuItem& menuitem)
{
  if (m_root)
  {
    CFX_MenuItem* lastitem = m_root->Previous();
    lastitem->SetNext(menuitem);
    menuitem.SetPrevious(*lastitem);
    m_root->SetPrevious(menuitem);
    menuitem.SetNext(*m_root);
  }
  else // first item
  {
    m_root = &menuitem;
    menuitem.SetNext(menuitem);
    menuitem.SetPrevious(menuitem);
 }
}

void CFX_Menu::OpenMenu()
{
  m_opened = true;
  m_currentItem = m_root;
  m_currentItem->Select();
}

void CFX_Menu::CloseMenu()
{
  m_opened = false;
  m_currentItem->Leave();
}

void CFX_Menu::Toggle()
{
  if (m_opened)
  {
    CloseMenu();
  }
  else
  {
    OpenMenu();
  }  
}

bool CFX_Menu::isOpen() const
{
  return m_opened;
}

void CFX_Menu::NextItem()
{
  if (m_opened)
  {
    m_currentItem->Leave();
    m_currentItem = m_currentItem->Next();
    m_currentItem->Select();
  }
}

void CFX_Menu::PreviousItem()
{
  if (m_opened)
  {
    m_currentItem->Leave();
    m_currentItem = m_currentItem->Previous();
    m_currentItem->Select();
  }
}

const CFX_MenuItem& CFX_Menu::GetActiveItem()
{
  return *m_currentItem;
}