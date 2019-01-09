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

#include <CFX_ColorPalette.hpp>

CFX_ColorPalette::CFX_ColorPalette(const byte depth)
{
  m_colors = new CFX_Color[depth];
  m_depth = depth;
}

CFX_ColorPalette::CFX_ColorPalette()
{
}

CFX_Color CFX_ColorPalette::GetColor(byte index) {
	if (index >= m_depth) {
		return m_colors[m_depth - 1];
	} else if (m_depth < 0) {
		return m_colors[0];
	}
	return m_colors[index];
}

void CFX_ColorPalette::SetColor(byte index, CFX_Color color) {
	if (index >= 0 && index < m_depth) {
		m_colors[index] = color;
	}
}

byte CFX_ColorPalette::GetColorDepth() {
	return m_depth;
}