#include "util.h"


NTSTATUS Real_Entry(PDRIVER_OBJECT driver_object, PUNICODE_STRING registry_path) {
	NTSTATUS status = STATUS_SUCCESS;
	UNREFERENCED_PARAMETER(registry_path);
	UNICODE_STRING Device_Name = {};
	RtlInitUnicodeString(&Device_Name, L"\\Device\\Akkiro");

	PDEVICE_OBJECT Device_Obj = nullptr;
	print("[Akkiro] [*] Creating Driver Device.\n");
	status = IoCreateDevice(driver_object, 0, &Device_Name, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &Device_Obj);

	if (status != STATUS_SUCCESS) {
		print("[Akkiro] [-] Failed to create Device.\n");
		return status;
	}

	print("[Akkiro] [*] Driver Device created.\n");

	UNICODE_STRING symbolic_link = {};
	RtlInitUnicodeString(&symbolic_link, L"\\DosDevices\\Akkiro");
	status = IoCreateSymbolicLink(&symbolic_link, &Device_Name);

	if (status != STATUS_SUCCESS) {
		print("[Akkiro] [-] Failed to establish symbolic link.\n");
		return status;
	}
	print("[Akkiro] [*] Established symbolic link.\n");

	SetFlag(Device_Obj->Flags, DO_BUFFERED_IO);

	driver_object->MajorFunction[IRP_MJ_CREATE] = driver::create;
	driver_object->MajorFunction[IRP_MJ_CLOSE] = driver::close;
	driver_object->MajorFunction[IRP_MJ_DEVICE_CONTROL] = driver::device_control;

	ClearFlag(Device_Obj->Flags, DO_DEVICE_INITIALIZING);

	print("[Akkiro] [*] Setup complete.\n");
	return status;
}


NTSTATUS DriverEntry() {
	print("[Akkiro] [*] Starting Entry.\n");

	UNICODE_STRING driver_name = {};
	RtlInitUnicodeString(&driver_name, L"\\Driver\\Akkiro");
	return IoCreateDriver(&driver_name, &Real_Entry);
}