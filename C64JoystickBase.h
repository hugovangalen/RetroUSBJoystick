#ifndef _C64_JOYSTICK_BASE_H_
#define _C64_JOYSTICK_BASE_H_

#include <Arduino.h>

#define SERIAL_DEBUG

#if defined(SERIAL_DEBUG)
  #define DEBUG( a )    Serial.print( a )
  #define DEBUGLN( a )  Serial.println( a )
#else
  #define DEBUG( a )    /* void */
  #define DEBUGLN( a )  /* void */
#endif


#define _C64_MAX_BUTTONS   5

/**
 * The C64 joystick is connected to digital 
 * pins 2, 3, 4, 5, 6:
 */
#ifndef C64_PORT
#define C64_PORT          PORTD
#endif

#ifndef C64_DDR
#define C64_DDR           DDRD
#endif

#ifndef C64_DDR_MASK
#define C64_DDR_MASK      0b01111100
#endif

#define C64_UP            1
#define C64_DOWN          2
#define C64_LEFT          4
#define C64_RIGHT         8
#define C64_FIRE         16

class C64JoystickBase {
  //const uint8_t Up = 0, Down = 1, Left = 2, Right = 3, Fire = 4;

  protected:
    uint8_t _buttonState = 0;
    
  public:
    C64JoystickBase() 
    {
        C64_DDR |= C64_DDR_MASK;
        _buttonState = 0;        
    } // constructor

    //void begin() {}
    bool update() 
    {
        uint8_t newState = C64_PORT; // 1111100
        newState = newState >> 2;    // 0011111
        
        if (newState != _buttonState)
        {
            _buttonState = newState;
            return true;
        }
        
        return false;
        
    } // bool update()
    
};

#endif /* _C64_JOYSTICK_BASE_H_ */
