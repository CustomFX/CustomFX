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

#include <CFX_MenuItem.hpp>

CFX_MenuItem::CFX_MenuItem(int id)
 : CFX_InputBase(id, CFX_Other_Input)
{
  m_event = 0;
  m_queuedevent = 0;
}

void CFX_MenuItem::SetNext(CFX_MenuItem& menuitem)
{
  m_next = &menuitem;
}

void CFX_MenuItem::SetPrevious(CFX_MenuItem& menuitem)
{
  m_previous = &menuitem;
}

void CFX_MenuItem::Select()
{
  m_queuedevent = CFX_CMD_MENUITEM_SELECT;
}

void CFX_MenuItem::Leave()
{
  m_event = CFX_CMD_MENUITEM_LEAVE;
}

CFX_MenuItem* CFX_MenuItem::Previous()
{
  return m_previous;
}

CFX_MenuItem* CFX_MenuItem::Next()
{
  return m_next;
}

const CFX_InputEvent* CFX_MenuItem::GetEvent(unsigned long time)
{
  if (m_event != 0)
  {
    SetEvent(m_event, 0);
    m_event = 0;
    return GetLastEvent();
  }
  else
  {
    if (m_queuedevent != 0)
    {
      m_event = m_queuedevent;
      m_queuedevent = 0;
    }
    return 0;
  }     
}

bool CFX_MenuItem::IsAnalog() const
{
  false;
}
