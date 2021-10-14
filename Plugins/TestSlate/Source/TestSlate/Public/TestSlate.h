// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FToolBarBuilder;
class FMenuBuilder;

class FTestSlateModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command (by default it will bring up plugin window) */
	void PluginButtonClicked();

	/** ����SWidget���в��� */
	TSharedRef<SWidget> CreateEditor();

private:

	void RegisterMenus();

	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);
	TSharedRef<SDockTab> OnSpawnViewportTab(const class FSpawnTabArgs& SpawnTabArgs);
	TSharedRef<SDockTab> OnSpawnFileTreeTab(const class FSpawnTabArgs& SpawnTabArgs);

	void UpdateFile(const TArray<FString>& Files);

private:
	TSharedPtr<class FUICommandList> PluginCommands;
	TSharedPtr<class SScrollBox> ScrollBox;
};
