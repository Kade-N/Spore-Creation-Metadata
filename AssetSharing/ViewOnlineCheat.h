#pragma once

#include <Spore\BasicIncludes.h>

class ViewOnlineCheat 
	: public ArgScript::ICommand, public Sporepedia::IShopperListener
{
public:
	ViewOnlineCheat();
	~ViewOnlineCheat();

	// Called when the cheat is invoked
	void ParseLine(const ArgScript::Line& line) override;
	
	// Returns a string containing the description. If mode != DescriptionMode::Basic, return a more elaborated description
	const char* GetDescription(ArgScript::DescriptionMode mode) const override;

	// Called when an asset is selected in the Sporepedia
	void OnShopperAccept(const ResourceKey& selection) override;

	// Opens the Spore.com Sporepedia page for the specified asset
	void OpenSpdWebsite(uint32_t instanceId, uint32_t groupId);
};

