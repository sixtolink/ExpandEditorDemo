#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "FileParsing.h"

class SFolder :public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SFolder)
	{}
	SLATE_END_ARGS()
		void Construct(const FArguments& InArgs, const NameTestSlate::FFileList& InFileList);
	const FSlateBrush* GetFileTypeICO() const;

private:
	TSharedPtr<class SExpandableArea> Area;
};