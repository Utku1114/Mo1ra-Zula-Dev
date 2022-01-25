#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <Process.h>
#include <iostream>
#include <math.h>
#include <map>
#include <TlHelp32.h>
#include <vector>
#include <thread>
#include <chrono>
#include <Userenv.h>
#include <array>
#include <fstream>
#include <NetCon.h>
#include <strsafe.h>
#include <random>
#include <tchar.h>
#include <string.h>
#include <wchar.h>
#pragma comment(lib,"Userenv")
#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")
#include <Psapi.h>
#pragma comment(lib,"psapi")
#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include "Enc.h"
//#include "Structs.h"

#include "cqweqasvfa.h"
#include "cqweqasvfa_impl_dx9.h"

//void loop_esp();
//
//struct Entity
//{
//	int id;
//	std::string name;
//	DWORD_PTR addr;
//	DWORD_PTR bone;
//	DWORD_PTR type;
//};