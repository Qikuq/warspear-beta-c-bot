#include "memory2.hpp"

DWORD Memory::getPid(std::wstring processName) {
	DWORD pid = 0;
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32W process;
	ZeroMemory(&process, sizeof(process));
	process.dwSize = sizeof(process);
	if (Process32FirstW(snapshot, &process)) {
		do {
			if (std::wstring(process.szExeFile) == processName) {
				pid = process.th32ProcessID;
				break;
			}
		} while (Process32NextW(snapshot, &process));
	}
	CloseHandle(snapshot);
	return pid;
}

Memory::Memory(std::wstring x) {
	processName = x;
	pid = getPid(processName);
	pHandle = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
}

uintptr_t Memory::getModuleBaseAddress(std::wstring moduleName) {
	uintptr_t modulebaseAddress = 0;
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid);
	MODULEENTRY32W module;
	ZeroMemory(&module, sizeof(module));
	module.dwSize = sizeof(module);
	if (Module32FirstW(snapshot, &module)) {
		do {
			if (_wcsicmp(module.szModule, moduleName.c_str()) == 0) {
				modulebaseAddress = (uintptr_t)module.modBaseAddr;
				break;
			}
		} while (Module32NextW(snapshot, &module));
	}
	CloseHandle(snapshot);
	return modulebaseAddress;
}

/*
Usage: 
int main() {
	Memory m(L"targetProcess.exe");

	uintptr_t baseAddress = m.getModuleBaseAddress(L"targetModule.exe");

	int health = m.Read<int>(baseAddress + offsets::health);

	m.Write(baseAddress + offsets::health, 9999);

	return 0;
}
*/ 