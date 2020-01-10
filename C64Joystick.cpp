/**
 * Project: RetroUSBJoystick
 * File: C64Joystick.cpp
 * 
 * Copyright: Hugo van Galen, 2020
 */
#include "C64Joystick.h"

void C64Joystick::setup() 
{
    C64JoystickBase::begin();
    Joystick_::begin( false );
}


void C64Joystick::sync()
{
    if (_lastSentState == _buttonState)
    {
        // Nothing to do...
        return;
    }
    
    
    DEBUG( "JoyState> " );
    
    if (_buttonState & C64_LEFT)
    {
        setXAxis( _C64_LEFT_X );
        DEBUG( "LEFT " );
    }
    else if (_buttonState & C64_RIGHT)
    { 
        setXAxis( _C64_RIGHT_X );
        DEBUG( "RGHT " );
    }
    else
    {
        setXAxis( _C64_CENTER_X );
        DEBUG( "---- " );
    }

    if (_buttonState & C64_UP)
    {
        setYAxis( _C64_UP_Y );
        DEBUG( "UP " );
    }
    else if (_buttonState & C64_DOWN)
    {
        setYAxis( _C64_DOWN_Y );
        DEBUG( "DN " );
    }
    else
    {
        setYAxis( _C64_CENTER_Y );
        DEBUG( "-- " );
    }

    DEBUGLN( _buttonState & C64_FIRE ? "FIRE" : "----" );
    
    setButton( _C64_FIRE_BUTTON, _buttonState & C64_FIRE ? 1 : 0 );
    sendState();
    
    _lastSentState = _buttonState;
    
} // void C64Joystick::sync()



/** 
 * This method updates button state. returns `true` if anything has changed
 * since last time.
 */
void C64Joystick::loop() 
{   
    while (update()) 
    {
        sync();
    }
    
} // void C64Joystick::loop()
