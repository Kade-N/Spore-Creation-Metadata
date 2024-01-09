#include "stdafx.h"
#include "AssetMetadataCheat.h"

AssetMetadataCheat::AssetMetadataCheat()
{
}


AssetMetadataCheat::~AssetMetadataCheat()
{
}


void AssetMetadataCheat::ParseLine(const ArgScript::Line& line)
{
	// This method is called when your cheat is invoked.
	// Put your cheat code here.

	// Open the Sporepedia
	Sporepedia::ShopperRequest request(this);
	Sporepedia::ShopperRequest::Show(request);
}

const char* AssetMetadataCheat::GetDescription(ArgScript::DescriptionMode mode) const
{
	if (mode == ArgScript::DescriptionMode::Basic) {
		return "Get or set the metadata for a creation in the Sporepedia";
	}
	else {
		return "assetMetadata: Get or set the metadata for a creation in the Sporepedia. Includes the name, resource key (TGI), server ID, and other data.";
	}
}

void AssetMetadataCheat::OnShopperAccept(const ResourceKey& selection)
{
	PrintMetadata(selection.instanceID, selection.groupID);
}

void AssetMetadataCheat::PrintMetadata(uint32_t instanceId, uint32_t groupId)
{
	cAssetMetadataPtr metadata;
	if (!Pollinator::GetMetadata(instanceId, groupId, metadata)) {
		App::ConsolePrintF("Asset metadata not found for %X!%X", groupId, instanceId);
	}
	else {
		App::ConsolePrintF("Asset metadata for %X!%X:", groupId, instanceId);
		App::ConsolePrintF("- Name: %ls", metadata->GetName().c_str());
		App::ConsolePrintF("- Server ID: %I64d", metadata->GetAssetID());
		App::ConsolePrintF("- Author: %ls (%I64d)", metadata->GetAuthor().c_str(), metadata->GetAuthorID());
		App::ConsolePrintF("- Parent ID: %I64d (local instance ID: %X)", metadata->GetParentAssetID(), metadata->GetParentAssetKey().instanceID);
		App::ConsolePrintF("- Original Parent ID: %I64d", metadata->GetOriginalParentAssetID());
		App::ConsolePrintF("- Created at %I64d, Downloaded at %I64d", metadata->GetTimeCreated(), metadata->GetTimeDownloaded());
		App::ConsolePrintF("- Shareable: %s", metadata->IsShareable() ? "true" : "false");
		App::ConsolePrintF("- Localized: %s", metadata->IsLocalized() ? "true" : "false");
	}
}