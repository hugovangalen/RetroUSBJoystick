#include "C64JoystickRX.h"

/**
 * This initialises the radio. If all looks okay, this will
 * return `true`.
 */
bool C64JoystickRX::begin( bool irq, uint8_t irqPin ) 
{
    C64Joystick::begin();
    
    if (!init( REMOTE_SERVER_ID, NRF24_CE, NRF24_SS, NRF24_BITRATE, NRF24_CHANNEL ))
    {
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

        _buttonState = _packet.buttonState;
        sync();

#ifdef ERROR_LED
        digitalWrite( ERROR_LED, LOW );
#endif

    }
    
} // void C64JoystickRX::loop()
