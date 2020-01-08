#ifndef _C64_JOYSTICK_BASE_H_
#define _C64_JOYSTICK_BASE_H_

#include <Arduino.h>

//#define SERIAL_DEBUG

#if defined(SERIAL_DEBUG)
  #define DEBUG( a )    Serial.print( a )
  #define DEBUGLN( a )  Serial.println( a )
#else
  #define DEBUG( a )    /* void */
  #define DEBUGLN( a )  /* void */
#endif

#define _C64_MAX_BUTTONS   5

#define _C64_PIN_UP        8
#define _C64_PIN_DOWN      9
#define _C64_PIN_LEFT     10
#define _C64_PIN_RIGHT     3
#define _C64_PIN_FIRE      2

#define C64_UP             1
#define C64_DOWN           2
#define C64_LEFT           4
#define C64_RIGHT          8
#define C64_FIRE          16

#define C64_USE_PORTS

/**
 * Interrupts are experimental. This appears
 * to behave quite buggy.
 */
 
//#define C64_USE_INTERRUPTS

/* PB4, PB5, PB6 */
#define _C64_PORTUDL   PORTB
#define _C64_DDRUDL    DDRB
#define _C64_PINUDL    PINB
#define _C64_MASKUDL   0b01110000

/* PD0, PD1 */
#define _C64_PORTRF    PORTD
#define _C64_DDRRF     DDRD
#define _C64_PINRF     PIND
#define _C64_MASKRF    0b00000011

#define _C64_PCINTU    PCINT4
#define _C64_PCINTD    PCINT5
#define _C64_PCINTL    PCINT6

#define _C64_INTF      INT0
#define _C64_INTR      INT1

class C64JoystickBase {
  private:
    bool    _irq;
#ifndef C64_USE_PORTS
    uint8_t _pins[ _C64_MAX_BUTTONS ];
#endif
    
  protected:
    uint8_t _buttonState = 0;
    
  public:
#ifdef C64_USE_PORTS
    C64JoystickBase() 
    {
        _irq = true;
                
    } // constructor
    
#else
    C64JoystickBase( 
        bool irq = false,
        uint8_t up = _C64_PIN_UP, 
        uint8_t down = _C64_PIN_DOWN, 
        uint8_t left = _C64_PIN_LEFT, 
        uint8_t right = _C64_PIN_RIGHT, 
        uint8_t fire = _C64_PIN_FIRE )
    {
        _pins[ 0 ] = up;
        _pins[ 1 ] = down;
        _pins[ 2 ] = left;
        _pins[ 3 ] = right;
        _pins[ 4 ] = fire;
        
        _irq = irq;
    } // constructor
#endif

    void begin();
    uint8_t read();
    bool update(); 
    uint8_t get();
    
    void set( uint8_t state );
};

#endif /* _C64_JOYSTICK_BASE_H_ */
