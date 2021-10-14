#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"

DECLARE_DELEGATE_OneParam(FAssetLibraryDelegate,const TArray<FString>&)

//extern È«¾Ö·ÃÎÊ
extern UStaticMeshComponent* GMeshComponent;
extern FAssetLibraryDelegate AssetLibraryDelegate;