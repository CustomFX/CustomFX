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

#include <CFX_LedStripBase.hpp>

uint16_t CFX_LedStripBase::NextPixel(const uint16_t pixel, const int increment) const
{
  uint16_t length = GetNrOfOutputs();
  int inc = abs(increment) % length;
  if (increment < 0)
  {
    inc = -inc;
  }

  if (inc + (int)pixel < 0)
  {
    return length + pixel + inc;
  }
  else if (pixel + inc >= length)
  {
    return pixel + inc - length;
  }
  else 
  {
    return pixel + inc;
  }
}


