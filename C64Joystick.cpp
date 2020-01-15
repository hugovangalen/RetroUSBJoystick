/**
 * Project: RetroUSBJoystick
 * File: C64Joystick.cpp
 * 
 * Copyright: Hugo van Galen, 2020
 */
#include "C64Joystick.h"

void C64Joystick::begin() 
{
    C64JoystickBase::begin();
    
    setXAxisRange( _C64_LEFT_X, _C64_RIGHT_X );
    setYAxisRange( _C64_UP_Y, _C64_DOWN_Y );
    
    /*
    setRxAxisRange( _C64_LEFT_X, _C64_RIGHT_X );
    setRyAxisRange( _C64_UP_Y, _C64_DOWN_Y );
    
    setRudderRange( _C64_LEFT_X, _C64_RIGHT_X );
    setSteeringRange( _C64_LEFT_X, _C64_RIGHT_X ); 

    setBrakeRange( _C64_LEFT_X, _C64_RIGHT_X );
    setThrottleRange( _C64_LEFT_X, _C64_RIGHT_X );
    */
    Joystick_::begin( false );
}

//#define SET_HORZ( a )       setXAxis( a ); setRxAxis( a ); setSteering( a ); setRudder( a )
//#define SET_VERT( a )       setYAxis( a ); setRyAxis( a ); setThrottle( a ); setBrake( a )
#define SET_HORZ( a )       setXAxis( a )
#define SET_VERT( a )       setYAxis( a )

//#define SET_HORZ( a )       
//#define SET_VERT( a )



void C64Joystick::sync()
{
    if (_lastSentState[0] == _buttonState[0]
        && _lastSentState[1] == _buttonState[1])
    {
        // Nothing to do...
        return;
    }
    
    _lastSentState[0] = _buttonState[0];
    _lastSentState[1] = _buttonState[1];

    DEBUG( "JoyState> " );
    // DEBUGBIN( _buttonState[0] );

      
    if (_buttonState[0] & C64_LEFT)
    {
        DEBUG( "LEFT " );
        
        SET_HORZ( _C64_LEFT_X );
        
setButton( _C64_BUTTON_LEFT,  1 );
setButton( _C64_BUTTON_RIGHT, 0 );
    }
    else if (_buttonState[0] & C64_RIGHT)
    { 
        DEBUG( "RGHT " );
        
        SET_HORZ( _C64_RIGHT_X );
        
setButton( _C64_BUTTON_LEFT,  0 );
setButton( _C64_BUTTON_RIGHT, 1 );

    }
    else
    {
        DEBUG( "---- " );
    
        SET_HORZ( _C64_CENTER_X );  
        
setButton( _C64_BUTTON_LEFT,  0 );
setButton( _C64_BUTTON_RIGHT, 0 );

    }

    
    
    if (_buttonState[0] & C64_UP)
    {
        DEBUG( "UP " );
        
        SET_VERT( _C64_UP_Y );
setButton( _C64_BUTTON_UP,   1 );
setButton( _C64_BUTTON_DOWN, 0 );
    }
    else if (_buttonState[0] & C64_DOWN)
    {
        DEBUG( "DN " );
        
        SET_VERT( _C64_DOWN_Y );
setButton( _C64_BUTTON_UP,   0 );
setButton( _C64_BUTTON_DOWN, 1 );
    }
    else
    {
        DEBUG( "-- " );
        
        SET_VERT( _C64_CENTER_Y );
setButton( _C64_BUTTON_UP,   0 );
setButton( _C64_BUTTON_DOWN, 0 );
    }

    DEBUGLN( _buttonState[0] & C64_FIRE ? "FIRE" : "----" );
    
    setButton( _C64_BUTTON_FIRE, _buttonState[0] & C64_FIRE ? 1 : 0 );
    sendState();
    
    
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
