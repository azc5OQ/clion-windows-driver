#include <ntddk.h>

PDEVICE_OBJECT pDeviceObject;
UNICODE_STRING dev, dos;

VOID UnloadDriver(PDRIVER_OBJECT pDriverObject)
{
	UNREFERENCED_PARAMETER(pDriverObject);
	DbgPrint("%s", "Goodbye from this Kernel Driver \n");
	IoDeleteSymbolicLink(&dos);
	IoDeleteDevice(pDriverObject->DeviceObject);
}

NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObject, PUNICODE_STRING pRegistryPath)
{
	UNREFERENCED_PARAMETER(pRegistryPath);

	pDriverObject->DriverUnload = UnloadDriver; //remove this line if you want to use kdmapper, otherwise it will crash the system and following lines too

	DbgPrint("%s", "Welcome to this Kernel Driver \n");

	RtlInitUnicodeString(&dev, L"\\Device\\RWDriver");
	RtlInitUnicodeString(&dos, L"\\DosDevices\\RWDriver");

	IoCreateDevice(pDriverObject, 0, &dev, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &pDeviceObject);
	IoCreateSymbolicLink(&dos, &dev);

	pDeviceObject->Flags |= DO_DIRECT_IO;
	pDeviceObject->Flags &= ~DO_DEVICE_INITIALIZING;

	return STATUS_SUCCESS;
}
