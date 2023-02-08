#include"head.h"

NTSTATUS Exit(DRIVER_OBJECT* DriverObject) {
	UNICODE_STRING symbolLinkName;
	DbgPrint("DriverUnload\n");
	if (DriverObject->DeviceObject)
		IoDeleteDevice(DriverObject->DeviceObject);
	RtlInitUnicodeString(&symbolLinkName, my_link_name);
	IoDeleteSymbolicLink(&symbolLinkName);
	return STATUS_SUCCESS;
}

NTSTATUS DriverEntry(DRIVER_OBJECT* DriverObject, UNICODE_STRING* STR) {
	DriverObject->DriverUnload = Exit;
	NTSTATUS status = STATUS_SUCCESS;
	status = Create_Device(DriverObject);
	Apc_Init();
	if (!NT_SUCCESS(status))
	{
		DbgPrint("Create Device Error.\n");
		goto Exit;
	}

	return status;
	
Exit://Unload Driver
	return Exit(DriverObject);
}