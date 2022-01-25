#include "Console.h"

void Console::Print(const char* prefix, const char* format, va_list args)
{
	printf("[");
	printf(prefix);
	printf("] ");
	vprintf(format, args);
	printf("\n");
}

void Console::PrintColored(const char* prefix, const char* format, int color, va_list args)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, color);
	Print(prefix, format, args);

	SetConsoleTextAttribute(console, COLOR_WHITE);
}

void Console::Debug(const char* format, ...)
{
	va_list args;
	va_start(args, format);

	PrintColored("+", format, COLOR_GREY, args);
}

void Console::Info(const char* format, ...)
{
	va_list args;
	va_start(args, format);

	PrintColored("+", format, COLOR_WHITE, args);
}

void Console::Success(const char* format, ...)
{
	va_list args;
	va_start(args, format);

	PrintColored("+", format, COLOR_GREEN, args);
}

void Console::Error(const char* format, ...)
{
	va_list args;
	va_start(args, format);

	PrintColored("-", format, COLOR_RED, args);
}
void Console::Warning(const char* format, ...)
{
	va_list args;
	va_start(args, format);

	PrintColored("-", format, COLOR_YELLOW, args);
}

void Console::PrintTitle(const char* name)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, COLOR_GREEN);
	printf(name);
	printf("\n");
	SetConsoleTextAttribute(console, COLOR_WHITE);
}

void Console::WaitForInput()
{
	std::cin.get();
}

void Console::WaitAndExit()
{
	std::cin.get();
	exit(0);
}