#pragma once

#include <Spore\BasicIncludes.h>

class ViewOnlineCheat
	: public ArgScript::ICommand, public Sporepedia::IShopperListener
{
public:
	ViewOnlineCheat();
	~ViewOnlineCheat();

	enum AssetWebsite
	{
		/// Spore.com official Sporepedia
		Sporepedia,
		/// Spore.com pollinator asset browser
		Pollinator,
		/// Spore.com static XML model
		Model,
		/// Spore Community Sporepedia
		CommunitySporepedia,
		/// Spore Community asset tool
		Tool,
		/// Sporistics
		Sporistics
	};

	// Called when the cheat is invoked
	void ParseLine(const ArgScript::Line& line) override;

	// Returns a string containing the description. If mode != DescriptionMode::Basic, return a more elaborated description
	const char* GetDescription(ArgScript::DescriptionMode mode) const override;

	// Called when an asset is selected in the Sporepedia
	void OnShopperAccept(const ResourceKey& selection) override;

	// Opens the Spore.com Sporepedia page for the specified asset
	void OpenAssetWebpage(uint32_t instanceId, uint32_t groupId, AssetWebsite website);
private:
	AssetWebsite websiteToOpen;
};