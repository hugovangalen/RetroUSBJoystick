/**
 * Project: RetroUSBJoystick
 * File: C64JoystickBase.cpp
 * 
 * Copyright: Hugo van Galen, 2020
 */
#include "C64JoystickBase.h"

void C64JoystickBase::begin()
{
    _C64_DDRUDL |= _C64_MASKUDL;
    _C64_PORTUDL |= _C64_MASKUDL; // enable pull-ups
    
    _C64_DDRRF |= _C64_MASKRF;
    _C64_PORTRF |= _C64_MASKRF;

#ifdef C64_EXTRA_BUTTONS
    
    _C64_DDR1235 |= _C64_MASK1235;
    _C64_PORT1235 |= _C64_MASK1235;
    
    _C64_DDR4 |= _C64_MASK4;
    _C64_PORT4 |= _C64_MASK4; // enable pull-ups -- doesn't work?!
    digitalWrite( 5, 1 ); // force pull-up...
     
    _C64_DDR67 |= _C64_MASK67;    
    _C64_PORT67 |= _C64_MASK67;
    digitalWrite( A3, 1 );
    digitalWrite( A2, 1 );
    
#endif

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
    uint8_t newState = 0;    
    uint8_t temp = _C64_PIN1235;
    
    if (temp & 0b10000000) newState |= 0b00001000; // button 5
    temp = temp & 0b00011100;
    newState |= (temp >> 2); 
    
    temp = _C64_PIN4 & 0b01000000;
    newState |= (temp >> 2);
    
    temp = _C64_PIN67 & 0b00110000;
    newState |= (temp << 1);
    
    newState = ~(0b10000000 | newState);
    
//    DEBUGBIN( newState );
//    DEBUG( "\n" );
    
    return newState;

} // uint8_t C64JoystickBase::readExtra()



/**
 * This reads the joystick state.
 */
uint8_t C64JoystickBase::read() 
{
    uint8_t newState = ~( 0b11100000 | (_C64_PINUDL >> 4) | (_C64_PINRF << 3) );
    
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

#ifdef C64_EXTRA_BUTTONS
    newState = readExtra();
#else
    newState = 0;
#endif

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
