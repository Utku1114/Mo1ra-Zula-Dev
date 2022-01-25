// dear cqweqasvfa, v1.53
// (headers)

// See cqweqasvfa.cpp file for documentation.
// Call and read cqweqasvfa::ShowDemoWindow() in cqweqasvfa_demo.cpp for demo code.
// Read 'Programmer guide' in cqweqasvfa.cpp for notes on how to setup cqweqasvfa in your codebase.
// Get latest version at https://github.com/ocornut/cqweqasvfa

#pragma once

#include <float.h>          // FLT_MAX
#include <stdarg.h>         // va_list
#include <stddef.h>         // ptrdiff_t, NULL
#include <string.h>         // memset, memmove, memcpy, strlen, strchr, strcpy, strcmp

#define cqweqasvfa_VERSION       "1.53"

// Define attributes of all API symbols declarations, e.g. for DLL under Windows.
#ifndef cqweqasvfa_API
#define cqweqasvfa_API
#endif

// Define assertion handler.
#ifndef IM_ASSERT
#include <assert.h>
#define IM_ASSERT(_EXPR)    assert(_EXPR)
#endif

// Helpers
// Some compilers support applying printf-style warnings to user functions.
#if defined(__clang__) || defined(__GNUC__)
#define IM_FMTARGS(FMT)             __attribute__((format(printf, FMT, FMT+1)))
#define IM_FMTLIST(FMT)             __attribute__((format(printf, FMT, 0)))
#else
#define IM_FMTARGS(FMT)
#define IM_FMTLIST(FMT)
#endif
#define IM_ARRAYSIZE(_ARR)          ((int)(sizeof(_ARR)/sizeof(*_ARR)))

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wold-style-cast"
#endif

// Forward declarations
struct ImDrawChannel;               // Temporary storage for outputting drawing commands out of order, used by ImDrawList::ChannelsSplit()
struct ImDrawCmd;                   // A single draw command within a parent ImDrawList (generally maps to 1 GPU draw call)
struct ImDrawData;                  // All draw command lists required to render the frame
struct ImDrawList;                  // A single draw command list (generally one per window)
struct ImDrawListSharedData;        // Data shared among multiple draw lists (typically owned by parent cqweqasvfa context, but you may create one yourself)
struct ImDrawVert;                  // A single vertex (20 bytes by default, override layout with cqweqasvfa_OVERRIDE_DRAWVERT_STRUCT_LAYOUT)
struct ImFont;                      // Runtime data for a single font within a parent ImFontAtlas
struct ImFontAtlas;                 // Runtime data for multiple fonts, bake multiple fonts into a single texture, TTF/OTF font loader
struct ImFontConfig;                // Configuration data when adding a font or merging fonts
struct ImColor;                     // Helper functions to create a color that can be converted to either u32 or float4
struct cqweqasvfaIO;                     // Main configuration and I/O between your application and cqweqasvfa
struct cqweqasvfaOnceUponAFrame;         // Simple helper for running a block of code not more than once a frame, used by cqweqasvfa_ONCE_UPON_A_FRAME macro
struct cqweqasvfaStorage;                // Simple custom key value storage
struct cqweqasvfaStyle;                  // Runtime data for styling/colors
struct cqweqasvfaTextFilter;             // Parse and apply text filters. In format "aaaaa[,bbbb][,ccccc]"
struct cqweqasvfaTextBuffer;             // Text buffer for logging/accumulating text
struct cqweqasvfaTextEditCallbackData;   // Shared state of cqweqasvfa::InputText() when using custom cqweqasvfaTextEditCallback (rare/advanced use)
struct cqweqasvfaSizeConstraintCallbackData;// Structure used to constraint window size in custom ways when using custom cqweqasvfaSizeConstraintCallback (rare/advanced use)
struct cqweqasvfaListClipper;            // Helper to manually clip large list of items
struct cqweqasvfaPayload;                // User data payload for drag and drop operations
struct cqweqasvfaContext;                // cqweqasvfa context (opaque)

// Typedefs and Enumerations (declared as int for compatibility and to not pollute the top of this file)
typedef unsigned int ImU32;         // 32-bit unsigned integer (typically used to store packed colors)
typedef unsigned int cqweqasvfaID;       // unique ID used by widgets (typically hashed from a stack of string)
typedef unsigned short ImWchar;     // character for keyboard input/display
typedef void* ImTextureID;          // user data to identify a texture (this is whatever to you want it to be! read the FAQ about ImTextureID in cqweqasvfa.cpp)
typedef int cqweqasvfaCol;               // enum: a color identifier for styling     // enum cqweqasvfaCol_
typedef int cqweqasvfaCond;              // enum: a condition for Set*()             // enum cqweqasvfaCond_
typedef int cqweqasvfaKey;               // enum: a key identifier (cqweqasvfa-side enum) // enum cqweqasvfaKey_
typedef int cqweqasvfaMouseCursor;       // enum: a mouse cursor identifier          // enum cqweqasvfaMouseCursor_
typedef int cqweqasvfaStyleVar;          // enum: a variable identifier for styling  // enum cqweqasvfaStyleVar_
typedef int ImDrawCornerFlags;      // flags: for ImDrawList::AddRect*() etc.   // enum ImDrawCornerFlags_
typedef int ImDrawListFlags;        // flags: for ImDrawList                    // enum ImDrawListFlags_
typedef int cqweqasvfaColorEditFlags;    // flags: for ColorEdit*(), ColorPicker*()  // enum cqweqasvfaColorEditFlags_
typedef int cqweqasvfaColumnsFlags;      // flags: for *Columns*()                   // enum cqweqasvfaColumnsFlags_
typedef int cqweqasvfaDragDropFlags;     // flags: for *DragDrop*()                  // enum cqweqasvfaDragDropFlags_
typedef int cqweqasvfaComboFlags;        // flags: for BeginCombo()                  // enum cqweqasvfaComboFlags_
typedef int cqweqasvfaFocusedFlags;      // flags: for IsWindowFocused()             // enum cqweqasvfaFocusedFlags_
typedef int cqweqasvfaHoveredFlags;      // flags: for IsItemHovered() etc.          // enum cqweqasvfaHoveredFlags_
typedef int cqweqasvfaInputTextFlags;    // flags: for InputText*()                  // enum cqweqasvfaInputTextFlags_
typedef int cqweqasvfaSelectableFlags;   // flags: for Selectable()                  // enum cqweqasvfaSelectableFlags_
typedef int cqweqasvfaTreeNodeFlags;     // flags: for TreeNode*(),CollapsingHeader()// enum cqweqasvfaTreeNodeFlags_
typedef int cqweqasvfaWindowFlags;       // flags: for Begin*()                      // enum cqweqasvfaWindowFlags_
typedef int (*cqweqasvfaTextEditCallback)(cqweqasvfaTextEditCallbackData* data);
typedef void (*cqweqasvfaSizeConstraintCallback)(cqweqasvfaSizeConstraintCallbackData* data);
#if defined(_MSC_VER) && !defined(__clang__)
typedef unsigned __int64 ImU64;     // 64-bit unsigned integer
#else
typedef unsigned long long ImU64;   // 64-bit unsigned integer
#endif 

// Others helpers at bottom of the file:
// class ImVector<>                 // Lightweight std::vector like class.
// cqweqasvfa_ONCE_UPON_A_FRAME          // Execute a block of code once per frame only (convenient for creating UI within deep-nested code that runs multiple times)

struct ImVec2
{
    float x, y;
    ImVec2() { x = y = 0.0f; }
    ImVec2(float _x, float _y) { x = _x; y = _y; }
#ifdef IM_VEC2_CLASS_EXTRA          // Define constructor and implicit cast operators in imconfig.h to convert back<>forth from your math types and ImVec2.
    IM_VEC2_CLASS_EXTRA
#endif
};

struct ImVec4
{
    float x, y, z, w;
    ImVec4() { x = y = z = w = 0.0f; }
    ImVec4(float _x, float _y, float _z, float _w) { x = _x; y = _y; z = _z; w = _w; }
#ifdef IM_VEC4_CLASS_EXTRA          // Define constructor and implicit cast operators in imconfig.h to convert back<>forth from your math types and ImVec4.
    IM_VEC4_CLASS_EXTRA
#endif
};

// cqweqasvfa end-user API
// In a namespace so that user can add extra functions in a separate file (e.g. Value() helpers for your vector or common types)
namespace cqweqasvfa
{
    // Main
    cqweqasvfa_API cqweqasvfaIO& GetIO();
    cqweqasvfa_API cqweqasvfaStyle& GetStyle();
    cqweqasvfa_API ImDrawData* GetDrawData();                              // same value as passed to your io.RenderDrawListsFn() function. valid after Render() and until the next call to NewFrame()
    cqweqasvfa_API void          NewFrame();                                 // start a new cqweqasvfa frame, you can submit any command from this point until Render()/EndFrame().
    cqweqasvfa_API void          Render();                                   // ends the cqweqasvfa frame, finalize the draw data, then call your io.RenderDrawListsFn() function if set.
    cqweqasvfa_API void          EndFrame();                                 // ends the cqweqasvfa frame. automatically called by Render(), so most likely don't need to ever call that yourself directly. If you don't need to render you may call EndFrame() but you'll have wasted CPU already. If you don't need to render, better to not create any cqweqasvfa windows instead!
    cqweqasvfa_API void          Shutdown();

    // Demo, Debug, Informations
    cqweqasvfa_API void          ShowDemoWindow(bool* p_open = NULL);        // create demo/test window (previously called ShowTestWindow). demonstrate most cqweqasvfa features. call this to learn about the library! try to make it always available in your application!
    cqweqasvfa_API void          ShowMetricsWindow(bool* p_open = NULL);     // create metrics window. display cqweqasvfa internals: draw commands (with individual draw calls and vertices), window list, basic internal state, etc.
    cqweqasvfa_API void          ShowStyleEditor(cqweqasvfaStyle* ref = NULL);    // add style editor block (not a window). you can pass in a reference cqweqasvfaStyle structure to compare to, revert to and save to (else it uses the default style)
    cqweqasvfa_API bool          ShowStyleSelector(const char* label);
    cqweqasvfa_API void          ShowFontSelector(const char* label);
    cqweqasvfa_API void          ShowUserGuide();                            // add basic help/info block (not a window): how to manipulate cqweqasvfa as a end-user (mouse/keyboard controls).

    // Window
    cqweqasvfa_API bool          Begin(const char* name, bool* p_open = NULL, cqweqasvfaWindowFlags flags = 0);                                                   // push window to the stack and start appending to it. see .cpp for details. return false when window is collapsed, so you can early out in your code. 'bool* p_open' creates a widget on the upper-right to close the window (which sets your bool to false).
    cqweqasvfa_API void          End();                                                                                                                      // finish appending to current window, pop it off the window stack.
    cqweqasvfa_API bool          BeginChild(const char* str_id, const ImVec2& size = ImVec2(0, 0), bool border = false, cqweqasvfaWindowFlags extra_flags = 0);    // begin a scrolling region. size==0.0f: use remaining window size, size<0.0f: use remaining window size minus abs(size). size>0.0f: fixed size. each axis can use a different mode, e.g. ImVec2(0,400).
    cqweqasvfa_API bool          BeginChild(cqweqasvfaID id, const ImVec2& size = ImVec2(0, 0), bool border = false, cqweqasvfaWindowFlags extra_flags = 0);            // "
    cqweqasvfa_API void          EndChild();
    cqweqasvfa_API ImVec2        GetContentRegionMax();                                              // current content boundaries (typically window boundaries including scrolling, or current column boundaries), in windows coordinates
    cqweqasvfa_API ImVec2        GetContentRegionAvail();                                            // == GetContentRegionMax() - GetCursorPos()
    cqweqasvfa_API float         GetContentRegionAvailWidth();                                       //
    cqweqasvfa_API ImVec2        GetWindowContentRegionMin();                                        // content boundaries min (roughly (0,0)-Scroll), in window coordinates
    cqweqasvfa_API ImVec2        GetWindowContentRegionMax();                                        // content boundaries max (roughly (0,0)+Size-Scroll) where Size can be override with SetNextWindowContentSize(), in window coordinates
    cqweqasvfa_API float         GetWindowContentRegionWidth();                                      //
    cqweqasvfa_API ImDrawList* GetWindowDrawList();                                                // get rendering command-list if you want to append your own draw primitives
    cqweqasvfa_API ImVec2        GetWindowPos();                                                     // get current window position in screen space (useful if you want to do your own drawing via the DrawList api)
    cqweqasvfa_API ImVec2        GetWindowSize();                                                    // get current window size
    cqweqasvfa_API float         GetWindowWidth();
    cqweqasvfa_API float         GetWindowHeight();
    cqweqasvfa_API bool          IsWindowCollapsed();
    cqweqasvfa_API bool          IsWindowAppearing();
    cqweqasvfa_API void          SetWindowFontScale(float scale);                                    // per-window font scale. Adjust IO.FontGlobalScale if you want to scale all windows

    cqweqasvfa_API void          SetNextWindowPos(const ImVec2& pos, cqweqasvfaCond cond = 0, const ImVec2& pivot = ImVec2(0, 0)); // set next window position. call before Begin(). use pivot=(0.5f,0.5f) to center on given point, etc.
    cqweqasvfa_API void          SetNextWindowSize(const ImVec2& size, cqweqasvfaCond cond = 0);          // set next window size. set axis to 0.0f to force an auto-fit on this axis. call before Begin()
    cqweqasvfa_API void          SetNextWindowSizeConstraints(const ImVec2& size_min, const ImVec2& size_max, cqweqasvfaSizeConstraintCallback custom_callback = NULL, void* custom_callback_data = NULL); // set next window size limits. use -1,-1 on either X/Y axis to preserve the current size. Use callback to apply non-trivial programmatic constraints.
    cqweqasvfa_API void          SetNextWindowContentSize(const ImVec2& size);                       // set next window content size (~ enforce the range of scrollbars). not including window decorations (title bar, menu bar, etc.). set an axis to 0.0f to leave it automatic. call before Begin()
    cqweqasvfa_API void          SetNextWindowCollapsed(bool collapsed, cqweqasvfaCond cond = 0);         // set next window collapsed state. call before Begin()
    cqweqasvfa_API void          SetNextWindowFocus();                                               // set next window to be focused / front-most. call before Begin()
    cqweqasvfa_API void          SetWindowPos(const ImVec2& pos, cqweqasvfaCond cond = 0);                // (not recommended) set current window position - call within Begin()/End(). prefer using SetNextWindowPos(), as this may incur tearing and side-effects.
    cqweqasvfa_API void          SetWindowSize(const ImVec2& size, cqweqasvfaCond cond = 0);              // (not recommended) set current window size - call within Begin()/End(). set to ImVec2(0,0) to force an auto-fit. prefer using SetNextWindowSize(), as this may incur tearing and minor side-effects.    
    cqweqasvfa_API void          SetWindowCollapsed(bool collapsed, cqweqasvfaCond cond = 0);             // (not recommended) set current window collapsed state. prefer using SetNextWindowCollapsed().
    cqweqasvfa_API void          SetWindowFocus();                                                   // (not recommended) set current window to be focused / front-most. prefer using SetNextWindowFocus().
    cqweqasvfa_API void          SetWindowPos(const char* name, const ImVec2& pos, cqweqasvfaCond cond = 0);      // set named window position.
    cqweqasvfa_API void          SetWindowSize(const char* name, const ImVec2& size, cqweqasvfaCond cond = 0);    // set named window size. set axis to 0.0f to force an auto-fit on this axis.
    cqweqasvfa_API void          SetWindowCollapsed(const char* name, bool collapsed, cqweqasvfaCond cond = 0);   // set named window collapsed state
    cqweqasvfa_API void          SetWindowFocus(const char* name);                                           // set named window to be focused / front-most. use NULL to remove focus.

    cqweqasvfa_API float         GetScrollX();                                                       // get scrolling amount [0..GetScrollMaxX()]
    cqweqasvfa_API float         GetScrollY();                                                       // get scrolling amount [0..GetScrollMaxY()]
    cqweqasvfa_API float         GetScrollMaxX();                                                    // get maximum scrolling amount ~~ ContentSize.X - WindowSize.X
    cqweqasvfa_API float         GetScrollMaxY();                                                    // get maximum scrolling amount ~~ ContentSize.Y - WindowSize.Y
    cqweqasvfa_API void          SetScrollX(float scroll_x);                                         // set scrolling amount [0..GetScrollMaxX()]
    cqweqasvfa_API void          SetScrollY(float scroll_y);                                         // set scrolling amount [0..GetScrollMaxY()]
    cqweqasvfa_API void          SetScrollHere(float center_y_ratio = 0.5f);                         // adjust scrolling amount to make current cursor position visible. center_y_ratio=0.0: top, 0.5: center, 1.0: bottom. When using to make a "default/current item" visible, consider using SetItemDefaultFocus() instead.
    cqweqasvfa_API void          SetScrollFromPosY(float pos_y, float center_y_ratio = 0.5f);        // adjust scrolling amount to make given position valid. use GetCursorPos() or GetCursorStartPos()+offset to get valid positions.
    cqweqasvfa_API void          SetStateStorage(cqweqasvfaStorage* tree);                                // replace tree state storage with our own (if you want to manipulate it yourself, typically clear subsection of it)
    cqweqasvfa_API cqweqasvfaStorage* GetStateStorage();

    // Parameters stacks (shared)
    cqweqasvfa_API void          PushFont(ImFont* font);                                             // use NULL as a shortcut to push default font
    cqweqasvfa_API void          PopFont();
    cqweqasvfa_API void          PushStyleColor(cqweqasvfaCol idx, ImU32 col);
    cqweqasvfa_API void          PushStyleColor(cqweqasvfaCol idx, const ImVec4& col);
    cqweqasvfa_API void          PopStyleColor(int count = 1);
    cqweqasvfa_API void          PushStyleVar(cqweqasvfaStyleVar idx, float val);
    cqweqasvfa_API void          PushStyleVar(cqweqasvfaStyleVar idx, const ImVec2& val);
    cqweqasvfa_API void          PopStyleVar(int count = 1);
    cqweqasvfa_API const ImVec4& GetStyleColorVec4(cqweqasvfaCol idx);                                    // retrieve style color as stored in cqweqasvfaStyle structure. use to feed back into PushStyleColor(), otherwhise use GetColorU32() to get style color + style alpha.
    cqweqasvfa_API ImFont* GetFont();                                                          // get current font
    cqweqasvfa_API float         GetFontSize();                                                      // get current font size (= height in pixels) of current font with current scale applied
    cqweqasvfa_API ImVec2        GetFontTexUvWhitePixel();                                           // get UV coordinate for a while pixel, useful to draw custom shapes via the ImDrawList API
    cqweqasvfa_API ImU32         GetColorU32(cqweqasvfaCol idx, float alpha_mul = 1.0f);                  // retrieve given style color with style alpha applied and optional extra alpha multiplier
    cqweqasvfa_API ImU32         GetColorU32(const ImVec4& col);                                     // retrieve given color with style alpha applied
    cqweqasvfa_API ImU32         GetColorU32(ImU32 col);                                             // retrieve given color with style alpha applied

    // Parameters stacks (current window)
    cqweqasvfa_API void          PushItemWidth(float item_width);                                    // width of items for the common item+label case, pixels. 0.0f = default to ~2/3 of windows width, >0.0f: width in pixels, <0.0f align xx pixels to the right of window (so -1.0f always align width to the right side)
    cqweqasvfa_API void          PopItemWidth();
    cqweqasvfa_API float         CalcItemWidth();                                                    // width of item given pushed settings and current cursor position
    cqweqasvfa_API void          PushTextWrapPos(float wrap_pos_x = 0.0f);                           // word-wrapping for Text*() commands. < 0.0f: no wrapping; 0.0f: wrap to end of window (or column); > 0.0f: wrap at 'wrap_pos_x' position in window local space
    cqweqasvfa_API void          PopTextWrapPos();
    cqweqasvfa_API void          PushAllowKeyboardFocus(bool allow_keyboard_focus);                  // allow focusing using TAB/Shift-TAB, enabled by default but you can disable it for certain widgets
    cqweqasvfa_API void          PopAllowKeyboardFocus();
    cqweqasvfa_API void          PushButtonRepeat(bool repeat);                                      // in 'repeat' mode, Button*() functions return repeated true in a typematic manner (using io.KeyRepeatDelay/io.KeyRepeatRate setting). Note that you can call IsItemActive() after any Button() to tell if the button is held in the current frame.
    cqweqasvfa_API void          PopButtonRepeat();

    // Cursor / Layout
    cqweqasvfa_API void          Separator();                                                        // separator, generally horizontal. inside a menu bar or in horizontal layout mode, this becomes a vertical separator.
    cqweqasvfa_API void          SameLine(float pos_x = 0.0f, float spacing_w = -1.0f);              // call between widgets or groups to layout them horizontally
    cqweqasvfa_API void          NewLine();                                                          // undo a SameLine()
    cqweqasvfa_API void          Spacing();                                                          // add vertical spacing
    cqweqasvfa_API void          Dummy(const ImVec2& size);                                          // add a dummy item of given size
    cqweqasvfa_API void          Indent(float indent_w = 0.0f);                                      // move content position toward the right, by style.IndentSpacing or indent_w if != 0
    cqweqasvfa_API void          Unindent(float indent_w = 0.0f);                                    // move content position back to the left, by style.IndentSpacing or indent_w if != 0
    cqweqasvfa_API void          BeginGroup();                                                       // lock horizontal starting position + capture group bounding box into one "item" (so you can use IsItemHovered() or layout primitives such as SameLine() on whole group, etc.)
    cqweqasvfa_API void          EndGroup();
    cqweqasvfa_API ImVec2        GetCursorPos();                                                     // cursor position is relative to window position
    cqweqasvfa_API float         GetCursorPosX();                                                    // "
    cqweqasvfa_API float         GetCursorPosY();                                                    // "
    cqweqasvfa_API void          SetCursorPos(const ImVec2& local_pos);                              // "
    cqweqasvfa_API void          SetCursorPosX(float x);                                             // "
    cqweqasvfa_API void          SetCursorPosY(float y);                                             // "
    cqweqasvfa_API ImVec2        GetCursorStartPos();                                                // initial cursor position
    cqweqasvfa_API ImVec2        GetCursorScreenPos();                                               // cursor position in absolute screen coordinates [0..io.DisplaySize] (useful to work with ImDrawList API)
    cqweqasvfa_API void          SetCursorScreenPos(const ImVec2& pos);                              // cursor position in absolute screen coordinates [0..io.DisplaySize]
    cqweqasvfa_API void          AlignTextToFramePadding();                                          // vertically align/lower upcoming text to FramePadding.y so that it will aligns to upcoming widgets (call if you have text on a line before regular widgets)
    cqweqasvfa_API float         GetTextLineHeight();                                                // ~ FontSize
    cqweqasvfa_API float         GetTextLineHeightWithSpacing();                                     // ~ FontSize + style.ItemSpacing.y (distance in pixels between 2 consecutive lines of text)
    cqweqasvfa_API float         GetFrameHeight();                                                   // ~ FontSize + style.FramePadding.y * 2
    cqweqasvfa_API float         GetFrameHeightWithSpacing();                                        // ~ FontSize + style.FramePadding.y * 2 + style.ItemSpacing.y (distance in pixels between 2 consecutive lines of framed widgets)

    // Columns
    // You can also use SameLine(pos_x) for simplified columns. The columns API is still work-in-progress and rather lacking.
    cqweqasvfa_API void          Columns(int count = 1, const char* id = NULL, bool border = true);
    cqweqasvfa_API void          NextColumn();                                                       // next column, defaults to current row or next row if the current row is finished
    cqweqasvfa_API int           GetColumnIndex();                                                   // get current column index
    cqweqasvfa_API float         GetColumnWidth(int column_index = -1);                              // get column width (in pixels). pass -1 to use current column
    cqweqasvfa_API void          SetColumnWidth(int column_index, float width);                      // set column width (in pixels). pass -1 to use current column
    cqweqasvfa_API float         GetColumnOffset(int column_index = -1);                             // get position of column line (in pixels, from the left side of the contents region). pass -1 to use current column, otherwise 0..GetColumnsCount() inclusive. column 0 is typically 0.0f
    cqweqasvfa_API void          SetColumnOffset(int column_index, float offset_x);                  // set position of column line (in pixels, from the left side of the contents region). pass -1 to use current column
    cqweqasvfa_API int           GetColumnsCount();

    // ID scopes
    // If you are creating widgets in a loop you most likely want to push a unique identifier (e.g. object pointer, loop index) so cqweqasvfa can differentiate them.
    // You can also use the "##foobar" syntax within widget label to distinguish them from each others. Read "A primer on the use of labels/IDs" in the FAQ for more details.
    cqweqasvfa_API void          PushID(const char* str_id);                                         // push identifier into the ID stack. IDs are hash of the entire stack!
    cqweqasvfa_API void          PushID(const char* str_id_begin, const char* str_id_end);
    cqweqasvfa_API void          PushID(const void* ptr_id);
    cqweqasvfa_API void          PushID(int int_id);
    cqweqasvfa_API void          PopID();
    cqweqasvfa_API cqweqasvfaID       GetID(const char* str_id);                                          // calculate unique ID (hash of whole ID stack + given parameter). e.g. if you want to query into cqweqasvfaStorage yourself
    cqweqasvfa_API cqweqasvfaID       GetID(const char* str_id_begin, const char* str_id_end);
    cqweqasvfa_API cqweqasvfaID       GetID(const void* ptr_id);

    // Widgets: Text
    cqweqasvfa_API void          TextUnformatted(const char* text, const char* text_end = NULL);               // raw text without formatting. Roughly equivalent to Text("%s", text) but: A) doesn't require null terminated string if 'text_end' is specified, B) it's faster, no memory copy is done, no buffer size limits, recommended for long chunks of text.
    cqweqasvfa_API void          Text(const char* fmt, ...)                                     IM_FMTARGS(1); // simple formatted text
    cqweqasvfa_API void          TextV(const char* fmt, va_list args)                           IM_FMTLIST(1);
    cqweqasvfa_API void          TextColored(const ImVec4& col, const char* fmt, ...)           IM_FMTARGS(2); // shortcut for PushStyleColor(cqweqasvfaCol_Text, col); Text(fmt, ...); PopStyleColor();
    cqweqasvfa_API void          TextColoredV(const ImVec4& col, const char* fmt, va_list args) IM_FMTLIST(2);
    cqweqasvfa_API void          TextDisabled(const char* fmt, ...)                             IM_FMTARGS(1); // shortcut for PushStyleColor(cqweqasvfaCol_Text, style.Colors[cqweqasvfaCol_TextDisabled]); Text(fmt, ...); PopStyleColor();
    cqweqasvfa_API void          TextDisabledV(const char* fmt, va_list args)                   IM_FMTLIST(1);
    cqweqasvfa_API void          TextWrapped(const char* fmt, ...)                              IM_FMTARGS(1); // shortcut for PushTextWrapPos(0.0f); Text(fmt, ...); PopTextWrapPos();. Note that this won't work on an auto-resizing window if there's no other widgets to extend the window width, yoy may need to set a size using SetNextWindowSize().
    cqweqasvfa_API void          TextWrappedV(const char* fmt, va_list args)                    IM_FMTLIST(1);
    cqweqasvfa_API void          LabelText(const char* label, const char* fmt, ...)             IM_FMTARGS(2); // display text+label aligned the same way as value+label widgets
    cqweqasvfa_API void          LabelTextV(const char* label, const char* fmt, va_list args)   IM_FMTLIST(2);
    cqweqasvfa_API void          BulletText(const char* fmt, ...)                               IM_FMTARGS(1); // shortcut for Bullet()+Text()
    cqweqasvfa_API void          BulletTextV(const char* fmt, va_list args)                     IM_FMTLIST(1);
    cqweqasvfa_API void          Bullet();                                                                     // draw a small circle and keep the cursor on the same line. advance cursor x position by GetTreeNodeToLabelSpacing(), same distance that TreeNode() uses

    // Widgets: Main
    cqweqasvfa_API bool          Button(const char* label, const ImVec2& size = ImVec2(0, 0));            // button
    cqweqasvfa_API bool          SmallButton(const char* label);                                         // button with FramePadding=(0,0) to easily embed within text
    cqweqasvfa_API bool          InvisibleButton(const char* str_id, const ImVec2& size);                // button behavior without the visuals, useful to build custom behaviors using the public api (along with IsItemActive, IsItemHovered, etc.)
    cqweqasvfa_API void          Image(ImTextureID user_texture_id, const ImVec2& size, const ImVec2& uv0 = ImVec2(0, 0), const ImVec2& uv1 = ImVec2(1, 1), const ImVec4& tint_col = ImVec4(1, 1, 1, 1), const ImVec4& border_col = ImVec4(0, 0, 0, 0));
    cqweqasvfa_API bool          ImageButton(ImTextureID user_texture_id, const ImVec2& size, const ImVec2& uv0 = ImVec2(0, 0), const ImVec2& uv1 = ImVec2(1, 1), int frame_padding = -1, const ImVec4& bg_col = ImVec4(0, 0, 0, 0), const ImVec4& tint_col = ImVec4(1, 1, 1, 1));    // <0 frame_padding uses default frame padding settings. 0 for no padding
    cqweqasvfa_API bool          Checkbox(const char* label, bool* v);
    cqweqasvfa_API bool          CheckboxFlags(const char* label, unsigned int* flags, unsigned int flags_value);
    cqweqasvfa_API bool          RadioButton(const char* label, bool active);
    cqweqasvfa_API bool          RadioButton(const char* label, int* v, int v_button);
    cqweqasvfa_API void          PlotLines(const char* label, const float* values, int values_count, int values_offset = 0, const char* overlay_text = NULL, float scale_min = FLT_MAX, float scale_max = FLT_MAX, ImVec2 graph_size = ImVec2(0, 0), int stride = sizeof(float));
    cqweqasvfa_API void          PlotLines(const char* label, float (*values_getter)(void* data, int idx), void* data, int values_count, int values_offset = 0, const char* overlay_text = NULL, float scale_min = FLT_MAX, float scale_max = FLT_MAX, ImVec2 graph_size = ImVec2(0, 0));
    cqweqasvfa_API void          PlotHistogram(const char* label, const float* values, int values_count, int values_offset = 0, const char* overlay_text = NULL, float scale_min = FLT_MAX, float scale_max = FLT_MAX, ImVec2 graph_size = ImVec2(0, 0), int stride = sizeof(float));
    cqweqasvfa_API void          PlotHistogram(const char* label, float (*values_getter)(void* data, int idx), void* data, int values_count, int values_offset = 0, const char* overlay_text = NULL, float scale_min = FLT_MAX, float scale_max = FLT_MAX, ImVec2 graph_size = ImVec2(0, 0));
    cqweqasvfa_API void          ProgressBar(float fraction, const ImVec2& size_arg = ImVec2(-1, 0), const char* overlay = NULL);

    // Widgets: Combo Box
    // The new BeginCombo()/EndCombo() api allows you to manage your contents and selection state however you want it. 
    // The old Combo() api are helpers over BeginCombo()/EndCombo() which are kept available for convenience purpose.
    cqweqasvfa_API bool          BeginCombo(const char* label, const char* preview_value, cqweqasvfaComboFlags flags = 0);
    cqweqasvfa_API void          EndCombo();
    cqweqasvfa_API bool          Combo(const char* label, int* current_item, const char* const items[], int items_count, int popup_max_height_in_items = -1);
    cqweqasvfa_API bool          Combo(const char* label, int* current_item, const char* items_separated_by_zeros, int popup_max_height_in_items = -1);      // Separate items with \0 within a string, end item-list with \0\0. e.g. "One\0Two\0Three\0"
    cqweqasvfa_API bool          Combo(const char* label, int* current_item, bool(*items_getter)(void* data, int idx, const char** out_text), void* data, int items_count, int popup_max_height_in_items = -1);

    // Widgets: Drags (tip: ctrl+click on a drag box to input with keyboard. manually input values aren't clamped, can go off-bounds)
    // For all the Float2/Float3/Float4/Int2/Int3/Int4 versions of every functions, note that a 'float v[X]' function argument is the same as 'float* v', the array syntax is just a way to document the number of elements that are expected to be accessible. You can pass address of your first element out of a contiguous set, e.g. &myvector.x
    cqweqasvfa_API bool          DragFloat(const char* label, float* v, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* display_format = "%.3f", float power = 1.0f);     // If v_min >= v_max we have no bound
    cqweqasvfa_API bool          DragFloat2(const char* label, float v[2], float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* display_format = "%.3f", float power = 1.0f);
    cqweqasvfa_API bool          DragFloat3(const char* label, float v[3], float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* display_format = "%.3f", float power = 1.0f);
    cqweqasvfa_API bool          DragFloat4(const char* label, float v[4], float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* display_format = "%.3f", float power = 1.0f);
    cqweqasvfa_API bool          DragFloatRange2(const char* label, float* v_current_min, float* v_current_max, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* display_format = "%.3f", const char* display_format_max = NULL, float power = 1.0f);
    cqweqasvfa_API bool          DragInt(const char* label, int* v, float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* display_format = "%.0f");                                       // If v_min >= v_max we have no bound
    cqweqasvfa_API bool          DragInt2(const char* label, int v[2], float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* display_format = "%.0f");
    cqweqasvfa_API bool          DragInt3(const char* label, int v[3], float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* display_format = "%.0f");
    cqweqasvfa_API bool          DragInt4(const char* label, int v[4], float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* display_format = "%.0f");
    cqweqasvfa_API bool          DragIntRange2(const char* label, int* v_current_min, int* v_current_max, float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* display_format = "%.0f", const char* display_format_max = NULL);

    // Widgets: Input with Keyboard
    cqweqasvfa_API bool          InputText(const char* label, char* buf, size_t buf_size, cqweqasvfaInputTextFlags flags = 0, cqweqasvfaTextEditCallback callback = NULL, void* user_data = NULL);
    cqweqasvfa_API bool          InputTextMultiline(const char* label, char* buf, size_t buf_size, const ImVec2& size = ImVec2(0, 0), cqweqasvfaInputTextFlags flags = 0, cqweqasvfaTextEditCallback callback = NULL, void* user_data = NULL);
    cqweqasvfa_API bool          InputFloat(const char* label, float* v, float step = 0.0f, float step_fast = 0.0f, int decimal_precision = -1, cqweqasvfaInputTextFlags extra_flags = 0);
    cqweqasvfa_API bool          InputFloat2(const char* label, float v[2], int decimal_precision = -1, cqweqasvfaInputTextFlags extra_flags = 0);
    cqweqasvfa_API bool          InputFloat3(const char* label, float v[3], int decimal_precision = -1, cqweqasvfaInputTextFlags extra_flags = 0);
    cqweqasvfa_API bool          InputFloat4(const char* label, float v[4], int decimal_precision = -1, cqweqasvfaInputTextFlags extra_flags = 0);
    cqweqasvfa_API bool          InputInt(const char* label, int* v, int step = 1, int step_fast = 100, cqweqasvfaInputTextFlags extra_flags = 0);
    cqweqasvfa_API bool          InputInt2(const char* label, int v[2], cqweqasvfaInputTextFlags extra_flags = 0);
    cqweqasvfa_API bool          InputInt3(const char* label, int v[3], cqweqasvfaInputTextFlags extra_flags = 0);
    cqweqasvfa_API bool          InputInt4(const char* label, int v[4], cqweqasvfaInputTextFlags extra_flags = 0);

    // Widgets: Sliders (tip: ctrl+click on a slider to input with keyboard. manually input values aren't clamped, can go off-bounds)
    cqweqasvfa_API bool          SliderFloat(const char* label, float* v, float v_min, float v_max, const char* display_format = "%.3f", float power = 1.0f);     // adjust display_format to decorate the value with a prefix or a suffix for in-slider labels or unit display. Use power!=1.0 for logarithmic sliders
    cqweqasvfa_API bool          SliderFloat2(const char* label, float v[2], float v_min, float v_max, const char* display_format = "%.3f", float power = 1.0f);
    cqweqasvfa_API bool          SliderFloat3(const char* label, float v[3], float v_min, float v_max, const char* display_format = "%.3f", float power = 1.0f);
    cqweqasvfa_API bool          SliderFloat4(const char* label, float v[4], float v_min, float v_max, const char* display_format = "%.3f", float power = 1.0f);
    cqweqasvfa_API bool          SliderAngle(const char* label, float* v_rad, float v_degrees_min = -360.0f, float v_degrees_max = +360.0f);
    cqweqasvfa_API bool          SliderInt(const char* label, int* v, int v_min, int v_max, const char* display_format = "%.0f");
    cqweqasvfa_API bool          SliderInt2(const char* label, int v[2], int v_min, int v_max, const char* display_format = "%.0f");
    cqweqasvfa_API bool          SliderInt3(const char* label, int v[3], int v_min, int v_max, const char* display_format = "%.0f");
    cqweqasvfa_API bool          SliderInt4(const char* label, int v[4], int v_min, int v_max, const char* display_format = "%.0f");
    cqweqasvfa_API bool          VSliderFloat(const char* label, const ImVec2& size, float* v, float v_min, float v_max, const char* display_format = "%.3f", float power = 1.0f);
    cqweqasvfa_API bool          VSliderInt(const char* label, const ImVec2& size, int* v, int v_min, int v_max, const char* display_format = "%.0f");

    // Widgets: Color Editor/Picker (tip: the ColorEdit* functions have a little colored preview square that can be left-clicked to open a picker, and right-clicked to open an option menu.)
    // Note that a 'float v[X]' function argument is the same as 'float* v', the array syntax is just a way to document the number of elements that are expected to be accessible. You can the pass the address of a first float element out of a contiguous structure, e.g. &myvector.x
    cqweqasvfa_API bool          ColorEdit3(const char* label, float col[3], cqweqasvfaColorEditFlags flags = 0);
    cqweqasvfa_API bool          ColorEdit4(const char* label, float col[4], cqweqasvfaColorEditFlags flags = 0);
    cqweqasvfa_API bool          ColorPicker3(const char* label, float col[3], cqweqasvfaColorEditFlags flags = 0);
    cqweqasvfa_API bool          ColorPicker4(const char* label, float col[4], cqweqasvfaColorEditFlags flags = 0, const float* ref_col = NULL);
    cqweqasvfa_API bool          ColorButton(const char* desc_id, const ImVec4& col, cqweqasvfaColorEditFlags flags = 0, ImVec2 size = ImVec2(0, 0));  // display a colored square/button, hover for details, return true when pressed.
    cqweqasvfa_API void          SetColorEditOptions(cqweqasvfaColorEditFlags flags);                         // initialize current options (generally on application startup) if you want to select a default format, picker type, etc. User will be able to change many settings, unless you pass the _NoOptions flag to your calls.

    // Widgets: Trees
    cqweqasvfa_API bool          TreeNode(const char* label);                                            // if returning 'true' the node is open and the tree id is pushed into the id stack. user is responsible for calling TreePop().
    cqweqasvfa_API bool          TreeNode(const char* str_id, const char* fmt, ...) IM_FMTARGS(2);       // read the FAQ about why and how to use ID. to align arbitrary text at the same level as a TreeNode() you can use Bullet().
    cqweqasvfa_API bool          TreeNode(const void* ptr_id, const char* fmt, ...) IM_FMTARGS(2);       // "
    cqweqasvfa_API bool          TreeNodeV(const char* str_id, const char* fmt, va_list args) IM_FMTLIST(2);
    cqweqasvfa_API bool          TreeNodeV(const void* ptr_id, const char* fmt, va_list args) IM_FMTLIST(2);
    cqweqasvfa_API bool          TreeNodeEx(const char* label, cqweqasvfaTreeNodeFlags flags = 0);
    cqweqasvfa_API bool          TreeNodeEx(const char* str_id, cqweqasvfaTreeNodeFlags flags, const char* fmt, ...) IM_FMTARGS(3);
    cqweqasvfa_API bool          TreeNodeEx(const void* ptr_id, cqweqasvfaTreeNodeFlags flags, const char* fmt, ...) IM_FMTARGS(3);
    cqweqasvfa_API bool          TreeNodeExV(const char* str_id, cqweqasvfaTreeNodeFlags flags, const char* fmt, va_list args) IM_FMTLIST(3);
    cqweqasvfa_API bool          TreeNodeExV(const void* ptr_id, cqweqasvfaTreeNodeFlags flags, const char* fmt, va_list args) IM_FMTLIST(3);
    cqweqasvfa_API void          TreePush(const char* str_id);                                           // ~ Indent()+PushId(). Already called by TreeNode() when returning true, but you can call Push/Pop yourself for layout purpose
    cqweqasvfa_API void          TreePush(const void* ptr_id = NULL);                                    // "
    cqweqasvfa_API void          TreePop();                                                              // ~ Unindent()+PopId()
    cqweqasvfa_API void          TreeAdvanceToLabelPos();                                                // advance cursor x position by GetTreeNodeToLabelSpacing()
    cqweqasvfa_API float         GetTreeNodeToLabelSpacing();                                            // horizontal distance preceding label when using TreeNode*() or Bullet() == (g.FontSize + style.FramePadding.x*2) for a regular unframed TreeNode
    cqweqasvfa_API void          SetNextTreeNodeOpen(bool is_open, cqweqasvfaCond cond = 0);                  // set next TreeNode/CollapsingHeader open state.
    cqweqasvfa_API bool          CollapsingHeader(const char* label, cqweqasvfaTreeNodeFlags flags = 0);      // if returning 'true' the header is open. doesn't indent nor push on ID stack. user doesn't have to call TreePop().
    cqweqasvfa_API bool          CollapsingHeader(const char* label, bool* p_open, cqweqasvfaTreeNodeFlags flags = 0); // when 'p_open' isn't NULL, display an additional small close button on upper right of the header

    // Widgets: Selectable / Lists
    cqweqasvfa_API bool          Selectable(const char* label, bool selected = false, cqweqasvfaSelectableFlags flags = 0, const ImVec2& size = ImVec2(0, 0));  // size.x==0.0: use remaining width, size.x>0.0: specify width. size.y==0.0: use label height, size.y>0.0: specify height
    cqweqasvfa_API bool          Selectable(const char* label, bool* p_selected, cqweqasvfaSelectableFlags flags = 0, const ImVec2& size = ImVec2(0, 0));
    cqweqasvfa_API bool          ListBox(const char* label, int* current_item, const char* const* items, int items_count, int height_in_items = -1);
    cqweqasvfa_API bool          ListBox(const char* label, int* current_item, bool (*items_getter)(void* data, int idx, const char** out_text), void* data, int items_count, int height_in_items = -1);
    cqweqasvfa_API bool          ListBoxHeader(const char* label, const ImVec2& size = ImVec2(0, 0));     // use if you want to reimplement ListBox() will custom data or interactions. make sure to call ListBoxFooter() afterwards.
    cqweqasvfa_API bool          ListBoxHeader(const char* label, int items_count, int height_in_items = -1); // "
    cqweqasvfa_API void          ListBoxFooter();                                                        // terminate the scrolling region

    // Widgets: Value() Helpers. Output single value in "name: value" format (tip: freely declare more in your code to handle your types. you can add functions to the cqweqasvfa namespace)
    cqweqasvfa_API void          Value(const char* prefix, bool b);
    cqweqasvfa_API void          Value(const char* prefix, int v);
    cqweqasvfa_API void          Value(const char* prefix, unsigned int v);
    cqweqasvfa_API void          Value(const char* prefix, float v, const char* float_format = NULL);

    // Tooltips
    cqweqasvfa_API void          SetTooltip(const char* fmt, ...) IM_FMTARGS(1);                     // set text tooltip under mouse-cursor, typically use with cqweqasvfa::IsItemHovered(). overidde any previous call to SetTooltip().
    cqweqasvfa_API void          SetTooltipV(const char* fmt, va_list args) IM_FMTLIST(1);
    cqweqasvfa_API void          BeginTooltip();                                                     // begin/append a tooltip window. to create full-featured tooltip (with any kind of contents).
    cqweqasvfa_API void          EndTooltip();

    // Menus
    cqweqasvfa_API bool          BeginMainMenuBar();                                                 // create and append to a full screen menu-bar. only call EndMainMenuBar() if this returns true!
    cqweqasvfa_API void          EndMainMenuBar();
    cqweqasvfa_API bool          BeginMenuBar();                                                     // append to menu-bar of current window (requires cqweqasvfaWindowFlags_MenuBar flag set on parent window). only call EndMenuBar() if this returns true!
    cqweqasvfa_API void          EndMenuBar();
    cqweqasvfa_API bool          BeginMenu(const char* label, bool enabled = true);                  // create a sub-menu entry. only call EndMenu() if this returns true!
    cqweqasvfa_API void          EndMenu();
    cqweqasvfa_API bool          MenuItem(const char* label, const char* shortcut = NULL, bool selected = false, bool enabled = true);  // return true when activated. shortcuts are displayed for convenience but not processed by cqweqasvfa at the moment
    cqweqasvfa_API bool          MenuItem(const char* label, const char* shortcut, bool* p_selected, bool enabled = true);              // return true when activated + toggle (*p_selected) if p_selected != NULL

    // Popups
    cqweqasvfa_API void          OpenPopup(const char* str_id);                                      // call to mark popup as open (don't call every frame!). popups are closed when user click outside, or if CloseCurrentPopup() is called within a BeginPopup()/EndPopup() block. By default, Selectable()/MenuItem() are calling CloseCurrentPopup(). Popup identifiers are relative to the current ID-stack (so OpenPopup and BeginPopup needs to be at the same level).
    cqweqasvfa_API bool          OpenPopupOnItemClick(const char* str_id = NULL, int mouse_button = 1);                                  // helper to open popup when clicked on last item. return true when just opened.
    cqweqasvfa_API bool          BeginPopup(const char* str_id);                                     // return true if the popup is open, and you can start outputting to it. only call EndPopup() if BeginPopup() returned true!
    cqweqasvfa_API bool          BeginPopupModal(const char* name, bool* p_open = NULL, cqweqasvfaWindowFlags extra_flags = 0);               // modal dialog (block interactions behind the modal window, can't close the modal window by clicking outside)
    cqweqasvfa_API bool          BeginPopupContextItem(const char* str_id = NULL, int mouse_button = 1);                                 // helper to open and begin popup when clicked on last item. if you can pass a NULL str_id only if the previous item had an id. If you want to use that on a non-interactive item such as Text() you need to pass in an explicit ID here. read comments in .cpp!
    cqweqasvfa_API bool          BeginPopupContextWindow(const char* str_id = NULL, int mouse_button = 1, bool also_over_items = true);  // helper to open and begin popup when clicked on current window.
    cqweqasvfa_API bool          BeginPopupContextVoid(const char* str_id = NULL, int mouse_button = 1);                                 // helper to open and begin popup when clicked in void (where there are no cqweqasvfa windows).
    cqweqasvfa_API void          EndPopup();
    cqweqasvfa_API bool          IsPopupOpen(const char* str_id);                                    // return true if the popup is open
    cqweqasvfa_API void          CloseCurrentPopup();                                                // close the popup we have begin-ed into. clicking on a MenuItem or Selectable automatically close the current popup.

    // Logging/Capture: all text output from interface is captured to tty/file/clipboard. By default, tree nodes are automatically opened during logging.
    cqweqasvfa_API void          LogToTTY(int max_depth = -1);                                       // start logging to tty
    cqweqasvfa_API void          LogToFile(int max_depth = -1, const char* filename = NULL);         // start logging to file
    cqweqasvfa_API void          LogToClipboard(int max_depth = -1);                                 // start logging to OS clipboard
    cqweqasvfa_API void          LogFinish();                                                        // stop logging (close file, etc.)
    cqweqasvfa_API void          LogButtons();                                                       // helper to display buttons for logging to tty/file/clipboard
    cqweqasvfa_API void          LogText(const char* fmt, ...) IM_FMTARGS(1);                        // pass text data straight to log (without being displayed)

    // Drag and Drop
    // [BETA API] Missing Demo code. API may evolve.
    cqweqasvfa_API bool          BeginDragDropSource(cqweqasvfaDragDropFlags flags = 0, int mouse_button = 0);                // call when the current item is active. If this return true, you can call SetDragDropPayload() + EndDragDropSource()
    cqweqasvfa_API bool          SetDragDropPayload(const char* type, const void* data, size_t size, cqweqasvfaCond cond = 0);// type is a user defined string of maximum 8 characters. Strings starting with '_' are reserved for dear cqweqasvfa internal types. Data is copied and held by cqweqasvfa.
    cqweqasvfa_API void          EndDragDropSource();
    cqweqasvfa_API bool          BeginDragDropTarget();                                                                  // call after submitting an item that may receive an item. If this returns true, you can call AcceptDragDropPayload() + EndDragDropTarget()
    cqweqasvfa_API const cqweqasvfaPayload* AcceptDragDropPayload(const char* type, cqweqasvfaDragDropFlags flags = 0);            // accept contents of a given type. If cqweqasvfaDragDropFlags_AcceptBeforeDelivery is set you can peek into the payload before the mouse button is released.
    cqweqasvfa_API void          EndDragDropTarget();

    // Clipping
    cqweqasvfa_API void          PushClipRect(const ImVec2& clip_rect_min, const ImVec2& clip_rect_max, bool intersect_with_current_clip_rect);
    cqweqasvfa_API void          PopClipRect();

    // Styles
    cqweqasvfa_API void          StyleColorsClassic(cqweqasvfaStyle* dst = NULL);
    cqweqasvfa_API void          StyleColorsDark(cqweqasvfaStyle* dst = NULL);
    cqweqasvfa_API void          StyleColorsLight(cqweqasvfaStyle* dst = NULL);

    // Focus
    // (FIXME: Those functions will be reworked after we merge the navigation branch + have a pass at focusing/tabbing features.)
    // (Prefer using "SetItemDefaultFocus()" over "if (IsWindowAppearing()) SetScrollHere()" when applicable, to make your code more forward compatible when navigation branch is merged)
    cqweqasvfa_API void          SetItemDefaultFocus();                                              // make last item the default focused item of a window (WIP navigation branch only). Pleaase use instead of SetScrollHere().
    cqweqasvfa_API void          SetKeyboardFocusHere(int offset = 0);                               // focus keyboard on the next widget. Use positive 'offset' to access sub components of a multiple component widget. Use -1 to access previous widget.

    // Utilities
    cqweqasvfa_API bool          IsItemHovered(cqweqasvfaHoveredFlags flags = 0);                         // is the last item hovered? (and usable, aka not blocked by a popup, etc.). See cqweqasvfaHoveredFlags for more options.
    cqweqasvfa_API bool          IsItemActive();                                                     // is the last item active? (e.g. button being held, text field being edited- items that don't interact will always return false)
    cqweqasvfa_API bool          IsItemClicked(int mouse_button = 0);                                // is the last item clicked? (e.g. button/node just clicked on)
    cqweqasvfa_API bool          IsItemVisible();                                                    // is the last item visible? (aka not out of sight due to clipping/scrolling.)
    cqweqasvfa_API bool          IsAnyItemHovered();
    cqweqasvfa_API bool          IsAnyItemActive();
    cqweqasvfa_API ImVec2        GetItemRectMin();                                                   // get bounding rectangle of last item, in screen space
    cqweqasvfa_API ImVec2        GetItemRectMax();                                                   // "
    cqweqasvfa_API ImVec2        GetItemRectSize();                                                  // get size of last item, in screen space
    cqweqasvfa_API void          SetItemAllowOverlap();                                              // allow last item to be overlapped by a subsequent item. sometimes useful with invisible buttons, selectables, etc. to catch unused area.
    cqweqasvfa_API bool          IsWindowFocused(cqweqasvfaFocusedFlags flags = 0);                       // is current window focused? or its root/child, depending on flags. see flags for options.
    cqweqasvfa_API bool          IsWindowHovered(cqweqasvfaHoveredFlags flags = 0);                       // is current window hovered (and typically: not blocked by a popup/modal)? see flags for options.
    cqweqasvfa_API bool          IsAnyWindowFocused();
    cqweqasvfa_API bool          IsAnyWindowHovered();                                               // is mouse hovering any visible window
    cqweqasvfa_API bool          IsRectVisible(const ImVec2& size);                                  // test if rectangle (of given size, starting from cursor position) is visible / not clipped.
    cqweqasvfa_API bool          IsRectVisible(const ImVec2& rect_min, const ImVec2& rect_max);      // test if rectangle (in screen space) is visible / not clipped. to perform coarse clipping on user's side.
    cqweqasvfa_API float         GetTime();
    cqweqasvfa_API int           GetFrameCount();
    cqweqasvfa_API ImDrawList* GetOverlayDrawList();                                               // this draw list will be the last rendered one, useful to quickly draw overlays shapes/text
    cqweqasvfa_API ImDrawListSharedData* GetDrawListSharedData();
    cqweqasvfa_API const char* GetStyleColorName(cqweqasvfaCol idx);
    cqweqasvfa_API ImVec2        CalcItemRectClosestPoint(const ImVec2& pos, bool on_edge = false, float outward = +0.0f);   // utility to find the closest point the last item bounding rectangle edge. useful to visually link items
    cqweqasvfa_API ImVec2        CalcTextSize(const char* text, const char* text_end = NULL, bool hide_text_after_double_hash = false, float wrap_width = -1.0f);
    cqweqasvfa_API void          CalcListClipping(int items_count, float items_height, int* out_items_display_start, int* out_items_display_end);    // calculate coarse clipping for large list of evenly sized items. Prefer using the cqweqasvfaListClipper higher-level helper if you can.

    cqweqasvfa_API bool          BeginChildFrame(cqweqasvfaID id, const ImVec2& size, cqweqasvfaWindowFlags extra_flags = 0);    // helper to create a child window / scrolling region that looks like a normal widget frame
    cqweqasvfa_API void          EndChildFrame();

    cqweqasvfa_API ImVec4        ColorConvertU32ToFloat4(ImU32 in);
    cqweqasvfa_API ImU32         ColorConvertFloat4ToU32(const ImVec4& in);
    cqweqasvfa_API void          ColorConvertRGBtoHSV(float r, float g, float b, float& out_h, float& out_s, float& out_v);
    cqweqasvfa_API void          ColorConvertHSVtoRGB(float h, float s, float v, float& out_r, float& out_g, float& out_b);

    // Inputs
    cqweqasvfa_API int           GetKeyIndex(cqweqasvfaKey cqweqasvfa_key);                                    // map cqweqasvfaKey_* values into user's key index. == io.KeyMap[key]
    cqweqasvfa_API bool          IsKeyDown(int user_key_index);                                      // is key being held. == io.KeysDown[user_key_index]. note that cqweqasvfa doesn't know the semantic of each entry of io.KeyDown[]. Use your own indices/enums according to how your backend/engine stored them into KeyDown[]!
    cqweqasvfa_API bool          IsKeyPressed(int user_key_index, bool repeat = true);               // was key pressed (went from !Down to Down). if repeat=true, uses io.KeyRepeatDelay / KeyRepeatRate
    cqweqasvfa_API bool          IsKeyReleased(int user_key_index);                                  // was key released (went from Down to !Down)..
    cqweqasvfa_API int           GetKeyPressedAmount(int key_index, float repeat_delay, float rate); // uses provided repeat rate/delay. return a count, most often 0 or 1 but might be >1 if RepeatRate is small enough that DeltaTime > RepeatRate
    cqweqasvfa_API bool          IsMouseDown(int button);                                            // is mouse button held
    cqweqasvfa_API bool          IsMouseClicked(int button, bool repeat = false);                    // did mouse button clicked (went from !Down to Down)
    cqweqasvfa_API bool          IsMouseDoubleClicked(int button);                                   // did mouse button double-clicked. a double-click returns false in IsMouseClicked(). uses io.MouseDoubleClickTime.
    cqweqasvfa_API bool          IsMouseReleased(int button);                                        // did mouse button released (went from Down to !Down)
    cqweqasvfa_API bool          IsMouseDragging(int button = 0, float lock_threshold = -1.0f);      // is mouse dragging. if lock_threshold < -1.0f uses io.MouseDraggingThreshold
    cqweqasvfa_API bool          IsMouseHoveringRect(const ImVec2& r_min, const ImVec2& r_max, bool clip = true);  // is mouse hovering given bounding rect (in screen space). clipped by current clipping settings. disregarding of consideration of focus/window ordering/blocked by a popup.
    cqweqasvfa_API bool          IsMousePosValid(const ImVec2* mouse_pos = NULL);                    //
    cqweqasvfa_API ImVec2        GetMousePos();                                                      // shortcut to cqweqasvfa::GetIO().MousePos provided by user, to be consistent with other calls
    cqweqasvfa_API ImVec2        GetMousePosOnOpeningCurrentPopup();                                 // retrieve backup of mouse positioning at the time of opening popup we have BeginPopup() into
    cqweqasvfa_API ImVec2        GetMouseDragDelta(int button = 0, float lock_threshold = -1.0f);    // dragging amount since clicking. if lock_threshold < -1.0f uses io.MouseDraggingThreshold
    cqweqasvfa_API void          ResetMouseDragDelta(int button = 0);                                //
    cqweqasvfa_API cqweqasvfaMouseCursor GetMouseCursor();                                                // get desired cursor type, reset in cqweqasvfa::NewFrame(), this is updated during the frame. valid before Render(). If you use software rendering by setting io.MouseDrawCursor cqweqasvfa will render those for you
    cqweqasvfa_API void          SetMouseCursor(cqweqasvfaMouseCursor type);                              // set desired cursor type
    cqweqasvfa_API void          CaptureKeyboardFromApp(bool capture = true);                        // manually override io.WantCaptureKeyboard flag next frame (said flag is entirely left for your application handle). e.g. force capture keyboard when your widget is being hovered.
    cqweqasvfa_API void          CaptureMouseFromApp(bool capture = true);                           // manually override io.WantCaptureMouse flag next frame (said flag is entirely left for your application handle).

    // Helpers functions to access functions pointers in cqweqasvfa::GetIO()
    cqweqasvfa_API void* MemAlloc(size_t sz);
    cqweqasvfa_API void          MemFree(void* ptr);
    cqweqasvfa_API const char* GetClipboardText();
    cqweqasvfa_API void          SetClipboardText(const char* text);

    // Internal context access - if you want to use multiple context, share context between modules (e.g. DLL). There is a default context created and active by default.
    // All contexts share a same ImFontAtlas by default. If you want different font atlas, you can new() them and overwrite the GetIO().Fonts variable of an cqweqasvfa context.
    cqweqasvfa_API const char* GetVersion();
    cqweqasvfa_API cqweqasvfaContext* CreateContext(void* (*malloc_fn)(size_t) = NULL, void (*free_fn)(void*) = NULL);
    cqweqasvfa_API void          DestroyContext(cqweqasvfaContext* ctx);
    cqweqasvfa_API cqweqasvfaContext* GetCurrentContext();
    cqweqasvfa_API void          SetCurrentContext(cqweqasvfaContext* ctx);

} // namespace cqweqasvfa

// Flags for cqweqasvfa::Begin()
enum cqweqasvfaWindowFlags_
{
    cqweqasvfaWindowFlags_NoTitleBar = 1 << 0,   // Disable title-bar
    cqweqasvfaWindowFlags_NoResize = 1 << 1,   // Disable user resizing with the lower-right grip
    cqweqasvfaWindowFlags_NoMove = 1 << 2,   // Disable user moving the window
    cqweqasvfaWindowFlags_NoScrollbar = 1 << 3,   // Disable scrollbars (window can still scroll with mouse or programatically)
    cqweqasvfaWindowFlags_NoScrollWithMouse = 1 << 4,   // Disable user vertically scrolling with mouse wheel. On child window, mouse wheel will be forwarded to the parent unless NoScrollbar is also set.
    cqweqasvfaWindowFlags_NoCollapse = 1 << 5,   // Disable user collapsing window by double-clicking on it
    cqweqasvfaWindowFlags_AlwaysAutoResize = 1 << 6,   // Resize every window to its content every frame
    //cqweqasvfaWindowFlags_ShowBorders          = 1 << 7,   // Show borders around windows and items (OBSOLETE! Use e.g. style.FrameBorderSize=1.0f to enable borders).
    cqweqasvfaWindowFlags_NoSavedSettings = 1 << 8,   // Never load/save settings in .ini file
    cqweqasvfaWindowFlags_NoInputs = 1 << 9,   // Disable catching mouse or keyboard inputs, hovering test with pass through.
    cqweqasvfaWindowFlags_MenuBar = 1 << 10,  // Has a menu-bar
    cqweqasvfaWindowFlags_HorizontalScrollbar = 1 << 11,  // Allow horizontal scrollbar to appear (off by default). You may use SetNextWindowContentSize(ImVec2(width,0.0f)); prior to calling Begin() to specify width. Read code in cqweqasvfa_demo in the "Horizontal Scrolling" section.
    cqweqasvfaWindowFlags_NoFocusOnAppearing = 1 << 12,  // Disable taking focus when transitioning from hidden to visible state
    cqweqasvfaWindowFlags_NoBringToFrontOnFocus = 1 << 13,  // Disable bringing window to front when taking focus (e.g. clicking on it or programatically giving it focus)
    cqweqasvfaWindowFlags_AlwaysVerticalScrollbar = 1 << 14,  // Always show vertical scrollbar (even if ContentSize.y < Size.y)
    cqweqasvfaWindowFlags_AlwaysHorizontalScrollbar = 1 << 15,  // Always show horizontal scrollbar (even if ContentSize.x < Size.x)
    cqweqasvfaWindowFlags_AlwaysUseWindowPadding = 1 << 16,  // Ensure child windows without border uses style.WindowPadding (ignored by default for non-bordered child windows, because more convenient)
    cqweqasvfaWindowFlags_ResizeFromAnySide = 1 << 17,  // (WIP) Enable resize from any corners and borders. Your back-end needs to honor the different values of io.MouseCursor set by cqweqasvfa.

    // [Internal]
    cqweqasvfaWindowFlags_ChildWindow = 1 << 24,  // Don't use! For internal use by BeginChild()
    cqweqasvfaWindowFlags_Tooltip = 1 << 25,  // Don't use! For internal use by BeginTooltip()
    cqweqasvfaWindowFlags_Popup = 1 << 26,  // Don't use! For internal use by BeginPopup()
    cqweqasvfaWindowFlags_Modal = 1 << 27,  // Don't use! For internal use by BeginPopupModal()
    cqweqasvfaWindowFlags_ChildMenu = 1 << 28   // Don't use! For internal use by BeginMenu()
};

// Flags for cqweqasvfa::InputText()
enum cqweqasvfaInputTextFlags_
{
    cqweqasvfaInputTextFlags_CharsDecimal = 1 << 0,   // Allow 0123456789.+-*/
    cqweqasvfaInputTextFlags_CharsHexadecimal = 1 << 1,   // Allow 0123456789ABCDEFabcdef
    cqweqasvfaInputTextFlags_CharsUppercase = 1 << 2,   // Turn a..z into A..Z
    cqweqasvfaInputTextFlags_CharsNoBlank = 1 << 3,   // Filter out spaces, tabs
    cqweqasvfaInputTextFlags_AutoSelectAll = 1 << 4,   // Select entire text when first taking mouse focus
    cqweqasvfaInputTextFlags_EnterReturnsTrue = 1 << 5,   // Return 'true' when Enter is pressed (as opposed to when the value was modified)
    cqweqasvfaInputTextFlags_CallbackCompletion = 1 << 6,   // Call user function on pressing TAB (for completion handling)
    cqweqasvfaInputTextFlags_CallbackHistory = 1 << 7,   // Call user function on pressing Up/Down arrows (for history handling)
    cqweqasvfaInputTextFlags_CallbackAlways = 1 << 8,   // Call user function every time. User code may query cursor position, modify text buffer.
    cqweqasvfaInputTextFlags_CallbackCharFilter = 1 << 9,   // Call user function to filter character. Modify data->EventChar to replace/filter input, or return 1 to discard character.
    cqweqasvfaInputTextFlags_AllowTabInput = 1 << 10,  // Pressing TAB input a '\t' character into the text field
    cqweqasvfaInputTextFlags_CtrlEnterForNewLine = 1 << 11,  // In multi-line mode, unfocus with Enter, add new line with Ctrl+Enter (default is opposite: unfocus with Ctrl+Enter, add line with Enter).
    cqweqasvfaInputTextFlags_NoHorizontalScroll = 1 << 12,  // Disable following the cursor horizontally
    cqweqasvfaInputTextFlags_AlwaysInsertMode = 1 << 13,  // Insert mode
    cqweqasvfaInputTextFlags_ReadOnly = 1 << 14,  // Read-only mode
    cqweqasvfaInputTextFlags_Password = 1 << 15,  // Password mode, display all characters as '*'
    cqweqasvfaInputTextFlags_NoUndoRedo = 1 << 16,  // Disable undo/redo. Note that input text owns the text data while active, if you want to provide your own undo/redo stack you need e.g. to call ClearActiveID().
    // [Internal]
    cqweqasvfaInputTextFlags_Multiline = 1 << 20   // For internal use by InputTextMultiline()
};

// Flags for cqweqasvfa::TreeNodeEx(), cqweqasvfa::CollapsingHeader*()
enum cqweqasvfaTreeNodeFlags_
{
    cqweqasvfaTreeNodeFlags_Selected = 1 << 0,   // Draw as selected
    cqweqasvfaTreeNodeFlags_Framed = 1 << 1,   // Full colored frame (e.g. for CollapsingHeader)
    cqweqasvfaTreeNodeFlags_AllowItemOverlap = 1 << 2,   // Hit testing to allow subsequent widgets to overlap this one
    cqweqasvfaTreeNodeFlags_NoTreePushOnOpen = 1 << 3,   // Don't do a TreePush() when open (e.g. for CollapsingHeader) = no extra indent nor pushing on ID stack
    cqweqasvfaTreeNodeFlags_NoAutoOpenOnLog = 1 << 4,   // Don't automatically and temporarily open node when Logging is active (by default logging will automatically open tree nodes)
    cqweqasvfaTreeNodeFlags_DefaultOpen = 1 << 5,   // Default node to be open
    cqweqasvfaTreeNodeFlags_OpenOnDoubleClick = 1 << 6,   // Need double-click to open node
    cqweqasvfaTreeNodeFlags_OpenOnArrow = 1 << 7,   // Only open when clicking on the arrow part. If cqweqasvfaTreeNodeFlags_OpenOnDoubleClick is also set, single-click arrow or double-click all box to open.
    cqweqasvfaTreeNodeFlags_Leaf = 1 << 8,   // No collapsing, no arrow (use as a convenience for leaf nodes). 
    cqweqasvfaTreeNodeFlags_Bullet = 1 << 9,   // Display a bullet instead of arrow
    cqweqasvfaTreeNodeFlags_FramePadding = 1 << 10,  // Use FramePadding (even for an unframed text node) to vertically align text baseline to regular widget height. Equivalent to calling AlignTextToFramePadding().
    //cqweqasvfaTreeNodeFlags_SpanAllAvailWidth  = 1 << 11,  // FIXME: TODO: Extend hit box horizontally even if not framed
    //cqweqasvfaTreeNodeFlags_NoScrollOnOpen     = 1 << 12,  // FIXME: TODO: Disable automatic scroll on TreePop() if node got just open and contents is not visible
    cqweqasvfaTreeNodeFlags_CollapsingHeader = cqweqasvfaTreeNodeFlags_Framed | cqweqasvfaTreeNodeFlags_NoAutoOpenOnLog

    // Obsolete names (will be removed)
#ifndef cqweqasvfa_DISABLE_OBSOLETE_FUNCTIONS
    , cqweqasvfaTreeNodeFlags_AllowOverlapMode = cqweqasvfaTreeNodeFlags_AllowItemOverlap
#endif
};

// Flags for cqweqasvfa::Selectable()
enum cqweqasvfaSelectableFlags_
{
    cqweqasvfaSelectableFlags_DontClosePopups = 1 << 0,   // Clicking this don't close parent popup window
    cqweqasvfaSelectableFlags_SpanAllColumns = 1 << 1,   // Selectable frame can span all columns (text will still fit in current column)
    cqweqasvfaSelectableFlags_AllowDoubleClick = 1 << 2    // Generate press events on double clicks too
};

// Flags for cqweqasvfa::BeginCombo()
enum cqweqasvfaComboFlags_
{
    cqweqasvfaComboFlags_PopupAlignLeft = 1 << 0,   // Align the popup toward the left by default
    cqweqasvfaComboFlags_HeightSmall = 1 << 1,   // Max ~4 items visible. Tip: If you want your combo popup to be a specific size you can use SetNextWindowSizeConstraints() prior to calling BeginCombo()
    cqweqasvfaComboFlags_HeightRegular = 1 << 2,   // Max ~8 items visible (default)
    cqweqasvfaComboFlags_HeightLarge = 1 << 3,   // Max ~20 items visible
    cqweqasvfaComboFlags_HeightLargest = 1 << 4,   // As many fitting items as possible
    cqweqasvfaComboFlags_HeightMask_ = cqweqasvfaComboFlags_HeightSmall | cqweqasvfaComboFlags_HeightRegular | cqweqasvfaComboFlags_HeightLarge | cqweqasvfaComboFlags_HeightLargest
};

// Flags for cqweqasvfa::IsWindowFocused()
enum cqweqasvfaFocusedFlags_
{
    cqweqasvfaFocusedFlags_ChildWindows = 1 << 0,   // IsWindowFocused(): Return true if any children of the window is focused
    cqweqasvfaFocusedFlags_RootWindow = 1 << 1,   // IsWindowFocused(): Test from root window (top most parent of the current hierarchy)
    cqweqasvfaFocusedFlags_RootAndChildWindows = cqweqasvfaFocusedFlags_RootWindow | cqweqasvfaFocusedFlags_ChildWindows
};

// Flags for cqweqasvfa::IsItemHovered(), cqweqasvfa::IsWindowHovered()
enum cqweqasvfaHoveredFlags_
{
    cqweqasvfaHoveredFlags_Default = 0,        // Return true if directly over the item/window, not obstructed by another window, not obstructed by an active popup or modal blocking inputs under them.
    cqweqasvfaHoveredFlags_ChildWindows = 1 << 0,   // IsWindowHovered() only: Return true if any children of the window is hovered
    cqweqasvfaHoveredFlags_RootWindow = 1 << 1,   // IsWindowHovered() only: Test from root window (top most parent of the current hierarchy)
    cqweqasvfaHoveredFlags_AllowWhenBlockedByPopup = 1 << 2,   // Return true even if a popup window is normally blocking access to this item/window
    //cqweqasvfaHoveredFlags_AllowWhenBlockedByModal     = 1 << 3,   // Return true even if a modal popup window is normally blocking access to this item/window. FIXME-TODO: Unavailable yet.
    cqweqasvfaHoveredFlags_AllowWhenBlockedByActiveItem = 1 << 4,   // Return true even if an active item is blocking access to this item/window. Useful for Drag and Drop patterns.
    cqweqasvfaHoveredFlags_AllowWhenOverlapped = 1 << 5,   // Return true even if the position is overlapped by another window
    cqweqasvfaHoveredFlags_RectOnly = cqweqasvfaHoveredFlags_AllowWhenBlockedByPopup | cqweqasvfaHoveredFlags_AllowWhenBlockedByActiveItem | cqweqasvfaHoveredFlags_AllowWhenOverlapped,
    cqweqasvfaHoveredFlags_RootAndChildWindows = cqweqasvfaHoveredFlags_RootWindow | cqweqasvfaHoveredFlags_ChildWindows
};

// Flags for cqweqasvfa::BeginDragDropSource(), cqweqasvfa::AcceptDragDropPayload()
enum cqweqasvfaDragDropFlags_
{
    // BeginDragDropSource() flags
    cqweqasvfaDragDropFlags_SourceNoPreviewTooltip = 1 << 0,       // By default, a successful call to BeginDragDropSource opens a tooltip so you can display a preview or description of the source contents. This flag disable this behavior.
    cqweqasvfaDragDropFlags_SourceNoDisableHover = 1 << 1,       // By default, when dragging we clear data so that IsItemHovered() will return true, to avoid subsequent user code submitting tooltips. This flag disable this behavior so you can still call IsItemHovered() on the source item.
    cqweqasvfaDragDropFlags_SourceNoHoldToOpenOthers = 1 << 2,       // Disable the behavior that allows to open tree nodes and collapsing header by holding over them while dragging a source item.
    cqweqasvfaDragDropFlags_SourceAllowNullID = 1 << 3,       // Allow items such as Text(), Image() that have no unique identifier to be used as drag source, by manufacturing a temporary identifier based on their window-relative position. This is extremely unusual within the dear cqweqasvfa ecosystem and so we made it explicit.
    cqweqasvfaDragDropFlags_SourceExtern = 1 << 4,       // External source (from outside of cqweqasvfa), won't attempt to read current item/window info. Will always return true. Only one Extern source can be active simultaneously.
    // AcceptDragDropPayload() flags
    cqweqasvfaDragDropFlags_AcceptBeforeDelivery = 1 << 10,      // AcceptDragDropPayload() will returns true even before the mouse button is released. You can then call IsDelivery() to test if the payload needs to be delivered.
    cqweqasvfaDragDropFlags_AcceptNoDrawDefaultRect = 1 << 11,      // Do not draw the default highlight rectangle when hovering over target.
    cqweqasvfaDragDropFlags_AcceptPeekOnly = cqweqasvfaDragDropFlags_AcceptBeforeDelivery | cqweqasvfaDragDropFlags_AcceptNoDrawDefaultRect  // For peeking ahead and inspecting the payload before delivery.
};

// Standard Drag and Drop payload types. You can define you own payload types using 8-characters long strings. Types starting with '_' are defined by Dear cqweqasvfa.
#define cqweqasvfa_PAYLOAD_TYPE_COLOR_3F     "_COL3F"    // float[3]     // Standard type for colors, without alpha. User code may use this type. 
#define cqweqasvfa_PAYLOAD_TYPE_COLOR_4F     "_COL4F"    // float[4]     // Standard type for colors. User code may use this type.

// User fill cqweqasvfaIO.KeyMap[] array with indices into the cqweqasvfaIO.KeysDown[512] array
enum cqweqasvfaKey_
{
    cqweqasvfaKey_Tab,       // for tabbing through fields
    cqweqasvfaKey_LeftArrow, // for text edit
    cqweqasvfaKey_RightArrow,// for text edit
    cqweqasvfaKey_UpArrow,   // for text edit
    cqweqasvfaKey_DownArrow, // for text edit
    cqweqasvfaKey_PageUp,
    cqweqasvfaKey_PageDown,
    cqweqasvfaKey_Home,      // for text edit
    cqweqasvfaKey_End,       // for text edit
    cqweqasvfaKey_Delete,    // for text edit
    cqweqasvfaKey_Backspace, // for text edit
    cqweqasvfaKey_Enter,     // for text edit
    cqweqasvfaKey_Escape,    // for text edit
    cqweqasvfaKey_A,         // for text edit CTRL+A: select all
    cqweqasvfaKey_C,         // for text edit CTRL+C: copy
    cqweqasvfaKey_V,         // for text edit CTRL+V: paste
    cqweqasvfaKey_X,         // for text edit CTRL+X: cut
    cqweqasvfaKey_Y,         // for text edit CTRL+Y: redo
    cqweqasvfaKey_Z,         // for text edit CTRL+Z: undo
    cqweqasvfaKey_COUNT
};

// Enumeration for PushStyleColor() / PopStyleColor()
enum cqweqasvfaCol_
{
    cqweqasvfaCol_Text,
    cqweqasvfaCol_TextDisabled,
    cqweqasvfaCol_WindowBg,              // Background of normal windows
    cqweqasvfaCol_ChildBg,               // Background of child windows
    cqweqasvfaCol_PopupBg,               // Background of popups, menus, tooltips windows
    cqweqasvfaCol_Border,
    cqweqasvfaCol_BorderShadow,
    cqweqasvfaCol_FrameBg,               // Background of checkbox, radio button, plot, slider, text input
    cqweqasvfaCol_FrameBgHovered,
    cqweqasvfaCol_FrameBgActive,
    cqweqasvfaCol_TitleBg,
    cqweqasvfaCol_TitleBgActive,
    cqweqasvfaCol_TitleBgCollapsed,
    cqweqasvfaCol_MenuBarBg,
    cqweqasvfaCol_ScrollbarBg,
    cqweqasvfaCol_ScrollbarGrab,
    cqweqasvfaCol_ScrollbarGrabHovered,
    cqweqasvfaCol_ScrollbarGrabActive,
    cqweqasvfaCol_CheckMark,
    cqweqasvfaCol_SliderGrab,
    cqweqasvfaCol_SliderGrabActive,
    cqweqasvfaCol_Button,
    cqweqasvfaCol_ButtonHovered,
    cqweqasvfaCol_ButtonActive,
    cqweqasvfaCol_Header,
    cqweqasvfaCol_HeaderHovered,
    cqweqasvfaCol_HeaderActive,
    cqweqasvfaCol_Separator,
    cqweqasvfaCol_SeparatorHovered,
    cqweqasvfaCol_SeparatorActive,
    cqweqasvfaCol_ResizeGrip,
    cqweqasvfaCol_ResizeGripHovered,
    cqweqasvfaCol_ResizeGripActive,
    cqweqasvfaCol_CloseButton,
    cqweqasvfaCol_CloseButtonHovered,
    cqweqasvfaCol_CloseButtonActive,
    cqweqasvfaCol_PlotLines,
    cqweqasvfaCol_PlotLinesHovered,
    cqweqasvfaCol_PlotHistogram,
    cqweqasvfaCol_PlotHistogramHovered,
    cqweqasvfaCol_TextSelectedBg,
    cqweqasvfaCol_ModalWindowDarkening,  // darken entire screen when a modal window is active
    cqweqasvfaCol_DragDropTarget,
    cqweqasvfaCol_COUNT

    // Obsolete names (will be removed)
#ifndef cqweqasvfa_DISABLE_OBSOLETE_FUNCTIONS
    //, cqweqasvfaCol_ComboBg = cqweqasvfaCol_PopupBg     // ComboBg has been merged with PopupBg, so a redirect isn't accurate.
    , cqweqasvfaCol_ChildWindowBg = cqweqasvfaCol_ChildBg, cqweqasvfaCol_Column = cqweqasvfaCol_Separator, cqweqasvfaCol_ColumnHovered = cqweqasvfaCol_SeparatorHovered, cqweqasvfaCol_ColumnActive = cqweqasvfaCol_SeparatorActive
#endif
};

// Enumeration for PushStyleVar() / PopStyleVar() to temporarily modify the cqweqasvfaStyle structure.
// NB: the enum only refers to fields of cqweqasvfaStyle which makes sense to be pushed/popped inside UI code. During initialization, feel free to just poke into cqweqasvfaStyle directly.
// NB: if changing this enum, you need to update the associated internal table GStyleVarInfo[] accordingly. This is where we link enum values to members offset/type.
enum cqweqasvfaStyleVar_
{
    // Enum name ......................// Member in cqweqasvfaStyle structure (see cqweqasvfaStyle for descriptions)
    cqweqasvfaStyleVar_Alpha,               // float     Alpha
    cqweqasvfaStyleVar_WindowPadding,       // ImVec2    WindowPadding
    cqweqasvfaStyleVar_WindowRounding,      // float     WindowRounding
    cqweqasvfaStyleVar_WindowBorderSize,    // float     WindowBorderSize
    cqweqasvfaStyleVar_WindowMinSize,       // ImVec2    WindowMinSize
    cqweqasvfaStyleVar_ChildRounding,       // float     ChildRounding
    cqweqasvfaStyleVar_ChildBorderSize,     // float     ChildBorderSize
    cqweqasvfaStyleVar_PopupRounding,       // float     PopupRounding
    cqweqasvfaStyleVar_PopupBorderSize,     // float     PopupBorderSize
    cqweqasvfaStyleVar_FramePadding,        // ImVec2    FramePadding
    cqweqasvfaStyleVar_FrameRounding,       // float     FrameRounding
    cqweqasvfaStyleVar_FrameBorderSize,     // float     FrameBorderSize
    cqweqasvfaStyleVar_ItemSpacing,         // ImVec2    ItemSpacing
    cqweqasvfaStyleVar_ItemInnerSpacing,    // ImVec2    ItemInnerSpacing
    cqweqasvfaStyleVar_IndentSpacing,       // float     IndentSpacing
    cqweqasvfaStyleVar_GrabMinSize,         // float     GrabMinSize
    cqweqasvfaStyleVar_ButtonTextAlign,     // ImVec2    ButtonTextAlign
    cqweqasvfaStyleVar_Count_

    // Obsolete names (will be removed)
#ifndef cqweqasvfa_DISABLE_OBSOLETE_FUNCTIONS
    , cqweqasvfaStyleVar_ChildWindowRounding = cqweqasvfaStyleVar_ChildRounding
#endif
};

// Enumeration for ColorEdit3() / ColorEdit4() / ColorPicker3() / ColorPicker4() / ColorButton()
enum cqweqasvfaColorEditFlags_
{
    cqweqasvfaColorEditFlags_NoAlpha = 1 << 1,   //              // ColorEdit, ColorPicker, ColorButton: ignore Alpha component (read 3 components from the input pointer).
    cqweqasvfaColorEditFlags_NoPicker = 1 << 2,   //              // ColorEdit: disable picker when clicking on colored square.
    cqweqasvfaColorEditFlags_NoOptions = 1 << 3,   //              // ColorEdit: disable toggling options menu when right-clicking on inputs/small preview.
    cqweqasvfaColorEditFlags_NoSmallPreview = 1 << 4,   //              // ColorEdit, ColorPicker: disable colored square preview next to the inputs. (e.g. to show only the inputs)
    cqweqasvfaColorEditFlags_NoInputs = 1 << 5,   //              // ColorEdit, ColorPicker: disable inputs sliders/text widgets (e.g. to show only the small preview colored square).
    cqweqasvfaColorEditFlags_NoTooltip = 1 << 6,   //              // ColorEdit, ColorPicker, ColorButton: disable tooltip when hovering the preview.
    cqweqasvfaColorEditFlags_NoLabel = 1 << 7,   //              // ColorEdit, ColorPicker: disable display of inline text label (the label is still forwarded to the tooltip and picker).
    cqweqasvfaColorEditFlags_NoSidePreview = 1 << 8,   //              // ColorPicker: disable bigger color preview on right side of the picker, use small colored square preview instead.
    // User Options (right-click on widget to change some of them). You can set application defaults using SetColorEditOptions(). The idea is that you probably don't want to override them in most of your calls, let the user choose and/or call SetColorEditOptions() during startup.
    cqweqasvfaColorEditFlags_AlphaBar = 1 << 9,   //              // ColorEdit, ColorPicker: show vertical alpha bar/gradient in picker.
    cqweqasvfaColorEditFlags_AlphaPreview = 1 << 10,  //              // ColorEdit, ColorPicker, ColorButton: display preview as a transparent color over a checkerboard, instead of opaque.
    cqweqasvfaColorEditFlags_AlphaPreviewHalf = 1 << 11,  //              // ColorEdit, ColorPicker, ColorButton: display half opaque / half checkerboard, instead of opaque.
    cqweqasvfaColorEditFlags_HDR = 1 << 12,  //              // (WIP) ColorEdit: Currently only disable 0.0f..1.0f limits in RGBA edition (note: you probably want to use cqweqasvfaColorEditFlags_Float flag as well).
    cqweqasvfaColorEditFlags_RGB = 1 << 13,  // [Inputs]     // ColorEdit: choose one among RGB/HSV/HEX. ColorPicker: choose any combination using RGB/HSV/HEX.
    cqweqasvfaColorEditFlags_HSV = 1 << 14,  // [Inputs]     // "
    cqweqasvfaColorEditFlags_HEX = 1 << 15,  // [Inputs]     // "
    cqweqasvfaColorEditFlags_Uint8 = 1 << 16,  // [DataType]   // ColorEdit, ColorPicker, ColorButton: _display_ values formatted as 0..255. 
    cqweqasvfaColorEditFlags_Float = 1 << 17,  // [DataType]   // ColorEdit, ColorPicker, ColorButton: _display_ values formatted as 0.0f..1.0f floats instead of 0..255 integers. No round-trip of value via integers.
    cqweqasvfaColorEditFlags_PickerHueBar = 1 << 18,  // [PickerMode] // ColorPicker: bar for Hue, rectangle for Sat/Value.
    cqweqasvfaColorEditFlags_PickerHueWheel = 1 << 19,  // [PickerMode] // ColorPicker: wheel for Hue, triangle for Sat/Value.
    // Internals/Masks
    cqweqasvfaColorEditFlags__InputsMask = cqweqasvfaColorEditFlags_RGB | cqweqasvfaColorEditFlags_HSV | cqweqasvfaColorEditFlags_HEX,
    cqweqasvfaColorEditFlags__DataTypeMask = cqweqasvfaColorEditFlags_Uint8 | cqweqasvfaColorEditFlags_Float,
    cqweqasvfaColorEditFlags__PickerMask = cqweqasvfaColorEditFlags_PickerHueWheel | cqweqasvfaColorEditFlags_PickerHueBar,
    cqweqasvfaColorEditFlags__OptionsDefault = cqweqasvfaColorEditFlags_Uint8 | cqweqasvfaColorEditFlags_RGB | cqweqasvfaColorEditFlags_PickerHueBar    // Change application default using SetColorEditOptions()
};

// Enumeration for GetMouseCursor()
enum cqweqasvfaMouseCursor_
{
    cqweqasvfaMouseCursor_None = -1,
    cqweqasvfaMouseCursor_Arrow = 0,
    cqweqasvfaMouseCursor_TextInput,         // When hovering over InputText, etc.
    cqweqasvfaMouseCursor_Move,              // Unused
    cqweqasvfaMouseCursor_ResizeNS,          // When hovering over an horizontal border
    cqweqasvfaMouseCursor_ResizeEW,          // When hovering over a vertical border or a column
    cqweqasvfaMouseCursor_ResizeNESW,        // When hovering over the bottom-left corner of a window
    cqweqasvfaMouseCursor_ResizeNWSE,        // When hovering over the bottom-right corner of a window
    cqweqasvfaMouseCursor_Count_
};

// Condition for cqweqasvfa::SetWindow***(), SetNextWindow***(), SetNextTreeNode***() functions
// All those functions treat 0 as a shortcut to cqweqasvfaCond_Always. From the point of view of the user use this as an enum (don't combine multiple values into flags).
enum cqweqasvfaCond_
{
    cqweqasvfaCond_Always = 1 << 0,   // Set the variable
    cqweqasvfaCond_Once = 1 << 1,   // Set the variable once per runtime session (only the first call with succeed)
    cqweqasvfaCond_FirstUseEver = 1 << 2,   // Set the variable if the window has no saved data (if doesn't exist in the .ini file)
    cqweqasvfaCond_Appearing = 1 << 3    // Set the variable if the window is appearing after being hidden/inactive (or the first time)

    // Obsolete names (will be removed)
#ifndef cqweqasvfa_DISABLE_OBSOLETE_FUNCTIONS
    , cqweqasvfaSetCond_Always = cqweqasvfaCond_Always, cqweqasvfaSetCond_Once = cqweqasvfaCond_Once, cqweqasvfaSetCond_FirstUseEver = cqweqasvfaCond_FirstUseEver, cqweqasvfaSetCond_Appearing = cqweqasvfaCond_Appearing
#endif
};

struct cqweqasvfaStyle
{
    float       Alpha;                      // Global alpha applies to everything in cqweqasvfa
    ImVec2      WindowPadding;              // Padding within a window
    float       WindowRounding;             // Radius of window corners rounding. Set to 0.0f to have rectangular windows
    float       WindowBorderSize;           // Thickness of border around windows. Generally set to 0.0f or 1.0f. (Other values are not well tested and more CPU/GPU costly)
    ImVec2      WindowMinSize;              // Minimum window size
    ImVec2      WindowTitleAlign;           // Alignment for title bar text. Defaults to (0.0f,0.5f) for left-aligned,vertically centered.
    float       ChildRounding;              // Radius of child window corners rounding. Set to 0.0f to have rectangular windows.
    float       ChildBorderSize;            // Thickness of border around child windows. Generally set to 0.0f or 1.0f. (Other values are not well tested and more CPU/GPU costly)
    float       PopupRounding;              // Radius of popup window corners rounding.
    float       PopupBorderSize;            // Thickness of border around popup windows. Generally set to 0.0f or 1.0f. (Other values are not well tested and more CPU/GPU costly)
    ImVec2      FramePadding;               // Padding within a framed rectangle (used by most widgets)
    float       FrameRounding;              // Radius of frame corners rounding. Set to 0.0f to have rectangular frame (used by most widgets).
    float       FrameBorderSize;            // Thickness of border around frames. Generally set to 0.0f or 1.0f. (Other values are not well tested and more CPU/GPU costly)
    ImVec2      ItemSpacing;                // Horizontal and vertical spacing between widgets/lines
    ImVec2      ItemInnerSpacing;           // Horizontal and vertical spacing between within elements of a composed widget (e.g. a slider and its label)
    ImVec2      TouchExtraPadding;          // Expand reactive bounding box for touch-based system where touch position is not accurate enough. Unfortunately we don't sort widgets so priority on overlap will always be given to the first widget. So don't grow this too much!
    float       IndentSpacing;              // Horizontal indentation when e.g. entering a tree node. Generally == (FontSize + FramePadding.x*2).
    float       ColumnsMinSpacing;          // Minimum horizontal spacing between two columns
    float       ScrollbarSize;              // Width of the vertical scrollbar, Height of the horizontal scrollbar
    float       ScrollbarRounding;          // Radius of grab corners for scrollbar
    float       GrabMinSize;                // Minimum width/height of a grab box for slider/scrollbar.
    float       GrabRounding;               // Radius of grabs corners rounding. Set to 0.0f to have rectangular slider grabs.
    ImVec2      ButtonTextAlign;            // Alignment of button text when button is larger than text. Defaults to (0.5f,0.5f) for horizontally+vertically centered.
    ImVec2      DisplayWindowPadding;       // Window positions are clamped to be visible within the display area by at least this amount. Only covers regular windows.
    ImVec2      DisplaySafeAreaPadding;     // If you cannot see the edge of your screen (e.g. on a TV) increase the safe area padding. Covers popups/tooltips as well regular windows.
    bool        AntiAliasedLines;           // Enable anti-aliasing on lines/borders. Disable if you are really tight on CPU/GPU.
    bool        AntiAliasedFill;            // Enable anti-aliasing on filled shapes (rounded rectangles, circles, etc.)
    float       CurveTessellationTol;       // Tessellation tolerance when using PathBezierCurveTo() without a specific number of segments. Decrease for highly tessellated curves (higher quality, more polygons), increase to reduce quality.
    ImVec4      Colors[cqweqasvfaCol_COUNT];

    cqweqasvfa_API cqweqasvfaStyle();
    cqweqasvfa_API void ScaleAllSizes(float scale_factor);
};

// This is where your app communicate with cqweqasvfa. Access via cqweqasvfa::GetIO().
// Read 'Programmer guide' section in .cpp file for general usage.
struct cqweqasvfaIO
{
    //------------------------------------------------------------------
    // Settings (fill once)                 // Default value:
    //------------------------------------------------------------------

    ImVec2        DisplaySize;              // <unset>              // Display size, in pixels. For clamping windows positions.
    float         DeltaTime;                // = 1.0f/60.0f         // Time elapsed since last frame, in seconds.
    float         IniSavingRate;            // = 5.0f               // Maximum time between saving positions/sizes to .ini file, in seconds.
    const char* IniFilename;              // = "cqweqasvfa.ini"        // Path to .ini file. NULL to disable .ini saving.
    const char* LogFilename;              // = "cqweqasvfa_log.txt"    // Path to .log file (default parameter to cqweqasvfa::LogToFile when no file is specified).
    float         MouseDoubleClickTime;     // = 0.30f              // Time for a double-click, in seconds.
    float         MouseDoubleClickMaxDist;  // = 6.0f               // Distance threshold to stay in to validate a double-click, in pixels.
    float         MouseDragThreshold;       // = 6.0f               // Distance threshold before considering we are dragging
    int           KeyMap[cqweqasvfaKey_COUNT];   // <unset>              // Map of indices into the KeysDown[512] entries array
    float         KeyRepeatDelay;           // = 0.250f             // When holding a key/button, time before it starts repeating, in seconds (for buttons in Repeat mode, etc.).
    float         KeyRepeatRate;            // = 0.050f             // When holding a key/button, rate at which it repeats, in seconds.
    void* UserData;                 // = NULL               // Store your own data for retrieval by callbacks.

    ImFontAtlas* Fonts;                    // <auto>               // Load and assemble one or more fonts into a single tightly packed texture. Output to Fonts array.
    float         FontGlobalScale;          // = 1.0f               // Global scale all fonts
    bool          FontAllowUserScaling;     // = false              // Allow user scaling text of individual window with CTRL+Wheel.
    ImFont* FontDefault;              // = NULL               // Font to use on NewFrame(). Use NULL to uses Fonts->Fonts[0].
    ImVec2        DisplayFramebufferScale;  // = (1.0f,1.0f)        // For retina display or other situations where window coordinates are different from framebuffer coordinates. User storage only, presently not used by cqweqasvfa.
    ImVec2        DisplayVisibleMin;        // <unset> (0.0f,0.0f)  // If you use DisplaySize as a virtual space larger than your screen, set DisplayVisibleMin/Max to the visible area.
    ImVec2        DisplayVisibleMax;        // <unset> (0.0f,0.0f)  // If the values are the same, we defaults to Min=(0.0f) and Max=DisplaySize

    // Advanced/subtle behaviors
    bool          OptMacOSXBehaviors;       // = defined(__APPLE__) // OS X style: Text editing cursor movement using Alt instead of Ctrl, Shortcuts using Cmd/Super instead of Ctrl, Line/Text Start and End using Cmd+Arrows instead of Home/End, Double click selects by word instead of selecting whole text, Multi-selection in lists uses Cmd/Super instead of Ctrl
    bool          OptCursorBlink;           // = true               // Enable blinking cursor, for users who consider it annoying.

    //------------------------------------------------------------------
    // Settings (User Functions)
    //------------------------------------------------------------------

    // Rendering function, will be called in Render().
    // Alternatively you can keep this to NULL and call GetDrawData() after Render() to get the same pointer.
    // See example applications if you are unsure of how to implement this.
    void        (*RenderDrawListsFn)(ImDrawData* data);

    // Optional: access OS clipboard
    // (default to use native Win32 clipboard on Windows, otherwise uses a private clipboard. Override to access OS clipboard on other architectures)
    const char* (*GetClipboardTextFn)(void* user_data);
    void        (*SetClipboardTextFn)(void* user_data, const char* text);
    void* ClipboardUserData;

    // Optional: override memory allocations. MemFreeFn() may be called with a NULL pointer.
    // (default to posix malloc/free)
    void* (*MemAllocFn)(size_t sz);
    void        (*MemFreeFn)(void* ptr);

    // Optional: notify OS Input Method Editor of the screen position of your cursor for text input position (e.g. when using Japanese/Chinese IME in Windows)
    // (default to use native imm32 api on Windows)
    void        (*ImeSetInputScreenPosFn)(int x, int y);
    void* ImeWindowHandle;            // (Windows) Set this to your HWND to get automatic IME cursor positioning.

    //------------------------------------------------------------------
    // Input - Fill before calling NewFrame()
    //------------------------------------------------------------------

    ImVec2      MousePos;                   // Mouse position, in pixels. Set to ImVec2(-FLT_MAX,-FLT_MAX) if mouse is unavailable (on another screen, etc.)
    bool        MouseDown[5];               // Mouse buttons: left, right, middle + extras. cqweqasvfa itself mostly only uses left button (BeginPopupContext** are using right button). Others buttons allows us to track if the mouse is being used by your application + available to user as a convenience via IsMouse** API.
    float       MouseWheel;                 // Mouse wheel: 1 unit scrolls about 5 lines text.
    bool        MouseDrawCursor;            // Request cqweqasvfa to draw a mouse cursor for you (if you are on a platform without a mouse cursor).
    bool        KeyCtrl;                    // Keyboard modifier pressed: Control
    bool        KeyShift;                   // Keyboard modifier pressed: Shift
    bool        KeyAlt;                     // Keyboard modifier pressed: Alt
    bool        KeySuper;                   // Keyboard modifier pressed: Cmd/Super/Windows
    bool        KeysDown[512];              // Keyboard keys that are pressed (in whatever storage order you naturally have access to keyboard data)
    ImWchar     InputCharacters[16 + 1];      // List of characters input (translated by user from keypress+keyboard state). Fill using AddInputCharacter() helper.

    // Functions
    cqweqasvfa_API void AddInputCharacter(ImWchar c);                        // Add new character into InputCharacters[]
    cqweqasvfa_API void AddInputCharactersUTF8(const char* utf8_chars);      // Add new characters into InputCharacters[] from an UTF-8 string
    inline void    ClearInputCharacters() { InputCharacters[0] = 0; }   // Clear the text input buffer manually

    //------------------------------------------------------------------
    // Output - Retrieve after calling NewFrame()
    //------------------------------------------------------------------

    bool        WantCaptureMouse;           // When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application. This is set by cqweqasvfa when it wants to use your mouse (e.g. unclicked mouse is hovering a window, or a widget is active). 
    bool        WantCaptureKeyboard;        // When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application. This is set by cqweqasvfa when it wants to use your keyboard inputs.
    bool        WantTextInput;              // Mobile/console: when io.WantTextInput is true, you may display an on-screen keyboard. This is set by cqweqasvfa when it wants textual keyboard input to happen (e.g. when a InputText widget is active).
    bool        WantMoveMouse;              // [BETA-NAV] MousePos has been altered, back-end should reposition mouse on next frame. Set only when 'NavMovesMouse=true'.
    float       Framerate;                  // Application framerate estimation, in frame per second. Solely for convenience. Rolling average estimation based on IO.DeltaTime over 120 frames
    int         MetricsAllocs;              // Number of active memory allocations
    int         MetricsRenderVertices;      // Vertices output during last call to Render()
    int         MetricsRenderIndices;       // Indices output during last call to Render() = number of triangles * 3
    int         MetricsActiveWindows;       // Number of visible root windows (exclude child windows)
    ImVec2      MouseDelta;                 // Mouse delta. Note that this is zero if either current or previous position are invalid (-FLT_MAX,-FLT_MAX), so a disappearing/reappearing mouse won't have a huge delta.

    //------------------------------------------------------------------
    // [Internal] cqweqasvfa will maintain those fields. Forward compatibility not guaranteed!
    //------------------------------------------------------------------

    ImVec2      MousePosPrev;               // Previous mouse position temporary storage (nb: not for public use, set to MousePos in NewFrame())
    ImVec2      MouseClickedPos[5];         // Position at time of clicking
    float       MouseClickedTime[5];        // Time of last click (used to figure out double-click)
    bool        MouseClicked[5];            // Mouse button went from !Down to Down
    bool        MouseDoubleClicked[5];      // Has mouse button been double-clicked?
    bool        MouseReleased[5];           // Mouse button went from Down to !Down
    bool        MouseDownOwned[5];          // Track if button was clicked inside a window. We don't request mouse capture from the application if click started outside cqweqasvfa bounds.
    float       MouseDownDuration[5];       // Duration the mouse button has been down (0.0f == just clicked)
    float       MouseDownDurationPrev[5];   // Previous time the mouse button has been down
    ImVec2      MouseDragMaxDistanceAbs[5]; // Maximum distance, absolute, on each axis, of how much mouse has traveled from the clicking point
    float       MouseDragMaxDistanceSqr[5]; // Squared maximum distance of how much mouse has traveled from the clicking point
    float       KeysDownDuration[512];      // Duration the keyboard key has been down (0.0f == just pressed)
    float       KeysDownDurationPrev[512];  // Previous duration the key has been down

    cqweqasvfa_API   cqweqasvfaIO();
};

//-----------------------------------------------------------------------------
// Obsolete functions (Will be removed! Also see 'API BREAKING CHANGES' section in cqweqasvfa.cpp)
//-----------------------------------------------------------------------------

#ifndef cqweqasvfa_DISABLE_OBSOLETE_FUNCTIONS
namespace cqweqasvfa
{
    static inline void  ShowTestWindow() { return ShowDemoWindow(); } // OBSOLETE 1.53+
    static inline bool  IsRootWindowFocused() { return IsWindowFocused(cqweqasvfaFocusedFlags_RootWindow); } // OBSOLETE 1.53+
    static inline bool  IsRootWindowOrAnyChildFocused() { return IsWindowFocused(cqweqasvfaFocusedFlags_RootAndChildWindows); } // OBSOLETE 1.53+
    static inline void  SetNextWindowContentWidth(float width) { SetNextWindowContentSize(ImVec2(width, 0.0f)); } // OBSOLETE 1.53+ (nb: original version preserved last Y value set by SetNextWindowContentSize())
    static inline bool  IsRootWindowOrAnyChildHovered(cqweqasvfaHoveredFlags flags = 0) { return IsItemHovered(flags | cqweqasvfaHoveredFlags_RootWindow | cqweqasvfaHoveredFlags_ChildWindows); } // OBSOLETE 1.53+ use flags directly
    bool                Begin(const char* name, bool* p_open, const ImVec2& size_on_first_use, float bg_alpha_override = -1.0f, cqweqasvfaWindowFlags flags = 0); // OBSOLETE 1.52+. use SetNextWindowSize() instead if you want to set a window size.
    static inline void  AlignFirstTextHeightToWidgets() { AlignTextToFramePadding(); }     // OBSOLETE 1.52+
    static inline void  SetNextWindowPosCenter(cqweqasvfaCond cond = 0) { SetNextWindowPos(ImVec2(GetIO().DisplaySize.x * 0.5f, GetIO().DisplaySize.y * 0.5f), cond, ImVec2(0.5f, 0.5f)); } // OBSOLETE 1.52+
    static inline bool  IsItemHoveredRect() { return IsItemHovered(cqweqasvfaHoveredFlags_RectOnly); } // OBSOLETE 1.51+
    static inline bool  IsPosHoveringAnyWindow(const ImVec2&) { IM_ASSERT(0); return false; } // OBSOLETE 1.51+. This was partly broken. You probably wanted to use cqweqasvfa::GetIO().WantCaptureMouse instead.
    static inline bool  IsMouseHoveringAnyWindow() { return IsAnyWindowHovered(); }        // OBSOLETE 1.51+
    static inline bool  IsMouseHoveringWindow() { return IsWindowHovered(cqweqasvfaHoveredFlags_AllowWhenBlockedByPopup | cqweqasvfaHoveredFlags_AllowWhenBlockedByActiveItem); } // OBSOLETE 1.51+
    static inline bool  CollapsingHeader(const char* label, const char* str_id, bool framed = true, bool default_open = false) { (void)str_id; (void)framed; cqweqasvfaTreeNodeFlags default_open_flags = 1 << 5; return CollapsingHeader(label, (default_open ? default_open_flags : 0)); } // OBSOLETE 1.49+
}
#endif

//-----------------------------------------------------------------------------
// Helpers
//-----------------------------------------------------------------------------

// Lightweight std::vector<> like class to avoid dragging dependencies (also: windows implementation of STL with debug enabled is absurdly slow, so let's bypass it so our code runs fast in debug).
// Our implementation does NOT call C++ constructors/destructors. This is intentional and we do not require it. Do not use this class as a straight std::vector replacement in your code!
template<typename T>
class ImVector
{
public:
    int                         Size;
    int                         Capacity;
    T* Data;

    typedef T                   value_type;
    typedef value_type* iterator;
    typedef const value_type* const_iterator;

    inline ImVector() { Size = Capacity = 0; Data = NULL; }
    inline ~ImVector() { if (Data) cqweqasvfa::MemFree(Data); }

    inline bool                 empty() const { return Size == 0; }
    inline int                  size() const { return Size; }
    inline int                  capacity() const { return Capacity; }

    inline value_type& operator[](int i) { IM_ASSERT(i < Size); return Data[i]; }
    inline const value_type& operator[](int i) const { IM_ASSERT(i < Size); return Data[i]; }

    inline void                 clear() { if (Data) { Size = Capacity = 0; cqweqasvfa::MemFree(Data); Data = NULL; } }
    inline iterator             begin() { return Data; }
    inline const_iterator       begin() const { return Data; }
    inline iterator             end() { return Data + Size; }
    inline const_iterator       end() const { return Data + Size; }
    inline value_type& front() { IM_ASSERT(Size > 0); return Data[0]; }
    inline const value_type& front() const { IM_ASSERT(Size > 0); return Data[0]; }
    inline value_type& back() { IM_ASSERT(Size > 0); return Data[Size - 1]; }
    inline const value_type& back() const { IM_ASSERT(Size > 0); return Data[Size - 1]; }
    inline void                 swap(ImVector<T>& rhs) { int rhs_size = rhs.Size; rhs.Size = Size; Size = rhs_size; int rhs_cap = rhs.Capacity; rhs.Capacity = Capacity; Capacity = rhs_cap; value_type* rhs_data = rhs.Data; rhs.Data = Data; Data = rhs_data; }

    inline int                  _grow_capacity(int size) const { int new_capacity = Capacity ? (Capacity + Capacity / 2) : 8; return new_capacity > size ? new_capacity : size; }

    inline void                 resize(int new_size) { if (new_size > Capacity) reserve(_grow_capacity(new_size)); Size = new_size; }
    inline void                 resize(int new_size, const T& v) { if (new_size > Capacity) reserve(_grow_capacity(new_size)); if (new_size > Size) for (int n = Size; n < new_size; n++) Data[n] = v; Size = new_size; }
    inline void                 reserve(int new_capacity)
    {
        if (new_capacity <= Capacity)
            return;
        T* new_data = (value_type*)cqweqasvfa::MemAlloc((size_t)new_capacity * sizeof(T));
        if (Data)
            memcpy(new_data, Data, (size_t)Size * sizeof(T));
        cqweqasvfa::MemFree(Data);
        Data = new_data;
        Capacity = new_capacity;
    }

    inline void                 push_back(const value_type& v) { if (Size == Capacity) reserve(_grow_capacity(Size + 1)); Data[Size++] = v; }
    inline void                 pop_back() { IM_ASSERT(Size > 0); Size--; }
    inline void                 push_front(const value_type& v) { if (Size == 0) push_back(v); else insert(Data, v); }

    inline iterator             erase(const_iterator it) { IM_ASSERT(it >= Data && it < Data + Size); const ptrdiff_t off = it - Data; memmove(Data + off, Data + off + 1, ((size_t)Size - (size_t)off - 1) * sizeof(value_type)); Size--; return Data + off; }
    inline iterator             insert(const_iterator it, const value_type& v) { IM_ASSERT(it >= Data && it <= Data + Size); const ptrdiff_t off = it - Data; if (Size == Capacity) reserve(_grow_capacity(Size + 1)); if (off < (int)Size) memmove(Data + off + 1, Data + off, ((size_t)Size - (size_t)off) * sizeof(value_type)); Data[off] = v; Size++; return Data + off; }
    inline bool                 contains(const value_type& v) const { const T* data = Data;  const T* data_end = Data + Size; while (data < data_end) if (*data++ == v) return true; return false; }
};

// Helper: execute a block of code at maximum once a frame. Convenient if you want to quickly create an UI within deep-nested code that runs multiple times every frame.
// Usage:
//   static cqweqasvfaOnceUponAFrame oaf;
//   if (oaf)
//       cqweqasvfa::Text("This will be called only once per frame");
struct cqweqasvfaOnceUponAFrame
{
    cqweqasvfaOnceUponAFrame() { RefFrame = -1; }
    mutable int RefFrame;
    operator bool() const { int current_frame = cqweqasvfa::GetFrameCount(); if (RefFrame == current_frame) return false; RefFrame = current_frame; return true; }
};

// Helper macro for cqweqasvfaOnceUponAFrame. Attention: The macro expands into 2 statement so make sure you don't use it within e.g. an if() statement without curly braces.
#ifndef cqweqasvfa_DISABLE_OBSOLETE_FUNCTIONS    // Will obsolete
#define cqweqasvfa_ONCE_UPON_A_FRAME     static cqweqasvfaOnceUponAFrame cqweqasvfa_oaf; if (cqweqasvfa_oaf)
#endif

// Helper: Parse and apply text filters. In format "aaaaa[,bbbb][,ccccc]"
struct cqweqasvfaTextFilter
{
    struct TextRange
    {
        const char* b;
        const char* e;

        TextRange() { b = e = NULL; }
        TextRange(const char* _b, const char* _e) { b = _b; e = _e; }
        const char* begin() const { return b; }
        const char* end() const { return e; }
        bool empty() const { return b == e; }
        char front() const { return *b; }
        static bool is_blank(char c) { return c == ' ' || c == '\t'; }
        void trim_blanks() { while (b < e && is_blank(*b)) b++; while (e > b && is_blank(*(e - 1))) e--; }
        cqweqasvfa_API void split(char separator, ImVector<TextRange>& out);
    };

    char                InputBuf[256];
    ImVector<TextRange> Filters;
    int                 CountGrep;

    cqweqasvfa_API           cqweqasvfaTextFilter(const char* default_filter = "");
    cqweqasvfa_API bool      Draw(const char* label = "Filter (inc,-exc)", float width = 0.0f);    // Helper calling InputText+Build
    cqweqasvfa_API bool      PassFilter(const char* text, const char* text_end = NULL) const;
    cqweqasvfa_API void      Build();
    void                Clear() { InputBuf[0] = 0; Build(); }
    bool                IsActive() const { return !Filters.empty(); }
};

// Helper: Text buffer for logging/accumulating text
struct cqweqasvfaTextBuffer
{
    ImVector<char>      Buf;

    cqweqasvfaTextBuffer() { Buf.push_back(0); }
    inline char         operator[](int i) { return Buf.Data[i]; }
    const char* begin() const { return &Buf.front(); }
    const char* end() const { return &Buf.back(); }      // Buf is zero-terminated, so end() will point on the zero-terminator
    int                 size() const { return Buf.Size - 1; }
    bool                empty() { return Buf.Size <= 1; }
    void                clear() { Buf.clear(); Buf.push_back(0); }
    void                reserve(int capacity) { Buf.reserve(capacity); }
    const char* c_str() const { return Buf.Data; }
    cqweqasvfa_API void      appendf(const char* fmt, ...) IM_FMTARGS(2);
    cqweqasvfa_API void      appendfv(const char* fmt, va_list args) IM_FMTLIST(2);
};

// Helper: Simple Key->value storage
// Typically you don't have to worry about this since a storage is held within each Window.
// We use it to e.g. store collapse state for a tree (Int 0/1), store color edit options. 
// This is optimized for efficient reading (dichotomy into a contiguous buffer), rare writing (typically tied to user interactions)
// You can use it as custom user storage for temporary values. Declare your own storage if, for example:
// - You want to manipulate the open/close state of a particular sub-tree in your interface (tree node uses Int 0/1 to store their state).
// - You want to store custom debug data easily without adding or editing structures in your code (probably not efficient, but convenient)
// Types are NOT stored, so it is up to you to make sure your Key don't collide with different types.
struct cqweqasvfaStorage
{
    struct Pair
    {
        cqweqasvfaID key;
        union { int val_i; float val_f; void* val_p; };
        Pair(cqweqasvfaID _key, int _val_i) { key = _key; val_i = _val_i; }
        Pair(cqweqasvfaID _key, float _val_f) { key = _key; val_f = _val_f; }
        Pair(cqweqasvfaID _key, void* _val_p) { key = _key; val_p = _val_p; }
    };
    ImVector<Pair>      Data;

    // - Get***() functions find pair, never add/allocate. Pairs are sorted so a query is O(log N)
    // - Set***() functions find pair, insertion on demand if missing.
    // - Sorted insertion is costly, paid once. A typical frame shouldn't need to insert any new pair.
    void                Clear() { Data.clear(); }
    cqweqasvfa_API int       GetInt(cqweqasvfaID key, int default_val = 0) const;
    cqweqasvfa_API void      SetInt(cqweqasvfaID key, int val);
    cqweqasvfa_API bool      GetBool(cqweqasvfaID key, bool default_val = false) const;
    cqweqasvfa_API void      SetBool(cqweqasvfaID key, bool val);
    cqweqasvfa_API float     GetFloat(cqweqasvfaID key, float default_val = 0.0f) const;
    cqweqasvfa_API void      SetFloat(cqweqasvfaID key, float val);
    cqweqasvfa_API void* GetVoidPtr(cqweqasvfaID key) const; // default_val is NULL
    cqweqasvfa_API void      SetVoidPtr(cqweqasvfaID key, void* val);

    // - Get***Ref() functions finds pair, insert on demand if missing, return pointer. Useful if you intend to do Get+Set.
    // - References are only valid until a new value is added to the storage. Calling a Set***() function or a Get***Ref() function invalidates the pointer.
    // - A typical use case where this is convenient for quick hacking (e.g. add storage during a live Edit&Continue session if you can't modify existing struct)
    //      float* pvar = cqweqasvfa::GetFloatRef(key); cqweqasvfa::SliderFloat("var", pvar, 0, 100.0f); some_var += *pvar;
    cqweqasvfa_API int* GetIntRef(cqweqasvfaID key, int default_val = 0);
    cqweqasvfa_API bool* GetBoolRef(cqweqasvfaID key, bool default_val = false);
    cqweqasvfa_API float* GetFloatRef(cqweqasvfaID key, float default_val = 0.0f);
    cqweqasvfa_API void** GetVoidPtrRef(cqweqasvfaID key, void* default_val = NULL);

    // Use on your own storage if you know only integer are being stored (open/close all tree nodes)
    cqweqasvfa_API void      SetAllInt(int val);

    // For quicker full rebuild of a storage (instead of an incremental one), you may add all your contents and then sort once.
    cqweqasvfa_API void      BuildSortByKey();
};

// Shared state of InputText(), passed to callback when a cqweqasvfaInputTextFlags_Callback* flag is used and the corresponding callback is triggered.
struct cqweqasvfaTextEditCallbackData
{
    cqweqasvfaInputTextFlags EventFlag;      // One of cqweqasvfaInputTextFlags_Callback* // Read-only
    cqweqasvfaInputTextFlags Flags;          // What user passed to InputText()      // Read-only
    void* UserData;       // What user passed to InputText()      // Read-only
    bool                ReadOnly;       // Read-only mode                       // Read-only

    // CharFilter event:
    ImWchar             EventChar;      // Character input                      // Read-write (replace character or set to zero)

    // Completion,History,Always events:
    // If you modify the buffer contents make sure you update 'BufTextLen' and set 'BufDirty' to true.
    cqweqasvfaKey            EventKey;       // Key pressed (Up/Down/TAB)            // Read-only
    char* Buf;            // Current text buffer                  // Read-write (pointed data only, can't replace the actual pointer)
    int                 BufTextLen;     // Current text length in bytes         // Read-write
    int                 BufSize;        // Maximum text length in bytes         // Read-only
    bool                BufDirty;       // Set if you modify Buf/BufTextLen!!   // Write
    int                 CursorPos;      //                                      // Read-write
    int                 SelectionStart; //                                      // Read-write (== to SelectionEnd when no selection)
    int                 SelectionEnd;   //                                      // Read-write

    // NB: Helper functions for text manipulation. Calling those function loses selection.
    cqweqasvfa_API void    DeleteChars(int pos, int bytes_count);
    cqweqasvfa_API void    InsertChars(int pos, const char* text, const char* text_end = NULL);
    bool              HasSelection() const { return SelectionStart != SelectionEnd; }
};

// Resizing callback data to apply custom constraint. As enabled by SetNextWindowSizeConstraints(). Callback is called during the next Begin().
// NB: For basic min/max size constraint on each axis you don't need to use the callback! The SetNextWindowSizeConstraints() parameters are enough.
struct cqweqasvfaSizeConstraintCallbackData
{
    void* UserData;       // Read-only.   What user passed to SetNextWindowSizeConstraints()
    ImVec2  Pos;            // Read-only.   Window position, for reference.
    ImVec2  CurrentSize;    // Read-only.   Current window size.
    ImVec2  DesiredSize;    // Read-write.  Desired size, based on user's mouse position. Write to this field to restrain resizing.
};

// Data payload for Drag and Drop operations
struct cqweqasvfaPayload
{
    // Members
    const void* Data;               // Data (copied and owned by dear cqweqasvfa)
    int             DataSize;           // Data size

    // [Internal]
    cqweqasvfaID         SourceId;           // Source item id
    cqweqasvfaID         SourceParentId;     // Source parent id (if available)
    int             DataFrameCount;     // Data timestamp
    char            DataType[8 + 1];    // Data type tag (short user-supplied string)
    bool            Preview;            // Set when AcceptDragDropPayload() was called and mouse has been hovering the target item (nb: handle overlapping drag targets)
    bool            Delivery;           // Set when AcceptDragDropPayload() was called and mouse button is released over the target item.

    cqweqasvfaPayload() { Clear(); }
    void Clear() { SourceId = SourceParentId = 0; Data = NULL; DataSize = 0; memset(DataType, 0, sizeof(DataType)); DataFrameCount = -1; Preview = Delivery = false; }
    bool IsDataType(const char* type) const { return DataFrameCount != -1 && strcmp(type, DataType) == 0; }
    bool IsPreview() const { return Preview; }
    bool IsDelivery() const { return Delivery; }
};

// Helpers macros to generate 32-bits encoded colors
#ifdef cqweqasvfa_USE_BGRA_PACKED_COLOR
#define IM_COL32_R_SHIFT    16
#define IM_COL32_G_SHIFT    8
#define IM_COL32_B_SHIFT    0
#define IM_COL32_A_SHIFT    24
#define IM_COL32_A_MASK     0xFF000000
#else
#define IM_COL32_R_SHIFT    0
#define IM_COL32_G_SHIFT    8
#define IM_COL32_B_SHIFT    16
#define IM_COL32_A_SHIFT    24
#define IM_COL32_A_MASK     0xFF000000
#endif
#define IM_COL32(R,G,B,A)    (((ImU32)(A)<<IM_COL32_A_SHIFT) | ((ImU32)(B)<<IM_COL32_B_SHIFT) | ((ImU32)(G)<<IM_COL32_G_SHIFT) | ((ImU32)(R)<<IM_COL32_R_SHIFT))
#define IM_COL32_WHITE       IM_COL32(255,255,255,255)  // Opaque white = 0xFFFFFFFF
#define IM_COL32_BLACK       IM_COL32(0,0,0,255)        // Opaque black
#define IM_COL32_BLACK_TRANS IM_COL32(0,0,0,0)          // Transparent black = 0x00000000

// ImColor() helper to implicity converts colors to either ImU32 (packed 4x1 byte) or ImVec4 (4x1 float)
// Prefer using IM_COL32() macros if you want a guaranteed compile-time ImU32 for usage with ImDrawList API.
// **Avoid storing ImColor! Store either u32 of ImVec4. This is not a full-featured color class. MAY OBSOLETE.
// **None of the cqweqasvfa API are using ImColor directly but you can use it as a convenience to pass colors in either ImU32 or ImVec4 formats. Explicitly cast to ImU32 or ImVec4 if needed.
struct ImColor
{
    ImVec4              Value;

    ImColor() { Value.x = Value.y = Value.z = Value.w = 0.0f; }
    ImColor(int r, int g, int b, int a = 255) { float sc = 1.0f / 255.0f; Value.x = (float)r * sc; Value.y = (float)g * sc; Value.z = (float)b * sc; Value.w = (float)a * sc; }
    ImColor(ImU32 rgba) { float sc = 1.0f / 255.0f; Value.x = (float)((rgba >> IM_COL32_R_SHIFT) & 0xFF) * sc; Value.y = (float)((rgba >> IM_COL32_G_SHIFT) & 0xFF) * sc; Value.z = (float)((rgba >> IM_COL32_B_SHIFT) & 0xFF) * sc; Value.w = (float)((rgba >> IM_COL32_A_SHIFT) & 0xFF) * sc; }
    ImColor(float r, float g, float b, float a = 1.0f) { Value.x = r; Value.y = g; Value.z = b; Value.w = a; }
    ImColor(const ImVec4& col) { Value = col; }
    inline operator ImU32() const { return cqweqasvfa::ColorConvertFloat4ToU32(Value); }
    inline operator ImVec4() const { return Value; }

    // FIXME-OBSOLETE: May need to obsolete/cleanup those helpers.
    inline void    SetHSV(float h, float s, float v, float a = 1.0f) { cqweqasvfa::ColorConvertHSVtoRGB(h, s, v, Value.x, Value.y, Value.z); Value.w = a; }
    static ImColor HSV(float h, float s, float v, float a = 1.0f) { float r, g, b; cqweqasvfa::ColorConvertHSVtoRGB(h, s, v, r, g, b); return ImColor(r, g, b, a); }
};

// Helper: Manually clip large list of items.
// If you are submitting lots of evenly spaced items and you have a random access to the list, you can perform coarse clipping based on visibility to save yourself from processing those items at all.
// The clipper calculates the range of visible items and advance the cursor to compensate for the non-visible items we have skipped. 
// cqweqasvfa already clip items based on their bounds but it needs to measure text size to do so. Coarse clipping before submission makes this cost and your own data fetching/submission cost null.
// Usage:
//     cqweqasvfaListClipper clipper(1000);  // we have 1000 elements, evenly spaced.
//     while (clipper.Step())
//         for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
//             cqweqasvfa::Text("line number %d", i);
// - Step 0: the clipper let you process the first element, regardless of it being visible or not, so we can measure the element height (step skipped if we passed a known height as second arg to constructor).
// - Step 1: the clipper infer height from first element, calculate the actual range of elements to display, and position the cursor before the first element.
// - (Step 2: dummy step only required if an explicit items_height was passed to constructor or Begin() and user call Step(). Does nothing and switch to Step 3.)
// - Step 3: the clipper validate that we have reached the expected Y position (corresponding to element DisplayEnd), advance the cursor to the end of the list and then returns 'false' to end the loop.
struct cqweqasvfaListClipper
{
    float   StartPosY;
    float   ItemsHeight;
    int     ItemsCount, StepNo, DisplayStart, DisplayEnd;

    // items_count:  Use -1 to ignore (you can call Begin later). Use INT_MAX if you don't know how many items you have (in which case the cursor won't be advanced in the final step).
    // items_height: Use -1.0f to be calculated automatically on first step. Otherwise pass in the distance between your items, typically GetTextLineHeightWithSpacing() or GetFrameHeightWithSpacing().
    // If you don't specify an items_height, you NEED to call Step(). If you specify items_height you may call the old Begin()/End() api directly, but prefer calling Step().
    cqweqasvfaListClipper(int items_count = -1, float items_height = -1.0f) { Begin(items_count, items_height); } // NB: Begin() initialize every fields (as we allow user to call Begin/End multiple times on a same instance if they want).
    ~cqweqasvfaListClipper() { IM_ASSERT(ItemsCount == -1); }      // Assert if user forgot to call End() or Step() until false.

    cqweqasvfa_API bool Step();                                              // Call until it returns false. The DisplayStart/DisplayEnd fields will be set and you can process/draw those items.
    cqweqasvfa_API void Begin(int items_count, float items_height = -1.0f);  // Automatically called by constructor if you passed 'items_count' or by Step() in Step 1.
    cqweqasvfa_API void End();                                               // Automatically called on the last call of Step() that returns false.
};

//-----------------------------------------------------------------------------
// Draw List
// Hold a series of drawing commands. The user provides a renderer for ImDrawData which essentially contains an array of ImDrawList.
//-----------------------------------------------------------------------------

// Draw callbacks for advanced uses.
// NB- You most likely do NOT need to use draw callbacks just to create your own widget or customized UI rendering (you can poke into the draw list for that)
// Draw callback may be useful for example, A) Change your GPU render state, B) render a complex 3D scene inside a UI element (without an intermediate texture/render target), etc.
// The expected behavior from your rendering function is 'if (cmd.UserCallback != NULL) cmd.UserCallback(parent_list, cmd); else RenderTriangles()'
typedef void (*ImDrawCallback)(const ImDrawList* parent_list, const ImDrawCmd* cmd);

// Typically, 1 command = 1 GPU draw call (unless command is a callback)
struct ImDrawCmd
{
    unsigned int    ElemCount;              // Number of indices (multiple of 3) to be rendered as triangles. Vertices are stored in the callee ImDrawList's vtx_buffer[] array, indices in idx_buffer[].
    ImVec4          ClipRect;               // Clipping rectangle (x1, y1, x2, y2)
    ImTextureID     TextureId;              // User-provided texture ID. Set by user in ImfontAtlas::SetTexID() for fonts or passed to Image*() functions. Ignore if never using images or multiple fonts atlas.
    ImDrawCallback  UserCallback;           // If != NULL, call the function instead of rendering the vertices. clip_rect and texture_id will be set normally.
    void* UserCallbackData;       // The draw callback code can access this.

    ImDrawCmd() { ElemCount = 0; ClipRect.x = ClipRect.y = ClipRect.z = ClipRect.w = 0.0f; TextureId = NULL; UserCallback = NULL; UserCallbackData = NULL; }
};

// Vertex index (override with '#define ImDrawIdx unsigned int' inside in imconfig.h)
#ifndef ImDrawIdx
typedef unsigned short ImDrawIdx;
#endif

// Vertex layout
#ifndef cqweqasvfa_OVERRIDE_DRAWVERT_STRUCT_LAYOUT
struct ImDrawVert
{
    ImVec2  pos;
    ImVec2  uv;
    ImU32   col;
};
#else
// You can override the vertex format layout by defining cqweqasvfa_OVERRIDE_DRAWVERT_STRUCT_LAYOUT in imconfig.h
// The code expect ImVec2 pos (8 bytes), ImVec2 uv (8 bytes), ImU32 col (4 bytes), but you can re-order them or add other fields as needed to simplify integration in your engine.
// The type has to be described within the macro (you can either declare the struct or use a typedef)
// NOTE: cqweqasvfa DOESN'T CLEAR THE STRUCTURE AND DOESN'T CALL A CONSTRUCTOR SO ANY CUSTOM FIELD WILL BE UNINITIALIZED. IF YOU ADD EXTRA FIELDS (SUCH AS A 'Z' COORDINATES) YOU WILL NEED TO CLEAR THEM DURING RENDER OR TO IGNORE THEM. 
cqweqasvfa_OVERRIDE_DRAWVERT_STRUCT_LAYOUT;
#endif

// Draw channels are used by the Columns API to "split" the render list into different channels while building, so items of each column can be batched together.
// You can also use them to simulate drawing layers and submit primitives in a different order than how they will be rendered.
struct ImDrawChannel
{
    ImVector<ImDrawCmd>     CmdBuffer;
    ImVector<ImDrawIdx>     IdxBuffer;
};

enum ImDrawCornerFlags_
{
    ImDrawCornerFlags_TopLeft = 1 << 0, // 0x1
    ImDrawCornerFlags_TopRight = 1 << 1, // 0x2
    ImDrawCornerFlags_BotLeft = 1 << 2, // 0x4
    ImDrawCornerFlags_BotRight = 1 << 3, // 0x8
    ImDrawCornerFlags_Top = ImDrawCornerFlags_TopLeft | ImDrawCornerFlags_TopRight,   // 0x3
    ImDrawCornerFlags_Bot = ImDrawCornerFlags_BotLeft | ImDrawCornerFlags_BotRight,   // 0xC
    ImDrawCornerFlags_Left = ImDrawCornerFlags_TopLeft | ImDrawCornerFlags_BotLeft,    // 0x5
    ImDrawCornerFlags_Right = ImDrawCornerFlags_TopRight | ImDrawCornerFlags_BotRight,  // 0xA
    ImDrawCornerFlags_All = 0xF     // In your function calls you may use ~0 (= all bits sets) instead of ImDrawCornerFlags_All, as a convenience
};

enum ImDrawListFlags_
{
    ImDrawListFlags_AntiAliasedLines = 1 << 0,
    ImDrawListFlags_AntiAliasedFill = 1 << 1
};

// Draw command list
// This is the low-level list of polygons that cqweqasvfa functions are filling. At the end of the frame, all command lists are passed to your cqweqasvfaIO::RenderDrawListFn function for rendering.
// Each cqweqasvfa window contains its own ImDrawList. You can use cqweqasvfa::GetWindowDrawList() to access the current window draw list and draw custom primitives.
// You can interleave normal cqweqasvfa:: calls and adding primitives to the current draw list.
// All positions are generally in pixel coordinates (top-left at (0,0), bottom-right at io.DisplaySize), however you are totally free to apply whatever transformation matrix to want to the data (if you apply such transformation you'll want to apply it to ClipRect as well)
// Important: Primitives are always added to the list and not culled (culling is done at higher-level by cqweqasvfa:: functions), if you use this API a lot consider coarse culling your drawn objects.
struct ImDrawList
{
    // This is what you have to render
    ImVector<ImDrawCmd>     CmdBuffer;          // Draw commands. Typically 1 command = 1 GPU draw call, unless the command is a callback.
    ImVector<ImDrawIdx>     IdxBuffer;          // Index buffer. Each command consume ImDrawCmd::ElemCount of those
    ImVector<ImDrawVert>    VtxBuffer;          // Vertex buffer.

    // [Internal, used while building lists]
    ImDrawListFlags         Flags;              // Flags, you may poke into these to adjust anti-aliasing settings per-primitive.
    const ImDrawListSharedData* _Data;          // Pointer to shared draw data (you can use cqweqasvfa::GetDrawListSharedData() to get the one from current cqweqasvfa context)
    const char* _OwnerName;         // Pointer to owner window's name for debugging
    unsigned int            _VtxCurrentIdx;     // [Internal] == VtxBuffer.Size
    ImDrawVert* _VtxWritePtr;       // [Internal] point within VtxBuffer.Data after each add command (to avoid using the ImVector<> operators too much)
    ImDrawIdx* _IdxWritePtr;       // [Internal] point within IdxBuffer.Data after each add command (to avoid using the ImVector<> operators too much)
    ImVector<ImVec4>        _ClipRectStack;     // [Internal]
    ImVector<ImTextureID>   _TextureIdStack;    // [Internal]
    ImVector<ImVec2>        _Path;              // [Internal] current path building
    int                     _ChannelsCurrent;   // [Internal] current channel number (0)
    int                     _ChannelsCount;     // [Internal] number of active channels (1+)
    ImVector<ImDrawChannel> _Channels;          // [Internal] draw channels for columns API (not resized down so _ChannelsCount may be smaller than _Channels.Size)

    ImDrawList(const ImDrawListSharedData* shared_data) { _Data = shared_data; _OwnerName = NULL; Clear(); }
    ~ImDrawList() { ClearFreeMemory(); }
    cqweqasvfa_API void  PushClipRect(ImVec2 clip_rect_min, ImVec2 clip_rect_max, bool intersect_with_current_clip_rect = false);  // Render-level scissoring. This is passed down to your render function but not used for CPU-side coarse clipping. Prefer using higher-level cqweqasvfa::PushClipRect() to affect logic (hit-testing and widget culling)
    cqweqasvfa_API void  PushClipRectFullScreen();
    cqweqasvfa_API void  PopClipRect();
    cqweqasvfa_API void  PushTextureID(const ImTextureID& texture_id);
    cqweqasvfa_API void  PopTextureID();
    inline ImVec2   GetClipRectMin() const { const ImVec4& cr = _ClipRectStack.back(); return ImVec2(cr.x, cr.y); }
    inline ImVec2   GetClipRectMax() const { const ImVec4& cr = _ClipRectStack.back(); return ImVec2(cr.z, cr.w); }

    // Primitives
    cqweqasvfa_API void  AddLine(const ImVec2& a, const ImVec2& b, ImU32 col, float thickness = 1.0f);
    cqweqasvfa_API void  AddRect(const ImVec2& a, const ImVec2& b, ImU32 col, float rounding = 0.0f, int rounding_corners_flags = ImDrawCornerFlags_All, float thickness = 1.0f);   // a: upper-left, b: lower-right, rounding_corners_flags: 4-bits corresponding to which corner to round
    cqweqasvfa_API void  AddRectFilled(const ImVec2& a, const ImVec2& b, ImU32 col, float rounding = 0.0f, int rounding_corners_flags = ImDrawCornerFlags_All);                     // a: upper-left, b: lower-right
    cqweqasvfa_API void  AddRectFilledMultiColor(const ImVec2& a, const ImVec2& b, ImU32 col_upr_left, ImU32 col_upr_right, ImU32 col_bot_right, ImU32 col_bot_left);
    cqweqasvfa_API void  AddQuad(const ImVec2& a, const ImVec2& b, const ImVec2& c, const ImVec2& d, ImU32 col, float thickness = 1.0f);
    cqweqasvfa_API void  AddQuadFilled(const ImVec2& a, const ImVec2& b, const ImVec2& c, const ImVec2& d, ImU32 col);
    cqweqasvfa_API void  AddTriangle(const ImVec2& a, const ImVec2& b, const ImVec2& c, ImU32 col, float thickness = 1.0f);
    cqweqasvfa_API void  AddTriangleFilled(const ImVec2& a, const ImVec2& b, const ImVec2& c, ImU32 col);
    cqweqasvfa_API void  AddCircle(const ImVec2& centre, float radius, ImU32 col, int num_segments = 12, float thickness = 1.0f);
    cqweqasvfa_API void  AddCircleFilled(const ImVec2& centre, float radius, ImU32 col, int num_segments = 12);
    cqweqasvfa_API void  AddText(const ImVec2& pos, ImU32 col, const char* text_begin, const char* text_end = NULL);
    cqweqasvfa_API void  AddText(const ImFont* font, float font_size, const ImVec2& pos, ImU32 col, const char* text_begin, const char* text_end = NULL, float wrap_width = 0.0f, const ImVec4* cpu_fine_clip_rect = NULL);
    cqweqasvfa_API void  AddImage(ImTextureID user_texture_id, const ImVec2& a, const ImVec2& b, const ImVec2& uv_a = ImVec2(0, 0), const ImVec2& uv_b = ImVec2(1, 1), ImU32 col = 0xFFFFFFFF);
    cqweqasvfa_API void  AddImageQuad(ImTextureID user_texture_id, const ImVec2& a, const ImVec2& b, const ImVec2& c, const ImVec2& d, const ImVec2& uv_a = ImVec2(0, 0), const ImVec2& uv_b = ImVec2(1, 0), const ImVec2& uv_c = ImVec2(1, 1), const ImVec2& uv_d = ImVec2(0, 1), ImU32 col = 0xFFFFFFFF);
    cqweqasvfa_API void  AddImageRounded(ImTextureID user_texture_id, const ImVec2& a, const ImVec2& b, const ImVec2& uv_a, const ImVec2& uv_b, ImU32 col, float rounding, int rounding_corners = ImDrawCornerFlags_All);
    cqweqasvfa_API void  AddPolyline(const ImVec2* points, const int num_points, ImU32 col, bool closed, float thickness);
    cqweqasvfa_API void  AddConvexPolyFilled(const ImVec2* points, const int num_points, ImU32 col);
    cqweqasvfa_API void  AddBezierCurve(const ImVec2& pos0, const ImVec2& cp0, const ImVec2& cp1, const ImVec2& pos1, ImU32 col, float thickness, int num_segments = 0);

    // Stateful path API, add points then finish with PathFill() or PathStroke()
    inline    void  PathClear() { _Path.resize(0); }
    inline    void  PathLineTo(const ImVec2& pos) { _Path.push_back(pos); }
    inline    void  PathLineToMergeDuplicate(const ImVec2& pos) { if (_Path.Size == 0 || memcmp(&_Path[_Path.Size - 1], &pos, 8) != 0) _Path.push_back(pos); }
    inline    void  PathFillConvex(ImU32 col) { AddConvexPolyFilled(_Path.Data, _Path.Size, col); PathClear(); }
    inline    void  PathStroke(ImU32 col, bool closed, float thickness = 1.0f) { AddPolyline(_Path.Data, _Path.Size, col, closed, thickness); PathClear(); }
    cqweqasvfa_API void  PathArcTo(const ImVec2& centre, float radius, float a_min, float a_max, int num_segments = 10);
    cqweqasvfa_API void  PathArcToFast(const ImVec2& centre, float radius, int a_min_of_12, int a_max_of_12);                                // Use precomputed angles for a 12 steps circle
    cqweqasvfa_API void  PathBezierCurveTo(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, int num_segments = 0);
    cqweqasvfa_API void  PathRect(const ImVec2& rect_min, const ImVec2& rect_max, float rounding = 0.0f, int rounding_corners_flags = ImDrawCornerFlags_All);

    // Channels
    // - Use to simulate layers. By switching channels to can render out-of-order (e.g. submit foreground primitives before background primitives)
    // - Use to minimize draw calls (e.g. if going back-and-forth between multiple non-overlapping clipping rectangles, prefer to append into separate channels then merge at the end)
    cqweqasvfa_API void  ChannelsSplit(int channels_count);
    cqweqasvfa_API void  ChannelsMerge();
    cqweqasvfa_API void  ChannelsSetCurrent(int channel_index);

    // Advanced
    cqweqasvfa_API void  AddCallback(ImDrawCallback callback, void* callback_data);  // Your rendering function must check for 'UserCallback' in ImDrawCmd and call the function instead of rendering triangles.
    cqweqasvfa_API void  AddDrawCmd();                                               // This is useful if you need to forcefully create a new draw call (to allow for dependent rendering / blending). Otherwise primitives are merged into the same draw-call as much as possible

    // Internal helpers
    // NB: all primitives needs to be reserved via PrimReserve() beforehand!
    cqweqasvfa_API void  Clear();
    cqweqasvfa_API void  ClearFreeMemory();
    cqweqasvfa_API void  PrimReserve(int idx_count, int vtx_count);
    cqweqasvfa_API void  PrimRect(const ImVec2& a, const ImVec2& b, ImU32 col);      // Axis aligned rectangle (composed of two triangles)
    cqweqasvfa_API void  PrimRectUV(const ImVec2& a, const ImVec2& b, const ImVec2& uv_a, const ImVec2& uv_b, ImU32 col);
    cqweqasvfa_API void  PrimQuadUV(const ImVec2& a, const ImVec2& b, const ImVec2& c, const ImVec2& d, const ImVec2& uv_a, const ImVec2& uv_b, const ImVec2& uv_c, const ImVec2& uv_d, ImU32 col);
    inline    void  PrimWriteVtx(const ImVec2& pos, const ImVec2& uv, ImU32 col) { _VtxWritePtr->pos = pos; _VtxWritePtr->uv = uv; _VtxWritePtr->col = col; _VtxWritePtr++; _VtxCurrentIdx++; }
    inline    void  PrimWriteIdx(ImDrawIdx idx) { *_IdxWritePtr = idx; _IdxWritePtr++; }
    inline    void  PrimVtx(const ImVec2& pos, const ImVec2& uv, ImU32 col) { PrimWriteIdx((ImDrawIdx)_VtxCurrentIdx); PrimWriteVtx(pos, uv, col); }
    cqweqasvfa_API void  UpdateClipRect();
    cqweqasvfa_API void  UpdateTextureID();
};

// All draw data to render an cqweqasvfa frame
struct ImDrawData
{
    bool            Valid;                  // Only valid after Render() is called and before the next NewFrame() is called.
    ImDrawList** CmdLists;
    int             CmdListsCount;
    int             TotalVtxCount;          // For convenience, sum of all cmd_lists vtx_buffer.Size
    int             TotalIdxCount;          // For convenience, sum of all cmd_lists idx_buffer.Size

    // Functions
    ImDrawData() { Valid = false; CmdLists = NULL; CmdListsCount = TotalVtxCount = TotalIdxCount = 0; }
    cqweqasvfa_API void DeIndexAllBuffers();               // For backward compatibility or convenience: convert all buffers from indexed to de-indexed, in case you cannot render indexed. Note: this is slow and most likely a waste of resources. Always prefer indexed rendering!
    cqweqasvfa_API void ScaleClipRects(const ImVec2& sc);  // Helper to scale the ClipRect field of each ImDrawCmd. Use if your final output buffer is at a different scale than cqweqasvfa expects, or if there is a difference between your window resolution and framebuffer resolution.
};

struct ImFontConfig
{
    void* FontData;                   //          // TTF/OTF data
    int             FontDataSize;               //          // TTF/OTF data size
    bool            FontDataOwnedByAtlas;       // true     // TTF/OTF data ownership taken by the container ImFontAtlas (will delete memory itself).
    int             FontNo;                     // 0        // Index of font within TTF/OTF file
    float           SizePixels;                 //          // Size in pixels for rasterizer.
    int             OversampleH, OversampleV;   // 3, 1     // Rasterize at higher quality for sub-pixel positioning. We don't use sub-pixel positions on the Y axis.
    bool            PixelSnapH;                 // false    // Align every glyph to pixel boundary. Useful e.g. if you are merging a non-pixel aligned font with the default font. If enabled, you can set OversampleH/V to 1.
    ImVec2          GlyphExtraSpacing;          // 0, 0     // Extra spacing (in pixels) between glyphs. Only X axis is supported for now.
    ImVec2          GlyphOffset;                // 0, 0     // Offset all glyphs from this font input.
    const ImWchar* GlyphRanges;                // NULL     // Pointer to a user-provided list of Unicode range (2 value per range, values are inclusive, zero-terminated list). THE ARRAY DATA NEEDS TO PERSIST AS LONG AS THE FONT IS ALIVE.
    bool            MergeMode;                  // false    // Merge into previous ImFont, so you can combine multiple inputs font into one ImFont (e.g. ASCII font + icons + Japanese glyphs). You may want to use GlyphOffset.y when merge font of different heights.
    unsigned int    RasterizerFlags;            // 0x00     // Settings for custom font rasterizer (e.g. cqweqasvfaFreeType). Leave as zero if you aren't using one.
    float           RasterizerMultiply;         // 1.0f     // Brighten (>1.0f) or darken (<1.0f) font output. Brightening small fonts may be a good workaround to make them more readable.

    // [Internal]
    char            Name[32];                               // Name (strictly to ease debugging)
    ImFont* DstFont;

    cqweqasvfa_API ImFontConfig();
};

struct ImFontGlyph
{
    ImWchar         Codepoint;          // 0x0000..0xFFFF
    float           AdvanceX;           // Distance to next character (= data from font + ImFontConfig::GlyphExtraSpacing.x baked in)
    float           X0, Y0, X1, Y1;     // Glyph corners
    float           U0, V0, U1, V1;     // Texture coordinates
};

// Load and rasterize multiple TTF/OTF fonts into a same texture.
// Sharing a texture for multiple fonts allows us to reduce the number of draw calls during rendering.
// We also add custom graphic data into the texture that serves for cqweqasvfa.
//  1. (Optional) Call AddFont*** functions. If you don't call any, the default font will be loaded for you.
//  2. Call GetTexDataAsAlpha8() or GetTexDataAsRGBA32() to build and retrieve pixels data.
//  3. Upload the pixels data into a texture within your graphics system.
//  4. Call SetTexID(my_tex_id); and pass the pointer/identifier to your texture. This value will be passed back to you during rendering to identify the texture.
// IMPORTANT: If you pass a 'glyph_ranges' array to AddFont*** functions, you need to make sure that your array persist up until the ImFont is build (when calling GetTextData*** or Build()). We only copy the pointer, not the data.
struct ImFontAtlas
{
    cqweqasvfa_API ImFontAtlas();
    cqweqasvfa_API ~ImFontAtlas();
    cqweqasvfa_API ImFont* AddFont(const ImFontConfig* font_cfg);
    cqweqasvfa_API ImFont* AddFontDefault(const ImFontConfig* font_cfg = NULL);
    cqweqasvfa_API ImFont* AddFontFromFileTTF(const char* filename, float size_pixels, const ImFontConfig* font_cfg = NULL, const ImWchar* glyph_ranges = NULL);
    cqweqasvfa_API ImFont* AddFontFromMemoryTTF(void* font_data, int font_size, float size_pixels, const ImFontConfig* font_cfg = NULL, const ImWchar* glyph_ranges = NULL); // Note: Transfer ownership of 'ttf_data' to ImFontAtlas! Will be deleted after Build(). Set font_cfg->FontDataOwnedByAtlas to false to keep ownership.
    cqweqasvfa_API ImFont* AddFontFromMemoryCompressedTTF(const void* compressed_font_data, int compressed_font_size, float size_pixels, const ImFontConfig* font_cfg = NULL, const ImWchar* glyph_ranges = NULL); // 'compressed_font_data' still owned by caller. Compress with binary_to_compressed_c.cpp.
    cqweqasvfa_API ImFont* AddFontFromMemoryCompressedBase85TTF(const char* compressed_font_data_base85, float size_pixels, const ImFontConfig* font_cfg = NULL, const ImWchar* glyph_ranges = NULL);              // 'compressed_font_data_base85' still owned by caller. Compress with binary_to_compressed_c.cpp with -base85 parameter.
    cqweqasvfa_API void              ClearTexData();             // Clear the CPU-side texture data. Saves RAM once the texture has been copied to graphics memory.
    cqweqasvfa_API void              ClearInputData();           // Clear the input TTF data (inc sizes, glyph ranges)
    cqweqasvfa_API void              ClearFonts();               // Clear the cqweqasvfa-side font data (glyphs storage, UV coordinates)
    cqweqasvfa_API void              Clear();                    // Clear all

    // Build atlas, retrieve pixel data.
    // User is in charge of copying the pixels into graphics memory (e.g. create a texture with your engine). Then store your texture handle with SetTexID().
    // RGBA32 format is provided for convenience and compatibility, but note that unless you use CustomRect to draw color data, the RGB pixels emitted from Fonts will all be white (~75% of waste). 
    // Pitch = Width * BytesPerPixels
    cqweqasvfa_API bool              Build();                    // Build pixels data. This is called automatically for you by the GetTexData*** functions.
    cqweqasvfa_API void              GetTexDataAsAlpha8(unsigned char** out_pixels, int* out_width, int* out_height, int* out_bytes_per_pixel = NULL);  // 1 byte per-pixel
    cqweqasvfa_API void              GetTexDataAsRGBA32(unsigned char** out_pixels, int* out_width, int* out_height, int* out_bytes_per_pixel = NULL);  // 4 bytes-per-pixel
    void                        SetTexID(ImTextureID id) { TexID = id; }

    //-------------------------------------------
    // Glyph Ranges
    //-------------------------------------------

    // Helpers to retrieve list of common Unicode ranges (2 value per range, values are inclusive, zero-terminated list)
    // NB: Make sure that your string are UTF-8 and NOT in your local code page. In C++11, you can create UTF-8 string literal using the u8"Hello world" syntax. See FAQ for details.
    cqweqasvfa_API const ImWchar* GetGlyphRangesDefault();    // Basic Latin, Extended Latin
    cqweqasvfa_API const ImWchar* GetGlyphRangesKorean();     // Default + Korean characters
    cqweqasvfa_API const ImWchar* GetGlyphRangesJapanese();   // Default + Hiragana, Katakana, Half-Width, Selection of 1946 Ideographs
    cqweqasvfa_API const ImWchar* GetGlyphRangesChinese();    // Default + Japanese + full set of about 21000 CJK Unified Ideographs
    cqweqasvfa_API const ImWchar* GetGlyphRangesCyrillic();   // Default + about 400 Cyrillic characters
    cqweqasvfa_API const ImWchar* GetGlyphRangesThai();       // Default + Thai characters

    // Helpers to build glyph ranges from text data. Feed your application strings/characters to it then call BuildRanges().
    struct GlyphRangesBuilder
    {
        ImVector<unsigned char> UsedChars;  // Store 1-bit per Unicode code point (0=unused, 1=used)
        GlyphRangesBuilder() { UsedChars.resize(0x10000 / 8); memset(UsedChars.Data, 0, 0x10000 / 8); }
        bool           GetBit(int n) { return (UsedChars[n >> 3] & (1 << (n & 7))) != 0; }
        void           SetBit(int n) { UsedChars[n >> 3] |= 1 << (n & 7); }  // Set bit 'c' in the array
        void           AddChar(ImWchar c) { SetBit(c); }                          // Add character
        cqweqasvfa_API void AddText(const char* text, const char* text_end = NULL);      // Add string (each character of the UTF-8 string are added)
        cqweqasvfa_API void AddRanges(const ImWchar* ranges);                            // Add ranges, e.g. builder.AddRanges(ImFontAtlas::GetGlyphRangesDefault) to force add all of ASCII/Latin+Ext
        cqweqasvfa_API void BuildRanges(ImVector<ImWchar>* out_ranges);                  // Output new ranges
    };

    //-------------------------------------------
    // Custom Rectangles/Glyphs API
    //-------------------------------------------

    // You can request arbitrary rectangles to be packed into the atlas, for your own purposes. After calling Build(), you can query the rectangle position and render your pixels.
    // You can also request your rectangles to be mapped as font glyph (given a font + Unicode point), so you can render e.g. custom colorful icons and use them as regular glyphs.
    struct CustomRect
    {
        unsigned int    ID;             // Input    // User ID. Use <0x10000 to map into a font glyph, >=0x10000 for other/internal/custom texture data.
        unsigned short  Width, Height;  // Input    // Desired rectangle dimension
        unsigned short  X, Y;           // Output   // Packed position in Atlas
        float           GlyphAdvanceX;  // Input    // For custom font glyphs only (ID<0x10000): glyph xadvance
        ImVec2          GlyphOffset;    // Input    // For custom font glyphs only (ID<0x10000): glyph display offset
        ImFont* Font;           // Input    // For custom font glyphs only (ID<0x10000): target font
        CustomRect() { ID = 0xFFFFFFFF; Width = Height = 0; X = Y = 0xFFFF; GlyphAdvanceX = 0.0f; GlyphOffset = ImVec2(0, 0); Font = NULL; }
        bool IsPacked() const { return X != 0xFFFF; }
    };

    cqweqasvfa_API int       AddCustomRectRegular(unsigned int id, int width, int height);                                                                   // Id needs to be >= 0x10000. Id >= 0x80000000 are reserved for cqweqasvfa and ImDrawList
    cqweqasvfa_API int       AddCustomRectFontGlyph(ImFont* font, ImWchar id, int width, int height, float advance_x, const ImVec2& offset = ImVec2(0, 0));   // Id needs to be < 0x10000 to register a rectangle to map into a specific font.
    cqweqasvfa_API void      CalcCustomRectUV(const CustomRect* rect, ImVec2* out_uv_min, ImVec2* out_uv_max);
    const CustomRect* GetCustomRectByIndex(int index) const { if (index < 0) return NULL; return &CustomRects[index]; }

    //-------------------------------------------
    // Members
    //-------------------------------------------

    ImTextureID                 TexID;              // User data to refer to the texture once it has been uploaded to user's graphic systems. It is passed back to you during rendering via the ImDrawCmd structure.
    int                         TexDesiredWidth;    // Texture width desired by user before Build(). Must be a power-of-two. If have many glyphs your graphics API have texture size restrictions you may want to increase texture width to decrease height.
    int                         TexGlyphPadding;    // Padding between glyphs within texture in pixels. Defaults to 1.

    // [Internal]
    // NB: Access texture data via GetTexData*() calls! Which will setup a default font for you.
    unsigned char* TexPixelsAlpha8;    // 1 component per pixel, each component is unsigned 8-bit. Total size = TexWidth * TexHeight
    unsigned int* TexPixelsRGBA32;    // 4 component per pixel, each component is unsigned 8-bit. Total size = TexWidth * TexHeight * 4
    int                         TexWidth;           // Texture width calculated during Build().
    int                         TexHeight;          // Texture height calculated during Build().
    ImVec2                      TexUvWhitePixel;    // Texture coordinates to a white pixel
    ImVector<ImFont*>           Fonts;              // Hold all the fonts returned by AddFont*. Fonts[0] is the default font upon calling cqweqasvfa::NewFrame(), use cqweqasvfa::PushFont()/PopFont() to change the current font.
    ImVector<CustomRect>        CustomRects;        // Rectangles for packing custom texture data into the atlas.
    ImVector<ImFontConfig>      ConfigData;         // Internal data
    int                         CustomRectIds[1];   // Identifiers of custom texture rectangle used by ImFontAtlas/ImDrawList
};

// Font runtime data and rendering
// ImFontAtlas automatically loads a default embedded font for you when you call GetTexDataAsAlpha8() or GetTexDataAsRGBA32().
struct ImFont
{
    // Members: Hot ~62/78 bytes
    float                       FontSize;           // <user set>   // Height of characters, set during loading (don't change after loading)
    float                       Scale;              // = 1.f        // Base font scale, multiplied by the per-window font scale which you can adjust with SetFontScale()
    ImVec2                      DisplayOffset;      // = (0.f,1.f)  // Offset font rendering by xx pixels
    ImVector<ImFontGlyph>       Glyphs;             //              // All glyphs.
    ImVector<float>             IndexAdvanceX;      //              // Sparse. Glyphs->AdvanceX in a directly indexable way (more cache-friendly, for CalcTextSize functions which are often bottleneck in large UI).
    ImVector<unsigned short>    IndexLookup;        //              // Sparse. Index glyphs by Unicode code-point.
    const ImFontGlyph* FallbackGlyph;      // == FindGlyph(FontFallbackChar)
    float                       FallbackAdvanceX;   // == FallbackGlyph->AdvanceX
    ImWchar                     FallbackChar;       // = '?'        // Replacement glyph if one isn't found. Only set via SetFallbackChar()

    // Members: Cold ~18/26 bytes
    short                       ConfigDataCount;    // ~ 1          // Number of ImFontConfig involved in creating this font. Bigger than 1 when merging multiple font sources into one ImFont.
    ImFontConfig* ConfigData;         //              // Pointer within ContainerAtlas->ConfigData
    ImFontAtlas* ContainerAtlas;     //              // What we has been loaded into
    float                       Ascent, Descent;    //              // Ascent: distance from top to bottom of e.g. 'A' [0..FontSize]
    int                         MetricsTotalSurface;//              // Total surface in pixels to get an idea of the font rasterization/texture cost (not exact, we approximate the cost of padding between glyphs)

    // Methods
    cqweqasvfa_API ImFont();
    cqweqasvfa_API ~ImFont();
    cqweqasvfa_API void              ClearOutputData();
    cqweqasvfa_API void              BuildLookupTable();
    cqweqasvfa_API const ImFontGlyph* FindGlyph(ImWchar c) const;
    cqweqasvfa_API void              SetFallbackChar(ImWchar c);
    float                       GetCharAdvance(ImWchar c) const { return ((int)c < IndexAdvanceX.Size) ? IndexAdvanceX[(int)c] : FallbackAdvanceX; }
    bool                        IsLoaded() const { return ContainerAtlas != NULL; }
    const char* GetDebugName() const { return ConfigData ? ConfigData->Name : "<unknown>"; }

    // 'max_width' stops rendering after a certain width (could be turned into a 2d size). FLT_MAX to disable.
    // 'wrap_width' enable automatic word-wrapping across multiple lines to fit into given width. 0.0f to disable.
    cqweqasvfa_API ImVec2            CalcTextSizeA(float size, float max_width, float wrap_width, const char* text_begin, const char* text_end = NULL, const char** remaining = NULL) const; // utf8
    cqweqasvfa_API const char* CalcWordWrapPositionA(float scale, const char* text, const char* text_end, float wrap_width) const;
    cqweqasvfa_API void              RenderChar(ImDrawList* draw_list, float size, ImVec2 pos, ImU32 col, unsigned short c) const;
    cqweqasvfa_API void              RenderText(ImDrawList* draw_list, float size, ImVec2 pos, ImU32 col, const ImVec4& clip_rect, const char* text_begin, const char* text_end, float wrap_width = 0.0f, bool cpu_fine_clip = false) const;

    // [Internal]
    cqweqasvfa_API void              GrowIndex(int new_size);
    cqweqasvfa_API void              AddGlyph(ImWchar c, float x0, float y0, float x1, float y1, float u0, float v0, float u1, float v1, float advance_x);
    cqweqasvfa_API void              AddRemapChar(ImWchar dst, ImWchar src, bool overwrite_dst = true); // Makes 'dst' character/glyph points to 'src' character/glyph. Currently needs to be called AFTER fonts have been built.

#ifndef cqweqasvfa_DISABLE_OBSOLETE_FUNCTIONS
    typedef ImFontGlyph Glyph; // OBSOLETE 1.52+
#endif
};

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

// Include cqweqasvfa_user.h at the end of cqweqasvfa.h (convenient for user to only explicitly include vanilla cqweqasvfa.h)
#ifdef cqweqasvfa_INCLUDE_cqweqasvfa_USER_H
#include "cqweqasvfa_user.h"
#endif
