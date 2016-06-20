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

#ifndef CFX_BUTTON_H
#define CFX_BUTTON_H

#include <CFX_InputBase.hpp>

#define CFX_CMD_BUTTON_CLICK            10
#define CFX_CMD_BUTTON_DOUBLE_CLICK     11
#define CFX_CMD_BUTTON_CLICK_AND_HOLD   12

// Digital Input
//
class CFX_Button: public CFX_InputBase
{
  public:
    CFX_Button(int inputPin, int id);
    virtual const CFX_InputEvent* GetEvent(unsigned long time);
    void DisableDoubleClick(bool disabled = true);
    
    void SetDoubleclickInterval(unsigned int doubleclickinterval);
    void SetClickAndHoldThreshold(unsigned int thresholdvalue);

  private:
    int m_command; // pressed, released, double click, click and hold
    unsigned int m_doubleclickInterval; // time between clicks to be recognised as double click
    unsigned int m_clickAndHoldThreshold; // time before a click and hold signals is given
    bool m_doubleClickEnabled;
    unsigned long m_lastClick;
    bool m_pressed;
    bool m_doubleClick;
    bool m_clicked;
    unsigned long m_clicks;
};




#endif // CFX_BUTTON_H
