/**
 * Project: RetroUSBJoystick
 * File: C64JoystickRX.h
 * Purpose: Handler for the wireless-server (that which receives
 * data from the wireless-client).
 * 
 * Copyright: Hugo van Galen, 2020
 */
#ifndef _C64_JOYSTICK_RX_H_
#define _C64_JOYSTICK_RX_H_

#include <Arduino.h>

#include "NRF24Config.h"
#include "RetroUSBJoystickConfig.h"

#include <SPI.h>
#include <NRFLite.h>
#include <Joystick.h>

#ifdef REMOTE_ENCRYPTION_KEY
#include <AESLib.h>
#endif

#include "C64Joystick.h"
#include "C64JoystickPacket.h"

typedef C64Joystick* JoystickPointer;

/**
 * This is the RECEIVING part of the C64 Wireless Joystick,
 * which could handle more than 1 device connected over 
 * the radio.
 */
class C64JoystickRX : public NRFLite {
    protected:
        JoystickPacket _packet;

#ifdef DUAL_JOYSTICK_MODE
        JoystickPointer _controller1;
        JoystickPointer _controller2;
#else
        JoystickPointer _controller;
#endif

#ifdef REMOTE_ENCRYPTION_KEY
        //uint8_t _aes_key[] = REMOTE_ENCRYPTION_KEY;
        uint8_t _payload[ sizeof(JoystickPacket) ];
#endif
        
    public:
        C64JoystickRX() : NRFLite() {
#ifdef DUAL_JOYSTICK_MODE
            _controller1 = new C64Joystick( _C64_HID_ID1 );
            _controller2 = new C64Joystick( _C64_HID_ID2 );
#else
            _controller = new C64Joystick( _C64_HID_ID1 );
#endif
        }

        bool begin( bool irq = false, uint8_t irqPin = NRF24_IRQ );
        void loop();
};

#endif /* _C64_JOYSTICK_RX_H_ */
