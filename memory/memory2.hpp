#include <Windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <vector>

#pragma once

class Memory {
public:
	std::wstring processName;
	Memory(std::wstring x);
	DWORD pid;
	HANDLE pHandle;
	uintptr_t getModuleBaseAddress(std::wstring moduleName);
	template <typename T> 
	T Read(uintptr_t Address) {
		T buffer;
		ReadProcessMemory(pHandle, (LPCVOID)Address, &buffer, sizeof(T), NULL);
		return buffer;
	}
	template <typename T>
	bool Write(uintptr_t Address, T value) {
		return WriteProcessMemory(pHandle, (LPVOID)Address, &value, sizeof(value), NULL);
	}
	bool ReadWIN(uintptr_t Address, LPVOID buffer, size_t size) {
		return ReadProcessMemory(pHandle, (LPCVOID)Address, buffer, size, NULL);
	}
	uintptr_t ReadChain(uintptr_t Address, std::vector<uintptr_t> offsets) {
		for (auto i : offsets) {
			Address = Read<uintptr_t>(Address);
			Address += i;
		}
		return Address;
	}
private:
	DWORD getPid(std::wstring ProcessName);
};
