// Copyright Epic Games, Inc. All Rights Reserved.

#include "ExtendEditor.h"
#include "ExtendEditorStyle.h"
#include "ExtendEditorCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"
#include "LevelEditor.h"
#include "ContentBrowserModule.h"

static const FName ExtendEditorTabName("ExtendEditor");

#define LOCTEXT_NAMESPACE "FExtendEditorModule"

void FExtendEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FExtendEditorStyle::Initialize();
	FExtendEditorStyle::ReloadTextures();

	FExtendEditorCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	//�󶨲���������Ͷ�Ӧ����
	PluginCommands->MapAction(
		FExtendEditorCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FExtendEditorModule::PluginButtonClicked),
		FCanExecuteAction());

	SubCommands = MakeShareable(new FUICommandList);

	SubCommands->MapAction(
		FExtendEditorCommands::Get().SubMenuAction,
		FExecuteAction::CreateRaw(this, &FExtendEditorModule::SubMenuButtonClicked),
		FCanExecuteAction());

	//ע����尴ť
	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FExtendEditorModule::RegisterMenus));
}

void FExtendEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FExtendEditorStyle::Shutdown();

	FExtendEditorCommands::Unregister();
}

void FExtendEditorModule::PluginButtonClicked()
{
	// Put your "OnButtonClicked" stuff here
	FText DialogText = FText::Format(
							LOCTEXT("PluginButtonDialogText", "Add code to {0} in {1} to override this button's actions"),
							FText::FromString(TEXT("FExtendEditorModule::PluginButtonClicked()")),
							FText::FromString(TEXT("ExtendEditor.cpp"))
					   );
	FMessageDialog::Open(EAppMsgType::Ok, DialogText);
}

void FExtendEditorModule::SubMenuButtonClicked()
{
	// Put your "OnButtonClicked" stuff here
	FText DialogText = FText::Format(
		LOCTEXT("SubPluginButtonDialogText", "SubSubSubSubSubSubSub"),
		FText::FromString(TEXT("FSubSubSubSub")),
		FText::FromString(TEXT("SubSubSubSub"))
	);
	FMessageDialog::Open(EAppMsgType::Ok, DialogText);
}

void FExtendEditorModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	//�����Ͻ�window��ť����Ӳ����ť
	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			//��Ӳ��󶨰�ťӳ��
			Section.AddMenuEntryWithCommandList(
				FExtendEditorCommands::Get().PluginAction,
				PluginCommands,
				FText::FromString(TEXT("PluginName")),
				FText::FromString(TEXT("ToolTip")),
				FSlateIcon(), FName(TEXT("highlight")),
				FName(TEXT("None"))
			);
		}
	}

	//��Viewport�Ϸ�ToolBar�����Ӳ����ť
	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->AddSection("CusToolBar");
			{
				//��ʼ��ToolMenuButton��ʽ
				FToolMenuEntry& Entry = Section.AddEntry(
					FToolMenuEntry::InitToolBarButton(FExtendEditorCommands::Get().PluginAction));
				//�󶨰�ť����
				Entry.SetCommandList(PluginCommands);
				FToolMenuEntry& EntryEntry = Section.AddEntry(
					FToolMenuEntry::InitComboButton(FName(TEXT("ComboTestTwo")),
						FToolUIActionChoice(),
						FNewToolMenuChoice(),
						FText::FromString(TEXT("ComboTestTwo")),
						FText::FromString(TEXT("ToolTipTwo")),
						FSlateIcon(),
						false,
						"ComboTestTwo"
					)
				);
				//�󶨰�ť����
				EntryEntry.SetCommandList(PluginCommands);
			}
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = *ToolbarMenu->FindSection("CusToolBar");
			{
				//��ʼ��ToolMenuButton��ʽ
				Section.AddEntry(
					FToolMenuEntry::InitComboButton(FName(TEXT("ComboTestThree")),
						FToolUIActionChoice(),
						FNewToolMenuChoice(FNewToolMenuDelegate::CreateRaw(this, &FExtendEditorModule::RegisterComboMenus)),
						FText::FromString(TEXT("ComboTestThree")),
						FText::FromString(TEXT("ToolTip")),
						FSlateIcon(),
						false,
						"ComboTestThree"
					)
				);
			}
		}
	}

	//��Window�ұ�����°�ť
	{
		UToolMenu* NewMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu");
		{
			FToolMenuSection& Section = NewMenu->FindOrAddSection("Help");
			{
				//��ʼ���˵���ʽ
				Section.AddMenuEntry(
					FExtendEditorCommands::Get().CreateSubMenuAction,
					FText::FromString(TEXT("CreateSubMenuAction")),
					FText::FromString(TEXT("ToolTip")), FSlateIcon(),
					FName(TEXT("HighLight"))
				);
			}
		}
	}

	//CreateSub��ť����Ӱ�ť
	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.CreateSubMenuAction");
		{
			FToolMenuSection& Section = Menu->AddSection("SubMenuItem", FText::FromString(TEXT("SubMenuItem")));
			//��Ӳ��󶨰�ťӳ��
			Section.AddMenuEntryWithCommandList(FExtendEditorCommands::Get().SubMenuAction, SubCommands, FText::FromString(TEXT("SubMenuItem")), FText::FromString(TEXT("ToolTip")), FSlateIcon(), FName(TEXT("HighLight")), FName(TEXT("None")));;
			Section.AddSeparator(FName(TEXT("MySeparator")));
			Section.AddMenuEntryWithCommandList(FExtendEditorCommands::Get().SubMenuAction, SubCommands, FText::FromString(TEXT("SubMenuItem")), FText::FromString(TEXT("ToolTip")), FSlateIcon(), FName(TEXT("HighLight")), FName(TEXT("None")));;
			Section.AddSeparator(FName(TEXT("MySeparator011")));
			Section.AddMenuEntryWithCommandList(FExtendEditorCommands::Get().SubMenuAction, SubCommands, FText::FromString(TEXT("SubMenuItem")), FText::FromString(TEXT("ToolTip")), FSlateIcon(), FName(TEXT("HighLight")), FName(TEXT("None")));;
			Section.AddSubMenu(FName(TEXT("SubMenus")), FText::FromString(TEXT("SubMenus")), FText::FromString(TEXT("ToolTip")), FNewToolMenuChoice(), false, FSlateIcon(), true);
		}
	}

	//CreateSub��ť����Ӹ��˵�
	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.CreateSubMenuAction.SubMenus");
		{
			FToolMenuSection& Section = Menu->AddSection("SubSubMenuItem", FText::FromString(TEXT("SubSubMenuItem")));
			//��Ӳ��󶨰�ťӳ��
			Section.AddMenuEntryWithCommandList(FExtendEditorCommands::Get().SubMenuAction, SubCommands, FText::FromString(TEXT("SubMenuItem")), FText::FromString(TEXT("ToolTip")), FSlateIcon(), FName(TEXT("HighLight")), FName(TEXT("None")));;
			Section.AddSeparator(FName(TEXT("MySeparator")));
			Section.AddMenuEntryWithCommandList(FExtendEditorCommands::Get().SubMenuAction, SubCommands, FText::FromString(TEXT("SubMenuItem")), FText::FromString(TEXT("ToolTip")), FSlateIcon(), FName(TEXT("HighLight")), FName(TEXT("None")));;
			Section.AddSeparator(FName(TEXT("MySeparator011")));
			Section.AddMenuEntryWithCommandList(FExtendEditorCommands::Get().SubMenuAction, SubCommands, FText::FromString(TEXT("SubMenuItem")), FText::FromString(TEXT("ToolTip")), FSlateIcon(), FName(TEXT("HighLight")), FName(TEXT("None")));;
			Section.AddMenuEntryWithCommandList(FExtendEditorCommands::Get().SubMenuAction, SubCommands, FText::FromString(TEXT("SubMenuItem")), FText::FromString(TEXT("ToolTip")), FSlateIcon(), FName(TEXT("HighLight")), FName(TEXT("None")));;
		}
	}

	//���viewport��outline��ѡ���Ҽ��˵�
	{
		FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
		auto& MenuButtonArray = LevelEditorModule.GetAllLevelViewportContextMenuExtenders();
		MenuButtonArray.Add(FLevelEditorModule::FLevelViewportMenuExtender_SelectedActors::CreateRaw(this, &FExtendEditorModule::CurrentSelectedActors));
		SelectedActorsHandle = MenuButtonArray.Last().GetHandle();
	}
	
	//���viewport��outline��δѡ���Ҽ��˵�
	/*{
		FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
		auto& MenuButtonArray = LevelEditorModule.GetAllLevelViewportContextMenuExtenders();
		MenuButtonArray.Add(FLevelEditorModule::FLevelViewportMenuExtender_SelectedActors::CreateRaw(this, &FExtendEditorModule::CurrentSelectedActors));
		SelectedActorsHandle = MenuButtonArray.Last().GetHandle();
	}*/

	//ContentBrowserPath�Ҽ�
	{
		FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
		auto& MenuButtonArray = ContentBrowserModule.GetAllPathViewContextMenuExtenders();

		MenuButtonArray.Add(FContentBrowserMenuExtender_SelectedPaths::CreateRaw(this,&FExtendEditorModule::CurrentSelectedPaths));
	}
	
	//ContentBrowserAsset�Ҽ�
	{
		FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
		auto& MenuButtonArray = ContentBrowserModule.GetAllAssetViewContextMenuExtenders();

		MenuButtonArray.Add(FContentBrowserMenuExtender_SelectedAssets::CreateRaw(this,&FExtendEditorModule::CurrentSelectedAssets));
	}
	
	//ContentBrowser�Ҽ�
	{
		FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
		auto& MenuButtonArray = ContentBrowserModule.GetAllAssetContextMenuExtenders();

		MenuButtonArray.Add(FContentBrowserMenuExtender_SelectedPaths::CreateRaw(this,&FExtendEditorModule::CurrentPaths));
	}
}

void FExtendEditorModule::RegisterComboMenus(UToolMenu* InMenu)
{
	{
		FToolMenuSection& Section = InMenu->AddSection("SubMenuItem", FText::FromString(TEXT("SubMenuItem")));
		//��Ӳ��󶨰�ťӳ��
		Section.AddMenuEntryWithCommandList(FExtendEditorCommands::Get().SubMenuAction, SubCommands, FText::FromString(TEXT("SubMenuItem")), FText::FromString(TEXT("ToolTip")), FSlateIcon(), FName(TEXT("HighLight")), FName(TEXT("None")));;
		Section.AddSeparator(FName(TEXT("MySeparator")));
		Section.AddMenuEntryWithCommandList(FExtendEditorCommands::Get().SubMenuAction, SubCommands, FText::FromString(TEXT("SubMenuItem")), FText::FromString(TEXT("ToolTip")), FSlateIcon(), FName(TEXT("HighLight")), FName(TEXT("None")));;
		Section.AddSeparator(FName(TEXT("MySeparator011")));
		Section.AddMenuEntryWithCommandList(FExtendEditorCommands::Get().SubMenuAction, SubCommands, FText::FromString(TEXT("SubMenuItem")), FText::FromString(TEXT("ToolTip")), FSlateIcon(), FName(TEXT("HighLight")), FName(TEXT("None")));;
		Section.AddSubMenu(FName(TEXT("SubMenus")),
			FText::FromString(TEXT("SubMenus")), 
			FText::FromString(TEXT("ToolTip")), 
			FNewToolMenuChoice(FNewToolMenuDelegate::CreateRaw(this, &FExtendEditorModule::RegisterComboSubMenus)),
			false, FSlateIcon(),
			true);
	}
}

void FExtendEditorModule::RegisterComboSubMenus(UToolMenu* InMenu)
{
	FToolMenuSection& Section = InMenu->AddSection("SubSubMenuItem", FText::FromString(TEXT("SubSubMenuItem")));
	//��Ӳ��󶨰�ťӳ��
	Section.AddMenuEntryWithCommandList(FExtendEditorCommands::Get().SubMenuAction, SubCommands, FText::FromString(TEXT("SubMenuItem")), FText::FromString(TEXT("ToolTip")), FSlateIcon(), FName(TEXT("HighLight")), FName(TEXT("None")));;
	Section.AddSeparator(FName(TEXT("MySeparator")));
	Section.AddMenuEntryWithCommandList(FExtendEditorCommands::Get().SubMenuAction, SubCommands, FText::FromString(TEXT("SubMenuItem")), FText::FromString(TEXT("ToolTip")), FSlateIcon(), FName(TEXT("HighLight")), FName(TEXT("None")));;
	Section.AddSeparator(FName(TEXT("MySeparator011")));
	Section.AddMenuEntryWithCommandList(FExtendEditorCommands::Get().SubMenuAction, SubCommands, FText::FromString(TEXT("SubMenuItem")), FText::FromString(TEXT("ToolTip")), FSlateIcon(), FName(TEXT("HighLight")), FName(TEXT("None")));;
	Section.AddMenuEntryWithCommandList(FExtendEditorCommands::Get().SubMenuAction, SubCommands, FText::FromString(TEXT("SubMenuItem")), FText::FromString(TEXT("ToolTip")), FSlateIcon(), FName(TEXT("HighLight")), FName(TEXT("None")));;
}

void FExtendEditorModule::AddSelectActorMenu(FMenuBuilder& NewBuilder)
{
	NewBuilder.AddMenuEntry(FExtendEditorCommands::Get().PluginAction);
	NewBuilder.AddSeparator();
	NewBuilder.AddSubMenu(
		LOCTEXT("ONEONE","juasjuas"),
		LOCTEXT("TWOTWO","juasjusadas"),
		FNewMenuDelegate::CreateRaw(this,&FExtendEditorModule::AddSelectActorMenuss)
	);
}

void FExtendEditorModule::AddSelectActorMenuss(FMenuBuilder& NewBuilder)
{
	NewBuilder.AddMenuEntry(FExtendEditorCommands::Get().PluginAction);
	NewBuilder.AddMenuEntry(FExtendEditorCommands::Get().PluginAction);
	NewBuilder.AddMenuEntry(FExtendEditorCommands::Get().PluginAction);
}

void FExtendEditorModule::AddSelectPathsMenu(FMenuBuilder& NewBuilder)
{
	NewBuilder.AddMenuEntry(FExtendEditorCommands::Get().PluginAction);
}

void FExtendEditorModule::AddSelectAssetsMenu(FMenuBuilder& NewBuilder)
{
	NewBuilder.AddMenuEntry(FExtendEditorCommands::Get().PluginAction);
}

void FExtendEditorModule::AddPathsMenu(FMenuBuilder& NewBuilder)
{
	NewBuilder.AddMenuEntry(FExtendEditorCommands::Get().PluginAction);
}

TSharedRef<FExtender> FExtendEditorModule::CurrentSelectedActors(const TSharedRef<FUICommandList> MyUICommandList, const TArray<AActor*> MyActors)
{
	TSharedRef<FExtender> Extender = MakeShareable(new FExtender);
	UE_LOG(LogTemp, Warning, TEXT("MyActors-------%s-------MyActors"), *FString::FromInt(MyActors.Num()));
	Extender->AddMenuExtension("ActorControl", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FExtendEditorModule::AddSelectActorMenu));

	return Extender;
}

TSharedRef<FExtender> FExtendEditorModule::CurrentSelectedPaths(const TArray<FString>& Pathes)
{
	TSharedRef<FExtender> Extender = MakeShareable(new FExtender);
	Extender->AddMenuExtension("NewFolder", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FExtendEditorModule::AddSelectPathsMenu));
	
	return Extender;
}

TSharedRef<FExtender> FExtendEditorModule::CurrentSelectedAssets(const TArray<FAssetData>& Assets)
{
	TSharedRef<FExtender> Extender = MakeShareable(new FExtender);
	UE_LOG(LogTemp, Warning, TEXT("Assets-------%s-------Assets"), *FString::FromInt(Assets.Num()));
	Extender->AddMenuExtension("Rename", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FExtendEditorModule::AddSelectAssetsMenu));

	return Extender;
}

TSharedRef<FExtender> FExtendEditorModule::CurrentPaths(const TArray<FString>& Pathes)
{
	TSharedRef<FExtender> Extender = MakeShareable(new FExtender);
	Extender->AddMenuExtension("NewFolder", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FExtendEditorModule::AddPathsMenu));

	return Extender;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FExtendEditorModule, ExtendEditor)