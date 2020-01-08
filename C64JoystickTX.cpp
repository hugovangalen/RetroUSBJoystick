#include "C64JoystickTX.h"

/**
 * EXPERIMENTAL IRQ STUFF
 * 
 * If we want IRQs to work, we need a handle to the instatiated object.
 * This gets assigned in the constructor.
 */
static C64JoystickTX *_radioPointer = NULL;

/*
static bool _sendSucceeded, _sendFailed;

static void radioInterrupt()
{
    if (_radioPointer == NULL)
    {
        // Unlikely that this happens. But just in case.
        return;
    }
    
    // Ask the radio what caused the interrupt.  This also resets the IRQ pin on the
    // radio so a new interrupt can be triggered.
    uint8_t txOk, txFail, rxReady;
    _radioPointer->whatHappened(txOk, txFail, rxReady);

    // txOk = the radio successfully transmitted data.
    // txFail = the radio failed to transmit data.
    // rxReady = the radio received data.

    if (txOk)
    {
        _sendSucceeded = true;
    }
    
    if (txFail)
    {
        _sendFailed = true;
    }
}
 */


/**
 * The constructor.
 */
C64JoystickTX::C64JoystickTX( uint8_t deviceId ) : NRFLite(), C64JoystickBase()
{
    _deviceId = deviceId;
}



/**
 * This initialises the radio. If all looks okay, this will
 * return `true`.
 */
bool C64JoystickTX::begin( bool irq, uint8_t irqPin ) 
{
    if (!init( _deviceId, NRF24_CE, NRF24_SS, NRF24_BITRATE, NRF24_CHANNEL ))
    {
        return false;
    }
    
    if (irq)
    {
#ifdef NRF24_SUPPORT_IRQ
        _radioPointer = this;
        attachInterrupt( digitalPinToInterrupt( irqPin ), radioInterrupt, FALLING );
#endif
    }
    else
    {
        _radioPointer = NULL;
    }
    
    return true;
    
} // begin()

