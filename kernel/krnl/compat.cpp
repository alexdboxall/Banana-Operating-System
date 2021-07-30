#include "krnl/powctrl.hpp"

namespace Krnl
{
	void handlePowerButton()
	{
		KeHandlePowerButton();
	}

	void handleSleepButton()
	{
		KeHandleSleepButton();
	}
}