#include "C64Joystick.h"

#define SERIAL_DEBUG
#define ERROR_LED       13

#if defined(SERIAL_DEBUG)
  #define DEBUG( a )    Serial.print( a )
  #define DEBUGLN( a )  Serial.println( a )
#else
  #define DEBUG( a )    /* void */
  #define DEBUGLN( a )  /* void */
#endif


/** `LOCAL_CLIENT` if no wireless is required. */
//#define LOCAL_CLIENT

/** `REMOTE_CLIENT` if this is the SENDER of wireless data. */
#define REMOTE_ClIENT

/** `REMOTE_SERVER` if this is the RECEIVER of wireless data. */
//#define REMOTE_SERVER

#if defined(REMOTE_CLIENT)
C64JoystickTX joy( 2, 3, 4, 5, 6 );
#endif

#if defined(LOCAL_CLIENT)
C64Joystick joy( 2, 3, 4, 5, 6 );
#endif

void setup() 
{
#ifdef ERROR_LED 
  pinMode( ERROR_LED, OUTPUT );
#endif
    
#ifdef SERIAL_DEBUG
  Serial.begin( 2000000 );
  while(!Serial);
  Serial.println( "v0.9.2 READY" );
#endif
 

#if defined(REMOTE_CLIENT)
  // Try to initialise the radio. Deadlock if there is a failure.
  if (!joy.begin())
  {
    DEBUGLN( "RF24 init failed!" );
    
    // Deadlock with optional blinking LED.
    while(1) {
#ifdef ERROR_LED
        digitalWrite( ERROR_LED, HIGH );
        delay( 250 );
        digitalWrite( ERROR_LED, LOW );
        delay( 250 );
#endif /* ERROR_LED */
    }
  }
  
#endif /* REMOTE_CLIENT */

#if defined(LOCAL_CLIENT)
  joy.begin();
#endif /* LOCAL_CLIENT */
  
} // void setup()



void loop() 
{
#if defined(LOCAL_CLIENT)
  joy.update();  
#endif /* LOCAL_CLIENT */
  
} // void loop()

