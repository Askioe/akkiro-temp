#include "ntifs.h"

extern "C" {
	NTKERNELAPI NTSTATUS IoCreateDriver(PUNICODE_STRING DriverName,
		PDRIVER_INITIALIZE IntializationFunction);

	NTKERNELAPI NTSTATUS MmCopyVirtualMemory(PEPROCESS SourceProcess,
		PVOID SourceAddress, PEPROCESS TargetProcess, PVOID TargetAddress,
		SIZE_T BufferSize, KPROCESSOR_MODE PreviousMode,
		PSIZE_T ReturnSize);
}

void print(PCSTR text) {
#ifndef DEBUG
	UNREFERENCED_PARAMETER(text);
#endif
	KdPrintEx((DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, text));
}

namespace driver {
	namespace codes {
		constexpr ULONG attach = CTL_CODE(FILE_DEVICE_UNKNOWN, 0x696, METHOD_BUFFERED, FILE_SPECIAL_ACCESS);
		constexpr ULONG read = CTL_CODE(FILE_DEVICE_UNKNOWN, 0x697, METHOD_BUFFERED, FILE_SPECIAL_ACCESS);
		constexpr ULONG write = CTL_CODE(FILE_DEVICE_UNKNOWN, 0x698, METHOD_BUFFERED, FILE_SPECIAL_ACCESS);
	}

	struct Request {
		HANDLE process_id;
		PVOID target, buffer;
		SIZE_T size, return_size;
	};

	NTSTATUS create(PDEVICE_OBJECT dev_obj, PIRP irp) {
		UNREFERENCED_PARAMETER(dev_obj);
		IoCompleteRequest(irp, IO_NO_INCREMENT);

		return irp->IoStatus.Status;
	}

	NTSTATUS close(PDEVICE_OBJECT dev_obj, PIRP irp) {
		UNREFERENCED_PARAMETER(dev_obj);
		IoCompleteRequest(irp, IO_NO_INCREMENT);

		return irp->IoStatus.Status;
	}

	NTSTATUS device_control(PDEVICE_OBJECT dev_obj, PIRP irp) {
		UNREFERENCED_PARAMETER(dev_obj);

		print("[Akkiro] [*] Device control called.\n");

		NTSTATUS status = STATUS_UNSUCCESSFUL;

		PIO_STACK_LOCATION stack_irp = IoGetCurrentIrpStackLocation(irp);

		auto request = reinterpret_cast<Request*>(irp->AssociatedIrp.SystemBuffer);

		if (stack_irp == nullptr || request == nullptr) {
			IoCompleteRequest(irp, IO_NO_INCREMENT);
			return status;
		}

		static PEPROCESS target_process = nullptr;
		
		const ULONG control_code = stack_irp->Parameters.DeviceIoControl.IoControlCode;
		switch (control_code){
			case codes::attach:
				status = PsLookupProcessByProcessId(request->process_id, &target_process);
				break;

			case codes::read:
				if (target_process != nullptr) {
					__try{
						status = MmCopyVirtualMemory(target_process, request->target,
						PsGetCurrentProcess(), request->buffer, request->size,
						KernelMode, &request->return_size);
						if (!NT_SUCCESS(status)) {
							return STATUS_ACCESS_DENIED;
						}
					}

					__except (EXCEPTION_EXECUTE_HANDLER) {
						return STATUS_ACCESS_DENIED;
						break;
					}
				}
				break;

			case codes::write:
				if (target_process != nullptr) {
					__try {
						status = MmCopyVirtualMemory(PsGetCurrentProcess(), request->buffer,
							target_process, request->target, request->size,
							KernelMode, &request->return_size);
					}
					__except (EXCEPTION_EXECUTE_HANDLER) {
						return STATUS_ACCESS_DENIED;
						break;
					}
				}
				break;

			default:
				break;
		}
		irp->IoStatus.Status = status;
		irp->IoStatus.Information = sizeof(Request);

		IoCompleteRequest(irp, IO_NO_INCREMENT);
		return status;
	}
}