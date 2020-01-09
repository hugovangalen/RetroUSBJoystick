#ifndef _C64JOYSTICK_PACKET_H_
#define _C64JOYSTICK_PACKET_H_

struct JoystickPacket
{
    uint8_t  id;    // client identification (radio ID)
    uint32_t seq;   // sequence number
    uint8_t  buttonState;
};

#endif /* _C64JOYSTICK_PACKET_H_ */
