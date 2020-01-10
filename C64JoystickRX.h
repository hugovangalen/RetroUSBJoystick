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

#include <SPI.h>
#include <NRFLite.h>
#include <Joystick.h>

#include "NRF24Config.h"
#include "RetroUSBJoystickConfig.h"

#include "C64Joystick.h"
#include "C64JoystickPacket.h"

/**
 * This is the RECEIVING part of the C64 Wireless Joystick,
 * which could handle more than 1 device connected over 
 * the radio.
 */
class C64JoystickRX : public NRFLite, C64Joystick {
    protected:
        JoystickPacket _packet;

    public:
        C64JoystickRX() : NRFLite(), C64Joystick() {}

        bool begin( bool irq = false, uint8_t irqPin = NRF24_IRQ );
        void loop();
};

#endif /* _C64_JOYSTICK_RX_H_ */
