#pragma once

#include <stdint.h>

/// <summary>
/// Calculates the CRC32 checksum for a given buffer.
/// </summary>
/// <param name="data">A pointer to the data to checksum.</param>
/// <param name="length">The length of the data.</param>
/// <returns>The CRC32 checksum.</returns>
uint32_t KeCalculateCRC32(uint8_t* data, int length);