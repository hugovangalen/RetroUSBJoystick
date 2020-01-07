#include "C64Joystick.h"

C64Joystick::C64Joystick( uint8_t up, 
    uint8_t down,
    uint8_t left,
    uint8_t right,
    uint8_t fire ) : C64JoystickBase( up, down, left, right, fire )
{
  _controller = new Joystick_( _C64_HID_ID, JOYSTICK_TYPE_JOYSTICK, 1 );
  
} // constructor


void C64Joystick::begin() 
{
  _controller->begin( false );
}



/** 
 * This method updates button state. returns `true` if anything has changed
 * since last time.
 */
bool C64Joystick::loop() 
{
    if (update()) 
    {
    #ifdef SERIAL_DEBUG
        Serial.print( "JoyState> " );
    #endif
        if (_pressed[ Left ]) 
        {
        _controller->setXAxis( _C64_LEFT_X );
    #ifdef SERIAL_DEBUG
        Serial.print( "LEFT " );
    #endif
        }
        else if (_pressed[ Right ])
        { 
        _controller->setXAxis( _C64_RIGHT_X );
    #ifdef SERIAL_DEBUG          
        Serial.print( "RGHT " );
    #endif          
        }
        else
        {
        _controller->setXAxis( _C64_CENTER_X );
    #ifdef SERIAL_DEBUG          
        Serial.print( "---- " );
    #endif          
        }

        if (_pressed[ Up ])
        {
        _controller->setYAxis( _C64_UP_Y );
    #ifdef SERIAL_DEBUG          
        Serial.print( "UP " );
    #endif
        }
        else if (_pressed[ Down ])
        {
        _controller->setYAxis( _C64_DOWN_Y );
    #ifdef SERIAL_DEBUG         
        Serial.print( "DN " );
    #endif          
        }
        else
        {
        _controller->setYAxis( _C64_CENTER_Y );
    #ifdef SERIAL_DEBUG          
        Serial.print( "-- " );
    #endif          
        }

    #ifdef SERIAL_DEBUG
        Serial.println( _pressed[ Fire ] ? "FIRE" : "----" );
    #endif        
        _controller->setButton( _C64_FIRE_BUTTON, _pressed[ Fire ] ? 1 : 0 );
        
        _controller->sendState();
        
        return true;
    }
    
    return false;
      
} // bool C64Joystick::loop()
