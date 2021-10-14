// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FToolBarBuilder;
class FMenuBuilder;

class FExtendEditorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command. */
	void PluginButtonClicked();

	void SubMenuButtonClicked();

	//D:\UEProject\AssetsLibrary\Content\Assets\SM_Freighter_A.uasset
	//Game\Assets\SM_Freighter_A.uasset
	//StaticMesh'/Game/Assets/SM_Freighter_A.SM_Freighter_A'
	template<class T>
	T* StaticLoadObjectFromPath(const FString& Filename)
	{
		const FString ObjectName = T::StaticClass()->GetName() + TEXT("'/") + Filename + TEXT(".") + FPackageName::GetShortName(Filename) + TEXT("'");
		T* ObjectInstance = Cast<T>(StaticLoadObject(T::StaticClass(), nullptr, *ObjectName));
		return ObjectInstance;
	}
	
private:

	void RegisterMenus();

	void RegisterComboMenus(class UToolMenu* InMenu);
	void RegisterComboSubMenus(class UToolMenu* InMenu);
	void AddSelectActorMenu(FMenuBuilder& NewBuilder);
	void AddSelectActorMenuss(FMenuBuilder& NewBuilder);
	void AddSelectPathsMenu(FMenuBuilder& NewBuilder);
	void AddSelectAssetsMenu(FMenuBuilder& NewBuilder);
	void AddPathsMenu(FMenuBuilder& NewBuilder);

	TSharedRef<FExtender> CurrentSelectedActors(const TSharedRef<FUICommandList> MyUICommandList, const TArray<AActor*> MyActors);
	TSharedRef<FExtender> CurrentSelectedPaths(const TArray<FString>& Pathes);
	TSharedRef<FExtender> CurrentSelectedAssets(const TArray<FAssetData>& Assets);
	TSharedRef<FExtender> CurrentPaths(const TArray<FString>& Pathes);


private:
	TSharedPtr<class FUICommandList> PluginCommands;
	TSharedPtr<FUICommandList> SubCommands;
	FDelegateHandle SelectedActorsHandle;
	FString CusNames;
};