#include <Arduino.h>
#include <Joystick.h>



#define _C64_HID_ID       0x03

#define _C64_MAX_BUTTONS   5

#define _C64_LEFT_X        0
#define _C64_CENTER_X    512
#define _C64_RIGHT_X    1023

#define _C64_UP_Y          0
#define _C64_CENTER_Y    512
#define _C64_DOWN_Y     1023

#define _C64_FIRE_BUTTON   0


class C64Joystick {
  const uint8_t Up = 0, Down = 1, Left = 2, Right = 3, Fire = 4;
  
  private:
    Joystick_ *_controller;
    
    uint8_t _buttons[ _C64_MAX_BUTTONS ];
    bool    _pressed[ _C64_MAX_BUTTONS ];
    
  public:
    C64Joystick( uint8_t up, 
      uint8_t down,
      uint8_t left,
      uint8_t right,
      uint8_t fire ) {

        _controller = new Joystick_( _C64_HID_ID, JOYSTICK_TYPE_JOYSTICK, 1 );
        
        _buttons[ Fire ] = fire;
        _buttons[ Left ] = left;
        _buttons[ Right ] = right;
        _buttons[ Down ] = down;
        _buttons[ Up ] = up;

        for(uint8_t iter=0; iter < _C64_MAX_BUTTONS; iter++)
        {
          pinMode( _buttons[ iter ], INPUT_PULLUP );
          _pressed[ iter ] = false;
        }
    }

    void begin() 
    {
      _controller->begin( false );
    }

    /** 
     * This method updates button state. returns `true` if anything has changed
     * since last time.
     */
    bool update() 
    {
      bool changed = false;
      for(uint8_t iter=0; iter < _C64_MAX_BUTTONS; iter++) 
      {
        // All C64 buttons are ACTIVE LOW.
        bool temp = (digitalRead( _buttons[ iter ] ) == LOW);
        if (temp != _pressed[ iter ])
        {
            _pressed[ iter ] = temp;
            changed = true;
        }  
      }

      if (changed)
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
      }

      return changed;
      
    } // update()
};


//
C64Joystick joy( 2, 3, 4, 5, 6 );

void setup() {
  
#ifdef SERIAL_DEBUG
  Serial.begin( 2000000 );
  while(!Serial);
  Serial.println( "Hello :) v0.9.1" );
#endif
 
  delay( 125 );
  
  joy.begin();
}

void loop() {
  joy.update();  
}
