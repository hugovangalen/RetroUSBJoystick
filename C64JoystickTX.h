#ifndef _C64_JOYSTICK_TX_H_
#define _C64_JOYSTICK_TX_H_

#include <SPI.h>
#include <NRFLite.h>

#include "C64JoystickBase.h"
#include "NRF24Config.h"

class C64JoystickTX : public NRFLite, C64JoystickBase {
    private:
        uint8_t _deviceId;

    public:
        C64JoystickTX( uint8_t deviceId, uint8_t up,  uint8_t down, uint8_t left, uint8_t right, uint8_t fire );
        bool begin( bool irq = false, uint8_t irqPin = NRF24_IRQ );
};


#endif /* _C64_JOYSTICK_TX_H_ */
