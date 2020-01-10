/**
 * Project: RetroUSBJoystick
 * File: C64JoystickRX.cpp
 * 
 * Copyright: Hugo van Galen, 2020
 */
#include "C64JoystickRX.h"

#ifdef DUAL_JOYSTICK_MODE
    Joystick_ _controller1( _C64_HID_ID1 );
    Joystick_ _controller2( _C64_HID_ID2 );
    Joystick_ _controller3( _C64_HID_ID3 );
    // C64Joystick _controller3( _C64_HID_ID3 );
#else
    C64Joystick _controller( _C64_HID_ID1 )
#endif
            

/**
 * This initialises the radio. If all looks okay, this will
 * return `true`.
 */
bool C64JoystickRX::begin( bool irq, uint8_t irqPin ) 
{
#ifdef DUAL_JOYSTICK_MODE
    DEBUGLN( "C64JoystickRX::begin DUAL MODE" );
    
    _controller1.begin(false);
    _controller2.begin(false);
    _controller3.begin(false);
    // _controller3.begin();
#else
    
    DEBUGLN( "C64JoystickRX::begin SINGLE MODE" );
    _controller.begin(false);
    
#endif
    
    if (!init( REMOTE_SERVER_ID, NRF24_CE, NRF24_SS, NRF24_BITRATE, NRF24_CHANNEL ))
    {
        DEBUGLN( "C64JoystickRX::NRF24 init fail!" );
        return false;
    }
    
#ifdef NRF24_SUPPORT_IRQ
    if (irq)
    {
        _radioPointer = this;
        attachInterrupt( digitalPinToInterrupt( irqPin ), radioInterrupt, FALLING );
    }
    else
    {
        _radioPointer = NULL;
    }
#endif
    
    return true;
    
} // bool C64JoystickRX::begin()


void C64JoystickRX::loop()
{
    while (hasData())
    {
        // DEBUGLN( "NRF24 has data." );
#ifdef ERROR_LED
        digitalWrite( ERROR_LED, HIGH );
#endif
        
        readData( &_packet );        
        
#ifdef SERIAL_DEBUG
        Serial.print( "Received seq=" );
        Serial.print( _packet.seq, DEC );
        Serial.print( ", data=" );
        Serial.println( _packet.buttonState, HEX );
#endif

#ifdef DUAL_JOYSTICK_MODE
        
        // The data could be for joystick#1 or joystick#2.
        if (_packet.id == 1)
        {
//            _controller1.set( _packet.buttonState );
//            _controller1.sync();
        }
        else if (_packet.id == 2)
        {
//            _controller2.set( _packet.buttonState );
//            _controller2.sync();
        }
#else
        _controller.set( _packet.buttonState );
        _controller.sync();
#endif

#ifdef ERROR_LED
        digitalWrite( ERROR_LED, LOW );
#endif

    }
    
} // void C64JoystickRX::loop()
