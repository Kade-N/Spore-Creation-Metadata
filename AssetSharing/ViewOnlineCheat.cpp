#include "stdafx.h"
#include "ViewOnlineCheat.h"
#include <windows.h>
#include <shellapi.h>

ViewOnlineCheat::ViewOnlineCheat()
{
}


ViewOnlineCheat::~ViewOnlineCheat()
{
}


void ViewOnlineCheat::ParseLine(const ArgScript::Line& line)
{
	// This method is called when your cheat is invoked.
	// Put your cheat code here.

	// Open the Sporepedia
	Sporepedia::ShopperRequest request(this);
	Sporepedia::ShopperRequest::Show(request);
}

const char* ViewOnlineCheat::GetDescription(ArgScript::DescriptionMode mode) const
{
	if (mode == ArgScript::DescriptionMode::Basic) {
		return "Opens a creation on Spore.com.";
	}
	else {
		return "ViewOnlineCheat: Opens Spore.com and shows the selected creation in the Sporepedia website. The creation must be shared. Works with modded creations.";
	}
}

void ViewOnlineCheat::OnShopperAccept(const ResourceKey& selection)
{
	OpenSpdWebsite(selection.instanceID, selection.groupID);
}

void ViewOnlineCheat::OpenSpdWebsite(uint32_t instanceId, uint32_t groupId)
{
	cAssetMetadataPtr metadata;
	Pollinator::GetMetadata(instanceId, groupId, metadata);
	if (!metadata) {
		App::ConsolePrintF("Asset metadata not found for %X!%X", groupId, instanceId);
	}
	else if (metadata->GetAssetID() < 0) {
		App::ConsolePrintF("Asset %X!%X (%s) is not shared", groupId, instanceId, metadata->GetName().c_str());
	}
	else {
		wstring url = L"";
		url.sprintf(L"https://www.spore.com/sporepedia#qry=ast-%I64d:sast-%I64d", metadata->GetAssetID(), metadata->GetAssetID());
		ShellExecute(NULL, L"open", url.c_str(), NULL, NULL, SW_SHOW);
	}
}