/**
 * Project: RetroUSBJoystick
 * File: NRF24Config.h
 * Purpose: NRF24 related compile-time configuration for the RetroUSBJoystick. 
 * 
 * This is only relevant for the wireless-client and wireless-server.
 * 
 * Copyright: Hugo van Galen, 2020
 */
#ifndef _NRF24_CONFIG_H_
#define _NRF24_CONFIG_H_

/**
 * IRQ is not used at this point.
 */
//#define NRF24_SUPPORT_IRQ


/**
 * PIN assignments.
 */
#ifndef NRF24_CE
#define NRF24_CE    A1
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
#define NRF24_CHANNEL  58
#endif

#endif /* _NRF24_CONFIG_H_ */
