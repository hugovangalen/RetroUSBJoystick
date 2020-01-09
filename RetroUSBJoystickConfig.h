#ifndef _RETROUSBJOYSTICK_CONFIG_H_
#define _RETROUSBJOYSTICK_CONFIG_H_

#define ERROR_LED       13

/***
 * Wireless operation requires 2 Arduino boards (tested
 * with Arduino Pro Micro clones) and 2 NRF24 modules connected
 * to each.
 * 
 * Two different sketches need to be uploaded to them:
 * - For the client you need to enable REMOTE_CLIENT and upload 
 *   that to the board that has the joystick physically connected.
 * 
 * - For the server, enable REMOTE_SERVER for the receiving part 
 *   that actually connects to the PC via USB.
 * 
 * Wired operation requires a single Arduino Pro Micro (or clone),
 * and no NRF24 modules. Enable LOCAL_CLIENT and upload sketch.
 */


/** 
 * Define `LOCAL_CLIENT` if no wireless is required, or if you 
 * want to debug joystick connections.
 */
#define LOCAL_CLIENT


/** 
 * `REMOTE_CLIENT` if this is the SENDER of wireless data, this
 * also sets the clientId for the radio transmissions.
 * 
 * 1: Joystick in port 1,
 * 2: Joystick in port 2.
 */
//#define REMOTE_CLIENT       1


/** 
 * `REMOTE_SERVER` if this is the RECEIVER of wireless data. 
 */
//#define REMOTE_SERVER


/**
 * This only applies to REMOTE_CLIENT and REMOTE_SERVER, it
 * defines the radio ID of the server.
 */
#define REMOTE_SERVER_ID    64


/**
 * Future stuff to support more than 1 joystick...
 */
#define REMOTE_PORT1_ID      1
#define REMOTE_PORT2_ID      2

#endif /*_RETROUSBJOYSTICK_CONFIG_H_*/
