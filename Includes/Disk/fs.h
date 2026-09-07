#ifndef FS_H
#define FS_H

#include <stdint.h>
#include "disk_state.h"

#define READ_BLOCKS 8
#define BLOCK_SIZE  512

// superblock
// 1 block - 512 bytes
typedef struct {
    uint8_t  signature[2];
    uint32_t total_blocks;
    uint32_t block_size;
    uint32_t file_count;
    uint32_t inode_table_start;
    uint32_t data_start;
} __attribute__((packed)) superblock;

typedef struct {
    uint8_t  name[255];
    uint32_t size;
    uint32_t block;
    uint32_t blocks;
    uint8_t  rights;
} __attribute__((packed)) inode;

static superblock Superblock;

static void vnfs_make_superblock()
{
    Superblock.signature[0]      = 'V';
    Superblock.signature[1]      = 'N';
    Superblock.total_blocks      = DiskState.total_sectors / READ_BLOCKS;
    Superblock.block_size        = BLOCK_SIZE * READ_BLOCKS;
    Superblock.file_count        = 0;
    Superblock.inode_table_start = 1;
    Superblock.data_start        = 2;
    // block[0] - Superblock
    // block[1] - Inode
    // block[2-max] - Data
}

#endif