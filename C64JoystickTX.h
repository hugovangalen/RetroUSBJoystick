/**
 * Project: RetroUSBJoystick
 * File: C64JoystickTX.h
 * Purpose: Handler for the wireless-client (that which sends
 * data to the wireless-server).
 * 
 * Copyright: Hugo van Galen, 2020
 */
#ifndef _C64_JOYSTICK_TX_H_
#define _C64_JOYSTICK_TX_H_

#include "NRF24Config.h"
#include "RetroUSBJoystickConfig.h"

#include <SPI.h>
#include <NRFLite.h>

#ifdef REMOTE_ENCRYPTION_KEY
#include <AESLib.h>
#endif

#include "C64JoystickBase.h"
#include "C64JoystickPacket.h"

/**
 * If `C64JOYSTICK_TX_TEST` is enabled, the loop() will
 * infinitely iterate all the buttons and press/release
 * them with a delay.
 */
//#define C64JOYSTICK_TX_TEST

class C64JoystickTX : public NRFLite, C64JoystickBase {
    private:
        uint8_t _deviceId;
        JoystickPacket _packet;
        
        uint32_t _txCount = 0;
        uint32_t _failedTx = 0;

#ifdef REMOTE_ENCRYPTION_KEY
        //uint8_t _aes_key[32] = REMOTE_ENCRYPTION_KEY;
        uint8_t _payload[ sizeof(JoystickPacket) ];
#endif

    public:
        C64JoystickTX( uint8_t deviceId );
        
        bool begin( bool irq = false, uint8_t irqPin = NRF24_IRQ );
        void loop();
        void sync();
};


#endif /* _C64_JOYSTICK_TX_H_ */
