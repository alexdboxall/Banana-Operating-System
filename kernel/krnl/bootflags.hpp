
#ifndef _BOOT_SETTINGS_HPP
#define _BOOT_SETTINGS_HPP

/*
Various configuration flags which are used to set the behaviour of the kernel. These can
be used to read, but not write these settings.
*/
enum class BootConfigurationFlag
{
	// each flag asks as a mask for a certain bit in keBootSettings
	// all other bits are reserved

	DisableAPIC							= 1,
	EnableSafeMode						= 2,
	AssumePS2KeyboardTranslationWorks	= 4,
	
	OptimiseForOldComputers				= 16,
	EnableCPUFeatures					= 32,

	DontNeedKeypressForDebugMessages	= 128,

	DisableAPICAndACPI					= 1024,
	ShowDebugAndMonochrome				= 2048,

	EnableFloppyDriver					= 8192,

	EnableRemoteSetup					= 32768,

};


void KeInitialiseBootConfigurationFlags();
bool KeGetBootConfigurationFlag(BootConfigurationFlag flag);

#endif
