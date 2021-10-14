#include "FileTree/FileParsing.h"

NameTestSlate::EFileType NameTestSlate::FFileList::GetFileType() const
{
	return Filename.Contains(TEXT(".")) ? EFileType::FILE : EFileType::FOLDER;
}

void NameTestSlate::FilesParsing(const TArray<FString>& Filenames, FFileList& List)
{
	//Filename = G:/asda/afafa/adad/a.uasset

	FFileList* FileList = &List;
	FileList->Filename = FApp::GetProjectName();
	for (const auto&Filename:Filenames)
	{
		auto Point = Filename;
		auto Pos = Point.Find("Content/");
		auto NewPoint = Point.RightChop(Pos);
		NewPoint.ReplaceInline(TEXT("Content/"), TEXT("Game/"));

		TArray<FString> FileLevle;
		NewPoint.ParseIntoArray(FileLevle, TEXT("/"));

		FileList = &List;
		for (const auto&TmpFile:FileLevle)
		{
			FFileList FileListElement;
			FileListElement.Filename = TmpFile;

			int32 i = FileList->Children.AddUnique(FileListElement);
			FileList = &(FileList->Children[i]);
		}
		FileList->Filename = NewPoint;
	}
}
