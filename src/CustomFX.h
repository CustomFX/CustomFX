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

#ifndef CUSTOM_FX_H
#define CUSTOM_FX_H

#ifndef MAX_INPUT_DEVICES
#define MAX_INPUT_DEVICES 15
#endif
#ifndef INPUT_UPDATE_INTERVAL
#define INPUT_UPDATE_INTERVAL 10
#endif
#ifndef MAX_OUTPUT_DEVICES
#define MAX_OUTPUT_DEVICES 15
#endif
#ifndef MAX_ANIMATIONS
#define MAX_ANIMATIONS 20
#endif
#ifndef ANIMATION_UPDATE_INTERVAL
#define ANIMATION_UPDATE_INTERVAL 10
#endif

#include <CFX_Color.hpp>

#include <CFX_InputBase.hpp>
#include <CFX_Button.hpp>
#include <CFX_Potentiometer.hpp>
#include <CFX_Timer.hpp>

#include <CFX_OutputBase.hpp>
#include <CFX_Led.hpp>
#include <CFX_RGBLed.hpp>
#include <CFX_LedStrip.hpp>
#include <CFX_LedStripPixel.hpp>
#include <CFX_Servo.hpp>

#include <CFX_InputController.hpp>
#include <CFX_AnimationController.hpp>

#include <CFX_AnimationBase.hpp>

#include <CFX_LedAnimationSequence.hpp>
#include <CFX_LedRandomAnimation.hpp>
#include <CFX_LedAnimationBlink.hpp>
#include <CFX_LedAnimationFadeInOut.hpp>

#include <CFX_RGBLedAnimationColorBlink.hpp>
#include <CFX_RGBLedAnimationFadeInOut.hpp>
#include <CFX_RGBLedAnimationFadeToColor.hpp>

#include <CFX_LedStripAnimationSweep.hpp>

#include <CFX_ServoAnimationMoveToPosition.hpp>
#include <CFX_ServoAnimationPath.hpp>
#include <CFX_ServoAnimationSweep.hpp>

#define CFX_Run() CFX_InputController::GetInstance()->ReadInputs();CFX_AnimationController::GetInstance()->UpdateAnimation();


#endif // CUSTOM_FX_H