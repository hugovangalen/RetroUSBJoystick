/**
 * RetroUSBJoystick.ino
 * 
 * Arduino sketch for connecting an old-school C64 joystick
 * to a modern machine via USB.
 * 
 * See README.md for more information.
 */
#include "RetroUSBJoystickConfig.h"

#if defined(REMOTE_CLIENT)

#include "C64JoystickTX.h"
#define C64JOYSTICK_MODE 1

/**
 * Instantiate the TX (transmit) component. This is what 
 * the actual joystick is connect to -- and which sends to
 * the RX (receiving) part.
 */
C64JoystickTX joy( REMOTE_CLIENT );

#endif

#if defined(REMOTE_SERVER)
#include "C64JoystickRX.h"
#define C64JOYSTICK_MODE 2

/**
 * Instantiate the RX (receive) component.
 */
C64JoystickRX joy;

#endif

#if defined(LOCAL_CLIENT)
#include "C64Joystick.h"
#define C64JOYSTICK_MODE 0

/**
 * Instantiate a local USB joystick that is connected locally. This
 * is the "wired" solution.
 */
C64Joystick joy;
#endif


#ifndef C64JOYSTICK_MODE
#error You need to enable REMOTE_SERVER, REMOTE_CLIENT or LOCAL_CLIENT. (These are mutually exclusive, you can only enable one.)
#endif


/**
 * Set-up everything.
 */
void setup() 
{
#ifdef ERROR_LED 
  pinMode( ERROR_LED, OUTPUT );
  digitalWrite( ERROR_LED, HIGH );
#endif
    
#ifdef SERIAL_DEBUG
  Serial.begin( 9600 );
  while(!Serial);
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
  joy.setup();
#endif /* LOCAL_CLIENT */
  

#ifdef SERIAL_DEBUG
    
  #if defined(LOCAL_CLIENT)
  DEBUG( "LocalClient " );
  #endif

  #if defined(REMOTE_CLIENT)
  DEBUG( "ControllerTX" );
  #endif

  #if defined(REMOTE_SERVER)
  DEBUG( "ControllerRX" );
  #endif
  
  Serial.println( " v0.9.3 by Hugo van Galen, 2020" );
#endif

#ifdef ERROR_LED 
  digitalWrite( ERROR_LED, LOW );
#endif

} // void setup()



/**
 * This just calls `loop` repeatedly in the classes
 * handling the joystick or wireless connection.
 */
void loop() 
{
  joy.loop();  
    
} // void loop()

