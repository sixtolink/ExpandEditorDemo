// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestSlate.h"
#include "TestSlateStyle.h"
#include "TestSlateCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"
#include "Viewport/PreviewViewport.h"
#include "EditorStyleSet.h"
#include "Widgets/Layout/SScrollBox.h"
#include "FileTree/FileParsing.h"
#include "FileTree/Folder.h"
#include "ViewType.h"
#include "Components/StaticMeshComponent.h"
#include "HAL/FileManager.h"

static const FName TestSlateTabName("TestSlate");

struct FAssetLibrary
{
	static const FName ViewportID;
	static const FName FileTreeID;
};

const FName FAssetLibrary::ViewportID(TEXT("AssetLibraryViewportID"));
const FName FAssetLibrary::FileTreeID(TEXT("FAssetLibraryFileTreeID"));

#define LOCTEXT_NAMESPACE "FTestSlateModule"

void FTestSlateModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FTestSlateStyle::Initialize();
	FTestSlateStyle::ReloadTextures();

	FTestSlateCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FTestSlateCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FTestSlateModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FTestSlateModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(
		TestSlateTabName, 
		FOnSpawnTab::CreateRaw(this, &FTestSlateModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FTestSlateTabTitle", "TestSlate"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

	FGlobalTabmanager::Get()->RegisterTabSpawner(
		FAssetLibrary::ViewportID,
		FOnSpawnTab::CreateRaw(this, &FTestSlateModule::OnSpawnViewportTab))
		.SetDisplayName(LOCTEXT("AssetLibraryViewportID", "Render"));

	FGlobalTabmanager::Get()->RegisterTabSpawner(
		FAssetLibrary::FileTreeID,
		FOnSpawnTab::CreateRaw(this, &FTestSlateModule::OnSpawnFileTreeTab))
		.SetDisplayName(LOCTEXT("FAssetLibraryFileTreeID", "FileTree"));

	if (!GMeshComponent)
	{
		GMeshComponent = NewObject<UStaticMeshComponent>();
		GMeshComponent->AddToRoot();
	}

	AssetLibraryDelegate.BindRaw(this, &FTestSlateModule::UpdateFile);
}

void FTestSlateModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FTestSlateStyle::Shutdown();

	FTestSlateCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterTabSpawner(FAssetLibrary::ViewportID);
	FGlobalTabmanager::Get()->UnregisterTabSpawner(FAssetLibrary::FileTreeID);

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(TestSlateTabName);
}

TSharedRef<SDockTab> FTestSlateModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	//SNew 返回共享指针 SAssignNew 返回共享指针
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			CreateEditor()
		];
}

TSharedRef<SDockTab> FTestSlateModule::OnSpawnViewportTab(const FSpawnTabArgs& SpawnTabArgs)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SBox)
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(PreviewViewport)
			]
		];
	UE_LOG(LogTemp, Error, TEXT("------->Viewport<-------"));
}

TSharedRef<SDockTab> FTestSlateModule::OnSpawnFileTreeTab(const FSpawnTabArgs& SpawnTabArgs)
{
	TSharedRef<SDockTab>lalala = SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SBox)
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SOverlay)
				+SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					SNew(SImage)
					.Image(FEditorStyle::Get().GetBrush("ExternalImagePicker.BlankImage"))
				]
				+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					SAssignNew(ScrollBox,SScrollBox)
					.Orientation(Orient_Vertical)
				]
			]
		];

	TArray<FString> AllPaths;
	FString FindPaths = "D:/UEProject/MyProject";
	//IFileManager::Get().FindFilesRecursive(AllPaths, *FPaths::ConvertRelativePathToFull(FPaths::ProjectDir()), *FString(TEXT("SM_Freighter_A.uasset")), true, true);
	IFileManager::Get().FindFilesRecursive(AllPaths, *FindPaths, *FString(TEXT("SM_Freighter_A.uasset")), true, true);
	AssetLibraryDelegate.ExecuteIfBound(AllPaths);

	return lalala;
}

void FTestSlateModule::UpdateFile(const TArray<FString>& Files)
{
	if (ScrollBox.IsValid())
	{
		NameTestSlate::FFileList FileList;
		NameTestSlate::FilesParsing(Files, FileList);

		ScrollBox->ClearChildren();
		ScrollBox->AddSlot()
			[
				SNew(SFolder,FileList)
			];
	}
}

void FTestSlateModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(TestSlateTabName);
}

TSharedRef<SWidget> FTestSlateModule::CreateEditor()
{
	TSharedRef<FTabManager::FLayout> Layout = FTabManager::NewLayout("AssetLibarary_Layout")
		->AddArea
		(
			FTabManager::NewPrimaryArea()
			->SetOrientation(Orient_Horizontal)
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.3f)
				->SetHideTabWell(true)
				->AddTab(FAssetLibrary::FileTreeID, ETabState::OpenedTab)
			)
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.7f)
				->SetHideTabWell(true)
				->AddTab(FAssetLibrary::ViewportID, ETabState::OpenedTab)
			)
		);
	TSharedPtr<SWindow> AssetLibararyWindows = SNew(SWindow);

	return FGlobalTabmanager::Get()->RestoreFrom(Layout, AssetLibararyWindows).ToSharedRef();
}

void FTestSlateModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FTestSlateCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FTestSlateCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FTestSlateModule, TestSlate)