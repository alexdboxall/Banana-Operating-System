#pragma once

#include <stdint.h>

/// <summary>
/// Registers a handler to be called on system shutdown or restart.
/// <param name="ebx">The file number.</param>
/// <param name="ecx">Maximum number of bytes to write.</param>
/// <param name="edx">Pointer to write data to.</param>
/// <returns>The number of bytes read, or -1 on failure.</returns>
/// </summary>

/// <summary>
/// Initialises the symlink subsystem.
/// </summary>
void KeInitialiseSymlinks();

/// <summary>
/// Adds a symlink entry to the registrar.
/// <param name="linkName">The symlink filepath.</param>
/// <param name="linkID">The symlink ID.</param>
/// </summary>
void KeRegisterSymlink(const char* linkName, uint64_t linkID);

/// <summary>
/// Checks if a filepath is a symlink and dereferences them if so.
/// <param name="linkName">The symlink filepath.</param>
/// <param name="dereferenced">A pointer to an output buffer.</param>
/// <returns>Returns 0 on if no symlinks were dereferenced, 1 if there was a dereference, and negative on error.</returns>
/// </summary>
int KeDereferenceSymlink(const char* linkName, char* dereferenced);

/// <summary>
/// Checks if a filepath is a symlink.
/// <param name="linkName">The symlink filepath.</param>
/// <returns>Returns true if it is a symlink.</returns>
/// </summary>
bool KeVerifySymlink(const char* linkName);

/// <summary>
/// Creates a symbolic link. WARNING: if relative or non-normalised paths are used
/// the system may become unstable.
/// <param name="existing">The absolute, normalised target filepath.</param>
/// <param name="linkName">The absolute, normalised symlink filepath.</param>
/// <returns>Returns 0 on success, and non-zero on error.</returns>
/// </summary>
int KeCreateSymlink(const char* existing, const char* linkName);