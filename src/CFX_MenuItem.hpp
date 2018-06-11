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

#ifndef CFX_MenuItem_H
#define CFX_MenuItem_H

#include <CFX_InputBase.hpp>

#define CFX_CMD_MENUITEM_SELECT           40
#define CFX_CMD_MENUITEM_LEAVE            41
#define CFX_CMD_MENUITEM_EXECUTE          42

class CFX_MenuItem: public CFX_InputBase
{
  public:
    CFX_MenuItem(int id);
    void SetNext(CFX_MenuItem& menuitem);
    void SetPrevious(CFX_MenuItem& menuitem);
    void Select();
    void Leave();
    CFX_MenuItem* Previous();
    CFX_MenuItem* Next();
    
    virtual const CFX_InputEvent* GetEvent(unsigned long time);
    virtual bool IsAnalog() const;

  private:
    CFX_MenuItem* m_next;
    CFX_MenuItem* m_previous;
    uint8_t m_event;
    uint8_t m_queuedevent;
};





#endif // CFX_MenuItem_H

