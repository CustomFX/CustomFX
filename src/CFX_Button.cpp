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

#include <CFX_Button.hpp>

CFX_Button::CFX_Button(int inputPin, int id) : CFX_InputBase(id)
{
  SetPinNumber(inputPin);
  pinMode(inputPin, INPUT);
  m_lastClick = 0;
  m_pressed = false;
  m_doubleClick = false;
  m_doubleClickEnabled = true;
  m_clicked = false;
  m_clicks = 0;
  
  m_doubleclickInterval = 400;
  m_clickAndHoldThreshold = 750;

}

const CFX_InputEvent* CFX_Button::GetEvent(unsigned long time)
{
  int value = digitalRead(GetPinNumber());
  if (m_pressed)
  {
    if (value == HIGH) // button (still) pressed
    {
      if (time - m_lastClick > m_clickAndHoldThreshold) // check press and hold
      {
        // generate press and hold event
        SetEvent(CFX_CMD_BUTTON_CLICK_AND_HOLD, m_clicks+1);
        return GetLastEvent();
      }
    }
    else // button released
    {
      if (m_doubleClickEnabled)
      {
        if (m_doubleClick)
        {
          if (time - m_lastClick < m_doubleclickInterval) // check if release before double click time
          {
            // generate double click event
            m_clicks++;
            SetEvent(CFX_CMD_BUTTON_DOUBLE_CLICK, m_clicks);
            m_pressed = false;
            m_doubleClick = false;
            m_clicked = false;
            return GetLastEvent();
          }
          else if (time - m_lastClick > m_clickAndHoldThreshold) // check if release after press and hold
          {
            m_pressed = false;
            m_doubleClick = false;
            m_clicked = false;
            m_clicks++;
          }
          else
          {
            m_pressed = false;
            m_doubleClick = false;
            m_clicked = false;
            m_clicks++;
            SetEvent(CFX_CMD_BUTTON_CLICK, m_clicks);
            return GetLastEvent();
          }
        }
        else
        {
          if (time - m_lastClick > m_clickAndHoldThreshold) // check if release after press and hold
          {
            m_pressed = false;
            m_clicked = false;
            m_clicks++;
          }
          else if (time - m_lastClick > m_doubleclickInterval)
          {
            // generate click event
            m_clicks++;
            SetEvent(CFX_CMD_BUTTON_CLICK, m_clicks);
            m_pressed = false;
            m_clicked = false;
            return GetLastEvent();
          }
          else //Release within doubleclick time
          {
            m_pressed = false;
            m_clicked = true;
          }
        }
      }
      else
      {
        if (time - m_lastClick < m_clickAndHoldThreshold) // check if release before press and hold time
        {
          // generate click event
          m_clicks++;
          SetEvent(CFX_CMD_BUTTON_CLICK, m_clicks);
          m_pressed = false;
          m_doubleClick = false;
          return GetLastEvent();
        }
        else
        {
          m_pressed = false;
          m_doubleClick = false;
          m_clicks++;
        }
      }
    }
  }
  else
  {
    if (value == HIGH)
    {
      if (m_doubleClickEnabled)
      {
        if (time - m_lastClick < m_doubleclickInterval) // check double click
        {
          m_doubleClick = true;
          m_pressed = true;
        }
        else // new click
        {
          m_lastClick = time;
          m_pressed = true;
        }
      }
      else
      {
        m_lastClick = time;
        m_pressed = true;
      }
    }
    else if (m_clicked)
    {
      if (time - m_lastClick > m_doubleclickInterval) // wait for doubleclick to end
      {
        // generate click event
        m_clicks++;
        SetEvent(CFX_CMD_BUTTON_CLICK, m_clicks);
        m_pressed = false;
        m_doubleClick = false;
        m_clicked = false;
        return GetLastEvent();
      }
    }
  }
  
  return 0;
}

void CFX_Button::DisableDoubleClick(bool disabled)
{
  m_doubleClickEnabled = !disabled;
}

void CFX_Button::SetDoubleclickInterval(unsigned int doubleclickinterval) 
{
  m_doubleclickInterval = doubleclickinterval;
  
  if (m_doubleclickInterval == 0)
  {
    DisableDoubleClick(true);
  }
}

void CFX_Button::SetClickAndHoldThreshold(unsigned int thresholdvalue) 
{
  m_clickAndHoldThreshold = thresholdvalue;
}
