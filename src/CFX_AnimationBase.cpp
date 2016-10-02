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

#include <CFX_AnimationBase.hpp>
#include <CFX_AnimationController.hpp>

CFX_AnimationBase::CFX_AnimationBase()
{
 	CFX_AnimationController::GetInstance()->RegisterAnimation(this);
  m_active = true;
}

void CFX_AnimationBase::Start()
{
  m_active = true;
}

void CFX_AnimationBase::Stop()
{
  m_active = false;
}

bool CFX_AnimationBase::IsActive() const
{
  return m_active;
}
