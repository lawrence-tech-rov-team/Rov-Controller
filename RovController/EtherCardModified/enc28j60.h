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
    static bool broadcast_enabled; //!< True if broadcasts enabled (used to allow temporary disable of broadcast for DHCP or other internal functions)
    static bool promiscuous_enabled; //!< True if promiscuous mode enabled (used to allow temporary disable of promiscuous mode)

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
    static bool isLinkUp ();

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

    /**   @brief  Copy data from ENC28J60 memory
    *     @param  page Data page of memory
    *     @param  data Pointer to buffer to copy data to
    */
    static void copyout (uint8_t page, const uint8_t* data);

    /**   @brief  Copy data to ENC28J60 memory
    *     @param  page Data page of memory
    *     @param  data Pointer to buffer to copy data from
    */
    static void copyin (uint8_t page, uint8_t* data);

    /**   @brief  Get single byte of data from ENC28J60 memory
    *     @param  page Data page of memory
    *     @param  off Offset of data within page
    *     @return Data value
    */
    static uint8_t peekin (uint8_t page, uint8_t off);

    /** @brief  reserves a block of RAM in the memory of the enc chip
     *  @param  size number of bytes to reserve
     *  @return <i>uint16_t</i> start address of the block within the enc memory. 0 if the remaining memory for malloc operation is less than size.
     *  @note  There is no enc_free(), i.e., reserved blocks stay reserved for the duration of the program.
     *  @note  The total memory available for malloc-operations is determined by ENC_HEAP_END-ENC_HEAP_START, defined in enc28j60.h; by default this is 0, i.e., you have to change these values in order to use enc_malloc().
     */
    static uint16_t enc_malloc(uint16_t size);

};

typedef ENC28J60 Ethernet; //!< Define alias Ethernet for ENC28J60


/** Workaround for Errata 13.
*   The transmission hardware may drop some packets because it thinks a late collision
*   occurred (which should never happen if all cable length etc. are ok). If setting
*   this to 1 these packages will be retried a fixed number of times. Costs about 150bytes
*   of flash.
*/
#define ETHERCARD_RETRY_LATECOLLISIONS 0

/** Enable pipelining of packet transmissions.
*   If enabled the packetSend function will not block/wait until the packet is actually
*   transmitted; but instead this wait is shifted to the next time that packetSend is
*   called. This gives higher performance; however in combination with
*   ETHERCARD_RETRY_LATECOLLISIONS this may lead to problems because a packet whose
*   transmission fails because the ENC-chip thinks that it is a late collision will
*   not be retried until the next call to packetSend.
*/
#define ETHERCARD_SEND_PIPELINING 0
#endif
