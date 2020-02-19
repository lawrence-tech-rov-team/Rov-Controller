// Microchip ENC28J60 Ethernet Interface Driver
// Author: Pascal Stang
// Modified by: Guido Socher
// Copyright: GPL V2
//
// This driver provides initialization and transmit/receive
// functions for the Microchip ENC28J60 10Mb Ethernet Controller and PHY.
// This chip is novel in that it is a full MAC+PHY interface all in a 28-pin
// chip, using an SPI interface to the host processor.
//
// 2010-05-20 <jc@wippler.nl>
/** @file */

#ifndef ENC28J60_H
#define ENC28J60_H

// buffer boundaries applied to internal 8K ram
// the entire available packet buffer space is allocated

#define RXSTART_INIT        0x0000  // start of RX buffer, (must be zero, Rev. B4 Errata point 5)
#define RXSTOP_INIT         0x0BFF  // end of RX buffer, room for 2 packets

#define TXSTART_INIT        0x0C00  // start of TX buffer, room for 1 packet
#define TXSTOP_INIT         0x11FF  // end of TX buffer

#define SCRATCH_START       0x1200  // start of scratch area
#define SCRATCH_LIMIT       0x2000  // past end of area, i.e. 3 Kb
#define SCRATCH_PAGE_SHIFT  6       // addressing is in pages of 64 bytes
#define SCRATCH_PAGE_SIZE   (1 << SCRATCH_PAGE_SHIFT)
#define SCRATCH_PAGE_NUM    ((SCRATCH_LIMIT-SCRATCH_START) >> SCRATCH_PAGE_SHIFT)
#define SCRATCH_MAP_SIZE    (((SCRATCH_PAGE_NUM % 8) == 0) ? (SCRATCH_PAGE_NUM / 8) : (SCRATCH_PAGE_NUM/8+1))

// area in the enc memory that can be used via enc_malloc; by default 0 bytes; decrease SCRATCH_LIMIT in order
// to use this functionality
#define ENC_HEAP_START      SCRATCH_LIMIT
#define ENC_HEAP_END        0x2000

#include "../PinDefinitions.h"

/** This class provide low-level interfacing with the ENC28J60 network interface. This is used by the EtherCard class and not intended for use by (normal) end users. */
class ENC28J60 {
public:
    static uint8_t buffer[]; //!< Data buffer (shared by receive and transmit)
    static uint16_t bufferSize; //!< Size of data buffer
	
    /**   @brief  Initialise SPI interface
    *     @note   Configures Arduino pins as input / output, etc.
    */
    static void initSPI ();

    /**   @brief  Initialise network interface
    *     @param  size Size of data buffer
    *     @param  macaddr Pointer to 6 byte hardware (MAC) address
    *     @param  csPin Arduino pin used for chip select (enable network interface SPI bus). Default = 8
    *     @return <i>uint8_t</i> ENC28J60 firmware version or zero on failure.
    */
    static uint8_t initialize (const uint16_t size, const uint8_t* macaddr,
                               Register& csDDR, Register& csPort, uint8_t csPin = 8);

    /**   @brief  Check if network link is connected
    *     @return <i>bool</i> True if link is up
    */
    static bool isLinkUp (); //Required, packerLoop

    /**   @brief  Sends data to network interface
    *     @param  len Size of data to send
    *     @note   Data buffer is shared by receive and transmit functions
    */
    static void packetSend (uint16_t len);

    /**   @brief  Copy received packets to data buffer
    *     @return <i>uint16_t</i> Size of received data
    *     @note   Data buffer is shared by receive and transmit functions
    */
    static uint16_t packetReceive ();

};

typedef ENC28J60 Ethernet; //!< Define alias Ethernet for ENC28J60

#endif
