#include "C64Joystick.h"

C64Joystick joy( 2, 3, 4, 5, 6 );

void setup() 
{
#ifdef SERIAL_DEBUG
  Serial.begin( 2000000 );
  while(!Serial);
  Serial.println( "v0.9.2 READY" );
#endif
 
  joy.begin();
}

void loop() 
{
  joy.update();  
}
