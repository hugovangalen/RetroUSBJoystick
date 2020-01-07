#ifndef _C64_JOYSTICK_BASE_H_
#define _C64_JOYSTICK_BASE_H_

#include <Arduino.h>

#define _C64_MAX_BUTTONS   5

class C64JoystickBase {
  const uint8_t Up = 0, Down = 1, Left = 2, Right = 3, Fire = 4;
  
  protected:
    // Joystick_ *_controller;
    uint8_t _buttons[ _C64_MAX_BUTTONS ];
    bool    _pressed[ _C64_MAX_BUTTONS ];
    
  public:
    C64JoystickBase( uint8_t up, uint8_t down, 
      uint8_t left, uint8_t right,
      uint8_t fire ) 
    {
        _buttons[ Fire ] = fire;
        _buttons[ Left ] = left;
        _buttons[ Right ] = right;
        _buttons[ Down ] = down;
        _buttons[ Up ] = up;

        for(uint8_t iter=0; iter < _C64_MAX_BUTTONS; iter++)
        {
            pinMode( _buttons[ iter ], INPUT_PULLUP );
            _pressed[ iter ] = false;
        }
        
    } // constructor

    //void begin() {}
    bool update() {
        bool changed = false;
        for(uint8_t iter=0; iter < _C64_MAX_BUTTONS; iter++) 
        {
            // All C64 buttons are ACTIVE LOW.
            bool temp = (digitalRead( _buttons[ iter ] ) == LOW);
            if (temp != _pressed[ iter ])
            {
                _pressed[ iter ] = temp;
                changed = true;
            }  
        }
        return changed;
    } // bool update()
};

#endif /* _C64_JOYSTICK_BASE_H_ */
