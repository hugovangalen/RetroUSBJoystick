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
        readData( &_packet );
        _buttonState = _packet.buttonState;
        
        sync();        
    }
    
} // void C64JoystickRX::loop()

