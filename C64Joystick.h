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
  const uint8_t Up = 0, Down = 1, Left = 2, Right = 3, Fire = 4;
  
  private:
    Joystick_ *_controller;
    
    ///uint8_t _buttons[ _C64_MAX_BUTTONS ];
    ///bool    _pressed[ _C64_MAX_BUTTONS ];
    
  public:
    C64Joystick( uint8_t up, uint8_t down, 
      uint8_t left, uint8_t right,
      uint8_t fire );

    void begin();
    bool loop();
    
    //bool update();
};

#endif /* _C64_JOYSTICK_H_ */
