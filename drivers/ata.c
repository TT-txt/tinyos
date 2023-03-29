/**
 * @file ata.c
 * @author Théodore MARTIN
 * @brief ATA Drivers library
 * @version 0.1
 * @date 2023-03-24
 */
#include "ata.h"

/**
 * @brief waits until the bit stating the drive is busy is clear
 * 
 * @return void
 */
static void waitUntilDriveNotBusy()
{
    while (portByteIn(0x1F7) & DRIVE_BUSY);
}

/**
 * @brief waits until the bit stating the drive is faulty is clear
 * 
 * @return void
 */
static void waitUntilDriveNotFaulty()
{
    while (portByteIn(0x1F5) & DRIVE_FAULTY);
}

//Needs testing
void readSectors(u32 addr, u32 LBA, u8 sectors)
{
    waitUntilDriveNotBusy();
    /* standard procedure - described in https://wiki.osdev.org/ATA_PIO_Mode */
    /* setting up the registers */
	portByteOut(0x1F6,0xE0 | ((LBA >>24) & 0xF));
	portByteOut(0x1F2,sectors);
	portByteOut(0x1F3, (u8) LBA);
	portByteOut(0x1F4, (u8)(LBA >> 8));
	portByteOut(0x1F5, (u8)(LBA >> 16));
    /* sending the read command */
	portByteOut(0x1F7,0x20);
    u16 *castedAddr = (u16 *)addr;
    /* retrieving the data */
    u16 *maxAddr = (u16 *)addr + 256 * sectors;
    for (; castedAddr < maxAddr; castedAddr += 256){
        waitUntilDriveNotBusy();
        waitUntilDriveNotFaulty();
        for (u8 j = 0; j != 255; ++j) {
            *(castedAddr + j) = portWordIn(0x1F0);
        }
    }
}

void writeSectors(u32 LBA, u8 sectors, u32 *bytes)
{
    waitUntilDriveNotBusy();
    /* standard procedure - described in https://wiki.osdev.org/ATA_PIO_Mode */
    /* setting up the registers */
    portByteOut(0x1F6,0xE0 | ((LBA >>24) & 0xF));
	portByteOut(0x1F2,sectors);
	portByteOut(0x1F3, (u8) LBA);
	portByteOut(0x1F4, (u8)(LBA >> 8));
	portByteOut(0x1F5, (u8)(LBA >> 16));
    /* sending the write command */
	portByteOut(0x1F7,0x30);
    for (u8 i = 0; i < sectors; ++i) {
        waitUntilDriveNotBusy();
        waitUntilDriveNotFaulty();
        for (u8 j = 0; j != 255; ++j) {
            portWordOut(0x1F0, *(bytes + j));
        }   
    }
}