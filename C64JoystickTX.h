#ifndef _C64_JOYSTICK_TX_H_
#define _C64_JOYSTICK_TX_H_

#include <SPI.h>
#include <NRFLite.h>

#include "NRF24Config.h"
#include "RetroUSBJoystickConfig.h"

#include "C64JoystickBase.h"
#include "C64JoystickPacket.h"


class C64JoystickTX : public NRFLite, C64JoystickBase {
    private:
        uint8_t _deviceId;
        JoystickPacket _packet;
        
    public:
        C64JoystickTX( uint8_t deviceId );
        
        bool begin( bool irq = false, uint8_t irqPin = NRF24_IRQ );
        void loop();
        void sync();
};


#endif /* _C64_JOYSTICK_TX_H_ */
