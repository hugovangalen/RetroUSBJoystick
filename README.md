# RetroUSBJoystick

This is a very simple sketch that allows you to connect your C64 joystick via USB using an Arduino Micro (or other based on 32u4 with native USB support).

## Dependencies

- Joystick library,
  https://github.com/MHeironimus/ArduinoJoystickLibrary

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




