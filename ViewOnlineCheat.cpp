#include "stdafx.h"
#include "ViewOnlineCheat.h"

ViewOnlineCheat::ViewOnlineCheat()
{
	websiteToOpen = Sporepedia;
}


ViewOnlineCheat::~ViewOnlineCheat()
{
}


void ViewOnlineCheat::ParseLine(const ArgScript::Line& line)
{
	// This method is called when your cheat is invoked.
	// Put your cheat code here.

	// If flag provided, change website to be opened
	if (line.HasFlag("pollinator")) websiteToOpen = Pollinator;
	if (line.HasFlag("model")) websiteToOpen = Model;
	if (line.HasFlag("community")) websiteToOpen = CommunitySporepedia;
	if (line.HasFlag("tool")) websiteToOpen = Tool;
	if (line.HasFlag("sporistics")) websiteToOpen = Sporistics;

	// Open the Sporepedia
	Sporepedia::ShopperRequest request(this);
	Sporepedia::ShopperRequest::Show(request);
}

const char* ViewOnlineCheat::GetDescription(ArgScript::DescriptionMode mode) const
{
	if (mode == ArgScript::DescriptionMode::Basic) {
		return "Open a creation on Spore.com or another website";
	}
	else {
		return "viewOnline: Open a creation on Spore.com. The creation must be shared. Works with modded creations.\nYou can open a different website by specifying one of the following:\n  -model    Open the XML model on static.spore.com\n  -community    Open the creation in the Community Sporepedia\n  -tool    Open the creation in the Asset Tool\n  -sporistics    Open the creation on Sporistics";
	}
}

void ViewOnlineCheat::OnShopperAccept(const ResourceKey& selection)
{
	OpenAssetWebpage(selection.instanceID, selection.groupID, websiteToOpen);

	// Reset back to default
	websiteToOpen = Sporepedia;
}

void ViewOnlineCheat::OpenAssetWebpage(uint32_t instanceId, uint32_t groupId, AssetWebsite website)
{
	cAssetMetadataPtr metadata;
	Pollinator::GetMetadata(instanceId, groupId, metadata);
	// Make sure creation/metadata exists
	if (!metadata) {
		App::ConsolePrintF("Asset metadata not found for %X!%X", groupId, instanceId);
		return;
	}
	// Asset ID will be -1 when not shared
	else if (metadata->GetAssetID() < 0) {
		App::ConsolePrintF("Asset %X!%X (%s) is not shared", groupId, instanceId, metadata->GetName().c_str());
		return;
	}

	// Asset ID as string
	string16 assetId = u"";
	assetId.sprintf(u"%I64d", metadata->GetAssetID());

	// Split form of ID, used in static URLs
	string16 splitId = assetId.substr(0, 3) + u"/" + assetId.substr(3, 3) + u"/" + assetId.substr(6, 3);

	// Build the URL
	string16 url = u"";
	switch (website)
	{
	case Sporepedia:
		url = u"http://www.spore.com/sporepedia#qry=ast-" + assetId + u":sast-" + assetId;
		break;
	case Pollinator:
		url = u"http://pollinator.spore.com/pollinator/admin/asset/" + assetId;
		break;
	case Model:
		url = u"http://static.spore.com/static/model/" + splitId + u"/" + assetId + u".xml";
		break;
	case CommunitySporepedia:
		url = u"https://sporecommunity.com/assets/" + assetId;
		break;
	case Tool:
		url = u"https://tools.sporecommunity.com/asset?assetId=" + assetId;
		break;
	case Sporistics:
		url = u"https://www.sporistics.com/?p=asset:" + assetId;
		break;
	}

	// Open the URL
	App::IAppSystem::Get()->OpenURL(url.c_str());
}