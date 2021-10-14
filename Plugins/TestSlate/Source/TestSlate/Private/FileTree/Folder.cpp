#include "FileTree/Folder.h"
#include "FileTree/File.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Layout/SExpandableArea.h"
#include "Widgets/Layout/SSpacer.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Text/STextBlock.h"
#include "EditorStyleSet.h"

#define LOCTEXT_NAMESPACE "Folder"

void SFolder::Construct(const FArguments& InArgs, const NameTestSlate::FFileList& InFileList)
{
	TSharedPtr<SVerticalBox> FileArray = SNew(SVerticalBox);
	for (const auto &Tmp : InFileList.Children)
	{
		if (Tmp.GetFileType()== NameTestSlate::EFileType::FOLDER)
		{
			FileArray->AddSlot()
			.AutoHeight()
			[
				SNew(SFolder, Tmp)
			];
		}
		else
		{
			FileArray->AddSlot()
			.AutoHeight()
			[
				SNew(SFile, Tmp)
			];
		}
	}

	ChildSlot
		[
			SAssignNew(Area, SExpandableArea)
			.BorderBackgroundColor(FLinearColor::Transparent)
			.InitiallyCollapsed(false)
			.Padding(FMargin(0.0f,1.0f,0.0f,8.0f))
			.HeaderContent()
			[
				SNew(SHorizontalBox)
				+SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SImage)
					.Image(this,&SFolder::GetFileTypeICO)
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(STextBlock)
					.Text(FText::Format(LOCTEXT("AnalyzingFilename","{0}"),FText::FromString(InFileList.Filename)))
				]
			]
			.BodyContent()
			[
				SNew(SHorizontalBox)
				+SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SSpacer)
					.Size(FVector2D(20.f,1.f))
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					FileArray.ToSharedRef()
				]
			]
		];
}

const FSlateBrush* SFolder::GetFileTypeICO() const
{
	return Area->IsExpanded() ? FEditorStyle::Get().GetBrush(TEXT("SceneOutliner.FolderClosed")) : FEditorStyle::Get().GetBrush(TEXT("SceneOutliner.FolderOpen"));
}

#undef LOCTEXT_NAMESPACE