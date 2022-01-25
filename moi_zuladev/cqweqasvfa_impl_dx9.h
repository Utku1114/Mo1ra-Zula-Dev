#include <Windows.h>
// cqweqasvfa Win32 + DirectX9 binding
// In this binding, ImTextureID is used to store a 'LPDIRECT3DTEXTURE9' texture identifier. Read the FAQ about ImTextureID in cqweqasvfa.cpp.

// You can copy and use unmodified cqweqasvfa_impl_* files in your project. See main.cpp for an example of using this.
// If you use this binding you'll need to call 4 functions: cqweqasvfa_ImplXXXX_Init(), cqweqasvfa_ImplXXXX_NewFrame(), cqweqasvfa::Render() and cqweqasvfa_ImplXXXX_Shutdown().
// If you are new to cqweqasvfa, see examples/README.txt and documentation at the top of cqweqasvfa.cpp.
// https://github.com/ocornut/cqweqasvfa

struct IDirect3DDevice9;

cqweqasvfa_API bool        cqweqasvfa_ImplDX9_Init(void* hwnd, IDirect3DDevice9* device);
cqweqasvfa_API void        cqweqasvfa_ImplDX9_Shutdown();
cqweqasvfa_API void        cqweqasvfa_ImplDX9_NewFrame();

// Use if you want to reset your rendering device without losing cqweqasvfa state.
cqweqasvfa_API void        cqweqasvfa_ImplDX9_InvalidateDeviceObjects();
cqweqasvfa_API bool        cqweqasvfa_ImplDX9_CreateDeviceObjects();

// Handler for Win32 messages, update mouse/keyboard data.
// You may or not need this for your implementation, but it can serve as reference for handling inputs.
// Commented out to avoid dragging dependencies on <windows.h> types. You can copy the extern declaration in your code.

extern cqweqasvfa_API LRESULT   cqweqasvfa_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

