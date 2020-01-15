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

#define _C64_HID_ID1    0x03
#define _C64_HID_ID2    0x04
#define _C64_HID_ID3    0x05

/**
 * The ranges for the analog sticks.
 */
#define _C64_LEFT_X     -1024
#define _C64_CENTER_X   0
#define _C64_RIGHT_X    1024

#define _C64_UP_Y       -1024
#define _C64_CENTER_Y   0
#define _C64_DOWN_Y     1024


/**
 * The buttons presses that will be sent to the host.
 */
#define _C64_BUTTON_FIRE     0
#define _C64_BUTTON_UP      12
#define _C64_BUTTON_DOWN    14
#define _C64_BUTTON_LEFT    15
#define _C64_BUTTON_RIGHT   13

class C64Joystick : public C64JoystickBase, Joystick_ {
  
  private:
    uint8_t _lastSentState[2] = {0xff,0xff};
    
  public:
    C64Joystick( uint8_t _id = _C64_HID_ID1 ) : Joystick_( _id,
        JOYSTICK_TYPE_JOYSTICK,
        16,     // button count
        0,      // hat switch count
        
        true,   // x axis
        true,   // y
        false,  // z
        
        false,  // rx axis
        false,  // ry
        false,  // rz
        
        false,  // rudder
        false,  // throttle
        false,  // accelerometer
        false,  // brake
        false   // steering
    ) {}
    
    //void setup();
    void loop();
    void sync();
    void begin();
    
    /* void begin() 
    {
        C64JoystickBase::begin();
        
        Joystick_::begin( false );
    } */
};

#endif /* _C64_JOYSTICK_H_ */
