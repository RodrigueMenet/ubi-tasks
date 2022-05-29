#include <cstdint>

/// @brief CRC32 checksum.
/// @details This CRC32 implementation uses the reverse polynomial `0xEDB88320`.
/// @param crc CRC32 seed value.
/// @param buf Input buffer.
/// @param size Size in bytes of `buf`.
uint32_t crc32(uint32_t crc, const void *buf, size_t size);