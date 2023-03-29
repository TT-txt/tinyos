/**
 * @file ata.h
 * @author Théodore MARTIN
 * @brief Headers of the ata driver library
 * @version 0.1
 * @date 2023-03-24
 * https://wiki.osdev.org/ATA_PIO_Mode
 */
#ifndef __ATA__
#define __ATA__
#include "../libs/utils.h"
#include "./ports.h"

#define DRIVE_BUSY 0x80
#define DRIVE_READY 0x40
#define DRIVE_WAITING 0x08
#define DRIVE_ERROR 0X01
#define DRIVE_FAULTY 0X20

/**
 * @brief Reads the drive sectors
 * 
 * @param[in] addr the address that will store the result
 * @param LBA the logical block address
 * @param sectors the number of sectors to read
 * 
 * @return void
 */
void readSectors(u32, u32, u8);

/**
 * @brief Write data to the sectors
 * 
 * @param LBA the LBA target address
 * @param sectors the number of sectors to write
 * @param bytes the localisation of the bytes to write
 * 
 * @return void
 */
void writeSectors(u32, u8, u32*);
#endif