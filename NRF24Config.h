#ifndef _NRF24_CONFIG_H_
#define _NRF24_CONFIG_H_

/**
 * Configuration
 */
//#define NRF24_SUPPORT_IRQ

/**
 * PIN assignments.
 */
#ifndef NRF24_CE
#define NRF24_CE    10
#endif

#ifndef NRF24_IRQ
#define NRF24_IRQ    7
#endif

#ifndef NRF24_SS
#define NRF24_SS    A0
#endif


/* NOTE: MISO, MOSI and CLK are board dependant -- they 
 * are hardware pins.
 */
#define NRF24_MISO  14
#define NRF24_MOSI  16
#define NRF24_CLK   15


/* Radio config -- the bitrate and channels must be
 * the same for devices that need to talk to each 
 * other.
 */
#ifndef NRF24_BITRATE
#define NRF24_BITRATE  NRFLite::BITRATE2MBPS
#endif

#ifndef NRF24_CHANNEL
#define NRF24_CHANNEL  70
#endif

struct JoystickPacket
{
    uint8_t  radio;
    uint32_t seq;
    
    uint8_t  buttonState;
};

#endif /* _NRF24_CONFIG_H_ */
