/**
 * Project: RetroUSBJoystick
 * File: C64JoystickBase.cpp
 * 
 * Copyright: Hugo van Galen, 2020
 */
#include "C64JoystickBase.h"

void C64JoystickBase::begin()
{
#ifndef C64_USE_PORTS
    for (uint8_t iter=0; iter < _C64_MAX_BUTTONS; iter++)
    {
        pinMode( _pins[ iter ], INPUT_PULLUP );
    }

#else
    _C64_DDRUDL |= _C64_MASKUDL;
    _C64_PORTUDL |= _C64_MASKUDL; // enable pull-ups
    
    _C64_DDRRF |= _C64_MASKRF;
    _C64_PORTRF |= _C64_MASKRF;

#ifdef C64_USE_INTERRUPTS
    
    /** 
     * Experimental interrupts don't quite work out.
     */
    
    cli();
    
    PCICR = _BV(PCIE0);
    PCMSK0 = _BV(PCINT4) | _BV(PCINT5) | _BV(PCINT6) | _BV(PCINT7);
    
    EICRA = (EICRA & ~((1<<ISC00) | (1<<ISC01))) | (CHANGE << ISC00);
    EIMSK |= _BV(INT0);
    
    EICRA = (EICRA & ~((1<<ISC10) | (1<<ISC11))) | (CHANGE << ISC10);
    EIMSK |= _BV(INT1);
    
    sei();
    
#endif /* C64_USE_INTERRUPTS */
    
#endif /* C64_USE_PORTS */
    
    // Set an initial invalid value to detect changes.
    _buttonState[0] = 0xFF;        
    _buttonState[1] = 0xFF;
}


uint8_t C64JoystickBase::get()
{
    return _buttonState[0];
}

uint8_t C64JoystickBase::getExtra()
{
    return _buttonState[1];
}

/**
 * This reads the extra button state.
 */
uint8_t C64JoystickBase::readExtra()
{
#ifdef C64_USE_PORTS
    uint8_t newState = 0;
    return newState;
#endif /* C64_USE_PORTS */
    
} // uint8_t C64JoystickBase::readExtra()


uint8_t C64JoystickBase::read() 
{
#ifdef C64_USE_PORTS
    
    //uint8_t udl = (_C64_PINUDL >> 4); // (0b00000111 & (_C64_PINUDL >> 4));
    //DEBUG( "UDL: " );
    //DEBUGBIN( udl );
    //uint8_t rf =  (_C64_PINRF << 3); // (0b00011000 & (_C64_PINRF << 3));
    
    //DEBUG( ", RF: " );
    //DEBUGBIN( rf );
    //uint8_t newState = ~( 0b11100000 | udl | rf );
    
    uint8_t newState = ~( 0b11100000 | (_C64_PINUDL >> 4) | (_C64_PINRF << 3) );
    
    //DEBUG( ", newState: " );
    //DEBUGBIN( newState );
    //newState = ~newState;
    
    //DEBUG( "buttonState: " );
    //DEBUGBIN( newState );
    //DEBUG( "\n" );
    
#else 

    uint8_t newState = 0;
    
    for (uint8_t iter = 0; iter < _C64_MAX_BUTTONS; iter++)
    {            
        if (digitalRead( _pins[ iter ] ) == LOW)
        {  
            newState |= (1 << iter);
        }
        
    }

#endif /* C64_USE_PORTS */

#ifdef C64_JOYSTICK_TEST
    DEBUG( "newState: " );
    DEBUGBIN( newState );
    DEBUG( "\n" );
#endif
    
    return newState;
    
} // uint8_t C64JoystickBase::read() 



/**
 * This updates the _buttonState and returns `true` if it has
 * changed since last time.
 */
bool C64JoystickBase::update() 
{
    bool ret = false;
    uint8_t newState;
    
    newState = read();
    if (newState != _buttonState[0])
    {
        _buttonState[0] = newState;        
        ret = true;
    }
    
    newState = readExtra();
    if (newState != _buttonState[1])
    {
        _buttonState[1] = newState;
        ret = true;
    }
    
    if (ret)
    {
        // If this delay is not added, we somehow
        // receive 3 events (DOWN, RELEASE and DOWN again)
        //
        // Possibly because of the lack of debouncing logic; but,
        // with "The Arcade" joystick anyway, strangely enough 
        // this only happens to the the directional buttons; the 
        // FIRE button works fine.
        delayMicroseconds( 10000 );
    }
    
#ifdef SERIAL_DEBUG   
    if (ret)
    {
        Serial.print( "buttonState: " );
        DEBUGBIN( _buttonState[0] );
        Serial.print( " " );
        DEBUGBIN( _buttonState[1] );
        Serial.println();
    }
#endif
    
    return ret;
    
} // bool C64JoystickBase::update()



/**
 * This method allows external updates (for example when
 * receiving wireless data.
 */
void C64JoystickBase::set( uint8_t state )
{
    _buttonState[0] = state;
}

void C64JoystickBase::setExtra( uint8_t state )
{
    _buttonState[1] = state;
}
