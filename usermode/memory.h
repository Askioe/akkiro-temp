#include "Windows.h"
#include "util.h"
#include <TlHelp32.h>
#include <cstdint>
#include <string>
#include "xor.h"
#include "offsets.h"
#include "Vectors.h"

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

class CMemory {
public:
    DWORD process = 0;
    uintptr_t client = 0;
    HANDLE driver_handle = 0;

    bool CreateDriverHandle() {
        driver_handle = CreateFile(L"\\\\.\\Akkiro", GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

        if (driver_handle == INVALID_HANDLE_VALUE) {
            return false;
        }
        else
            return true;
    }


    CMemory() {
        bool status = false;

        status = CreateDriverHandle();
        if (status) {
            Logger("[Akkiro] [+] Created Driver Handle");
        }
        else {
            Logger("[Akkiro] [-] Failed to get Driver Handle.");
        }

        status = get_process(XOR(L"cs2.exe"));
        if (status) {
            Logger(XOR("[Akkiro] [+] Found cs2."));
        }
        else {
            Logger(XOR("[Akkiro] [-] Failed to find cs2."));
        }

        status = get_module_address(XOR(L"client.dll"));

        if (status) {
            Logger(XOR("[Akkiro] [+] Client found."));
        }
        else {
            Logger(XOR("[Akkiro] [-] Failed to find Client."));
        }

        status = attach_to_process(process);
        if (status) {
            Logger("[Akkiro] [+] Attached to cs2.");
        }
        else {
            Logger("[Akkiro] [-] Failed to attach.");
        }

    }

    bool get_process(const wchar_t* name) {
        DWORD process_id = 0;

        HANDLE snap_shot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
        if (snap_shot == INVALID_HANDLE_VALUE)
        {
            return false;
        }

        PROCESSENTRY32W entry = {};
        entry.dwSize = sizeof(decltype(entry));

        if (Process32First(snap_shot, &entry) == TRUE) {
            if (_wcsicmp(name, entry.szExeFile) == 0) {
                process_id = entry.th32ProcessID;
            }
            else {
                while (Process32NextW(snap_shot, &entry) == TRUE) {
                    if (_wcsicmp(name, entry.szExeFile) == 0) {
                        process_id = entry.th32ProcessID;
                    }
                }
            }
        }
        CloseHandle(snap_shot);
        process = process_id;
        if (process == 0) {
            return false;
        }
        else
            return true;
    }



    bool get_module_address(const wchar_t* name) {
        std::uintptr_t module_base = 0;

        HANDLE snap_shot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, process);
        if (snap_shot == INVALID_HANDLE_VALUE)
        {
            return false;
        }

        MODULEENTRY32W entry = {};
        entry.dwSize = sizeof(decltype(entry));

        if (Module32FirstW(snap_shot, &entry) == TRUE) {
            if (wcsstr(name, entry.szModule) != nullptr) {
                module_base = reinterpret_cast<uintptr_t>(entry.modBaseAddr);
            }
            else {
                while (Module32NextW(snap_shot, &entry) == TRUE) {
                    if (wcsstr(name, entry.szModule) != nullptr) {
                        module_base = reinterpret_cast<uintptr_t>(entry.modBaseAddr);
                    }
                }
            }
        }
        CloseHandle(snap_shot);
        client = module_base;
        if (client == 0) {
            return false;
        }
        else
            return true;
    }

    bool attach_to_process(const DWORD pid) {
        return true;
    }

    template <class T>
    T read_memory(const uintptr_t addr) {
        T temp = {};

        Request r;
        r.target = reinterpret_cast<PVOID>(addr);
        r.buffer = &temp;
        r.size = sizeof(T);

        DeviceIoControl(driver_handle, codes::read, &r, sizeof(r), &r, sizeof(r), nullptr, nullptr);

        return temp;
    }

    template <class T>
    void write_memory(const uintptr_t addr, const T& value) {

    }
};