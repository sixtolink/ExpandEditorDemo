// Copyright Epic Games, Inc. All Rights Reserved.

#include "ExtendEditorCommands.h"

#define LOCTEXT_NAMESPACE "FExtendEditorModule"

void FExtendEditorCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "ExtendEditor", "Execute ExtendEditor action", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(CreateSubMenuAction, "ExtendEditor", "Execute ExtendEditor action", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(SubMenuAction, "ExtendEditor", "Execute ExtendEditor action", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
