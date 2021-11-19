#pragma once

#include <stdint.h>

/// <summary>
/// Generates a 32-bit random number.
/// </summary>
/// <returns></returns>
uint32_t KeRand();

/// <summary>
/// Performs a hardware-specific initialisation of the random number generator.
/// </summary>
void KeInitRand();

/// <summary>
/// Seeds the random number generator, combined with a hardware-specific seed.
/// </summary>
/// <param name="seed">The seed.</param>
void KeSeedRand(uint32_t seed);