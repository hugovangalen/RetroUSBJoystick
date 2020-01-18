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
    
    Joystick_::begin( false );
}

//#define SET_HORZ( a )       setXAxis( a ); setRxAxis( a ); setSteering( a ); setRudder( a )
//#define SET_VERT( a )       setYAxis( a ); setRyAxis( a ); setThrottle( a ); setBrake( a )
//#define SET_HORZ( a )       
//#define SET_VERT( a )
#define SET_HORZ( a )       setXAxis( a )
#define SET_VERT( a )       setYAxis( a )


/**
 * This synchronises the button state over the USB bus.
 */
void C64Joystick::sync()
{
    if (_lastSentState[0] != _buttonState[0])
    {
        _lastSentState[0] = _buttonState[0];
        DEBUG( "JoyState> " );
      
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
#ifdef C64_EXTRA_BUTTONS
        setButton( _C64_RTRIG, _buttonState[0] & C64_FIRE ? 1 : 0 );
#else
        setButton( _C64_BUTTON_FIRE, _buttonState[0] & C64_FIRE ? 1 : 0 );
#endif
        
    } // _lastSentState[0]
    
#ifdef C64_EXTRA_BUTTONS
    
    if (_lastSentState[1] != _buttonState[1])
    {
        _lastSentState[1] = _buttonState[1];

        setButton( _C64_BACK, _buttonState[1] & C64_EXTRA_BACK ? 1 : 0 );
        setButton( _C64_START, _buttonState[1] & C64_EXTRA_START ? 1 : 0 );
        setButton( _C64_A, _buttonState[1] & C64_EXTRA_ENTER ? 1 : 0 );
        setButton( _C64_B, _buttonState[1] & C64_EXTRA_SELECT ? 1 : 0 );
        
        setButton( _C64_X, _buttonState[1] & C64_EXTRA_X ? 1 : 0 );
        setButton( _C64_Y, _buttonState[1] & C64_EXTRA_Y ? 1 : 0 );
        
        //setButton( _C64_LTRIG, _buttonState[1] & C64_EXTRA_TRIGGER ? 1 : 0 );
        setButton( _C64_LTRIG, _buttonState[1] & C64_EXTRA_TRIGGER ? 1 : 0 );
    }

#endif
    
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
