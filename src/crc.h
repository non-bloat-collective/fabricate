#ifndef FAB_CRC_H
#define FAB_CRC_H

#include <stdint.h>
#include <stddef.h>

uint32_t Crc32(const char*, size_t);
uint32_t CaseCrc32(const char*, size_t);
uint32_t ContCrc32(uint32_t, const char*, size_t);
uint32_t ContCaseCrc32(uint32_t, const char*, size_t);

#endif
