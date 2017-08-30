#include "F4SE/PluginAPI.h"

#include "F4SE_common/F4SE_version.h"
#include "F4SE_common/Relocation.h"
#include "F4SE_common/SafeWrite.h"


#include <shlobj.h>

IDebugLog						gLog;
UInt32							g_runtimeVersion = 0;
PluginHandle					g_pluginHandle = kPluginHandle_Invalid;




void InitHooks_1_9_4()
{
	constexpr char* configFile = "Data\\F4se\\Plugins\\UnlimitedFastTravel.ini";
	constexpr char* settingsSection = "Settings";
	if (GetPrivateProfileInt(settingsSection, "iConditionA", 0, configFile))
	{
		//enable fast travel in survival mode...
		UInt8 instructions[] = { 0xE9, 0xF2, 0x00, 0x00, 0x00, 0x90 };
		SafeWriteBuf(RelocAddr<uint32_t*>(0xB7D0EB).GetUIntPtr(), instructions, 6);
	}

	if (GetPrivateProfileInt(settingsSection, "iConditionB", 0, configFile))
	{
		//enable fast travel form interior and independent worldspace.
		SafeWrite8(RelocAddr<uint32_t*>(0xE82BB3).GetUIntPtr(), 0xEB);
		SafeWrite8(RelocAddr<uint32_t*>(0xE82BC4).GetUIntPtr(), 0xEB);
	}

	if (GetPrivateProfileInt(settingsSection, "iConditionC", 0, configFile))
	{
		//enable fast travel when enemies are nearby
		SafeWrite8(RelocAddr<uint32_t*>(0xE8294A).GetUIntPtr(), 0xEB);
	}

	if (GetPrivateProfileInt(settingsSection, "iConditionD", 0, configFile))
	{
		//enable fast travel while guards are pursuing you.
		SafeWrite8(RelocAddr<uint32_t*>(0xE82994).GetUIntPtr(), 0xEB);
	}

	if (GetPrivateProfileInt(settingsSection, "iConditionE", 0, configFile))
	{
		//enable fast travel while taking health damage.
		SafeWrite8(RelocAddr<uint32_t*>(0xE829BE).GetUIntPtr(), 0xEB);
	}

	if (GetPrivateProfileInt(settingsSection, "iConditionF", 0, configFile))
	{
		//enable fast travel when you're carrying too much.
		SafeWrite8(RelocAddr<uint32_t*>(0xE82A36).GetUIntPtr(), 0xEB);
	}
	if (GetPrivateProfileInt(settingsSection, "iConditionG", 0, configFile))
	{
		//enable fast travel while jumping or falling.
		SafeWrite8(RelocAddr<uint32_t*>(0xE82A55).GetUIntPtr(), 0xEB);
	}

	if (GetPrivateProfileInt(settingsSection, "iConditionH", 0, configFile))
	{
		//enable fast travel when you can only travel to an exterior location on a Vertibird.
		SafeWrite8(RelocAddr<uint32_t*>(0xE82BEB).GetUIntPtr(), 0xEB);
	}

	if (GetPrivateProfileInt(settingsSection, "iConditionI", 0, configFile))
	{
		//enable fast travel when fast travel is unavailable from current location.
		SafeWrite8(RelocAddr<uint32_t*>(0xE829ED).GetUIntPtr(), 0xEB);
	}
	if (GetPrivateProfileInt(settingsSection, "iConditionJ", 0, configFile))
	{
		//enable fast travel when fast travel is disabled by Papyrus scripts.
		UInt8 instructions[] = { 0xEB, 0x49, 0x90, 0x90, 0x90, 0x90 };
		SafeWriteBuf(RelocAddr<uint32_t*>(0xE82A8C).GetUIntPtr(), instructions, 6);
		SafeWrite8(RelocAddr<uint32_t*>(0xE82B22).GetUIntPtr(), 0xEB);
	}
	//isInSurvivalMode E968B0
}

void InitHooks_1_10_20()
{
	//FF 50 08 0F 57 C9 0F 2E C1 75 2A pattern
	constexpr char* configFile = "Data\\F4se\\Plugins\\UnlimitedFastTravel.ini";
	constexpr char* settingsSection = "Settings";
	if (GetPrivateProfileInt(settingsSection, "iConditionA", 0, configFile))
	{
		//enable fast travel in survival mode...
		//V1.10
		UInt8 instructions[] = { 0xE9, 0xF2, 0x00, 0x00, 0x00, 0x90 };
		SafeWriteBuf(RelocAddr<uintptr_t>(0xB94A8B).GetUIntPtr(), instructions, 6);
	}

	if (GetPrivateProfileInt(settingsSection, "iConditionB", 0, configFile))
	{
		//V1.10
		//enable fast travel form interior and independent worldspace.
		SafeWrite8(RelocAddr<uintptr_t>(0xE9A953).GetUIntPtr(), 0xEB);
		SafeWrite8(RelocAddr<uintptr_t>(0xE9A964).GetUIntPtr(), 0xEB);
	}

	if (GetPrivateProfileInt(settingsSection, "iConditionC", 0, configFile))
	{
		//V1.10
		//enable fast travel when enemies are nearby
		SafeWrite8(RelocAddr<uintptr_t>(0xE9A6EA).GetUIntPtr(), 0xEB);
	}

	if (GetPrivateProfileInt(settingsSection, "iConditionD", 0, configFile))
	{
		//enable fast travel while guards are pursuing you.
		SafeWrite8(RelocAddr<uintptr_t>(0xE9A734).GetUIntPtr(), 0xEB);  //17DA0
	}

	if (GetPrivateProfileInt(settingsSection, "iConditionE", 0, configFile))
	{
		//enable fast travel while taking health damage.
		SafeWrite8(RelocAddr<uintptr_t>(0xE9A75E).GetUIntPtr(), 0xEB);
	}

	if (GetPrivateProfileInt(settingsSection, "iConditionF", 0, configFile))
	{
		//enable fast travel when you're carrying too much.
		SafeWrite8(RelocAddr<uintptr_t>(0xE9A7D6).GetUIntPtr(), 0xEB);
	}
	if (GetPrivateProfileInt(settingsSection, "iConditionG", 0, configFile))
	{
		//enable fast travel while jumping or falling.
		SafeWrite8(RelocAddr<uintptr_t>(0xE9A7F5).GetUIntPtr(), 0xEB);
	}

	if (GetPrivateProfileInt(settingsSection, "iConditionH", 0, configFile))
	{
		//enable fast travel when you can only travel to an exterior location on a Vertibird.
		SafeWrite8(RelocAddr<uintptr_t>(0xE9A98B).GetUIntPtr(), 0xEB);
	}

	if (GetPrivateProfileInt(settingsSection, "iConditionI", 0, configFile))
	{
		//enable fast travel when fast travel is unavailable from current location.
		SafeWrite8(RelocAddr<uintptr_t>(0xE9A78D).GetUIntPtr(), 0xEB);
	}
	if (GetPrivateProfileInt(settingsSection, "iConditionJ", 0, configFile))
	{
		//enable fast travel when fast travel is disabled by Papyrus scripts.
		UInt8 instructions[] = { 0xEB, 0x49, 0x90, 0x90, 0x90, 0x90 }; //0F 85 8E 01 00 00
		SafeWriteBuf(RelocAddr<uintptr_t>(0xE9A82C).GetUIntPtr(), instructions, 6);
		SafeWrite8(RelocAddr<uintptr_t>(0xE9A8C2).GetUIntPtr(), 0xEB);
	}
}

extern "C"
{

	uintptr_t Init(void)
	{
		gLog.OpenRelative(CSIDL_MYDOCUMENTS, "\\My Games\\Fallout4\\F4SE\\UnlimitedFastTravel.log");
		_MESSAGE("UnlimitedFastTravel: %d.%d.%d", 1, 2, 0);
		InitHooks_1_10_20();
		return 0;
	}

	bool F4SEPlugin_Query(const F4SEInterface * f4se, PluginInfo * info)
	{
		gLog.OpenRelative(CSIDL_MYDOCUMENTS, "\\My Games\\Fallout4\\F4SE\\UnlimitedFastTravel.log");
		_MESSAGE("UnlimitedFastTravel: %d.%d.%d", 1, 2, 0);

		// populate info structure
		info->infoVersion = PluginInfo::kInfoVersion;
		info->name = "UnlimitedFastTravel";
		info->version = 1;

		// store plugin handle so we can identify ourselves later
		g_pluginHandle = f4se->GetPluginHandle();

		//g_runtimeVersion
		if (f4se->runtimeVersion < RUNTIME_VERSION_1_9_4)
		{
			MessageBox(nullptr, "UNSUPPORTED GAME VERSION.", "UnlimitedSurvivalMode", MB_OK);
			return false;
		}
		g_runtimeVersion = f4se->runtimeVersion;

		if (f4se->isEditor)
		{
			_FATALERROR("loaded in editor, marking as incompatible");
			return false;
		}

		return true;
	}


	bool F4SEPlugin_Load(const F4SEInterface * f4se)
	{
		if (g_runtimeVersion == RUNTIME_VERSION_1_9_4)
		{
			InitHooks_1_9_4();
		}
		else/* if (g_runtimeVersion == RUNTIME_VERSION_1_10_20)*/
		{
			InitHooks_1_10_20();
		}
		return true;
	}

};