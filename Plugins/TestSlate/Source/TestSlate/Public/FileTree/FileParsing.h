#pragma once

#include "CoreMinimal.h"

namespace NameTestSlate
{
	enum class EFileType : uint8
	{
		FILE,
		FOLDER
	};

	struct FFileList
	{
		FString Filename;
		TArray<FFileList> Children;

		FORCEINLINE friend bool operator==(const FFileList& A, const FFileList& B) 
		{
			return A.Filename == B.Filename;
		}

		EFileType GetFileType()const;

	};

	void FilesParsing(const TArray<FString>& Filenames, FFileList& List);
}