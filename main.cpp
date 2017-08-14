#include "F4SE/PluginAPI.h"

#include "F4SE_common/F4SE_version.h"
#include "F4SE_common/Relocation.h"
#include "F4SE_common/SafeWrite.h"


#include <shlobj.h>

IDebugLog	gLog;

PluginHandle				  g_pluginHandle = kPluginHandle_Invalid;




void InitHooks()
{
	constexpr char* configFile = "Data\\F4se\\Plugins\\UnlimitedFastTravel.ini";
	constexpr char* settingsSection = "Settings";
	if (GetPrivateProfileInt(settingsSection, "iConditonA", 0, configFile))
	{
		//enable fast travel in survival mode...
		UInt8 instructions[] = { 0xE9, 0xF2, 0x00, 0x00, 0x00, 0x90 };
		SafeWriteBuf(RelocAddr<uint32_t*>(0xB7D0EB).GetUIntPtr(), instructions, 6);
	}

	if (GetPrivateProfileInt(settingsSection, "iConditonB", 0, configFile))
	{
		//enable fast travel form interior and independent worldspace.
		SafeWrite8(RelocAddr<uint32_t*>(0xE82BB3).GetUIntPtr(), 0xEB);
		SafeWrite8(RelocAddr<uint32_t*>(0xE82BC4).GetUIntPtr(), 0xEB);
	}

	if (GetPrivateProfileInt(settingsSection, "iConditonC", 0, configFile))
	{
		//enable fast travel when enemies are nearby
		SafeWrite8(RelocAddr<uint32_t*>(0xE8294A).GetUIntPtr(), 0xEB);
	}

	if (GetPrivateProfileInt(settingsSection, "iConditonD", 0, configFile))
	{
		//enable fast travel while guards are pursuing you.
		SafeWrite8(RelocAddr<uint32_t*>(0xE82994).GetUIntPtr(), 0xEB);
	}

	if (GetPrivateProfileInt(settingsSection, "iConditonE", 0, configFile))
	{
		//enable fast travel while taking health damage.
		SafeWrite8(RelocAddr<uint32_t*>(0xE829BE).GetUIntPtr(), 0xEB);
	}

	if (GetPrivateProfileInt(settingsSection, "iConditonF", 0, configFile))
	{
		//enable fast travel when you're carrying too much.
		SafeWrite8(RelocAddr<uint32_t*>(0xE82A36).GetUIntPtr(), 0xEB);
	}
	if (GetPrivateProfileInt(settingsSection, "iConditonG", 0, configFile))
	{
		//enable fast travel while jumping or falling.
		SafeWrite8(RelocAddr<uint32_t*>(0xE82A55).GetUIntPtr(), 0xEB);
	}

	if (GetPrivateProfileInt(settingsSection, "iConditonH", 0, configFile))
	{
		//enable fast travel when you can only travel to an exterior location on a Vertibird.
		SafeWrite8(RelocAddr<uint32_t*>(0xE82BEB).GetUIntPtr(), 0xEB);
	}

	if (GetPrivateProfileInt(settingsSection, "iConditonI", 0, configFile))
	{
		//enable fast travel when fast travel is unavailable from current location.
		SafeWrite8(RelocAddr<uint32_t*>(0xE829ED).GetUIntPtr(), 0xEB);
	}
	if (GetPrivateProfileInt(settingsSection, "iConditonJ", 0, configFile))
	{
		//enable fast travel when fast travel is disabled by Papyrus scripts.
		UInt8 instructions[] = { 0xEB, 0x49, 0x90, 0x90, 0x90, 0x90 };
		SafeWriteBuf(RelocAddr<uint32_t*>(0xE82A8C).GetUIntPtr(), instructions, 6);
		SafeWrite8(RelocAddr<uint32_t*>(0xE82B22).GetUIntPtr(), 0xEB);
	}
	//isInSurvivalMode E968B0
}



extern "C"
{
	bool F4SEPlugin_Query(const F4SEInterface * f4se, PluginInfo * info)
	{
		gLog.OpenRelative(CSIDL_MYDOCUMENTS, "\\My Games\\Fallout4\\F4SE\\UnlimitedFastTravel.log");
		_MESSAGE("UnlimitedFastTravel: %d.%d.%d", 1, 1, 0);

		// populate info structure
		info->infoVersion = PluginInfo::kInfoVersion;
		info->name = "UnlimitedFastTravel";
		info->version = 1;

		// store plugin handle so we can identify ourselves later
		g_pluginHandle = f4se->GetPluginHandle();

		if (f4se->runtimeVersion != RUNTIME_VERSION_1_9_4)
		{
			MessageBox(nullptr, "UNSUPPORTED GAME VERSION.", "UnlimitedFastTravel", MB_OK);
			return false;
		}

		if (f4se->isEditor)
		{
			_FATALERROR("loaded in editor, marking as incompatible");
			return false;
		}

		return true;
	}


	bool F4SEPlugin_Load(const F4SEInterface * f4se)
	{
		InitHooks();
		return true;
	}

};