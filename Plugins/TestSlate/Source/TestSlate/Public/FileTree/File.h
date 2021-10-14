#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "FileParsing.h"

class SFile :public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SFile)
	{}
	SLATE_END_ARGS()
		void Construct(const FArguments& InArgs, const NameTestSlate::FFileList& InFileList);

	FReply OnClicked();

	UStaticMesh* StaticLoadObjectFromPath(const FString& Filename)
	{
		auto Point = Filename;
		auto Pos = Point.Find(".");
		auto NewPoint = Point.Left(Pos);
		const FString ObjectName = UStaticMesh::StaticClass()->GetName() + TEXT("'/") + NewPoint + TEXT(".") + FPackageName::GetShortName(NewPoint) + TEXT("'");
		UStaticMesh* ObjectInstance = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, *ObjectName));
		return ObjectInstance;
	}

private:
	FString AssetPaths;
};