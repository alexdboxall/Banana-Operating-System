#include <stdint.h>

#include "main.hpp"

#include "core/common.hpp"
#include "core/virtmgr.hpp"
#include "core/physmgr.hpp"
#include "hw/acpi.hpp"
#include "hw/cpu.hpp"
#include "hw/ports.hpp"
#include "hw/bus/pci.hpp"

void begin(void* __acpi__);
void start(void* __acpi__)
{
	begin(__acpi__);
}





extern "C" void strcmpDebug(void* a, void* b, int c)
{
	kprintf("STRCMP %c: 0x%X 0x%X\n", c + 'A', a, b);
}

void begin(void* __acpi__)
{
	ACPI* acpi = (ACPI*) __acpi__;

	kprintf("TODO: Check ACPI version.");

	/*kprintf("%s\n", testC);
	kprintf("%s\n", testA);
	kprintf("%s\n", testD);
	kprintf("%s\n", testB);

	kprintf("Name is at 0x%X. %s\n", AcpiGbl_PreDefinedNames[0].Name, AcpiGbl_PreDefinedNames[0].Name);
	*/
	acpi->acpi2 = true;
	kprintf("we got to %d\n", __LINE__ +353 - 418);

	ACPI_STATUS a = AcpiInitializeSubsystem();
	kprintf("we got to %d\n", __LINE__ +353 - 418);

	a = AcpiInitializeTables(nullptr, 16, true);
	if (ACPI_FAILURE(a)) panic("FAILURE AcpiInitializeTables");
	kprintf("we got to %d\n", __LINE__ +353 - 418);

	a = AcpiInstallAddressSpaceHandler(ACPI_ROOT_OBJECT,
										ACPI_ADR_SPACE_SYSTEM_MEMORY, ACPI_DEFAULT_HANDLER, NULL, NULL);
	if (ACPI_FAILURE(a)) panic("FAILURE AcpiInstallAddressSpaceHandler ACPI_ADR_SPACE_SYSTEM_MEMORY");
	kprintf("we got to %d\n", __LINE__ +353 - 418);

	a = AcpiInstallAddressSpaceHandler(ACPI_ROOT_OBJECT,
										ACPI_ADR_SPACE_SYSTEM_IO, ACPI_DEFAULT_HANDLER, NULL, NULL);
	if (ACPI_FAILURE(a)) panic("FAILURE AcpiInstallAddressSpaceHandler ACPI_ADR_SPACE_SYSTEM_IO");
	kprintf("we got to %d\n", __LINE__ +353 - 418);

	a = AcpiInstallAddressSpaceHandler(ACPI_ROOT_OBJECT,
										ACPI_ADR_SPACE_PCI_CONFIG, ACPI_DEFAULT_HANDLER, NULL, NULL);
	if (ACPI_FAILURE(a)) panic("FAILURE AcpiInstallAddressSpaceHandler ACPI_ADR_SPACE_PCI_CONFIG");
	kprintf("we got to %d\n", __LINE__ +353 - 418);

	a = AcpiLoadTables();
	if (ACPI_FAILURE(a)) panic("FAILURE AcpiLoadTables");
	kprintf("we got to %d\n", __LINE__ +353 - 418);

	a = AcpiEnableSubsystem(ACPI_FULL_INITIALIZATION);
	if (ACPI_FAILURE(a)) panic("FAILURE AcpiEnableSubsystem");
	kprintf("we got to %d\n", __LINE__ +353 - 418);

	a = AcpiInitializeObjects(ACPI_FULL_INITIALIZATION);
	if (ACPI_FAILURE(a)) panic("FAILURE AcpiInitializeObjects");
	kprintf("we got to %d\n", __LINE__ +353 - 418);

	installHandlers();
	kprintf("we got to %d\n", __LINE__ +353 - 418);

	ACPI_STATUS status;
	if (computer->features.hasAPIC) {
		ACPI_OBJECT_LIST params;
		ACPI_OBJECT arg[1];

		params.Count = 1;
		params.Pointer = arg;

		arg[0].Type = ACPI_TYPE_INTEGER;
		arg[0].Integer.Value = thisCPU()->intCtrl->getName()[0] == 'A';

		status = AcpiEvaluateObject(NULL, (ACPI_STRING) "\\_PIC", &params, NULL);
		if (ACPI_FAILURE(status) && status != AE_NOT_FOUND) {
			kprintf("status = 0x%X\n", status);
			panic("ACPI failure AcpiEvaluateObject(_PIC)");
		}
	}


	AcpiWriteBitRegister(ACPI_BITREG_SCI_ENABLE, 1);

	a = AcpiInstallGlobalEventHandler(acpiGlobalEventHandler, nullptr);
	if (a != AE_OK) panic("FAILURE AcpiInstallGlobalEventHandler");

	a = AcpiEnableEvent(ACPI_EVENT_SLEEP_BUTTON, 0);
	a = AcpiEnableEvent(ACPI_EVENT_POWER_BUTTON, 0);

	void* ret;
	status = AcpiGetDevices(nullptr, (ACPI_WALK_CALLBACK) acpiWalkCallback, (void*) acpi, &ret);
	if (ACPI_FAILURE(status)) {
		panic("NAMESPACE COULD NOT BE WALKED FOR PCI DEVICES");
	}

	void* retVal;
	status = AcpiWalkNamespace(ACPI_TYPE_ANY, ACPI_ROOT_OBJECT, 8, (ACPI_WALK_CALLBACK) acpiWalkDescendingCallback, (ACPI_WALK_CALLBACK) acpiWalkAscendingCallback, (void*) acpi, &retVal);
}