/**
 * Project: RetroUSBJoystick
 * File: C64Joystick.h
 * Purpose: Code for the standalone / wired solution.
 * 
 * Copyright: Hugo van Galen, 2020
 */
#ifndef _C64_JOYSTICK_H_
#define _C64_JOYSTICK_H_

#include "C64JoystickBase.h"

#include <Arduino.h>
#include <Joystick.h>

#define _C64_HID_ID       0x03

#define _C64_LEFT_X        0
#define _C64_CENTER_X    512
#define _C64_RIGHT_X    1023

#define _C64_UP_Y          0
#define _C64_CENTER_Y    512
#define _C64_DOWN_Y     1023

#define _C64_FIRE_BUTTON   0

class C64Joystick : public C64JoystickBase {
  
  private:
    Joystick_ *_controller;
    uint8_t _lastSentState = 0;
    
  public:
    C64Joystick();
    
    void setup();
    void loop();
    void sync();
};

#endif /* _C64_JOYSTICK_H_ */
