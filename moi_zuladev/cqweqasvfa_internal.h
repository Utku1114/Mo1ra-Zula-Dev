// dear cqweqasvfa, v1.53
// (internals)

// You may use this file to debug, understand or extend cqweqasvfa features but we don't provide any guarantee of forward compatibility!
// Set:
//   #define cqweqasvfa_DEFINE_MATH_OPERATORS
// To implement maths operators for ImVec2 (disabled by default to not collide with using IM_VEC2_CLASS_EXTRA along with your own math types+operators)

#pragma once

#ifndef cqweqasvfa_VERSION
#error Must include cqweqasvfa.h before cqweqasvfa_internal.h
#endif

#include <stdio.h>      // FILE*
#include <math.h>       // sqrtf, fabsf, fmodf, powf, floorf, ceilf, cosf, sinf

#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable: 4251) // class 'xxx' needs to have dll-interface to be used by clients of struct 'xxx' // when cqweqasvfa_API is set to__declspec(dllexport)
#endif

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-function"        // for stb_textedit.h
#pragma clang diagnostic ignored "-Wmissing-prototypes"     // for stb_textedit.h
#pragma clang diagnostic ignored "-Wold-style-cast"
#endif

//-----------------------------------------------------------------------------
// Forward Declarations
//-----------------------------------------------------------------------------

struct ImRect;
struct cqweqasvfaColMod;
struct cqweqasvfaStyleMod;
struct cqweqasvfaGroupData;
struct cqweqasvfaSimpleColumns;
struct cqweqasvfaDrawContext;
struct cqweqasvfaTextEditState;
struct cqweqasvfaMouseCursorData;
struct cqweqasvfaPopupRef;
struct cqweqasvfaWindow;
struct cqweqasvfaWindowSettings;

typedef int cqweqasvfaLayoutType;        // enum: horizontal or vertical             // enum cqweqasvfaLayoutType_
typedef int cqweqasvfaButtonFlags;       // flags: for ButtonEx(), ButtonBehavior()  // enum cqweqasvfaButtonFlags_
typedef int cqweqasvfaItemFlags;         // flags: for PushItemFlag()                // enum cqweqasvfaItemFlags_
typedef int cqweqasvfaSeparatorFlags;    // flags: for Separator() - internal        // enum cqweqasvfaSeparatorFlags_
typedef int cqweqasvfaSliderFlags;       // flags: for SliderBehavior()              // enum cqweqasvfaSliderFlags_

//-------------------------------------------------------------------------
// STB libraries
//-------------------------------------------------------------------------

namespace cqweqasvfaStb
{

#undef STB_TEXTEDIT_STRING
#undef STB_TEXTEDIT_CHARTYPE
#define STB_TEXTEDIT_STRING             cqweqasvfaTextEditState
#define STB_TEXTEDIT_CHARTYPE           ImWchar
#define STB_TEXTEDIT_GETWIDTH_NEWLINE   -1.0f
#include "stb_textedit.h"

} // namespace cqweqasvfaStb

//-----------------------------------------------------------------------------
// Context
//-----------------------------------------------------------------------------

#ifndef Gcqweqasvfa
extern cqweqasvfa_API cqweqasvfaContext* Gcqweqasvfa;  // Current implicit cqweqasvfa context pointer
#endif

//-----------------------------------------------------------------------------
// Helpers
//-----------------------------------------------------------------------------

#define IM_PI                       3.14159265358979323846f
#define IM_OFFSETOF(_TYPE,_ELM)     ((size_t)&(((_TYPE*)0)->_ELM))

// Helpers: UTF-8 <> wchar
cqweqasvfa_API int           ImTextStrToUtf8(char* buf, int buf_size, const ImWchar* in_text, const ImWchar* in_text_end);      // return output UTF-8 bytes count
cqweqasvfa_API int           ImTextCharFromUtf8(unsigned int* out_char, const char* in_text, const char* in_text_end);          // return input UTF-8 bytes count
cqweqasvfa_API int           ImTextStrFromUtf8(ImWchar* buf, int buf_size, const char* in_text, const char* in_text_end, const char** in_remaining = NULL);   // return input UTF-8 bytes count
cqweqasvfa_API int           ImTextCountCharsFromUtf8(const char* in_text, const char* in_text_end);                            // return number of UTF-8 code-points (NOT bytes count)
cqweqasvfa_API int           ImTextCountUtf8BytesFromStr(const ImWchar* in_text, const ImWchar* in_text_end);                   // return number of bytes to express string as UTF-8 code-points

// Helpers: Misc
cqweqasvfa_API ImU32         ImHash(const void* data, int data_size, ImU32 seed = 0);    // Pass data_size==0 for zero-terminated strings
cqweqasvfa_API void* ImFileLoadToMemory(const char* filename, const char* file_open_mode, int* out_file_size = NULL, int padding_bytes = 0);
cqweqasvfa_API FILE* ImFileOpen(const char* filename, const char* file_open_mode);
static inline bool      ImCharIsSpace(int c) { return c == ' ' || c == '\t' || c == 0x3000; }
static inline bool      ImIsPowerOfTwo(int v) { return v != 0 && (v & (v - 1)) == 0; }
static inline int       ImUpperPowerOfTwo(int v) { v--; v |= v >> 1; v |= v >> 2; v |= v >> 4; v |= v >> 8; v |= v >> 16; v++; return v; }

// Helpers: Geometry
cqweqasvfa_API ImVec2        ImLineClosestPoint(const ImVec2& a, const ImVec2& b, const ImVec2& p);
cqweqasvfa_API bool          ImTriangleContainsPoint(const ImVec2& a, const ImVec2& b, const ImVec2& c, const ImVec2& p);
cqweqasvfa_API ImVec2        ImTriangleClosestPoint(const ImVec2& a, const ImVec2& b, const ImVec2& c, const ImVec2& p);
cqweqasvfa_API void          ImTriangleBarycentricCoords(const ImVec2& a, const ImVec2& b, const ImVec2& c, const ImVec2& p, float& out_u, float& out_v, float& out_w);

// Helpers: String
cqweqasvfa_API int           ImStricmp(const char* str1, const char* str2);
cqweqasvfa_API int           ImStrnicmp(const char* str1, const char* str2, size_t count);
cqweqasvfa_API void          ImStrncpy(char* dst, const char* src, size_t count);
cqweqasvfa_API char* ImStrdup(const char* str);
cqweqasvfa_API char* ImStrchrRange(const char* str_begin, const char* str_end, char c);
cqweqasvfa_API int           ImStrlenW(const ImWchar* str);
cqweqasvfa_API const ImWchar* ImStrbolW(const ImWchar* buf_mid_line, const ImWchar* buf_begin); // Find beginning-of-line
cqweqasvfa_API const char* ImStristr(const char* haystack, const char* haystack_end, const char* needle, const char* needle_end);
cqweqasvfa_API int           ImFormatString(char* buf, size_t buf_size, const char* fmt, ...) IM_FMTARGS(3);
cqweqasvfa_API int           ImFormatStringV(char* buf, size_t buf_size, const char* fmt, va_list args) IM_FMTLIST(3);

// Helpers: Math
// We are keeping those not leaking to the user by default, in the case the user has implicit cast operators between ImVec2 and its own types (when IM_VEC2_CLASS_EXTRA is defined)
#ifdef cqweqasvfa_DEFINE_MATH_OPERATORS
static inline ImVec2 operator*(const ImVec2& lhs, const float rhs) { return ImVec2(lhs.x * rhs, lhs.y * rhs); }
static inline ImVec2 operator/(const ImVec2& lhs, const float rhs) { return ImVec2(lhs.x / rhs, lhs.y / rhs); }
static inline ImVec2 operator+(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x + rhs.x, lhs.y + rhs.y); }
static inline ImVec2 operator-(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x - rhs.x, lhs.y - rhs.y); }
static inline ImVec2 operator*(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x * rhs.x, lhs.y * rhs.y); }
static inline ImVec2 operator/(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x / rhs.x, lhs.y / rhs.y); }
static inline ImVec2& operator+=(ImVec2& lhs, const ImVec2& rhs) { lhs.x += rhs.x; lhs.y += rhs.y; return lhs; }
static inline ImVec2& operator-=(ImVec2& lhs, const ImVec2& rhs) { lhs.x -= rhs.x; lhs.y -= rhs.y; return lhs; }
static inline ImVec2& operator*=(ImVec2& lhs, const float rhs) { lhs.x *= rhs; lhs.y *= rhs; return lhs; }
static inline ImVec2& operator/=(ImVec2& lhs, const float rhs) { lhs.x /= rhs; lhs.y /= rhs; return lhs; }
static inline ImVec4 operator+(const ImVec4& lhs, const ImVec4& rhs) { return ImVec4(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w); }
static inline ImVec4 operator-(const ImVec4& lhs, const ImVec4& rhs) { return ImVec4(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w); }
static inline ImVec4 operator*(const ImVec4& lhs, const ImVec4& rhs) { return ImVec4(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w); }
#endif

static inline int    ImMin(int lhs, int rhs) { return lhs < rhs ? lhs : rhs; }
static inline int    ImMax(int lhs, int rhs) { return lhs >= rhs ? lhs : rhs; }
static inline float  ImMin(float lhs, float rhs) { return lhs < rhs ? lhs : rhs; }
static inline float  ImMax(float lhs, float rhs) { return lhs >= rhs ? lhs : rhs; }
static inline ImVec2 ImMin(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(ImMin(lhs.x, rhs.x), ImMin(lhs.y, rhs.y)); }
static inline ImVec2 ImMax(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(ImMax(lhs.x, rhs.x), ImMax(lhs.y, rhs.y)); }
static inline int    ImClamp(int v, int mn, int mx) { return (v < mn) ? mn : (v > mx) ? mx : v; }
static inline float  ImClamp(float v, float mn, float mx) { return (v < mn) ? mn : (v > mx) ? mx : v; }
static inline ImVec2 ImClamp(const ImVec2& f, const ImVec2& mn, ImVec2 mx) { return ImVec2(ImClamp(f.x, mn.x, mx.x), ImClamp(f.y, mn.y, mx.y)); }
static inline float  ImSaturate(float f) { return (f < 0.0f) ? 0.0f : (f > 1.0f) ? 1.0f : f; }
static inline void   ImSwap(int& a, int& b) { int tmp = a; a = b; b = tmp; }
static inline void   ImSwap(float& a, float& b) { float tmp = a; a = b; b = tmp; }
static inline int    ImLerp(int a, int b, float t) { return (int)(a + (b - a) * t); }
static inline float  ImLerp(float a, float b, float t) { return a + (b - a) * t; }
static inline ImVec2 ImLerp(const ImVec2& a, const ImVec2& b, float t) { return ImVec2(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t); }
static inline ImVec2 ImLerp(const ImVec2& a, const ImVec2& b, const ImVec2& t) { return ImVec2(a.x + (b.x - a.x) * t.x, a.y + (b.y - a.y) * t.y); }
static inline ImVec4 ImLerp(const ImVec4& a, const ImVec4& b, float t) { return ImVec4(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t, a.z + (b.z - a.z) * t, a.w + (b.w - a.w) * t); }
static inline float  ImLengthSqr(const ImVec2& lhs) { return lhs.x * lhs.x + lhs.y * lhs.y; }
static inline float  ImLengthSqr(const ImVec4& lhs) { return lhs.x * lhs.x + lhs.y * lhs.y + lhs.z * lhs.z + lhs.w * lhs.w; }
static inline float  ImInvLength(const ImVec2& lhs, float fail_value) { float d = lhs.x * lhs.x + lhs.y * lhs.y; if (d > 0.0f) return 1.0f / sqrtf(d); return fail_value; }
static inline float  ImFloor(float f) { return (float)(int)f; }
static inline ImVec2 ImFloor(const ImVec2& v) { return ImVec2((float)(int)v.x, (float)(int)v.y); }
static inline float  ImDot(const ImVec2& a, const ImVec2& b) { return a.x * b.x + a.y * b.y; }
static inline ImVec2 ImRotate(const ImVec2& v, float cos_a, float sin_a) { return ImVec2(v.x * cos_a - v.y * sin_a, v.x * sin_a + v.y * cos_a); }
static inline float  ImLinearSweep(float current, float target, float speed) { if (current < target) return ImMin(current + speed, target); if (current > target) return ImMax(current - speed, target); return current; }
static inline ImVec2 ImMul(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x * rhs.x, lhs.y * rhs.y); }

// We call C++ constructor on own allocated memory via the placement "new(ptr) Type()" syntax.
// Defining a custom placement new() with a dummy parameter allows us to bypass including <new> which on some platforms complains when user has disabled exceptions.
struct ImNewPlacementDummy {};
inline void* operator   new(size_t, ImNewPlacementDummy, void* ptr) { return ptr; }
inline void  operator   delete(void*, ImNewPlacementDummy, void*) {} // This is only required so we can use the symetrical new()
#define IM_PLACEMENT_NEW(_PTR)              new(ImNewPlacementDummy(), _PTR)
#define IM_NEW(_TYPE)                       new(ImNewPlacementDummy(), cqweqasvfa::MemAlloc(sizeof(_TYPE))) _TYPE
template <typename T> void IM_DELETE(T*& p) { if (p) { p->~T(); cqweqasvfa::MemFree(p); p = NULL; } }

//-----------------------------------------------------------------------------
// Types
//-----------------------------------------------------------------------------

// Internal Drag and Drop payload types. String starting with '_' are reserved for Dear cqweqasvfa.
#define cqweqasvfa_PAYLOAD_TYPE_DOCKABLE         "_IMDOCK"   // cqweqasvfaWindow* // [Internal] Docking/tabs

enum cqweqasvfaButtonFlags_
{
    cqweqasvfaButtonFlags_Repeat = 1 << 0,   // hold to repeat
    cqweqasvfaButtonFlags_PressedOnClickRelease = 1 << 1,   // return true on click + release on same item [DEFAULT if no PressedOn* flag is set]
    cqweqasvfaButtonFlags_PressedOnClick = 1 << 2,   // return true on click (default requires click+release)
    cqweqasvfaButtonFlags_PressedOnRelease = 1 << 3,   // return true on release (default requires click+release)
    cqweqasvfaButtonFlags_PressedOnDoubleClick = 1 << 4,   // return true on double-click (default requires click+release)
    cqweqasvfaButtonFlags_FlattenChildren = 1 << 5,   // allow interactions even if a child window is overlapping
    cqweqasvfaButtonFlags_AllowItemOverlap = 1 << 6,   // require previous frame HoveredId to either match id or be null before being usable, use along with SetItemAllowOverlap()
    cqweqasvfaButtonFlags_DontClosePopups = 1 << 7,   // disable automatically closing parent popup on press // [UNUSED]
    cqweqasvfaButtonFlags_Disabled = 1 << 8,   // disable interactions
    cqweqasvfaButtonFlags_AlignTextBaseLine = 1 << 9,   // vertically align button to match text baseline - ButtonEx() only // FIXME: Should be removed and handled by SmallButton(), not possible currently because of DC.CursorPosPrevLine
    cqweqasvfaButtonFlags_NoKeyModifiers = 1 << 10,  // disable interaction if a key modifier is held
    cqweqasvfaButtonFlags_NoHoldingActiveID = 1 << 11,  // don't set ActiveId while holding the mouse (cqweqasvfaButtonFlags_PressedOnClick only)
    cqweqasvfaButtonFlags_PressedOnDragDropHold = 1 << 12   // press when held into while we are drag and dropping another item (used by e.g. tree nodes, collapsing headers)
};

enum cqweqasvfaSliderFlags_
{
    cqweqasvfaSliderFlags_Vertical = 1 << 0
};

enum cqweqasvfaColumnsFlags_
{
    // Default: 0
    cqweqasvfaColumnsFlags_NoBorder = 1 << 0,   // Disable column dividers
    cqweqasvfaColumnsFlags_NoResize = 1 << 1,   // Disable resizing columns when clicking on the dividers
    cqweqasvfaColumnsFlags_NoPreserveWidths = 1 << 2,   // Disable column width preservation when adjusting columns
    cqweqasvfaColumnsFlags_NoForceWithinWindow = 1 << 3,   // Disable forcing columns to fit within window
    cqweqasvfaColumnsFlags_GrowParentContentsSize = 1 << 4    // (WIP) Restore pre-1.51 behavior of extending the parent window contents size but _without affecting the columns width at all_. Will eventually remove.
};

enum cqweqasvfaSelectableFlagsPrivate_
{
    // NB: need to be in sync with last value of cqweqasvfaSelectableFlags_
    cqweqasvfaSelectableFlags_Menu = 1 << 3,   // -> PressedOnClick
    cqweqasvfaSelectableFlags_MenuItem = 1 << 4,   // -> PressedOnRelease
    cqweqasvfaSelectableFlags_Disabled = 1 << 5,
    cqweqasvfaSelectableFlags_DrawFillAvailWidth = 1 << 6
};

enum cqweqasvfaSeparatorFlags_
{
    cqweqasvfaSeparatorFlags_Horizontal = 1 << 0,   // Axis default to current layout type, so generally Horizontal unless e.g. in a menu bar
    cqweqasvfaSeparatorFlags_Vertical = 1 << 1
};

// FIXME: this is in development, not exposed/functional as a generic feature yet.
enum cqweqasvfaLayoutType_
{
    cqweqasvfaLayoutType_Vertical,
    cqweqasvfaLayoutType_Horizontal
};

enum cqweqasvfaAxis
{
    cqweqasvfaAxis_None = -1,
    cqweqasvfaAxis_X = 0,
    cqweqasvfaAxis_Y = 1
};

enum cqweqasvfaPlotType
{
    cqweqasvfaPlotType_Lines,
    cqweqasvfaPlotType_Histogram
};

enum cqweqasvfaDataType
{
    cqweqasvfaDataType_Int,
    cqweqasvfaDataType_Float,
    cqweqasvfaDataType_Float2
};

enum cqweqasvfaDir
{
    cqweqasvfaDir_None = -1,
    cqweqasvfaDir_Left = 0,
    cqweqasvfaDir_Right = 1,
    cqweqasvfaDir_Up = 2,
    cqweqasvfaDir_Down = 3,
    cqweqasvfaDir_Count_
};

// 2D axis aligned bounding-box
// NB: we can't rely on ImVec2 math operators being available here
struct cqweqasvfa_API ImRect
{
    ImVec2      Min;    // Upper-left
    ImVec2      Max;    // Lower-right

    ImRect() : Min(FLT_MAX, FLT_MAX), Max(-FLT_MAX, -FLT_MAX) {}
    ImRect(const ImVec2& min, const ImVec2& max) : Min(min), Max(max) {}
    ImRect(const ImVec4& v) : Min(v.x, v.y), Max(v.z, v.w) {}
    ImRect(float x1, float y1, float x2, float y2) : Min(x1, y1), Max(x2, y2) {}

    ImVec2      GetCenter() const { return ImVec2((Min.x + Max.x) * 0.5f, (Min.y + Max.y) * 0.5f); }
    ImVec2      GetSize() const { return ImVec2(Max.x - Min.x, Max.y - Min.y); }
    float       GetWidth() const { return Max.x - Min.x; }
    float       GetHeight() const { return Max.y - Min.y; }
    ImVec2      GetTL() const { return Min; }                   // Top-left
    ImVec2      GetTR() const { return ImVec2(Max.x, Min.y); }  // Top-right
    ImVec2      GetBL() const { return ImVec2(Min.x, Max.y); }  // Bottom-left
    ImVec2      GetBR() const { return Max; }                   // Bottom-right
    bool        Contains(const ImVec2& p) const { return p.x >= Min.x && p.y >= Min.y && p.x < Max.x&& p.y < Max.y; }
    bool        Contains(const ImRect& r) const { return r.Min.x >= Min.x && r.Min.y >= Min.y && r.Max.x < Max.x&& r.Max.y < Max.y; }
    bool        Overlaps(const ImRect& r) const { return r.Min.y < Max.y&& r.Max.y > Min.y && r.Min.x < Max.x&& r.Max.x > Min.x; }
    void        Add(const ImVec2& rhs) { if (Min.x > rhs.x)     Min.x = rhs.x;     if (Min.y > rhs.y) Min.y = rhs.y;         if (Max.x < rhs.x) Max.x = rhs.x;         if (Max.y < rhs.y) Max.y = rhs.y; }
    void        Add(const ImRect& rhs) { if (Min.x > rhs.Min.x) Min.x = rhs.Min.x; if (Min.y > rhs.Min.y) Min.y = rhs.Min.y; if (Max.x < rhs.Max.x) Max.x = rhs.Max.x; if (Max.y < rhs.Max.y) Max.y = rhs.Max.y; }
    void        Expand(const float amount) { Min.x -= amount;   Min.y -= amount;   Max.x += amount;   Max.y += amount; }
    void        Expand(const ImVec2& amount) { Min.x -= amount.x; Min.y -= amount.y; Max.x += amount.x; Max.y += amount.y; }
    void        Translate(const ImVec2& v) { Min.x += v.x; Min.y += v.y; Max.x += v.x; Max.y += v.y; }
    void        ClipWith(const ImRect& clip) { if (Min.x < clip.Min.x) Min.x = clip.Min.x; if (Min.y < clip.Min.y) Min.y = clip.Min.y; if (Max.x > clip.Max.x) Max.x = clip.Max.x; if (Max.y > clip.Max.y) Max.y = clip.Max.y; }
    void        Floor() { Min.x = (float)(int)Min.x; Min.y = (float)(int)Min.y; Max.x = (float)(int)Max.x; Max.y = (float)(int)Max.y; }
    void        FixInverted() { if (Min.x > Max.x) ImSwap(Min.x, Max.x); if (Min.y > Max.y) ImSwap(Min.y, Max.y); }
    bool        IsFinite() const { return Min.x != FLT_MAX; }
    ImVec2      GetClosestPoint(ImVec2 p, bool on_edge) const
    {
        if (!on_edge && Contains(p))
            return p;
        if (p.x > Max.x) p.x = Max.x;
        else if (p.x < Min.x) p.x = Min.x;
        if (p.y > Max.y) p.y = Max.y;
        else if (p.y < Min.y) p.y = Min.y;
        return p;
    }
};

// Stacked color modifier, backup of modified data so we can restore it
struct cqweqasvfaColMod
{
    cqweqasvfaCol    Col;
    ImVec4      BackupValue;
};

// Stacked style modifier, backup of modified data so we can restore it. Data type inferred from the variable.
struct cqweqasvfaStyleMod
{
    cqweqasvfaStyleVar   VarIdx;
    union { int BackupInt[2]; float BackupFloat[2]; };
    cqweqasvfaStyleMod(cqweqasvfaStyleVar idx, int v) { VarIdx = idx; BackupInt[0] = v; }
    cqweqasvfaStyleMod(cqweqasvfaStyleVar idx, float v) { VarIdx = idx; BackupFloat[0] = v; }
    cqweqasvfaStyleMod(cqweqasvfaStyleVar idx, ImVec2 v) { VarIdx = idx; BackupFloat[0] = v.x; BackupFloat[1] = v.y; }
};

// Stacked data for BeginGroup()/EndGroup()
struct cqweqasvfaGroupData
{
    ImVec2      BackupCursorPos;
    ImVec2      BackupCursorMaxPos;
    float       BackupIndentX;
    float       BackupGroupOffsetX;
    float       BackupCurrentLineHeight;
    float       BackupCurrentLineTextBaseOffset;
    float       BackupLogLinePosY;
    bool        BackupActiveIdIsAlive;
    bool        AdvanceCursor;
};

// Simple column measurement currently used for MenuItem() only. This is very short-sighted/throw-away code and NOT a generic helper.
struct cqweqasvfa_API cqweqasvfaSimpleColumns
{
    int         Count;
    float       Spacing;
    float       Width, NextWidth;
    float       Pos[8], NextWidths[8];

    cqweqasvfaSimpleColumns();
    void        Update(int count, float spacing, bool clear);
    float       DeclColumns(float w0, float w1, float w2);
    float       CalcExtraSpace(float avail_w);
};

// Internal state of the currently focused/edited text input box
struct cqweqasvfa_API cqweqasvfaTextEditState
{
    cqweqasvfaID             Id;                         // widget id owning the text state
    ImVector<ImWchar>   Text;                       // edit buffer, we need to persist but can't guarantee the persistence of the user-provided buffer. so we copy into own buffer.
    ImVector<char>      InitialText;                // backup of end-user buffer at the time of focus (in UTF-8, unaltered)
    ImVector<char>      TempTextBuffer;
    int                 CurLenA, CurLenW;           // we need to maintain our buffer length in both UTF-8 and wchar format.
    int                 BufSizeA;                   // end-user buffer size
    float               ScrollX;
    cqweqasvfaStb::STB_TexteditState   StbState;
    float               CursorAnim;
    bool                CursorFollow;
    bool                SelectedAllMouseLock;

    cqweqasvfaTextEditState() { memset(this, 0, sizeof(*this)); }
    void                CursorAnimReset() { CursorAnim = -0.30f; }                                   // After a user-input the cursor stays on for a while without blinking
    void                CursorClamp() { StbState.cursor = ImMin(StbState.cursor, CurLenW); StbState.select_start = ImMin(StbState.select_start, CurLenW); StbState.select_end = ImMin(StbState.select_end, CurLenW); }
    bool                HasSelection() const { return StbState.select_start != StbState.select_end; }
    void                ClearSelection() { StbState.select_start = StbState.select_end = StbState.cursor; }
    void                SelectAll() { StbState.select_start = 0; StbState.select_end = CurLenW; StbState.cursor = StbState.select_end; StbState.has_preferred_x = false; }
    void                OnKeyPressed(int key);
};

// Data saved in cqweqasvfa.ini file
struct cqweqasvfaWindowSettings
{
    char* Name;
    cqweqasvfaID     Id;
    ImVec2      Pos;
    ImVec2      Size;
    bool        Collapsed;

    cqweqasvfaWindowSettings() { Name = NULL; Id = 0; Pos = Size = ImVec2(0, 0); Collapsed = false; }
};

struct cqweqasvfaSettingsHandler
{
    const char* TypeName;   // Short description stored in .ini file. Disallowed characters: '[' ']'  
    cqweqasvfaID     TypeHash;   // == ImHash(TypeName, 0, 0)
    void* (*ReadOpenFn)(cqweqasvfaContext& ctx, const char* name);
    void        (*ReadLineFn)(cqweqasvfaContext& ctx, void* entry, const char* line);
    void        (*WriteAllFn)(cqweqasvfaContext& ctx, cqweqasvfaTextBuffer* out_buf);
};

// Mouse cursor data (used when io.MouseDrawCursor is set)
struct cqweqasvfaMouseCursorData
{
    cqweqasvfaMouseCursor    Type;
    ImVec2              HotOffset;
    ImVec2              Size;
    ImVec2              TexUvMin[2];
    ImVec2              TexUvMax[2];
};

// Storage for current popup stack
struct cqweqasvfaPopupRef
{
    cqweqasvfaID             PopupId;        // Set on OpenPopup()
    cqweqasvfaWindow* Window;         // Resolved on BeginPopup() - may stay unresolved if user never calls OpenPopup()
    cqweqasvfaWindow* ParentWindow;   // Set on OpenPopup()
    cqweqasvfaID             ParentMenuSet;  // Set on OpenPopup()
    ImVec2              MousePosOnOpen; // Copy of mouse position at the time of opening popup

    cqweqasvfaPopupRef(cqweqasvfaID id, cqweqasvfaWindow* parent_window, cqweqasvfaID parent_menu_set, const ImVec2& mouse_pos) { PopupId = id; Window = NULL; ParentWindow = parent_window; ParentMenuSet = parent_menu_set; MousePosOnOpen = mouse_pos; }
};

struct cqweqasvfaColumnData
{
    float               OffsetNorm;         // Column start offset, normalized 0.0 (far left) -> 1.0 (far right)
    float               OffsetNormBeforeResize;
    cqweqasvfaColumnsFlags   Flags;              // Not exposed
    ImRect              ClipRect;

    cqweqasvfaColumnData() { OffsetNorm = OffsetNormBeforeResize = 0.0f; Flags = 0; }
};

struct cqweqasvfaColumnsSet
{
    cqweqasvfaID             ID;
    cqweqasvfaColumnsFlags   Flags;
    bool                IsFirstFrame;
    bool                IsBeingResized;
    int                 Current;
    int                 Count;
    float               MinX, MaxX;
    float               StartPosY;
    float               StartMaxPosX;       // Backup of CursorMaxPos
    float               CellMinY, CellMaxY;
    ImVector<cqweqasvfaColumnData> Columns;

    cqweqasvfaColumnsSet() { Clear(); }
    void Clear()
    {
        ID = 0;
        Flags = 0;
        IsFirstFrame = false;
        IsBeingResized = false;
        Current = 0;
        Count = 1;
        MinX = MaxX = 0.0f;
        StartPosY = 0.0f;
        StartMaxPosX = 0.0f;
        CellMinY = CellMaxY = 0.0f;
        Columns.clear();
    }
};

struct ImDrawListSharedData
{
    ImVec2          TexUvWhitePixel;            // UV of white pixel in the atlas
    ImFont* Font;                       // Current/default font (optional, for simplified AddText overload)
    float           FontSize;                   // Current/default font size (optional, for simplified AddText overload)
    float           CurveTessellationTol;
    ImVec4          ClipRectFullscreen;         // Value for PushClipRectFullscreen()

    // Const data
    // FIXME: Bake rounded corners fill/borders in atlas
    ImVec2          CircleVtx12[12];

    ImDrawListSharedData();
};

// Main state for cqweqasvfa
struct cqweqasvfaContext
{
    bool                    Initialized;
    cqweqasvfaIO                 IO;
    cqweqasvfaStyle              Style;
    ImFont* Font;                               // (Shortcut) == FontStack.empty() ? IO.Font : FontStack.back()
    float                   FontSize;                           // (Shortcut) == FontBaseSize * g.CurrentWindow->FontWindowScale == window->FontSize(). Text height for current window.
    float                   FontBaseSize;                       // (Shortcut) == IO.FontGlobalScale * Font->Scale * Font->FontSize. Base text height.
    ImDrawListSharedData    DrawListSharedData;

    float                   Time;
    int                     FrameCount;
    int                     FrameCountEnded;
    int                     FrameCountRendered;
    ImVector<cqweqasvfaWindow*>  Windows;
    ImVector<cqweqasvfaWindow*>  WindowsSortBuffer;
    ImVector<cqweqasvfaWindow*>  CurrentWindowStack;
    cqweqasvfaStorage            WindowsById;
    int                     WindowsActiveCount;
    cqweqasvfaWindow* CurrentWindow;                      // Being drawn into
    cqweqasvfaWindow* NavWindow;                          // Nav/focused window for navigation
    cqweqasvfaWindow* HoveredWindow;                      // Will catch mouse inputs
    cqweqasvfaWindow* HoveredRootWindow;                  // Will catch mouse inputs (for focus/move only)
    cqweqasvfaID                 HoveredId;                          // Hovered widget
    bool                    HoveredIdAllowOverlap;
    cqweqasvfaID                 HoveredIdPreviousFrame;
    float                   HoveredIdTimer;
    cqweqasvfaID                 ActiveId;                           // Active widget
    cqweqasvfaID                 ActiveIdPreviousFrame;
    float                   ActiveIdTimer;
    bool                    ActiveIdIsAlive;                    // Active widget has been seen this frame
    bool                    ActiveIdIsJustActivated;            // Set at the time of activation for one frame
    bool                    ActiveIdAllowOverlap;               // Active widget allows another widget to steal active id (generally for overlapping widgets, but not always)
    ImVec2                  ActiveIdClickOffset;                // Clicked offset from upper-left corner, if applicable (currently only set by ButtonBehavior)
    cqweqasvfaWindow* ActiveIdWindow;
    cqweqasvfaWindow* MovingWindow;                       // Track the child window we clicked on to move a window.
    cqweqasvfaID                 MovingWindowMoveId;                 // == MovingWindow->MoveId
    ImVector<cqweqasvfaColMod>   ColorModifiers;                     // Stack for PushStyleColor()/PopStyleColor()
    ImVector<cqweqasvfaStyleMod> StyleModifiers;                     // Stack for PushStyleVar()/PopStyleVar()
    ImVector<ImFont*>       FontStack;                          // Stack for PushFont()/PopFont()
    ImVector<cqweqasvfaPopupRef> OpenPopupStack;                     // Which popups are open (persistent)
    ImVector<cqweqasvfaPopupRef> CurrentPopupStack;                  // Which level of BeginPopup() we are in (reset every frame)

    // Storage for SetNexWindow** and SetNextTreeNode*** functions
    ImVec2                  SetNextWindowPosVal;
    ImVec2                  SetNextWindowPosPivot;
    ImVec2                  SetNextWindowSizeVal;
    ImVec2                  SetNextWindowContentSizeVal;
    bool                    SetNextWindowCollapsedVal;
    cqweqasvfaCond               SetNextWindowPosCond;
    cqweqasvfaCond               SetNextWindowSizeCond;
    cqweqasvfaCond               SetNextWindowContentSizeCond;
    cqweqasvfaCond               SetNextWindowCollapsedCond;
    ImRect                  SetNextWindowSizeConstraintRect;           // Valid if 'SetNextWindowSizeConstraint' is true
    cqweqasvfaSizeConstraintCallback SetNextWindowSizeConstraintCallback;
    void* SetNextWindowSizeConstraintCallbackUserData;
    bool                    SetNextWindowSizeConstraint;
    bool                    SetNextWindowFocus;
    bool                    SetNextTreeNodeOpenVal;
    cqweqasvfaCond               SetNextTreeNodeOpenCond;

    // Render
    ImDrawData              RenderDrawData;                     // Main ImDrawData instance to pass render information to the user
    ImVector<ImDrawList*>   RenderDrawLists[3];
    float                   ModalWindowDarkeningRatio;
    ImDrawList              OverlayDrawList;                    // Optional software render of mouse cursors, if io.MouseDrawCursor is set + a few debug overlays
    cqweqasvfaMouseCursor        MouseCursor;
    cqweqasvfaMouseCursorData    MouseCursorData[cqweqasvfaMouseCursor_Count_];

    // Drag and Drop
    bool                    DragDropActive;
    cqweqasvfaDragDropFlags      DragDropSourceFlags;
    int                     DragDropMouseButton;
    cqweqasvfaPayload            DragDropPayload;
    ImRect                  DragDropTargetRect;
    cqweqasvfaID                 DragDropTargetId;
    float                   DragDropAcceptIdCurrRectSurface;
    cqweqasvfaID                 DragDropAcceptIdCurr;               // Target item id (set at the time of accepting the payload)
    cqweqasvfaID                 DragDropAcceptIdPrev;               // Target item id from previous frame (we need to store this to allow for overlapping drag and drop targets)
    int                     DragDropAcceptFrameCount;           // Last time a target expressed a desire to accept the source
    ImVector<unsigned char> DragDropPayloadBufHeap;             // We don't expose the ImVector<> directly
    unsigned char           DragDropPayloadBufLocal[8];

    // Widget state
    cqweqasvfaTextEditState      InputTextState;
    ImFont                  InputTextPasswordFont;
    cqweqasvfaID                 ScalarAsInputTextId;                // Temporary text input when CTRL+clicking on a slider, etc.
    cqweqasvfaColorEditFlags     ColorEditOptions;                   // Store user options for color edit widgets
    ImVec4                  ColorPickerRef;
    float                   DragCurrentValue;                   // Currently dragged value, always float, not rounded by end-user precision settings
    ImVec2                  DragLastMouseDelta;
    float                   DragSpeedDefaultRatio;              // If speed == 0.0f, uses (max-min) * DragSpeedDefaultRatio
    float                   DragSpeedScaleSlow;
    float                   DragSpeedScaleFast;
    ImVec2                  ScrollbarClickDeltaToGrabCenter;    // Distance between mouse and center of grab box, normalized in parent space. Use storage?
    int                     TooltipOverrideCount;
    ImVector<char>          PrivateClipboard;                   // If no custom clipboard handler is defined
    ImVec2                  OsImePosRequest, OsImePosSet;       // Cursor position request & last passed to the OS Input Method Editor

    // Settings
    float                          SettingsDirtyTimer;          // Save .ini Settings on disk when time reaches zero
    ImVector<cqweqasvfaWindowSettings>  SettingsWindows;             // .ini settings for cqweqasvfaWindow
    ImVector<cqweqasvfaSettingsHandler> SettingsHandlers;            // List of .ini settings handlers

    // Logging
    bool                    LogEnabled;
    FILE* LogFile;                            // If != NULL log to stdout/ file
    cqweqasvfaTextBuffer* LogClipboard;                       // Else log to clipboard. This is pointer so our Gcqweqasvfa static constructor doesn't call heap allocators.
    int                     LogStartDepth;
    int                     LogAutoExpandMaxDepth;

    // Misc
    float                   FramerateSecPerFrame[120];          // calculate estimate of framerate for user
    int                     FramerateSecPerFrameIdx;
    float                   FramerateSecPerFrameAccum;
    int                     WantCaptureMouseNextFrame;          // explicit capture via CaptureInputs() sets those flags
    int                     WantCaptureKeyboardNextFrame;
    int                     WantTextInputNextFrame;
    char                    TempBuffer[1024 * 3 + 1];               // temporary text buffer

    cqweqasvfaContext() : OverlayDrawList(NULL)
    {
        Initialized = false;
        Font = NULL;
        FontSize = FontBaseSize = 0.0f;

        Time = 0.0f;
        FrameCount = 0;
        FrameCountEnded = FrameCountRendered = -1;
        WindowsActiveCount = 0;
        CurrentWindow = NULL;
        NavWindow = NULL;
        HoveredWindow = NULL;
        HoveredRootWindow = NULL;
        HoveredId = 0;
        HoveredIdAllowOverlap = false;
        HoveredIdPreviousFrame = 0;
        HoveredIdTimer = 0.0f;
        ActiveId = 0;
        ActiveIdPreviousFrame = 0;
        ActiveIdTimer = 0.0f;
        ActiveIdIsAlive = false;
        ActiveIdIsJustActivated = false;
        ActiveIdAllowOverlap = false;
        ActiveIdClickOffset = ImVec2(-1, -1);
        ActiveIdWindow = NULL;
        MovingWindow = NULL;
        MovingWindowMoveId = 0;

        SetNextWindowPosVal = ImVec2(0.0f, 0.0f);
        SetNextWindowSizeVal = ImVec2(0.0f, 0.0f);
        SetNextWindowCollapsedVal = false;
        SetNextWindowPosCond = 0;
        SetNextWindowSizeCond = 0;
        SetNextWindowContentSizeCond = 0;
        SetNextWindowCollapsedCond = 0;
        SetNextWindowSizeConstraintRect = ImRect();
        SetNextWindowSizeConstraintCallback = NULL;
        SetNextWindowSizeConstraintCallbackUserData = NULL;
        SetNextWindowSizeConstraint = false;
        SetNextWindowFocus = false;
        SetNextTreeNodeOpenVal = false;
        SetNextTreeNodeOpenCond = 0;

        DragDropActive = false;
        DragDropSourceFlags = 0;
        DragDropMouseButton = -1;
        DragDropTargetId = 0;
        DragDropAcceptIdPrev = DragDropAcceptIdCurr = 0;
        DragDropAcceptFrameCount = -1;
        memset(DragDropPayloadBufLocal, 0, sizeof(DragDropPayloadBufLocal));

        ScalarAsInputTextId = 0;
        ColorEditOptions = cqweqasvfaColorEditFlags__OptionsDefault;
        DragCurrentValue = 0.0f;
        DragLastMouseDelta = ImVec2(0.0f, 0.0f);
        DragSpeedDefaultRatio = 1.0f / 100.0f;
        DragSpeedScaleSlow = 1.0f / 100.0f;
        DragSpeedScaleFast = 10.0f;
        ScrollbarClickDeltaToGrabCenter = ImVec2(0.0f, 0.0f);
        TooltipOverrideCount = 0;
        OsImePosRequest = OsImePosSet = ImVec2(-1.0f, -1.0f);

        ModalWindowDarkeningRatio = 0.0f;
        OverlayDrawList._Data = &DrawListSharedData;
        OverlayDrawList._OwnerName = "##Overlay"; // Give it a name for debugging
        MouseCursor = cqweqasvfaMouseCursor_Arrow;
        memset(MouseCursorData, 0, sizeof(MouseCursorData));

        SettingsDirtyTimer = 0.0f;

        LogEnabled = false;
        LogFile = NULL;
        LogClipboard = NULL;
        LogStartDepth = 0;
        LogAutoExpandMaxDepth = 2;

        memset(FramerateSecPerFrame, 0, sizeof(FramerateSecPerFrame));
        FramerateSecPerFrameIdx = 0;
        FramerateSecPerFrameAccum = 0.0f;
        WantCaptureMouseNextFrame = WantCaptureKeyboardNextFrame = WantTextInputNextFrame = -1;
        memset(TempBuffer, 0, sizeof(TempBuffer));
    }
};

// Transient per-window flags, reset at the beginning of the frame. For child window, inherited from parent on first Begin().
enum cqweqasvfaItemFlags_
{
    cqweqasvfaItemFlags_AllowKeyboardFocus = 1 << 0,  // true
    cqweqasvfaItemFlags_ButtonRepeat = 1 << 1,  // false    // Button() will return true multiple times based on io.KeyRepeatDelay and io.KeyRepeatRate settings.
    cqweqasvfaItemFlags_Disabled = 1 << 2,  // false    // FIXME-WIP: Disable interactions but doesn't affect visuals. Should be: grey out and disable interactions with widgets that affect data + view widgets (WIP) 
    //cqweqasvfaItemFlags_NoNav                      = 1 << 3,  // false
    //cqweqasvfaItemFlags_NoNavDefaultFocus          = 1 << 4,  // false
    cqweqasvfaItemFlags_SelectableDontClosePopup = 1 << 5,  // false    // MenuItem/Selectable() automatically closes current Popup window
    cqweqasvfaItemFlags_Default_ = cqweqasvfaItemFlags_AllowKeyboardFocus
};

// Transient per-window data, reset at the beginning of the frame
// FIXME: That's theory, in practice the delimitation between cqweqasvfaWindow and cqweqasvfaDrawContext is quite tenuous and could be reconsidered.
struct cqweqasvfa_API cqweqasvfaDrawContext
{
    ImVec2                  CursorPos;
    ImVec2                  CursorPosPrevLine;
    ImVec2                  CursorStartPos;
    ImVec2                  CursorMaxPos;           // Used to implicitly calculate the size of our contents, always growing during the frame. Turned into window->SizeContents at the beginning of next frame
    float                   CurrentLineHeight;
    float                   CurrentLineTextBaseOffset;
    float                   PrevLineHeight;
    float                   PrevLineTextBaseOffset;
    float                   LogLinePosY;
    int                     TreeDepth;
    cqweqasvfaID                 LastItemId;
    ImRect                  LastItemRect;
    bool                    LastItemRectHoveredRect;
    bool                    MenuBarAppending;
    float                   MenuBarOffsetX;
    ImVector<cqweqasvfaWindow*>  ChildWindows;
    cqweqasvfaStorage* StateStorage;
    cqweqasvfaLayoutType         LayoutType;

    // We store the current settings outside of the vectors to increase memory locality (reduce cache misses). The vectors are rarely modified. Also it allows us to not heap allocate for short-lived windows which are not using those settings.
    cqweqasvfaItemFlags          ItemFlags;              // == ItemFlagsStack.back() [empty == cqweqasvfaItemFlags_Default]
    float                   ItemWidth;              // == ItemWidthStack.back(). 0.0: default, >0.0: width in pixels, <0.0: align xx pixels to the right of window
    float                   TextWrapPos;            // == TextWrapPosStack.back() [empty == -1.0f]
    ImVector<cqweqasvfaItemFlags>ItemFlagsStack;
    ImVector<float>         ItemWidthStack;
    ImVector<float>         TextWrapPosStack;
    ImVector<cqweqasvfaGroupData>GroupStack;
    int                     StackSizesBackup[6];    // Store size of various stacks for asserting

    float                   IndentX;                // Indentation / start position from left of window (increased by TreePush/TreePop, etc.)
    float                   GroupOffsetX;
    float                   ColumnsOffsetX;         // Offset to the current column (if ColumnsCurrent > 0). FIXME: This and the above should be a stack to allow use cases like Tree->Column->Tree. Need revamp columns API.
    cqweqasvfaColumnsSet* ColumnsSet;             // Current columns set

    cqweqasvfaDrawContext()
    {
        CursorPos = CursorPosPrevLine = CursorStartPos = CursorMaxPos = ImVec2(0.0f, 0.0f);
        CurrentLineHeight = PrevLineHeight = 0.0f;
        CurrentLineTextBaseOffset = PrevLineTextBaseOffset = 0.0f;
        LogLinePosY = -1.0f;
        TreeDepth = 0;
        LastItemId = 0;
        LastItemRect = ImRect();
        LastItemRectHoveredRect = false;
        MenuBarAppending = false;
        MenuBarOffsetX = 0.0f;
        StateStorage = NULL;
        LayoutType = cqweqasvfaLayoutType_Vertical;
        ItemWidth = 0.0f;
        ItemFlags = cqweqasvfaItemFlags_Default_;
        TextWrapPos = -1.0f;
        memset(StackSizesBackup, 0, sizeof(StackSizesBackup));

        IndentX = 0.0f;
        GroupOffsetX = 0.0f;
        ColumnsOffsetX = 0.0f;
        ColumnsSet = NULL;
    }
};

// Windows data
struct cqweqasvfa_API cqweqasvfaWindow
{
    char* Name;
    cqweqasvfaID                 ID;                                 // == ImHash(Name)
    cqweqasvfaWindowFlags        Flags;                              // See enum cqweqasvfaWindowFlags_
    ImVec2                  PosFloat;
    ImVec2                  Pos;                                // Position rounded-up to nearest pixel
    ImVec2                  Size;                               // Current size (==SizeFull or collapsed title bar size)
    ImVec2                  SizeFull;                           // Size when non collapsed
    ImVec2                  SizeFullAtLastBegin;                // Copy of SizeFull at the end of Begin. This is the reference value we'll use on the next frame to decide if we need scrollbars.
    ImVec2                  SizeContents;                       // Size of contents (== extents reach of the drawing cursor) from previous frame. Include decoration, window title, border, menu, etc.
    ImVec2                  SizeContentsExplicit;               // Size of contents explicitly set by the user via SetNextWindowContentSize()
    ImRect                  ContentsRegionRect;                 // Maximum visible content position in window coordinates. ~~ (SizeContentsExplicit ? SizeContentsExplicit : Size - ScrollbarSizes) - CursorStartPos, per axis
    ImVec2                  WindowPadding;                      // Window padding at the time of begin.
    float                   WindowRounding;                     // Window rounding at the time of begin.
    float                   WindowBorderSize;                   // Window border size at the time of begin.
    cqweqasvfaID                 MoveId;                             // == window->GetID("#MOVE")
    ImVec2                  Scroll;
    ImVec2                  ScrollTarget;                       // target scroll position. stored as cursor position with scrolling canceled out, so the highest point is always 0.0f. (FLT_MAX for no change)
    ImVec2                  ScrollTargetCenterRatio;            // 0.0f = scroll so that target position is at top, 0.5f = scroll so that target position is centered
    bool                    ScrollbarX, ScrollbarY;
    ImVec2                  ScrollbarSizes;
    bool                    Active;                             // Set to true on Begin()
    bool                    WasActive;
    bool                    WriteAccessed;                      // Set to true when any widget access the current window
    bool                    Collapsed;                          // Set when collapsing window to become only title-bar
    bool                    SkipItems;                          // Set when items can safely be all clipped (e.g. window not visible or collapsed)
    bool                    Appearing;                          // Set during the frame where the window is appearing (or re-appearing)
    bool                    CloseButton;                        // Set when the window has a close button (p_open != NULL)
    int                     BeginOrderWithinParent;             // Order within immediate parent window, if we are a child window. Otherwise 0.
    int                     BeginOrderWithinContext;            // Order within entire cqweqasvfa context. This is mostly used for debugging submission order related issues.
    int                     BeginCount;                         // Number of Begin() during the current frame (generally 0 or 1, 1+ if appending via multiple Begin/End pairs)
    cqweqasvfaID                 PopupId;                            // ID in the popup stack when this window is used as a popup/menu (because we use generic Name/ID for recycling)
    int                     AutoFitFramesX, AutoFitFramesY;
    bool                    AutoFitOnlyGrows;
    int                     AutoFitChildAxises;
    cqweqasvfaDir                AutoPosLastDirection;
    int                     HiddenFrames;
    cqweqasvfaCond               SetWindowPosAllowFlags;             // store condition flags for next SetWindowPos() call.
    cqweqasvfaCond               SetWindowSizeAllowFlags;            // store condition flags for next SetWindowSize() call.
    cqweqasvfaCond               SetWindowCollapsedAllowFlags;       // store condition flags for next SetWindowCollapsed() call.
    ImVec2                  SetWindowPosVal;                    // store window position when using a non-zero Pivot (position set needs to be processed when we know the window size)
    ImVec2                  SetWindowPosPivot;                  // store window pivot for positioning. ImVec2(0,0) when positioning from top-left corner; ImVec2(0.5f,0.5f) for centering; ImVec2(1,1) for bottom right.

    cqweqasvfaDrawContext        DC;                                 // Temporary per-window data, reset at the beginning of the frame
    ImVector<cqweqasvfaID>       IDStack;                            // ID stack. ID are hashes seeded with the value at the top of the stack
    ImRect                  ClipRect;                           // = DrawList->clip_rect_stack.back(). Scissoring / clipping rectangle. x1, y1, x2, y2.
    ImRect                  WindowRectClipped;                  // = WindowRect just after setup in Begin(). == window->Rect() for root window.
    ImRect                  InnerRect;
    int                     LastFrameActive;
    float                   ItemWidthDefault;
    cqweqasvfaSimpleColumns      MenuColumns;                        // Simplified columns storage for menu items
    cqweqasvfaStorage            StateStorage;
    ImVector<cqweqasvfaColumnsSet> ColumnsStorage;
    float                   FontWindowScale;                    // Scale multiplier per-window
    ImDrawList* DrawList;
    cqweqasvfaWindow* ParentWindow;                       // If we are a child _or_ popup window, this is pointing to our parent. Otherwise NULL.
    cqweqasvfaWindow* RootWindow;                         // Generally point to ourself. If we are a child window, this is pointing to the first non-child parent window.
    cqweqasvfaWindow* RootNonPopupWindow;                 // Generally point to ourself. Used to display TitleBgActive color and for selecting which window to use for NavWindowing

    // Navigation / Focus
    int                     FocusIdxAllCounter;                 // Start at -1 and increase as assigned via FocusItemRegister()
    int                     FocusIdxTabCounter;                 // (same, but only count widgets which you can Tab through)
    int                     FocusIdxAllRequestCurrent;          // Item being requested for focus
    int                     FocusIdxTabRequestCurrent;          // Tab-able item being requested for focus
    int                     FocusIdxAllRequestNext;             // Item being requested for focus, for next update (relies on layout to be stable between the frame pressing TAB and the next frame)
    int                     FocusIdxTabRequestNext;             // "

public:
    cqweqasvfaWindow(cqweqasvfaContext* context, const char* name);
    ~cqweqasvfaWindow();

    cqweqasvfaID     GetID(const char* str, const char* str_end = NULL);
    cqweqasvfaID     GetID(const void* ptr);
    cqweqasvfaID     GetIDNoKeepAlive(const char* str, const char* str_end = NULL);
    cqweqasvfaID     GetIDFromRectangle(const ImRect& r_abs);

    // We don't use g.FontSize because the window may be != g.CurrentWidow.
    ImRect      Rect() const { return ImRect(Pos.x, Pos.y, Pos.x + Size.x, Pos.y + Size.y); }
    float       CalcFontSize() const { return Gcqweqasvfa->FontBaseSize * FontWindowScale; }
    float       TitleBarHeight() const { return (Flags & cqweqasvfaWindowFlags_NoTitleBar) ? 0.0f : CalcFontSize() + Gcqweqasvfa->Style.FramePadding.y * 2.0f; }
    ImRect      TitleBarRect() const { return ImRect(Pos, ImVec2(Pos.x + SizeFull.x, Pos.y + TitleBarHeight())); }
    float       MenuBarHeight() const { return (Flags & cqweqasvfaWindowFlags_MenuBar) ? CalcFontSize() + Gcqweqasvfa->Style.FramePadding.y * 2.0f : 0.0f; }
    ImRect      MenuBarRect() const { float y1 = Pos.y + TitleBarHeight(); return ImRect(Pos.x, y1, Pos.x + SizeFull.x, y1 + MenuBarHeight()); }
};

// Backup and restore just enough data to be able to use IsItemHovered() on item A after another B in the same window has overwritten the data.  
struct cqweqasvfaItemHoveredDataBackup
{
    cqweqasvfaID     LastItemId;
    ImRect      LastItemRect;
    bool        LastItemRectHoveredRect;

    cqweqasvfaItemHoveredDataBackup() { Backup(); }
    void Backup() { cqweqasvfaWindow* window = Gcqweqasvfa->CurrentWindow; LastItemId = window->DC.LastItemId; LastItemRect = window->DC.LastItemRect; LastItemRectHoveredRect = window->DC.LastItemRectHoveredRect; }
    void Restore() const { cqweqasvfaWindow* window = Gcqweqasvfa->CurrentWindow; window->DC.LastItemId = LastItemId; window->DC.LastItemRect = LastItemRect; window->DC.LastItemRectHoveredRect = LastItemRectHoveredRect; }
};

//-----------------------------------------------------------------------------
// Internal API
// No guarantee of forward compatibility here.
//-----------------------------------------------------------------------------

namespace cqweqasvfa
{
    // We should always have a CurrentWindow in the stack (there is an implicit "Debug" window)
    // If this ever crash because g.CurrentWindow is NULL it means that either
    // - cqweqasvfa::NewFrame() has never been called, which is illegal.
    // - You are calling cqweqasvfa functions after cqweqasvfa::Render() and before the next cqweqasvfa::NewFrame(), which is also illegal.
    inline    cqweqasvfaWindow* GetCurrentWindowRead() { cqweqasvfaContext& g = *Gcqweqasvfa; return g.CurrentWindow; }
    inline    cqweqasvfaWindow* GetCurrentWindow() { cqweqasvfaContext& g = *Gcqweqasvfa; g.CurrentWindow->WriteAccessed = true; return g.CurrentWindow; }
    cqweqasvfa_API cqweqasvfaWindow* FindWindowByName(const char* name);
    cqweqasvfa_API void          FocusWindow(cqweqasvfaWindow* window);
    cqweqasvfa_API void          BringWindowToFront(cqweqasvfaWindow* window);
    cqweqasvfa_API void          BringWindowToBack(cqweqasvfaWindow* window);
    cqweqasvfa_API bool          IsWindowChildOf(cqweqasvfaWindow* window, cqweqasvfaWindow* potential_parent);

    cqweqasvfa_API void          Initialize();

    cqweqasvfa_API void                  MarkIniSettingsDirty();
    cqweqasvfa_API cqweqasvfaSettingsHandler* FindSettingsHandler(cqweqasvfaID type_id);
    cqweqasvfa_API cqweqasvfaWindowSettings* FindWindowSettings(cqweqasvfaID id);

    cqweqasvfa_API void          SetActiveID(cqweqasvfaID id, cqweqasvfaWindow* window);
    cqweqasvfa_API void          ClearActiveID();
    cqweqasvfa_API void          SetHoveredID(cqweqasvfaID id);
    cqweqasvfa_API void          KeepAliveID(cqweqasvfaID id);

    cqweqasvfa_API void          ItemSize(const ImVec2& size, float text_offset_y = 0.0f);
    cqweqasvfa_API void          ItemSize(const ImRect& bb, float text_offset_y = 0.0f);
    cqweqasvfa_API bool          ItemAdd(const ImRect& bb, cqweqasvfaID id);
    cqweqasvfa_API bool          ItemHoverable(const ImRect& bb, cqweqasvfaID id);
    cqweqasvfa_API bool          IsClippedEx(const ImRect& bb, cqweqasvfaID id, bool clip_even_when_logged);
    cqweqasvfa_API bool          FocusableItemRegister(cqweqasvfaWindow* window, cqweqasvfaID id, bool tab_stop = true);      // Return true if focus is requested
    cqweqasvfa_API void          FocusableItemUnregister(cqweqasvfaWindow* window);
    cqweqasvfa_API ImVec2        CalcItemSize(ImVec2 size, float default_x, float default_y);
    cqweqasvfa_API float         CalcWrapWidthForPos(const ImVec2& pos, float wrap_pos_x);
    cqweqasvfa_API void          PushMultiItemsWidths(int components, float width_full = 0.0f);
    cqweqasvfa_API void          PushItemFlag(cqweqasvfaItemFlags option, bool enabled);
    cqweqasvfa_API void          PopItemFlag();

    cqweqasvfa_API void          OpenPopupEx(cqweqasvfaID id, bool reopen_existing);
    cqweqasvfa_API void          ClosePopup(cqweqasvfaID id);
    cqweqasvfa_API bool          IsPopupOpen(cqweqasvfaID id);
    cqweqasvfa_API bool          BeginPopupEx(cqweqasvfaID id, cqweqasvfaWindowFlags extra_flags);
    cqweqasvfa_API void          BeginTooltipEx(cqweqasvfaWindowFlags extra_flags, bool override_previous_tooltip = true);

    cqweqasvfa_API int           CalcTypematicPressedRepeatAmount(float t, float t_prev, float repeat_delay, float repeat_rate);

    cqweqasvfa_API void          Scrollbar(cqweqasvfaLayoutType direction);
    cqweqasvfa_API void          VerticalSeparator();        // Vertical separator, for menu bars (use current line height). not exposed because it is misleading what it doesn't have an effect on regular layout.
    cqweqasvfa_API bool          SplitterBehavior(cqweqasvfaID id, const ImRect& bb, cqweqasvfaAxis axis, float* size1, float* size2, float min_size1, float min_size2, float hover_extend = 0.0f);

    cqweqasvfa_API bool          BeginDragDropTargetCustom(const ImRect& bb, cqweqasvfaID id);
    cqweqasvfa_API void          ClearDragDrop();
    cqweqasvfa_API bool          IsDragDropPayloadBeingAccepted();

    // FIXME-WIP: New Columns API
    cqweqasvfa_API void          BeginColumns(const char* str_id, int count, cqweqasvfaColumnsFlags flags = 0); // setup number of columns. use an identifier to distinguish multiple column sets. close with EndColumns().
    cqweqasvfa_API void          EndColumns();                                                             // close columns
    cqweqasvfa_API void          PushColumnClipRect(int column_index = -1);

    // NB: All position are in absolute pixels coordinates (never using window coordinates internally)
    // AVOID USING OUTSIDE OF cqweqasvfa.CPP! NOT FOR PUBLIC CONSUMPTION. THOSE FUNCTIONS ARE A MESS. THEIR SIGNATURE AND BEHAVIOR WILL CHANGE, THEY NEED TO BE REFACTORED INTO SOMETHING DECENT.
    cqweqasvfa_API void          RenderText(ImVec2 pos, const char* text, const char* text_end = NULL, bool hide_text_after_hash = true);
    cqweqasvfa_API void          RenderTextWrapped(ImVec2 pos, const char* text, const char* text_end, float wrap_width);
    cqweqasvfa_API void          RenderTextClipped(const ImVec2& pos_min, const ImVec2& pos_max, const char* text, const char* text_end, const ImVec2* text_size_if_known, const ImVec2& align = ImVec2(0, 0), const ImRect* clip_rect = NULL);
    cqweqasvfa_API void          RenderFrame(ImVec2 p_min, ImVec2 p_max, ImU32 fill_col, bool border = true, float rounding = 0.0f);
    cqweqasvfa_API void          RenderFrameBorder(ImVec2 p_min, ImVec2 p_max, float rounding = 0.0f);
    cqweqasvfa_API void          RenderColorRectWithAlphaCheckerboard(ImVec2 p_min, ImVec2 p_max, ImU32 fill_col, float grid_step, ImVec2 grid_off, float rounding = 0.0f, int rounding_corners_flags = ~0);
    cqweqasvfa_API void          RenderTriangle(ImVec2 pos, cqweqasvfaDir dir, float scale = 1.0f);
    cqweqasvfa_API void          RenderBullet(ImVec2 pos);
    cqweqasvfa_API void          RenderCheckMark(ImVec2 pos, ImU32 col, float sz);
    cqweqasvfa_API void          RenderRectFilledRangeH(ImDrawList* draw_list, const ImRect& rect, ImU32 col, float x_start_norm, float x_end_norm, float rounding);
    cqweqasvfa_API const char* FindRenderedTextEnd(const char* text, const char* text_end = NULL); // Find the optional ## from which we stop displaying text.

    cqweqasvfa_API bool          ButtonBehavior(const ImRect& bb, cqweqasvfaID id, bool* out_hovered, bool* out_held, cqweqasvfaButtonFlags flags = 0);
    cqweqasvfa_API bool          ButtonEx(const char* label, const ImVec2& size_arg = ImVec2(0, 0), cqweqasvfaButtonFlags flags = 0);
    cqweqasvfa_API bool          CloseButton(cqweqasvfaID id, const ImVec2& pos, float radius);
    cqweqasvfa_API bool          ArrowButton(cqweqasvfaID id, cqweqasvfaDir dir, ImVec2 padding, cqweqasvfaButtonFlags flags = 0);

    cqweqasvfa_API bool          SliderBehavior(const ImRect& frame_bb, cqweqasvfaID id, float* v, float v_min, float v_max, float power, int decimal_precision, cqweqasvfaSliderFlags flags = 0);
    cqweqasvfa_API bool          SliderFloatN(const char* label, float* v, int components, float v_min, float v_max, const char* display_format, float power);
    cqweqasvfa_API bool          SliderIntN(const char* label, int* v, int components, int v_min, int v_max, const char* display_format);

    cqweqasvfa_API bool          DragBehavior(const ImRect& frame_bb, cqweqasvfaID id, float* v, float v_speed, float v_min, float v_max, int decimal_precision, float power);
    cqweqasvfa_API bool          DragFloatN(const char* label, float* v, int components, float v_speed, float v_min, float v_max, const char* display_format, float power);
    cqweqasvfa_API bool          DragIntN(const char* label, int* v, int components, float v_speed, int v_min, int v_max, const char* display_format);

    cqweqasvfa_API bool          InputTextEx(const char* label, char* buf, int buf_size, const ImVec2& size_arg, cqweqasvfaInputTextFlags flags, cqweqasvfaTextEditCallback callback = NULL, void* user_data = NULL);
    cqweqasvfa_API bool          InputFloatN(const char* label, float* v, int components, int decimal_precision, cqweqasvfaInputTextFlags extra_flags);
    cqweqasvfa_API bool          InputIntN(const char* label, int* v, int components, cqweqasvfaInputTextFlags extra_flags);
    cqweqasvfa_API bool          InputScalarEx(const char* label, cqweqasvfaDataType data_type, void* data_ptr, void* step_ptr, void* step_fast_ptr, const char* scalar_format, cqweqasvfaInputTextFlags extra_flags);
    cqweqasvfa_API bool          InputScalarAsWidgetReplacement(const ImRect& aabb, const char* label, cqweqasvfaDataType data_type, void* data_ptr, cqweqasvfaID id, int decimal_precision);

    cqweqasvfa_API void          ColorTooltip(const char* text, const float* col, cqweqasvfaColorEditFlags flags);
    cqweqasvfa_API void          ColorEditOptionsPopup(const float* col, cqweqasvfaColorEditFlags flags);

    cqweqasvfa_API bool          TreeNodeBehavior(cqweqasvfaID id, cqweqasvfaTreeNodeFlags flags, const char* label, const char* label_end = NULL);
    cqweqasvfa_API bool          TreeNodeBehaviorIsOpen(cqweqasvfaID id, cqweqasvfaTreeNodeFlags flags = 0);                     // Consume previous SetNextTreeNodeOpened() data, if any. May return true when logging
    cqweqasvfa_API void          TreePushRawID(cqweqasvfaID id);

    cqweqasvfa_API void          PlotEx(cqweqasvfaPlotType plot_type, const char* label, float (*values_getter)(void* data, int idx), void* data, int values_count, int values_offset, const char* overlay_text, float scale_min, float scale_max, ImVec2 graph_size);

    cqweqasvfa_API int           ParseFormatPrecision(const char* fmt, int default_value);
    cqweqasvfa_API float         RoundScalar(float value, int decimal_precision);

    // Shade functions
    cqweqasvfa_API void          ShadeVertsLinearColorGradientKeepAlpha(ImDrawVert* vert_start, ImDrawVert* vert_end, ImVec2 gradient_p0, ImVec2 gradient_p1, ImU32 col0, ImU32 col1);
    cqweqasvfa_API void          ShadeVertsLinearAlphaGradientForLeftToRightText(ImDrawVert* vert_start, ImDrawVert* vert_end, float gradient_p0_x, float gradient_p1_x);
    cqweqasvfa_API void          ShadeVertsLinearUV(ImDrawVert* vert_start, ImDrawVert* vert_end, const ImVec2& a, const ImVec2& b, const ImVec2& uv_a, const ImVec2& uv_b, bool clamp);

} // namespace cqweqasvfa

// ImFontAtlas internals
cqweqasvfa_API bool              ImFontAtlasBuildWithStbTruetype(ImFontAtlas* atlas);
cqweqasvfa_API void              ImFontAtlasBuildRegisterDefaultCustomRects(ImFontAtlas* atlas);
cqweqasvfa_API void              ImFontAtlasBuildSetupFont(ImFontAtlas* atlas, ImFont* font, ImFontConfig* font_config, float ascent, float descent);
cqweqasvfa_API void              ImFontAtlasBuildPackCustomRects(ImFontAtlas* atlas, void* spc);
cqweqasvfa_API void              ImFontAtlasBuildFinish(ImFontAtlas* atlas);
cqweqasvfa_API void              ImFontAtlasBuildMultiplyCalcLookupTable(unsigned char out_table[256], float in_multiply_factor);
cqweqasvfa_API void              ImFontAtlasBuildMultiplyRectAlpha8(const unsigned char table[256], unsigned char* pixels, int x, int y, int w, int h, int stride);

#ifdef __clang__
#pragma clang diagnostic pop
#endif

#ifdef _MSC_VER
#pragma warning (pop)
#endif
