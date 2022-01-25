#include "Includes.h"
#include "Fonts.h"
#include "icons.h"
#include "Config.h"
#include <ShlObj_core.h>

#pragma comment(lib,"shell32")
class FRotator;
class Vector3;
typedef struct
{
	DWORD R;
	DWORD G;
	DWORD B;
	DWORD A;
}RGBA;
void DrawStrokeText(int x, int y, RGBA* color, const char* str);
void DrawNewText(int x, int y, RGBA* color, const char* str);
void DrawRect(int x, int y, int w, int h, RGBA* color, int thickness);
void DrawFilledRect(int x, int y, int w, int h, RGBA* color);
void DrawCircleFilled(int x, int y, int radius, RGBA* color, int segments);
void DrawCircle(int x, int y, int radius, RGBA* color, int segments);
void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, RGBA* color, float thickne);
void DrawTriangleFilled(int x1, int y1, int x2, int y2, int x3, int y3, RGBA* color);
void DrawLine(int x1, int y1, int x2, int y2, RGBA* color, int thickness);
void DrawCornerBox(int x, int y, int w, int h, int borderPx, RGBA* color);
void seqwdasvweweq();
void xqweqwef();
inline bool file_exists(const std::string& name);
WPARAM MainLoop();
void loop_esp();
LRESULT CALLBACK WinProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);
void CleanuoD3D();
int isTopwin();
void SetWindowToTarget();
HRESULT DirectXInit(HWND hWnd);
extern LRESULT cqweqasvfa_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
HWND tWnd = 0x0;
HWND hWnd = 0x0;
HWND hMsg = 0x0;
HWND GameWnd = NULL;
HWND MyWnd = NULL;
MSG Message = { NULL };
RECT GameRect = { NULL };
IDirect3D9Ex* p_Object = NULL;
IDirect3DDevice9Ex* p_Device = NULL;
D3DPRESENT_PARAMETERS p_Params = { NULL };
int Width = GetSystemMetrics(SM_CXSCREEN);
int Height = GetSystemMetrics(SM_CYSCREEN);
int rWidth = 0;
int rHeight = 0;
bool Opened = true;
#define M_Name " "
#define TopWindowGame 11
#define TopWindowMvoe 22
const MARGINS Margin = { -1 };
DWORD ScreenCenterX;
DWORD ScreenCenterY;
IDirect3DDevice9Ex* pDevice;
ImU32 ColorTeamBox;
ImU32 ColorEnemyBox;
//void RenderEsp();

int iTab = 0;
int hHealthType, hAimBone, hBoxType, nSelect, tSelect, hDistType, hScopedx, hChamsType, hLanguage, hLineLoc, SpeedVal, hAimKey = 0;

float AimSpeed = 1.50f;
static int rad_items = 0, rad_speed = 0;
float jump_val = 443.0f;
float gravity_val = 1.0f;
bool radar = false;

bool isaimbotting;
float AimFOV = 60.f;
float s_Smooth = 10.f;
DWORD_PTR entityx;
class Color
{
public:
	RGBA moi_blue = { 0, 143, 209,255 };
	RGBA moi_red = { 241,34,34,255 };
	RGBA moi_green = { 0,209,91,255 };

	RGBA red = { 255,0,0,255 };
	RGBA Magenta = { 255,0,255,255 };
	RGBA yellow = { 255,255,0,255 };
	RGBA grayblue = { 128,128,255,255 };
	RGBA green = { 128,224,0,255 };
	RGBA darkgreen2 = { 26, 128, 0, 255 };
	RGBA darkgreen3 = { 6, 68, 0, 255 };
	RGBA darkgreen = { 0,224,128,255 };
	RGBA brown = { 192,96,0,255 };
	RGBA pink = { 255,168,255,255 };
	RGBA DarkYellow = { 216,216,0,255 };
	RGBA SilverWhite = { 236,236,236,255 };
	RGBA purple = { 144,0,255,255 };
	RGBA Navy = { 88,48,224,255 };
	RGBA skyblue = { 0,136,255,255 };
	RGBA graygreen = { 128,160,128,255 };
	RGBA blue = { 0,96,192,255 };
	
	RGBA orange = { 255,128,0,255 };
	RGBA peachred = { 255,80,128,255 };
	RGBA reds = { 255,128,192,255 };
	RGBA darkgray = { 96,96,96,255 };
	RGBA Navys = { 0,0,128,255 };
	RGBA darkgreens = { 0,128,0,255 };
	RGBA darkblue = { 0,128,128,255 };
	RGBA redbrown = { 128,0,0,255 };
	RGBA red4 = { 255, 24, 101, 255 };
	RGBA purplered = { 128,0,128,255 };
	RGBA greens = { 0,255,0,255 };
	RGBA envy = { 0,255,255,255 };
	RGBA black = { 0,0,0,255 };
	RGBA gray = { 128,128,128,255 };
	RGBA white = { 255,255,255,255 };
	RGBA blues = { 30,144,255,255 };
	RGBA lightblue = { 135,206,250,160 };
	RGBA Scarlet = { 220, 20, 60, 160 };
	RGBA white_ = { 255,255,255,200 };
	RGBA gray_ = { 128,128,128,200 };
	RGBA black_ = { 0,0,0,200 };
	RGBA red_ = { 255,0,0,200 };
	RGBA Magenta_ = { 255, 95, 96, 255 };
	RGBA yellow_ = { 255,255,0,200 };
	RGBA grayblue_ = { 128,128,255,200 };
	RGBA green_ = { 128,224,0,200 };
	RGBA darkgreen_ = { 0,224,128,200 };
	RGBA brown_ = { 192,96,0,200 };
	RGBA pink_ = { 255,168,255,200 };
	RGBA darkyellow_ = { 216,216,0,200 };
	RGBA silverwhite_ = { 236,236,236,200 };
	RGBA purple_ = { 144,0,255,200 };
	RGBA Blue_ = { 88,48,224,200 };
	RGBA skyblue_ = { 0,136,255,200 };
	RGBA graygreen_ = { 128,160,128,200 };
	RGBA blue_ = { 0,96,192,180 };
	RGBA orange_ = { 255,128,0,200 };
	RGBA orange2_ = { 255,100,0,180 };
	RGBA pinks_ = { 255,80,128,200 };
	RGBA Fuhong_ = { 255,128,192,200 };
	RGBA darkgray_ = { 96,96,96,200 };
	RGBA Navy_ = { 0,0,128,200 };
	RGBA darkgreens_ = { 0,128,0,200 };
	RGBA darkblue_ = { 0,128,128,200 };
	RGBA redbrown_ = { 128,0,0,200 };
	RGBA purplered_ = { 128,0,128,200 };
	RGBA greens_ = { 0,255,0,200 };
	RGBA envy_ = { 0,255,255,200 };

	RGBA glassblack = { 0, 0, 0, 180 };
	RGBA GlassBlue = { 65,105,225,80 };
	RGBA glassyellow = { 255,255,0,160 };
	RGBA glass = { 200,200,200,60 };


	RGBA Plum = { 221,160,221,160 };

};
Color Col;

struct Ozellikler
{
	Ozellikler() { }

	struct Esp_s
	{
		bool Box, Line, Name, Distance, Skeleton, Player, Robot, Radar, radar_distance, Crosshair, Smoke, Flash, Dot, Fire, AimAt, Offscreen, Energy, LookDirection,
			Near, DetectHack, C4, Danger;
	} Esp;

	struct xqweqwfac_s
	{
		bool ON, Bone, FOV, DrawFov;
	} xqweqwfac;

	struct Misc_s
	{
		bool NoRecoil, NoReload, NoSpread, gunrapid, sniprapid, FastReload, Jump, AFK, NoFallDamage, RapidFire, RapidKnife, NoWeaponSway, Speed, RapidGun, FastWeaponSwitch, FastBomb, FastAim, Trigger, TriggerSniper;
	} Misc;

	struct Teleport_s
	{
		bool ON;
	} Teleport;

	struct Settings_s
	{

	} Settings;
};
Ozellikler Moi;

static ImVec2 pRadar;
int ak = 1;
D3DCOLOR FLOAT4TOD3DCOLOR(float Col[])
{
	ImU32 col32_no_alpha = cqweqasvfa::ColorConvertFloat4ToU32(ImVec4(Col[0], Col[1], Col[2], Col[3]));
	float a = (col32_no_alpha >> 24) & 255;
	float r = (col32_no_alpha >> 16) & 255;
	float g = (col32_no_alpha >> 8) & 255;
	float b = col32_no_alpha & 255;
	return D3DCOLOR_ARGB((int)a, (int)b, (int)g, (int)r);
}

static int local_size = 1;
static int enemy_size = 1;


void CConfig::Setup()
{

	// Esp (Box, Dot, Smoke, Name, C4, Distance, Skeleton, Line, LookDirection, Radar, radar_distance, Danger)
	SetupValue(Moi.Esp.Box, false, XorString("Esp"), XorString("Box"));
	SetupValue(Moi.Esp.Dot, false, XorString("Esp"), XorString("Crosshair"));
	SetupValue(Moi.Esp.Smoke, false, XorString("Esp"), XorString("Smoke"));
	SetupValue(Moi.Esp.Name, false, XorString("Esp"), XorString("Name"));
	SetupValue(Moi.Esp.C4, false, XorString("Esp"), XorString("C4"));
	SetupValue(Moi.Esp.Distance, false, XorString("Esp"), XorString("Distance"));
	SetupValue(Moi.Esp.Skeleton, false, XorString("Esp"), XorString("Skeleton"));
	SetupValue(Moi.Esp.Line, false, XorString("Esp"), XorString("Line"));
	SetupValue(Moi.Esp.LookDirection, false, XorString("Esp"), XorString("LookDirection"));
	SetupValue(Moi.Esp.Radar, false, XorString("Esp"), XorString("Radar"));
	SetupValue(Moi.Esp.radar_distance, false, XorString("Esp"), XorString("radar_distance"));
	SetupValue(Moi.Esp.Danger, false, XorString("Esp"), XorString("Danger"));

	SetupValue(nSelect, 0, XorString("NameColor"), XorString("NameColor"));

	// Aim
	SetupValue(Moi.xqweqwfac.ON, false, XorString("xqweqwfac"), XorString("ON"));
	SetupValue(Moi.Misc.Trigger, false, XorString("Misc"), XorString("Trigger"));
	SetupValue(Moi.Misc.TriggerSniper, false, XorString("Misc"), XorString("TriggerSniper"));
	SetupValue(AimSpeed, 1.50f, XorString("xqweqwfac"), XorString("Smooth"));

	SetupValue(hAimBone, 0, XorString("bone"), XorString("bone"));
	SetupValue(hAimKey, 0, XorString("a_key"), XorString("a_key"));

	//Misc
	SetupValue(Moi.Misc.NoRecoil, false, XorString("Misc"), XorString("NoRecoil"));
	SetupValue(Moi.Misc.FastBomb, false, XorString("Misc"), XorString("FastBomb"));
	SetupValue(Moi.Misc.NoSpread, false, XorString("Misc"), XorString("NoSpread"));
	SetupValue(Moi.Misc.FastAim, false, XorString("Misc"), XorString("FastAim"));
	SetupValue(Moi.Misc.NoReload, false, XorString("Misc"), XorString("NoReload"));
	SetupValue(Moi.Misc.Jump, false, XorString("Misc"), XorString("Jump"));
	SetupValue(Moi.Misc.RapidFire, false, XorString("Misc"), XorString("RapidFire"));
	SetupValue(Moi.Misc.NoWeaponSway, false, XorString("Misc"), XorString("NoWeaponSway"));
	SetupValue(Moi.Misc.RapidKnife, false, XorString("Misc"), XorString("RapidKnife"));
	SetupValue(Moi.Misc.Speed, false, XorString("Misc"), XorString("Speed"));
	SetupValue(Moi.Misc.RapidGun, false, XorString("Misc"), XorString("RapidGun"));
	SetupValue(Moi.Misc.FastWeaponSwitch, false, XorString("Misc"), XorString("FastWeaponSwitch"));

	SetupValue(SpeedVal, 0, XorString("a_select"), XorString("a_select"));
}

void CConfig::SetupValue(int& value, int def, std::string category, std::string name)
{
	value = def;
	ints.push_back(new ConfigValue< int >(category, name, &value));
}

void CConfig::SetupValue(float& value, float def, std::string category, std::string name)
{
	value = def;
	floats.push_back(new ConfigValue< float >(category, name, &value));
}

void CConfig::SetupValue(bool& value, bool def, std::string category, std::string name)
{
	value = def;
	bools.push_back(new ConfigValue< bool >(category, name, &value));
}

void CConfig::Save()
{
	static TCHAR path[MAX_PATH];
	std::string folder, file;

	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, path)))
	{
		folder = std::string(path) + XorString("\\moi_zulaLog\\");
		file = std::string(path) + XorString("\\moi_zulaLog\\moi_zlconfig.ini");
	}

	CreateDirectory(folder.c_str(), NULL);

	for (auto value : ints)
		WritePrivateProfileString(value->category.c_str(), value->name.c_str(), std::to_string(*value->value).c_str(), file.c_str());

	for (auto value : floats)
		WritePrivateProfileString(value->category.c_str(), value->name.c_str(), std::to_string(*value->value).c_str(), file.c_str());

	for (auto value : bools)
		WritePrivateProfileString(value->category.c_str(), value->name.c_str(), *value->value ? "true" : "false", file.c_str());
}

void CConfig::Load()
{
	static TCHAR path[MAX_PATH];
	std::string folder, file;

	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, path)))
	{
		folder = std::string(path) + XorString("\\moi_zulaLog\\");
		file = std::string(path) + XorString("\\moi_zulaLog\\moi_zlconfig.ini");
	}

	CreateDirectory(folder.c_str(), NULL);

	char value_l[32] = { '\0' };

	for (auto value : ints)
	{
		GetPrivateProfileString(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = atoi(value_l);
	}

	for (auto value : floats)
	{
		GetPrivateProfileString(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = atof(value_l);
	}

	for (auto value : bools)
	{
		GetPrivateProfileString(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = !strcmp(value_l, "true");
	}
}
uint32_t MemoryBase = NULL;
float xd1, xd2, xd3, xd4, xd5, xd6;
CConfig* Config = new CConfig();
#define MoiText(icon, text) std::string(std::string(XorString(icon)) + text).c_str()
namespace XRender
{
	//const char* Healthtype[] = { "Bar" };
	//const char* Boxtype[] = { "3D", "2D" };
	//	const char* Linepos[] = { "Top", "Middle", "Bottom" };
	const char* bone[2] = { "Only Head", "Random (for legit)" };
	const char* a_key[] = { "Shift", "Capslock", "Click/Fire", "RButton", "CTRL", "Alt", "X", "F", "T", "C", "G", "Auto" };


	const char* Teamselect[] = { "Enemy", "Both" };
	const char* NameColor[] = { "Silver", "Red", "Yellow", "DarkGrey" };
	const char* a_select[] = { "1", "2" };

	const char* TeamSelect2[] = { "Zula", "Gladio" };
	//// Enemy Default Colors
	//float EnemyBoneColor[3] = { 1.00F, 0.10f, 0.08f };//red
	//float EnemyTeamNumber[3] = { 1.00F, 0.10f, 0.08f };//red
	//float EnemyNameColor[3] = { 1.00F, 0.10f, 0.08f };//red
	//float EnemyHealthColor[3] = { 1.00F, 0.10f, 0.08f };//red
	//float EnemyBoxColor[3] = { 1.0f, 0.0f, 0.0f };//red
	////0.882, 0.259, 0.02

	//float TeamBoxColor[3] = { 0.031f, 0.89f, 0.f };//blue
	//float AllBoxColor[3] = { 0.03f, 0.48f, 0.92f };//blue
	//float LineColor[3] = { 0.03f, 0.48f, 0.92f };//blue
	////float NameColor[3] = { 0.03f, 0.48f, 0.92f };//blue
	//float DistanceColor[3] = { 0.03f, 0.48f, 0.92f };//blue
	//float VehicleColor[3] = { 0.03f, 0.48f, 0.92f };//blue
	//float HealthColor[3] = { 0.03f, 0.48f, 0.92f };//blue
	//float ItemColor[3] = { 0.03f, 0.48f, 0.92f };//blue

	//float item_1col[3] = { 0.03f, 0.48f, 0.92f };//blue
	//float item_2col[3] = { 0.03f, 0.48f, 0.92f };//blue
	//float item_3col[3] = { 0.03f, 0.48f, 0.92f };//blue
	//float item_4col[3] = { 0.03f, 0.48f, 0.92f };//blue
	//float item_5col[3] = { 0.03f, 0.48f, 0.92f };//blue
	//float item_6col[3] = { 0.03f, 0.48f, 0.92f };//blue

	//float EnemyChamsColor[3] = { 0.94F, 0.14f, 0.012f };//red
	//float TeamChamsColor[3] = { 0.03f, 0.48f, 0.92f };//blue
	//float AllChamsColor[3] = { 0.03f, 0.48f, 0.92f };//blue

	static D3DCOLOR FloatToD3DCol(float Col[])
	{
		ImU32 col32_no_alpha = cqweqasvfa::ColorConvertFloat4ToU32(ImVec4(Col[0], Col[1], Col[2], Col[3]));
		float a = (col32_no_alpha >> 24) & 255;
		float r = (col32_no_alpha >> 16) & 255;
		float g = (col32_no_alpha >> 8) & 255;
		float b = col32_no_alpha & 255;
		return D3DCOLOR_RGBA((int)g, (int)r, (int)a, (int)b);
	}

	float enemy_behind[3] = { 0.03f, 0.48f, 0.92f };//blue
	float enemy_front[3] = { 0.03f, 0.48f, 0.92f };//blue

	void DrawMenu(IDirect3DDevice9* pDevice) {

		//ColorEnemyBox = cqweqasvfa::ColorConvertFloat4ToU32(ImVec4(EnemyBoxColor[0], EnemyBoxColor[1], EnemyBoxColor[2], 1.f));
		//ColorTeamBox = cqweqasvfa::ColorConvertFloat4ToU32(ImVec4(TeamBoxColor[0], TeamBoxColor[1], TeamBoxColor[2], 1.f));
		cqweqasvfaStyle* style = &cqweqasvfa::GetStyle();
		if (GetAsyncKeyState(VK_F7) & 1)
			Opened = !Opened;
		loop_esp();
		//loop_esp();
		//cqweqasvfa::NewFrame();

		style->Colors[cqweqasvfaCol_ChildBg] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		style->Colors[cqweqasvfaCol_PopupBg] = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);//combobox arkaplan
		style->Colors[cqweqasvfaCol_Border] = ImVec4(0.f, 0.f, 0.f, 1.00f);
		style->Colors[cqweqasvfaCol_TextDisabled] = ImVec4(0.86f, 0.93f, 0.89f, 1.0f);
		style->Colors[cqweqasvfaCol_WindowBg] = ImColor(50, 50, 50, 255);
		style->Colors[cqweqasvfaCol_ChildWindowBg] = ImColor(50, 50, 50, 255);// hile özellikleri arkaplan
		style->Colors[cqweqasvfaCol_FrameBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.0f);//checkbox
		style->Colors[cqweqasvfaCol_FrameBgHovered] = ImVec4(0.10f, 0.10f, 0.10f, 1.0f);
		style->Colors[cqweqasvfaCol_FrameBgActive] = ImVec4(0.10f, 0.10f, 0.10f, 1.0f);
		style->Colors[cqweqasvfaCol_TitleBg] = ImColor(207, 43, 71, 255); // title dont-click
		style->Colors[cqweqasvfaCol_TitleBgCollapsed] = ImColor(0, 73, 177, 255);
		style->Colors[cqweqasvfaCol_TitleBgActive] = ImColor(207, 43, 71, 255); // title-active
		style->Colors[cqweqasvfaCol_MenuBarBg] = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
		style->Colors[cqweqasvfaCol_ScrollbarBg] = ImVec4(0.13f, 0.13f, 0.13f, 1.00f);
		style->Colors[cqweqasvfaCol_ScrollbarGrab] = ImVec4(0.09f, 0.15f, 0.16f, 1.00f);
		style->Colors[cqweqasvfaCol_ScrollbarGrabHovered] = ImVec4(0.15f, 0.60f, 0.78f, 1.00f);
		style->Colors[cqweqasvfaCol_ScrollbarGrabActive] = ImVec4(0.15f, 0.60f, 0.78f, 1.00f);
		style->Colors[cqweqasvfaCol_SliderGrabActive] = ImColor(200, 3, 59, 255);
		style->Colors[cqweqasvfaCol_SliderGrab] = ImColor(200, 3, 59, 255);
		style->Colors[cqweqasvfaCol_CheckMark] = ImColor(207, 43, 71, 255);
		style->Colors[cqweqasvfaCol_Button] = ImColor(255, 24, 101, 255);
		style->Colors[cqweqasvfaCol_ButtonHovered] = ImColor(255, 24, 101, 255);
		style->Colors[cqweqasvfaCol_ButtonActive] = ImColor(255, 24, 101, 255);
		style->Colors[cqweqasvfaCol_Header] = ImColor(31, 34, 41, 255);
		style->Colors[cqweqasvfaCol_HeaderHovered] = ImColor(31, 34, 41, 255);
		style->Colors[cqweqasvfaCol_HeaderActive] = ImColor(31, 34, 41, 255);
		style->Colors[cqweqasvfaCol_ColumnHovered] = ImVec4(0.70f, 0.02f, 0.60f, 1.00f);

		style->WindowTitleAlign.x = 0.50f;
		style->WindowRounding = 3.0f;
		style->FrameRounding = 5.0f;
		style->WindowBorderSize = 0.0f;
		style->WindowPadding = ImVec2(0, 14);
		ImVec2 pos;
		//0x183BA2D

		int inrank = readmem<int>(MemoryBase + 0x183BCF1);
		cqweqasvfa::GetIO().MouseDrawCursor = Opened;
		if (Opened)
		{
			//auto ColorFlags = cqweqasvfaColorEditFlags_PickerHueBar | cqweqasvfaColorEditFlags_NoLabel | cqweqasvfaColorEditFlags_NoOptions | cqweqasvfaColorEditFlags_NoInputs;

			//auto ColorFlags = cqweqasvfaColorEditFlags_NoLabel;
			if (cqweqasvfa::Begin(XorString("Zula Apathe Premium v2.3 [Developed by Mo1ra]"), &Opened, ImVec2(500, 340), 100.f, cqweqasvfaWindowFlags_NoCollapse | cqweqasvfaWindowFlags_NoResize | cqweqasvfaWindowFlags_NoScrollbar))
			{
				//cqweqasvfa::Text("%d", cqweqasvfa::IsWindowFocused());
		/*		if (cqweqasvfa::IsWindowFocused() == true)
				{
					radaropt = false;
					radar_hider = false;

					dropboxopt = false;
					dropbox_hider = false;
				}*/
				pos = cqweqasvfa::GetWindowPos();

				pRadar.x = ScreenCenterX + 598;
				pRadar.y = ScreenCenterY - ScreenCenterY + 80;
				//cqweqasvfa::PushStyleColor(cqweqasvfaCol_SliderGrab, 0);
				//cqweqasvfa::SetNextWindowPos();
				cqweqasvfa::BeginChildFrame(0, ImVec2(800, 31));

				if (iTab == 0)
				{
					style->Colors[cqweqasvfaCol_Text] = ImColor(255, 255, 255, 255);
					style->Colors[cqweqasvfaCol_Button] = ImColor(181, 3, 59, 255);
					style->Colors[cqweqasvfaCol_ButtonHovered] = ImColor(181, 3, 59, 255);
					style->Colors[cqweqasvfaCol_ButtonActive] = ImColor(181, 3, 59, 255);

				}
				else
				{
					style->Colors[cqweqasvfaCol_Text] = ImColor(200, 200, 200, 255);
					style->Colors[cqweqasvfaCol_Button] = ImColor(122, 0, 37, 255);
					style->Colors[cqweqasvfaCol_ButtonHovered] = ImColor(172, 0, 37, 255);
					style->Colors[cqweqasvfaCol_ButtonActive] = ImColor(122, 0, 37, 255);
				}


				cqweqasvfa::SameLine(60);
				if (cqweqasvfa::Button(std::string(std::string(XorString(ICON_FA_EYE)) + XorString(" Visual")).c_str(), ImVec2(120, 25)))
					iTab = 0;

				if (iTab == 1)
				{
					style->Colors[cqweqasvfaCol_Text] = ImColor(255, 255, 255, 255);
					style->Colors[cqweqasvfaCol_Button] = ImColor(181, 3, 59, 255);
					style->Colors[cqweqasvfaCol_ButtonHovered] = ImColor(181, 3, 59, 255);
					style->Colors[cqweqasvfaCol_ButtonActive] = ImColor(181, 3, 59, 255);

				}
				else
				{
					style->Colors[cqweqasvfaCol_Text] = ImColor(200, 200, 200, 255);
					style->Colors[cqweqasvfaCol_Button] = ImColor(122, 0, 37, 255);
					style->Colors[cqweqasvfaCol_ButtonHovered] = ImColor(172, 0, 37, 255);
					style->Colors[cqweqasvfaCol_ButtonActive] = ImColor(122, 0, 37, 255);
				}

				cqweqasvfa::SameLine(190);
				if (cqweqasvfa::Button(std::string(std::string(XorString(ICON_FA_CROSSHAIRS)) + XorString(" Aimbot")).c_str(), ImVec2(120, 25))) iTab = 1;


				///* Misc Menu */

				if (iTab == 2)
				{
					style->Colors[cqweqasvfaCol_Text] = ImColor(255, 255, 255, 255);
					style->Colors[cqweqasvfaCol_Button] = ImColor(181, 3, 59, 255);
					style->Colors[cqweqasvfaCol_ButtonHovered] = ImColor(181, 3, 59, 255);
					style->Colors[cqweqasvfaCol_ButtonActive] = ImColor(181, 3, 59, 255);

				}
				else
				{
					style->Colors[cqweqasvfaCol_Text] = ImColor(200, 200, 200, 255);
					style->Colors[cqweqasvfaCol_Button] = ImColor(122, 0, 37, 255);
					style->Colors[cqweqasvfaCol_ButtonHovered] = ImColor(172, 0, 37, 255);
					style->Colors[cqweqasvfaCol_ButtonActive] = ImColor(122, 0, 37, 255);
				}

				cqweqasvfa::SameLine(320);
				if (cqweqasvfa::Button(std::string(std::string(XorString(ICON_FA_REDDIT_ALIEN)) + XorString(" Memory")).c_str(), ImVec2(120, 25))) iTab = 2;

				cqweqasvfa::EndChildFrame();
				style->Colors[cqweqasvfaCol_Text] = ImColor(255, 255, 255, 255);

				ImVec2 curpos = cqweqasvfa::GetMousePos();

				cqweqasvfa::BeginChild(XorString("main"), ImVec2(640, 400));
				{
					switch (iTab) {
					case 0:
						cqweqasvfa::NewLine(); cqweqasvfa::NewLine(); cqweqasvfa::SameLine(50); 
						cqweqasvfa::Checkbox(XorString("Box Esp"), &Moi.Esp.Box);

						cqweqasvfa::SameLine(300);
						cqweqasvfa::Checkbox(XorString("Crosshair"), &Moi.Esp.Dot);

						cqweqasvfa::NewLine(); cqweqasvfa::SameLine(72);
						cqweqasvfa::Text(XorString("Team Select:"));
						cqweqasvfa::PushItemWidth(70);				
						cqweqasvfa::SameLine(160);
						cqweqasvfa::Combo(XorString("##teamselect"), &tSelect, inrank ? TeamSelect2 : Teamselect, IM_ARRAYSIZE(Teamselect));
						cqweqasvfa::PopItemWidth();

						cqweqasvfa::SameLine(300);
						cqweqasvfa::Checkbox(XorString("No Smoke"), &Moi.Esp.Smoke);
						
						//cqweqasvfa::SameLine(300);
						cqweqasvfa::NewLine(); cqweqasvfa::SameLine(50);
						cqweqasvfa::Checkbox(XorString("Name Esp"), &Moi.Esp.Name);
						cqweqasvfa::SameLine(300);
						cqweqasvfa::Checkbox(XorString("No Flash"), &Moi.Esp.Smoke);

						cqweqasvfa::NewLine(); cqweqasvfa::SameLine(72);
						cqweqasvfa::Text(XorString("Color:"));
						cqweqasvfa::PushItemWidth(70);
						cqweqasvfa::SameLine(120);
						cqweqasvfa::Combo(XorString("##nameselect"), &nSelect, NameColor, IM_ARRAYSIZE(NameColor));
						cqweqasvfa::PopItemWidth();

						cqweqasvfa::SameLine(300);
						cqweqasvfa::Checkbox(XorString("Esp C4 Bomb"), &Moi.Esp.C4);

						cqweqasvfa::NewLine(); cqweqasvfa::SameLine(50);
						cqweqasvfa::Checkbox(XorString("Distance Esp"), &Moi.Esp.Distance);
						cqweqasvfa::SameLine(300);
						cqweqasvfa::Checkbox(XorString("Esp Skeleton"), &Moi.Esp.Skeleton);

						cqweqasvfa::NewLine(); cqweqasvfa::SameLine(50);
						cqweqasvfa::Checkbox(XorString("Line Esp"), &Moi.Esp.Line);
						cqweqasvfa::NewLine(); cqweqasvfa::SameLine(50);
						cqweqasvfa::Checkbox(XorString("Aim Direction Esp"), &Moi.Esp.LookDirection);

						cqweqasvfa::NewLine(); cqweqasvfa::SameLine(50);
						cqweqasvfa::Checkbox(XorString("Draw Radar"), &Moi.Esp.Radar);
						cqweqasvfa::NewLine(); cqweqasvfa::SameLine(72);
						cqweqasvfa::Checkbox(XorString("Distance"), &Moi.Esp.radar_distance);

						cqweqasvfa::NewLine(); cqweqasvfa::SameLine(50);
						cqweqasvfa::Checkbox(XorString("Esp Bomb Danger"), &Moi.Esp.Danger);

						//cqweqasvfa::Checkbox(XorString("Offscreen Esp"), &Moi.Esp.Offscreen);
						break;

					case 1:
						cqweqasvfa::NewLine(); cqweqasvfa::NewLine(); cqweqasvfa::SameLine(50); cqweqasvfa::Checkbox(XorString("Aimbot"), &Moi.xqweqwfac.ON);

						cqweqasvfa::NewLine(); cqweqasvfa::SameLine(50); cqweqasvfa::Text(XorString("Mode:"));
						cqweqasvfa::PushItemWidth(100);
						cqweqasvfa::SameLine(120);
						cqweqasvfa::Combo(XorString("##hitbox"), &hAimBone, bone, IM_ARRAYSIZE(bone));
						cqweqasvfa::PopItemWidth();

						cqweqasvfa::NewLine(); cqweqasvfa::SameLine(50);	cqweqasvfa::Text(XorString("Key:"));
						cqweqasvfa::PushItemWidth(100);
						cqweqasvfa::SameLine(120);
						cqweqasvfa::Combo(XorString("##aimkeyxd"), &hAimKey, a_key, IM_ARRAYSIZE(a_key));
						cqweqasvfa::PopItemWidth();

					/*	cqweqasvfa::NewLine(); cqweqasvfa::SameLine(50);	
						cqweqasvfa::Text(XorString("Field of View:"));
						cqweqasvfa::PushItemWidth(100);
						cqweqasvfa::SameLine(160);
						cqweqasvfa::SliderFloat(XorString("[f]"), &AimFOV, 10.0f, 360.0f, XorString("%.f"));
						cqweqasvfa::PopItemWidth();*/


						cqweqasvfa::NewLine(); cqweqasvfa::SameLine(50);	cqweqasvfa::Text(XorString("Smooth:"));
						cqweqasvfa::PushItemWidth(100);
						cqweqasvfa::SameLine(120);
						cqweqasvfa::SliderFloat(XorString("Kayma hizi"), &AimSpeed, 0.50f, 5.00f, XorString("%.2f"));
						cqweqasvfa::PopItemWidth();

						cqweqasvfa::NewLine(); cqweqasvfa::SameLine(50);
						cqweqasvfa::Checkbox(XorString("Trigger bot"), &Moi.Misc.Trigger);

						cqweqasvfa::NewLine(); cqweqasvfa::SameLine(50);
						cqweqasvfa::Checkbox(XorString("Trigger bot (Sniper)"), &Moi.Misc.TriggerSniper);



						/*cqweqasvfa::NewLine(); cqweqasvfa::SameLine(50);
						cqweqasvfa::PushItemWidth(100);
						cqweqasvfa::SameLine(110);
						cqweqasvfa::SliderFloat(XorString("xd1"), &xd1, 0.0f, 80.0f, XorString("%.2f"));
						cqweqasvfa::PopItemWidth();

						cqweqasvfa::NewLine(); cqweqasvfa::SameLine(50);
						cqweqasvfa::PushItemWidth(100);
						cqweqasvfa::SameLine(110);
						cqweqasvfa::SliderFloat(XorString("xd2"), &xd2, 0.0f, 80.0f, XorString("%.2f"));
						cqweqasvfa::PopItemWidth();*/
						break;

					case 2:

						cqweqasvfa::NewLine(); cqweqasvfa::NewLine(); cqweqasvfa::SameLine(50);
						cqweqasvfa::Checkbox(XorString("No Recoil"), &Moi.Misc.NoRecoil);
						cqweqasvfa::SameLine(300);
						cqweqasvfa::Checkbox(XorString("Fast Bomb"), &Moi.Misc.FastBomb);
						cqweqasvfa::NewLine(); cqweqasvfa::SameLine(50);
						cqweqasvfa::Checkbox(XorString("No Spread"), &Moi.Misc.NoSpread);
						cqweqasvfa::SameLine(300);
						cqweqasvfa::Checkbox(XorString("Fast Aim"), &Moi.Misc.FastAim);
						cqweqasvfa::NewLine(); cqweqasvfa::SameLine(50);
						cqweqasvfa::Checkbox(XorString("No Reload"), &Moi.Misc.NoReload);
						cqweqasvfa::SameLine(300);
						cqweqasvfa::Checkbox(XorString("Jump Hack"), &Moi.Misc.Jump);
						cqweqasvfa::NewLine(); cqweqasvfa::SameLine(50);
						cqweqasvfa::Checkbox(XorString("Rapid Fire"), &Moi.Misc.RapidFire);
						cqweqasvfa::SameLine(300);
						cqweqasvfa::Checkbox(XorString("No Weapon Sway"), &Moi.Misc.NoWeaponSway);
						cqweqasvfa::NewLine(); cqweqasvfa::SameLine(50);
						cqweqasvfa::Checkbox(XorString("Rapid Knife"), &Moi.Misc.RapidKnife);

						cqweqasvfa::SameLine(300);
						cqweqasvfa::Checkbox(XorString("Movement Speed (E)"), &Moi.Misc.Speed);
						cqweqasvfa::NewLine(); cqweqasvfa::SameLine(50);
						cqweqasvfa::Checkbox(XorString("Rapid Gun"), &Moi.Misc.RapidGun);

						cqweqasvfa::SameLine(324);
						cqweqasvfa::Text(XorString("Max:"));
						cqweqasvfa::PushItemWidth(50);
						cqweqasvfa::SameLine(354);
						cqweqasvfa::Combo(XorString("##speedval"), &SpeedVal, a_select, IM_ARRAYSIZE(a_select));
						cqweqasvfa::PopItemWidth();

						cqweqasvfa::NewLine(); cqweqasvfa::SameLine(50);
						cqweqasvfa::Checkbox(XorString("Fast Weapon Switch"), &Moi.Misc.FastWeaponSwitch);


						cqweqasvfa::SameLine(300);
						cqweqasvfa::Checkbox(XorString("Anti AFK (NEW)"), &Moi.Misc.AFK);

						cqweqasvfa::NewLine(); cqweqasvfa::NewLine(); cqweqasvfa::SameLine(115);
						if (cqweqasvfa::Button(std::string(std::string(XorString(ICON_FA_FILE)) + XorString(" Kaydet")).c_str(), ImVec2(120, 30)))
						{
							Config->Save();
						}

						cqweqasvfa::SameLine(260);

						if (cqweqasvfa::Button(std::string(std::string(XorString(ICON_FA_FILE)) + XorString(" Yukle")).c_str(), ImVec2(120, 30)))
						{
							Config->Load();
						}
						break;
					}
					cqweqasvfa::EndChild();
				}
				//	cqweqasvfa::PopStyleColor();
			}
			cqweqasvfa::End();
		}

		if (Moi.Esp.Radar)
		{
			cqweqasvfa::Begin(XorString("- Modern Radar -"), &radar, ImVec2(310, 310), 1.0f, cqweqasvfaWindowFlags_NoCollapse | cqweqasvfaWindowFlags_NoResize | cqweqasvfaWindowFlags_NoScrollbar | cqweqasvfaWindowFlags_NoMove);
			{
				//	cqweqasvfaWindow* window = FindWindowByName(name);

				cqweqasvfa::SetWindowPos(ImVec2(pRadar.x, pRadar.y));
				auto radar_posX = pRadar.x + 155;
				auto radar_posY = pRadar.y + 165;





				// sol & sað çapraz		
			/*sað*/	DrawLine(radar_posX + 154, radar_posY - 146, radar_posX, radar_posY, &Col.SilverWhite, 0.1);
			/*sol*/ DrawLine(radar_posX - 154, radar_posY - 146, radar_posX, radar_posY, &Col.SilverWhite, 0.1);

				// alt & üst
				DrawLine(radar_posX, radar_posY, radar_posX, radar_posY + 144, &Col.SilverWhite, 0.1);
				//DrawLine(radar_posX, radar_posY, radar_posX, radar_posY - 139, &Col.SilverWhite, 0.1);

				// sol & sað
				DrawLine(radar_posX, radar_posY, radar_posX + 154, radar_posY, &Col.SilverWhite, 0.1);
				DrawLine(radar_posX, radar_posY, radar_posX - 154, radar_posY, &Col.SilverWhite, 0.1);

				/*int r, g, b;
				r = (int)(local_col[0] * 255);
				g = (int)(local_col[1] * 255);
				b = (int)(local_col[2] * 255);
			//	DWORD CrossColor = D3DCOLOR_XRGB(r, g, b);

				RGBA loc = { r, g, b, 255 };*/
				DrawCircleFilled(radar_posX + 0.50f, radar_posY, local_size, &Col.blue, 50);

				//	DrawFilledRect(radar_posX, radar_posY, 5, 5, &Col.darkgreen2);// local

				/*
					auto radar_posX = pRadar.x + 175;
				auto radar_posY = pRadar.y + 185;





				// sol & sað çapraz		
				DrawLine(radar_posX + 173, radar_posY - 165, radar_posX, radar_posY, &Col.SilverWhite, 0.1);
				DrawLine(radar_posX - 173, radar_posY - 165, radar_posX, radar_posY, &Col.SilverWhite, 0.1);

				// alt & üst
				DrawLine(radar_posX, radar_posY, radar_posX, radar_posY + 165, &Col.SilverWhite, 0.1);
				DrawLine(radar_posX, radar_posY, radar_posX, radar_posY - 166, &Col.SilverWhite, 0.1);

				// sol & sað
				DrawLine(radar_posX, radar_posY, radar_posX + 175, radar_posY, &Col.SilverWhite, 0.1);
				DrawLine(radar_posX, radar_posY, radar_posX - 175, radar_posY, &Col.SilverWhite, 0.1);

				*/
				cqweqasvfa::End();
			}
		}
		//cqweqasvfa::Render();
	}
}

static std::string string_To_UTF8(const std::string& str)
{
	int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);

	wchar_t* pwBuf = new wchar_t[nwLen + 1];
	ZeroMemory(pwBuf, nwLen * 2 + 2);

	::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);

	int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

	char* pBuf = new char[nLen + 1];
	ZeroMemory(pBuf, nLen + 1);

	::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	std::string retStr(pBuf);

	delete[]pwBuf;
	delete[]pBuf;

	pwBuf = NULL;
	pBuf = NULL;

	return retStr;
}

static void DrawStrokeText(int x, int y, RGBA* color, const char* str)
{
	ImFont a;
	std::string utf_8_1 = std::string(str);
	std::string utf_8_2 = string_To_UTF8(utf_8_1);
	cqweqasvfa::GetOverlayDrawList()->AddText(ImVec2(x, y - 1), cqweqasvfa::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), utf_8_2.c_str());
	cqweqasvfa::GetOverlayDrawList()->AddText(ImVec2(x, y + 1), cqweqasvfa::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), utf_8_2.c_str());
	cqweqasvfa::GetOverlayDrawList()->AddText(ImVec2(x - 1, y), cqweqasvfa::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), utf_8_2.c_str());
	cqweqasvfa::GetOverlayDrawList()->AddText(ImVec2(x + 1, y), cqweqasvfa::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), utf_8_2.c_str());
	cqweqasvfa::GetOverlayDrawList()->AddText(ImVec2(x, y), cqweqasvfa::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), utf_8_2.c_str());
}
static void DrawNewText(int x, int y, RGBA* color, const char* str)
{
	//	ImFont a;
	//cqweqasvfaIO& io = cqweqasvfa::GetIO();
		//ImFont* pFont = io.Fonts->AddFontFromFileTTF("sansation.ttf", 10.0f);
		//a.FontSize = 5.f;
	std::string utf_8_1 = std::string(str);
	std::string utf_8_2 = string_To_UTF8(utf_8_1);
	cqweqasvfa::GetOverlayDrawList()->AddText(ImVec2(x, y), cqweqasvfa::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), utf_8_2.c_str());
}

static void DrawRect(int x, int y, int w, int h, RGBA* color, int thickness)
{
	cqweqasvfa::GetOverlayDrawList()->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), cqweqasvfa::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), 0, 0, thickness);
}

static void DrawFilledRect(int x, int y, int w, int h, RGBA* color)
{
	cqweqasvfa::GetOverlayDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), cqweqasvfa::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), 0, 0);
}

static void DrawFilledRectIMCol(int x, int y, int w, int h, ImU32 col)
{
	cqweqasvfa::GetOverlayDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), col, 0, 0);
}


static void DrawCircleFilled(int x, int y, int radius, RGBA* color, int segments)
{
	cqweqasvfa::GetOverlayDrawList()->AddCircleFilled(ImVec2(x, y), radius, cqweqasvfa::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), segments);
}

static void DrawCircle(int x, int y, int radius, RGBA* color, int segments)
{
	cqweqasvfa::GetOverlayDrawList()->AddCircle(ImVec2(x, y), radius, cqweqasvfa::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), segments);
}

static void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, RGBA* color, float thickne)
{
	cqweqasvfa::GetOverlayDrawList()->AddTriangle(ImVec2(x1, y1), ImVec2(x2, y2), ImVec2(x3, y3), cqweqasvfa::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), thickne);
}

static void DrawTriangleFilled(int x1, int y1, int x2, int y2, int x3, int y3, RGBA* color)
{
	cqweqasvfa::GetOverlayDrawList()->AddTriangleFilled(ImVec2(x1, y1), ImVec2(x2, y2), ImVec2(x3, y3), cqweqasvfa::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)));
}

static void DrawLine(int x1, int y1, int x2, int y2, RGBA* color, int thickness)
{
	cqweqasvfa::GetOverlayDrawList()->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), cqweqasvfa::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), thickness);
}

static void DrawCornerBox(int x, int y, int w, int h, int borderPx, RGBA* color)
{
	DrawFilledRect(x + borderPx, y, w / 3, borderPx, color); //top 
	DrawFilledRect(x + w - w / 3 + borderPx, y, w / 3, borderPx, color); //top 
	DrawFilledRect(x, y, borderPx, h / 3, color); //left 
	DrawFilledRect(x, y + h - h / 3 + borderPx * 2, borderPx, h / 3, color); //left 
	DrawFilledRect(x + borderPx, y + h + borderPx, w / 3, borderPx, color); //bottom 
	DrawFilledRect(x + w - w / 3 + borderPx, y + h + borderPx, w / 3, borderPx, color); //bottom 
	DrawFilledRect(x + w + borderPx, y, borderPx, h / 3, color);//right 
	DrawFilledRect(x + w + borderPx, y + h - h / 3 + borderPx * 2, borderPx, h / 3, color);//right 
}
struct Process_Informations {
	HWND targetHWND;
	HWND overlayHWND;
	LPCWSTR className;
	MSG msg;
	RECT wRect;
};
Process_Informations proc;
BOOL CALLBACK EnumWindowsCallback(HWND hwnd, LPARAM lParam) {
	wchar_t className[255] = L"";
	GetClassNameW(hwnd, className, 255);
	//waevdfawd
	std::wstring xw = std::wstring(L"vd");

	std::wstring yw = (std::wstring(L"wae") + xw + std::wstring(L"fa") + std::wstring(L"wd"));
	const wchar_t* ptr = yw.c_str();

	if (wcscmp((wchar_t*)ptr, className) == 0)
	{
		Process_Informations* proc = (Process_Informations*)lParam;
		proc->overlayHWND = hwnd;
		memset((void*)&ptr[0], 0x00, yw.size() * 2);
		yw.clear();
		return TRUE;
	}
	return TRUE;
}
DWORD xqwerafcsdfaser()
{
	//if (qiqiqi)
	//{
	const MARGINS margins = { -1 ,-1, -1, -1 };
	WNDCLASSEXA wc;
	//HWND hwnd;
	MSG Msg;
	HINSTANCE hInstance = 0;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = DefWindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = (HINSTANCE)hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(RGB(0, 0, 0));
	wc.lpszMenuName = NULL;
	wc.lpszClassName = XorString("waevdfawd");
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassExA(&wc);

	MyWnd = CreateWindowExA(
		WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOPMOST,
		XorString("waevdfawd"),
		XorString("waevdfawd"),
		WS_POPUP | WS_VISIBLE,
		GameRect.left, GameRect.top, 1920, 1080,
		NULL, NULL, hInstance, 0);

	//SetLayeredWindowAttributes(MyWnd, RGB(0, 0, 0), 255, LWA_ALPHA);
	//DwmExtendFrameIntoClientArea(MyWnd, &margins);

	SetLayeredWindowAttributes(MyWnd, RGB(0, 0, 0), 255, LWA_ALPHA);
	MARGINS Margin = { -1 };
	DwmExtendFrameIntoClientArea(MyWnd, &Margin);

	ShowWindow(MyWnd, SW_SHOW);
	UpdateWindow(MyWnd);
	EnumWindows(EnumWindowsCallback, (LPARAM)&proc);
	Console::Success(XorString("Window hijacked."));
	Console::Success(XorString("Oyun icinde menu gozukmuyorsa, oyunun ayarlarindan ekran turunu 'Pencere' veya 'Tam pencere' olarak ayarlamalisiniz."));
	Console::Warning(XorString("Menu gizle/goster: F7"));
	DirectXInit(MyWnd);
	MainLoop();
	return 0;
	//qiqiqi = false;
}

void xqweqwef() {

	p_Params.BackBufferHeight = rHeight;
	p_Params.BackBufferWidth = rWidth;
	p_Device->Reset(&p_Params);
	p_Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
	p_Device->BeginScene();

	//std::wstring xw = std::wstring(L"al");
	//std::wstring yw = (std::wstring(L"Unre") + xw + std::wstring(L"Win") + std::wstring(L"dow"));
	//const wchar_t* ptr = yw.c_str();
	tWnd = FindWindow(XorString("acknex_mainwin"), 0);
	//memset((void*)&ptr[0], 0x00, yw.size() * 2);
	//yw.clear();
	if (tWnd == GetForegroundWindow() || GetActiveWindow() == GetForegroundWindow())
	{
		cqweqasvfa_ImplDX9_NewFrame();
		XRender::DrawMenu(p_Device);
		cqweqasvfa::Render();
	}
	else
	{

	}
	p_Device->EndScene();
	p_Device->PresentEx(0, 0, 0, 0, 0);
}

WPARAM MainLoop()
{
	static RECT old_rc;
	ZeroMemory(&Message, sizeof(MSG));

	while (Message.message != WM_QUIT)
	{
		if (PeekMessage(&Message, MyWnd, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}

		HWND hwnd_active = GetForegroundWindow();

		if (hwnd_active == GameWnd) {
			HWND hwndtest = GetWindow(hwnd_active, GW_HWNDPREV);
			SetWindowPos(MyWnd, hwndtest, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		}
		RECT rc;
		POINT xy;

		ZeroMemory(&rc, sizeof(RECT));
		ZeroMemory(&xy, sizeof(POINT));
		GetClientRect(GameWnd, &rc);
		ClientToScreen(GameWnd, &xy);
		rc.left = xy.x;
		rc.top = xy.y;

		cqweqasvfaIO& io = cqweqasvfa::GetIO();
		io.ImeWindowHandle = GameWnd;
		//io.DeltaTime = 1.0f / 60.0f;

		POINT p;
		GetCursorPos(&p);
		io.MousePos.x = p.x - xy.x;
		io.MousePos.y = p.y - xy.y;

		if (GetAsyncKeyState(VK_LBUTTON))
		{
			io.MouseDown[0] = true;
			io.MouseClicked[0] = true;
			io.MouseClickedPos[0].x = io.MousePos.x;
			io.MouseClickedPos[0].x = io.MousePos.y;
		}
		else
			io.MouseDown[0] = false;
		if (rc.left != old_rc.left || rc.right != old_rc.right || rc.top != old_rc.top || rc.bottom != old_rc.bottom)
		{
			old_rc = rc;

			Width = rc.right;
			Height = rc.bottom;

			p_Params.BackBufferWidth = Width;
			p_Params.BackBufferHeight = Height;
			SetWindowPos(MyWnd, (HWND)0, xy.x, xy.y, Width, Height, SWP_NOREDRAW);
			p_Device->Reset(&p_Params);
		}
		xqweqwef();
		Sleep(5);
	}
	cqweqasvfa_ImplDX9_Shutdown();
	//	cqweqasvfa_ImplWin32_Shutdown();
		//cqweqasvfa::DestroyContext();


	CleanuoD3D();
	DestroyWindow(MyWnd);

	return Message.wParam;
}

static LRESULT CALLBACK WinProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	if (cqweqasvfa_ImplWin32_WndProcHandler(hWnd, Message, wParam, lParam))
		return true;

	switch (Message)
	{
	case WM_DESTROY:
		CleanuoD3D();
		PostQuitMessage(0);
		exit(4);
		break;
	case WM_SIZE:
		if (p_Device != NULL && wParam != SIZE_MINIMIZED)
		{
			cqweqasvfa_ImplDX9_InvalidateDeviceObjects();
			p_Params.BackBufferWidth = LOWORD(lParam);
			p_Params.BackBufferHeight = HIWORD(lParam);
			HRESULT hr = p_Device->Reset(&p_Params);
			if (hr == D3DERR_INVALIDCALL)
				IM_ASSERT(0);
			cqweqasvfa_ImplDX9_CreateDeviceObjects();
		}
		break;
	default:
		return DefWindowProc(hWnd, Message, wParam, lParam);
		break;
	}
	return 0;
}


static void CleanuoD3D()
{
	if (p_Device != NULL)
	{
		p_Device->EndScene();
		p_Device->Release();
	}
	if (p_Object != NULL)
	{
		p_Object->Release();
	}
}

static int isTopwin()
{
	HWND hWnd = GetForegroundWindow();
	if (hWnd == GameWnd)
		return TopWindowGame;
	if (hWnd == MyWnd)
		return TopWindowMvoe;

	return 0;
}
static void SetWindowToTarget()
{
	//std::wstring xw = std::wstring(L"eal");

	//std::wstring yw = (std::wstring(L"Unr") + xw + std::wstring(L"Wi") + std::wstring(L"ndow"));
	//std::wstring xw = std::wstring(L"spa");
	while (1)
	{
		//std::wstring yw = (std::wstring(L"Re") + xw + std::wstring(L"wn0") + std::wstring(L"01"));
		//const wchar_t* ptr = yw.c_str();

		HWND XGameWnd = FindWindow(XorString("acknex_mainwin"), 0);

		if (XGameWnd)
		{
			ZeroMemory(&GameRect, sizeof(GameRect));
			GetWindowRect(XGameWnd, &GameRect);
			Width = GameRect.right - GameRect.left;
			Height = GameRect.bottom - GameRect.top;
			DWORD dwStyle = GetWindowLong(XGameWnd, GWL_STYLE);

			if (dwStyle & WS_BORDER)
			{
				GameRect.top += 32;
				Height -= 39;
			}
			ScreenCenterX = Width / 2;
			ScreenCenterY = Height / 2;
			MoveWindow(MyWnd, GameRect.left, GameRect.top, Width, Height, true);
		}
		Sleep(5);
	}
}


static HRESULT DirectXInit(HWND hWnd)
{
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)SetWindowToTarget, 0, 0, 0);

	WNDCLASSEX wClass =
	{
		sizeof(WNDCLASSEX),0,WinProc,0,0,nullptr,LoadIcon(nullptr, IDI_APPLICATION),LoadCursor(nullptr, IDC_ARROW),nullptr,nullptr, M_Name,LoadIcon(nullptr, IDI_APPLICATION)
	};

	if (!RegisterClassEx(&wClass))
		exit(1);

	GameWnd = FindWindow(XorString("waevdfawd"), 0);
	if (GameWnd)
	{
		GetClientRect(GameWnd, &GameRect);
		POINT xy;
		ClientToScreen(GameWnd, &xy);
		GameRect.left = xy.x;
		GameRect.top = xy.y;

		Width = GameRect.right;
		Height = GameRect.bottom;
	}
	else exit(2);
	//SetLayeredWindowAttributes(MyWnd, RGB(0, 0, 0), 255, LWA_ALPHA);
	//MARGINS Margin = { -1 };
	DwmExtendFrameIntoClientArea(MyWnd, &Margin);

	SetWindowLong(MyWnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW);

	//ShowWindow(MyWnd, SW_SHOW);
	//UpdateWindow(MyWnd);

	if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &p_Object)))
		exit(3);

	ZeroMemory(&p_Params, sizeof(p_Params));
	p_Params.Windowed = TRUE;
	p_Params.SwapEffect = D3DSWAPEFFECT_DISCARD;
	p_Params.hDeviceWindow = hWnd;
	p_Params.MultiSampleQuality = D3DMULTISAMPLE_NONE;
	p_Params.BackBufferFormat = D3DFMT_A8R8G8B8;
	p_Params.BackBufferWidth = Width;
	p_Params.BackBufferHeight = Height;
	p_Params.EnableAutoDepthStencil = TRUE;
	p_Params.AutoDepthStencilFormat = D3DFMT_D16;

	if (FAILED(p_Object->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &p_Params, 0, &p_Device)))
	{
		p_Object->Release();
		exit(4);
	}

	cqweqasvfa_ImplDX9_Init(hWnd, p_Device);

	cqweqasvfaIO& io = cqweqasvfa::GetIO();
	io.Fonts->AddFontDefault();

	static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
	ImFontConfig icons_config;
	icons_config.MergeMode = true;

	io.Fonts->AddFontFromMemoryCompressedTTF(FontAwesome_data, FontAwesome_size, 13.0f, &icons_config, icons_ranges);
	io.Fonts->Build();
	p_Object->Release();

	return S_OK;
}
inline bool file_exists(const std::string& name) {
	std::ifstream f(name.c_str());
	return f.good();
}

