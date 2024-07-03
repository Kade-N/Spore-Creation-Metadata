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

		// This was probably some testing code, don't think it's needed but I don't quite remember why this was here
		//list<Resource::IResourceFactory*> factories;
		//ResourceManager.GetFactoryList(factories);
		//for each (auto factory in factories)
		//{
		//	App::ConsolePrintF("%X:", factory->GetFactoryType());

		//	uint32_t types[10];
		//	factory->GetSupportedTypes(types, 10);
		//	string typesString = "";
		//	for each (auto type in types)
		//	{
		//		if (auto typeName = ResourceManager.GetTypenameFromType(type))
		//		{
		//			App::ConsolePrintF("  %ls", typeName);
		//		}
		//		else
		//		{
		//			//App::ConsolePrintF("  %X", type);
		//		}
		//	}
		//}
	}
	else {
		string16 fileName;
		ResourceManager.GetNameFromKey(metadata->GetAssetKey(), fileName);

		App::ConsolePrintF("Asset metadata for %ls:", fileName);
		App::ConsolePrintF("- Name: %ls", metadata->GetName().c_str());
		App::ConsolePrintF("- Server ID: %I64d", metadata->GetAssetID());
		App::ConsolePrintF("- Author: %ls (%I64d)", metadata->GetAuthor().c_str(), metadata->GetAuthorID());
		App::ConsolePrintF("- Parent ID: %I64d (local instance ID: %X)", metadata->GetParentAssetID(), metadata->GetParentAssetKey().instanceID);
		App::ConsolePrintF("- Original Parent ID: %I64d", metadata->GetOriginalParentAssetID());
		App::ConsolePrintF("- Created at %I64d, Downloaded at %I64d", metadata->GetTimeCreated(), metadata->GetTimeDownloaded());
		App::ConsolePrintF("- Shareable: %s", metadata->IsShareable() ? "true" : "false");
		App::ConsolePrintF("- Localized: %s", metadata->IsLocalized() ? "true" : "false");

		string16 tagsString = u"";
		for each (auto tag in metadata->GetTags())
		{
			tagsString += tag + u", ";
		}
		App::ConsolePrintF("- Tags: %ls", tagsString);

		string dataString = "";
		for each (auto item in metadata->GetAuthors())
		{
			dataString += item + ", ";
		}
		App::ConsolePrintF("- Data: %s", dataString);

		string16 databasePath = u"unknown";
		if (auto database = ResourceManager.FindDatabase(metadata->GetAssetKey())) databasePath = database->GetLocation();
		App::ConsolePrintF("- Database: %ls", databasePath);
	}
}