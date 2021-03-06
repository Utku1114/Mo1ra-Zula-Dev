#pragma once
#include <Windows.h>
#include <inttypes.h>
#include <iostream>
#include <vector>
#include <exception>
#include "NtDefines.h"

using std::exception;

struct KernelContext
{
	HMODULE NtLib;
	uint64_t NtBase;

	template<typename T = fnFreeCall>
	T GetProcAddress(const char* Proc)
	{
		FARPROC LocProc = ::GetProcAddress(this->NtLib, Proc);

		if (!LocProc)
			return (T)(nullptr);

		uint32_t Delta = (uintptr_t)(LocProc)-(uintptr_t)(this->NtLib);

		return (T)(this->NtBase + Delta);
	}
};

static KernelContext* Kr_InitContext()
{
	KernelContext* Kc = new KernelContext;

	std::vector<BYTE> Buffer(1024 * 1024);

	ULONG ReqSize = 0;

	do
	{
		if (!NtQuerySystemInformation(SystemModuleInformation, Buffer.data(), Buffer.size(), &ReqSize))
			break;

		Buffer.resize(ReqSize * 2);
	} while (ReqSize > Buffer.size());

	SYSTEM_MODULE_INFORMATION* ModuleInfo = (SYSTEM_MODULE_INFORMATION*)Buffer.data();

	char* KernelFileName = (char*)ModuleInfo->Module[0].FullPathName + ModuleInfo->Module[0].OffsetToFileName;

	Kc->NtBase = (uint64_t)ModuleInfo->Module[0].ImageBase; //ntkrnlmp.exe
	Kc->NtLib = LoadLibraryA(KernelFileName);                //ntkrnlmp.exe

	if (!Kc->NtBase || !Kc->NtLib)
	{
		delete Kc;
		throw exception("[+] Failed to get kernel module information!\n");
	}

	return Kc;
}

static void Kr_FreeContext(KernelContext* Ctx)
{
	delete Ctx;
}