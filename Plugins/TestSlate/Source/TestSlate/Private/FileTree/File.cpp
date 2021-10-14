#include "FileTree/File.h"
#include "ViewType.h"

#define LOCTEXT_NAMESPACE "File"

void SFile::Construct(const FArguments& InArgs, const NameTestSlate::FFileList& InFileList)
{
	AssetPaths = InFileList.Filename;
	FString AssetName = FPackageName::GetShortName(InFileList.Filename);
	ChildSlot[
		SNew(SButton)
		.Text(FText::Format(LOCTEXT("AnalyzingFilename","{0}"),FText::FromString(FPackageName::GetShortName(AssetName))))
		.HAlign(HAlign_Fill)
		.OnClicked(this,&SFile::OnClicked)
		.ButtonStyle(FCoreStyle::Get(),"NoBorder")
		.TextStyle(FEditorStyle::Get(),"FlatButton.DefaultTextStyle")
	];
}

FReply SFile::OnClicked()
{
	if (!AssetPaths.IsEmpty())
	{
		UStaticMesh* loadStaticMesh = StaticLoadObjectFromPath(AssetPaths);
		if (loadStaticMesh)
		{
			GMeshComponent->SetStaticMesh(loadStaticMesh);
		}
	}
	return FReply::Handled();
}


#undef LOCTEXT_NAMESPACE