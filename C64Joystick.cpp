#include "C64Joystick.h"

C64Joystick::C64Joystick() : C64JoystickBase()
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
        DEBUG( "JoyState> " );
        
        if (_buttonState & C64_LEFT)
        {
            _controller->setXAxis( _C64_LEFT_X );
            DEBUG( "LEFT " );
        }
        else if (_buttonState & C64_RIGHT)
        { 
            _controller->setXAxis( _C64_RIGHT_X );
            DEBUG( "RGHT " );
        }
        else
        {
            _controller->setXAxis( _C64_CENTER_X );
            DEBUG( "---- " );
        }

        if (_buttonState & C64_UP)
        {
            _controller->setYAxis( _C64_UP_Y );
            DEBUG( "UP " );
        }
        else if (_buttonState & C64_DOWN)
        {
            _controller->setYAxis( _C64_DOWN_Y );
            DEBUG( "DN " );
        }
        else
        {
            _controller->setYAxis( _C64_CENTER_Y );
            DEBUG( "-- " );
        }

        DEBUGLN( _buttonState & C64_FIRE ? "FIRE" : "----" );
        
        _controller->setButton( _C64_FIRE_BUTTON, _buttonState & C64_FIRE ? 1 : 0 );
        _controller->sendState();
        
        return true;
    }
    
    return false;
      
} // bool C64Joystick::loop()
