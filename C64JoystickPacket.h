/**
 * Project: RetroUSBJoystick
 * File: C64JoystickPacket.h
 * Purpose: Relevant for wireless-server and wireless-client, this 
 * defines the structure of the radio packet.
 * 
 * Copyright: Hugo van Galen, 2020
 */
#ifndef _C64JOYSTICK_PACKET_H_
#define _C64JOYSTICK_PACKET_H_

struct JoystickPacket
{
    uint8_t  id;    // client identification (radio ID)
    uint32_t seq;   // sequence number
    
    uint8_t  buttonState[2]; // two bytes now for additional buttons
    
#ifdef REMOTE_ENCRYPTION_KEY
    // The following is only used when encryption is enabled.
    uint8_t  padding[8]; // to make the packet mod 16 in size for encryption
    uint8_t  check; // id + sec, used to verify decrypted packet validity...
#endif /* REMOTE_ENCRYPTION_KEY */

};

#endif /* _C64JOYSTICK_PACKET_H_ */
