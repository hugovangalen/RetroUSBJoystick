# RetroUSBJoystick

This is a very simple sketch that allows you to connect your "retro" C64 joystick on modern systems via USB. It requires an Arduino Micro (or other boards based on ATmega32u4 with native USB support). 

## Dependencies

- Arduino IDE,
- Joystick library, https://github.com/MHeironimus/ArduinoJoystickLibrary

## Connections

Female joystick connector as seen at the end of the cable:
```
                 Joystick    Arduino Micro
                        1 => N/C
   1 2 3 4 5            2 => Digital pin 5 (RIGHT)
 +-----------+          3 => Digital pin 4 (LEFT)
 | o o o o o |          4 => Digital pin 3 (DOWN)
  \ o o o o /           5 => Digital pin 2 (UP)
   +-------+            6 => N/C
    6 7 8 9             7 => GND
                        8 => VCC (+5V)
                        9 => Digital pin 6 (FIRE)
```


## Wireless (NRF24)

I am working on a solution that allows you to use these old joysticks *wirelessly*.


## License

Copyright (C) 2020 Hugo van Galen

This software is provided 'as-is', without any express or implied warranty. In no event will the authors be held liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:

- The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.

- Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.

- This notice may not be removed or altered from any source distribution.

