#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"

DECLARE_DELEGATE_OneParam(FAssetLibraryDelegate,const TArray<FString>&)

//extern ȫ�ַ���
extern UStaticMeshComponent* GMeshComponent;
extern FAssetLibraryDelegate AssetLibraryDelegate;