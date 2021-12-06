#pragma once

#include <Spore\BasicIncludes.h>

class AssetMetadataCheat 
	: public ArgScript::ICommand, public Sporepedia::IShopperListener
{
public:
	AssetMetadataCheat();
	~AssetMetadataCheat();

	// Called when the cheat is invoked
	void ParseLine(const ArgScript::Line& line) override;
	
	// Returns a string containing the description. If mode != DescriptionMode::Basic, return a more elaborated description
	const char* GetDescription(ArgScript::DescriptionMode mode) const override;

	// Called when an asset is selected in the Sporepedia
	void OnShopperAccept(const ResourceKey& selection) override;

	// Prints the metadata for the specified asset to the console
	void PrintMetadata(uint32_t instanceId, uint32_t groupId);
};

