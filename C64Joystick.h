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

#define _C64_HID_ID1    0x64
#define _C64_HID_ID2    0x65
#define _C64_HID_ID3    0x66

#define _C64_LEFT_X        0
#define _C64_CENTER_X    512
#define _C64_RIGHT_X    1023

#define _C64_UP_Y          0
#define _C64_CENTER_Y    512
#define _C64_DOWN_Y     1023

#define _C64_FIRE_BUTTON   0

//typedef Joystick_* JoystickPointer;

class C64Joystick : public C64JoystickBase, Joystick_ {
  
  private:
    uint8_t _lastSentState = 0;
    
  public:
    C64Joystick( uint8_t _id ) : Joystick_( _id,
        JOYSTICK_TYPE_GAMEPAD,
        1,      // button count
        0,      // hat switch count
        
        true,   // x axis
        true,   // y
        false,  // z
        
        false,  // rx axis
        false,  // ry
        false,  // rz
        
        false, // rudder
        false, // accelerometer
        false, // brake
        false  // steering
    ) {}
    
    void setup();
    void loop();
    void sync();
    
    void begin() 
    {
        C64JoystickBase::begin();
        Joystick_::begin( false );
    }
};

#endif /* _C64_JOYSTICK_H_ */
