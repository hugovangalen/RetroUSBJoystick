/**
 * Project: RetroUSBJoystick
 * File: C64JoystickRX.cpp
 * 
 * Copyright: Hugo van Galen, 2020
 */
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
    
    _packet.id = _deviceId;
    _packet.seq = 0;
}



/**
 * This initialises the radio. If all looks okay, this will
 * return `true`.
 */
bool C64JoystickTX::begin( bool irq, uint8_t irqPin ) 
{
    C64JoystickBase::begin();
    
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


/**
 * This sends the buttonState to the server component.
 */
void C64JoystickTX::sync()
{
    /*
    // Send the last operation multiple times to ensure
    // it reaches the other side.
    if (_buttonState != _packet.buttonState)
    {
        _txCount = 0;
    }
    else
    {
        _txCount++;
    }
    
    
    if (_txCount < 16)
    { 
    */
    if ((_buttonState[0] != _packet.buttonState[0])
        || (_buttonState[1] != _packet.buttonState[1]))
    {   
#ifdef ACTIVITY_ON_TX 
        TXLED1;
#endif

        _packet.seq++;
        
        _packet.buttonState[ 0 ] = _buttonState[ 0 ];
        _packet.buttonState[ 1 ] = _buttonState[ 1 ];
        
#ifdef SERIAL_DEBUG
        Serial.print( "Sending seq=" );
        Serial.print( _packet.seq, DEC );
        Serial.print( ", data=" );
        Serial.print( _packet.buttonState[0], HEX );
        Serial.print( " " );
        Serial.println( _packet.buttonState[1], HEX );
#endif
        
        if (!send( REMOTE_SERVER_ID, &_packet, sizeof( _packet )))
        {
            _failedTx++;
        
   

 #ifdef SERIAL_DEBUG
            if (_failedTx > 16)
            {
#ifdef ERROR_LED
                digitalWrite( ERROR_LED, HIGH );
#endif
                Serial.println( "NRF24 send failed more than 16 times!" );
                _failedTx = 0;
            }
#endif
        
        }
        else
        {
#ifdef ERROR_LED
            if (_failedTx > 16)
            {
                digitalWrite( ERROR_LED, LOW );
            }
#endif
            _failedTx = 0;
        
        }

#ifdef ACTIVITY_ON_TX 
        TXLED0;
#endif
        
    }
    
} // void C64JoystickTX::sync()


/** 
 * This method updates button state. returns `true` if anything has changed
 * since last time.
 */
void C64JoystickTX::loop() 
{   
#ifdef C64JOYSTICK_TX_TEST
    
    // In test mode we'll send one button after the 
    // other with some delay in between.
    for (uint8_t testState = 0b00000001; testState <= 0b00010000; testState = testState << 1)
    {
        // Send button press:
        _buttonState[ 0 ] = testState;
        
        sync();
        delay( 500 );
        
        // Send release:
        _buttonState[ 0 ] = 0;
        sync();
        
        delay( 1000 );
    }
    
    for (uint8_t testState = 0b00000001; testState <= 0b01000000; testState = testState << 1)
    {
        // Send button press:
        _buttonState[ 1 ] = testState;
        
        sync();
        delay( 500 );
        
        // Send release:
        _buttonState[ 1 ] = 0;
        sync();
        
        delay( 1000 );
    }
    
    
#else

    while (update()) 
    {
        sync();
    }
    
#endif /* C64JOYSTICK_TX_TEST */


} // bool C64JoystickTX::loop()
