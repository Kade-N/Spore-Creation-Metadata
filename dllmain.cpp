// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "AssetMetadataCheat.h"
#include "ViewOnlineCheat.h"


static void RegisterCommonResourceTypes()
{
	// Creations
	ResourceManager.SetTypename(TypeIDs::cll, u"cll");
	ResourceManager.SetTypename(TypeIDs::crt, u"crt");
	ResourceManager.SetTypename(TypeIDs::vcl, u"vcl");
	ResourceManager.SetTypename(TypeIDs::bld, u"bld");
	ResourceManager.SetTypename(TypeIDs::ufo, u"ufo");
	ResourceManager.SetTypename(TypeIDs::flr, u"flr");
	ResourceManager.SetTypename(TypeIDs::cmp, u"cmp");
	ResourceManager.SetTypename(TypeIDs::adventure, u"adventure");

	// Other associated files
	ResourceManager.SetTypename(TypeIDs::pollen_metadata, u"pollen_metadata");
	ResourceManager.SetTypename(TypeIDs::png, u"png");
	ResourceManager.SetTypename(TypeIDs::bem, u"bem");
	ResourceManager.SetTypename(0x02D5C9AF, u"summary");
	ResourceManager.SetTypename(id("creaturedata"), u"creaturedata");
}


void Initialize()
{
	// This method is executed when the game starts, before the user interface is shown
	// Here you can do things such as:
	//  - Add new cheats
	//  - Add new simulator classes
	//  - Add new game modes
	//  - Add new space tools
	//  - Change materials

	// Add common types to resource manager
	RegisterCommonResourceTypes();

	CheatManager.AddCheat("assetMetadata", new AssetMetadataCheat());
	CheatManager.AddCheat("viewOnline", new ViewOnlineCheat());
}

void Dispose()
{
	// This method is called when the game is closing
}

void AttachDetours()
{
	// Call the attach() method on any detours you want to add
	// For example: cViewer_SetRenderType_detour::attach(GetAddress(cViewer, SetRenderType));
}


// Generally, you don't need to touch any code here
BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		ModAPI::AddPostInitFunction(Initialize);
		ModAPI::AddDisposeFunction(Dispose);

		PrepareDetours(hModule);
		AttachDetours();
		CommitDetours();
		break;

	case DLL_PROCESS_DETACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	}
	return TRUE;
}