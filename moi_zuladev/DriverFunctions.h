

typedef struct cqwevqwxe {
	DWORD pid = 0;
	void* address;
	void* value;
	SIZE_T size;
	void* data;

}info, * p_info;

HANDLE drv;
DWORD p = NULL;

uintptr_t base;

#define DICC(a1, a2, a3, a4, a5, a6, a7, a8) DeviceIoControl(##a1, ##a2, ##a3, ##a4, ##a5, ##a6, ##a7, ##a8)
#define DIC DICC
template <typename Type>
Type readmem(unsigned long long int Address)
{
	__try
	{
		J();
		cqwevqwxe ciktiyapisi;
		ciktiyapisi.pid = p;
		ciktiyapisi.address = (void*)Address;
		Type Return_Value;
		ciktiyapisi.value = &Return_Value;
		ciktiyapisi.size = sizeof Return_Value;
		//unsigned long int okunan_bayt_miktari;
		J();
		if (DIC(drv, CTL_CODE(FILE_DEVICE_UNKNOWN, 0x850, METHOD_BUFFERED, FILE_SPECIAL_ACCESS), &ciktiyapisi, sizeof ciktiyapisi, &ciktiyapisi, sizeof ciktiyapisi, nullptr, nullptr))
			return Return_Value;
		J();
	}
	__except(1)
	{ }
}
template <typename Type>
Type readmemA(unsigned long long int Address, SIZE_T size)
{
	__try
	{
		J();
		cqwevqwxe ciktiyapisi;
		ciktiyapisi.pid = p;
		ciktiyapisi.address = (void*)Address;
		Type Return_Value;
		ciktiyapisi.value = &Return_Value;
		ciktiyapisi.size = size;
		// unsigned long int okunan_bayt_miktari;
		J();
		if (DIC(drv, CTL_CODE(FILE_DEVICE_UNKNOWN, 0x850, METHOD_BUFFERED, FILE_SPECIAL_ACCESS), &ciktiyapisi, sizeof ciktiyapisi, &ciktiyapisi, sizeof ciktiyapisi, nullptr, nullptr))
			return Return_Value;
		J();
	}
	__except (1)
	{
	}
}

#define READ(addr) readmem<uint64_t>(addr)
template<typename T>
bool readmemB(unsigned long long int Address, T* ptr, SIZE_T size)
{
	__try
	{
		J();
		cqwevqwxe ciktiyapisi;
		ciktiyapisi.pid = p;
		ciktiyapisi.address = (void*)Address;
		ciktiyapisi.value = ptr;
		ciktiyapisi.size = size;
		// unsigned long int okunan_bayt_miktari;
		J();
		if (DIC(drv, CTL_CODE(FILE_DEVICE_UNKNOWN, 0x850, METHOD_BUFFERED, FILE_SPECIAL_ACCESS), &ciktiyapisi, sizeof ciktiyapisi, &ciktiyapisi, sizeof ciktiyapisi, nullptr, nullptr))
			return ptr;
		J();
	}
	__except (1)
	{
	}
}

template<typename A>
void writemem(unsigned long long int Address, A* Return_Value, SIZE_T size)
{
	cqwevqwxe ciktiyapisi;
	ciktiyapisi.pid = p;
	ciktiyapisi.address = (void*)Address;
	ciktiyapisi.value = Return_Value;
	ciktiyapisi.size = size;
	//  unsigned long int okunan_bayt_miktari;
	J();
	DIC(drv, CTL_CODE(FILE_DEVICE_UNKNOWN, 0x851, METHOD_BUFFERED, FILE_SPECIAL_ACCESS), &ciktiyapisi, sizeof ciktiyapisi, &ciktiyapisi, sizeof ciktiyapisi, nullptr, nullptr);
}
