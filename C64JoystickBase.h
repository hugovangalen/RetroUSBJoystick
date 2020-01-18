/**
 * Project: RetroUSBJoystick
 * File: C64JoystickBase.h
 * Purpose: Code that polls the joystick. This is used by the standalone/wired
 * operation mode, and the wireless-client.
 * 
 * Copyright: Hugo van Galen, 2020
 */
#ifndef _C64_JOYSTICK_BASE_H_
#define _C64_JOYSTICK_BASE_H_

#include <Arduino.h>
#include "RetroUSBJoystickConfig.h"

/** 
 * If `C64_JOYSTICK_TEST` is defined, the button state
 * is logged to Serial monitor.
 * 
 * This requires `SERIAL_DEBUG` to also be defined.
 */
//#define C64_JOYSTICK_TEST


/**
 * Debugging macros. These do nothing if SERIAL_DEBUG is 
 * not defined.
 */
#if defined(SERIAL_DEBUG)
  #define DEBUG( a )    Serial.print( a )
  #define DEBUGLN( a )  Serial.println( a )
  #define DEBUGBIN( a ) for(uint8_t i = 8 ; i > 0 ; i--) {\
            uint8_t test = 1 << (i-1); \
            Serial.print( a & test ? "1":"0" ); \
        }

#else
  #define DEBUG( a )    /* void */
  #define DEBUGLN( a )  /* void */
  #define DEBUGBIN( a )
#endif


/**
 * Bits in _buttonState[0]
 */
#define C64_UP             0b00001
#define C64_DOWN           0b00010
#define C64_LEFT           0b00100
#define C64_RIGHT          0b01000
#define C64_FIRE           0b10000



/**
 * Interrupts are experimental. This appears
 * to behave quite buggy.
 */
//#define C64_USE_INTERRUPTS

/**
 * JOYSTICK CONNECTIONS
 */

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



/** 
 * Bits in _buttonState[1]
 */
#define C64_EXTRA_BACK     0b0000100
#define C64_EXTRA_START    0b0001000
#define C64_EXTRA_ENTER    0b0000001
#define C64_EXTRA_SELECT   0b0000010

#define C64_EXTRA_X        0b0010000
#define C64_EXTRA_Y        0b0100000

#define C64_EXTRA_TRIGGER  0b1000000

/** 
 * Extra button to USB button assignments.
 */
#define _C64_START         11
#define _C64_A              2
#define _C64_B              1
#define _C64_BACK           8

// Shoulder buttons
#define _C64_X              3
#define _C64_Y              9

// Fire buttons:
#define _C64_LTRIG          4
#define _C64_RTRIG          5


/**
 * EXTRA BUTTONS ON PCB BOARD for additional functions. 
 * 
 * This is mainly for TheC64.
 */

// Buttons 1,2,3 and 5 (pin 0 (PD2), 1 (PD3), 4 (PD4) and 6 (PD7) respectively)
#define _C64_PORT1235   PORTD
#define _C64_DDR1235    DDRD
#define _C64_PIN1235    PIND
#define _C64_MASK1235   0b10011100

// Button 4 (pin 5 (PC6)
#define _C64_PORT4      PORTC
#define _C64_DDR4       DDRC
#define _C64_PIN4       PINC
#define _C64_MASK4      0x01000000

// Button 6 and 7 (A3 (PF4) and A2 (PF5))
#define _C64_PORT67     PORTF
#define _C64_DDR67      DDRF
#define _C64_PIN67      PINF
#define _C64_MASK67     0x00110000

/**
 * Interrupt stuff is not quite working out well.
 */
#define _C64_PCINTU    PCINT4
#define _C64_PCINTD    PCINT5
#define _C64_PCINTL    PCINT6

#define _C64_INTF      INT0
#define _C64_INTR      INT1

class C64JoystickBase {
  private:      
#ifdef C64_USE_INTERRUPTS
    bool    _irq;
#endif
    
  protected:
    uint8_t _buttonState[2] = { 0, 0 };
    
  public:
    
    C64JoystickBase() 
    {
#ifdef C64_USE_INTERRUPTS
        _irq = true;
#endif
    } // constructor

    void begin();
    bool update(); 
    
    uint8_t read();
    uint8_t get();
    void set( uint8_t state );
    
    uint8_t readExtra();
    uint8_t getExtra();
    void setExtra( uint8_t state );
};

#endif /* _C64_JOYSTICK_BASE_H_ */
