#pragma once

#include "CoreMinimal.h"
#include "EditorViewportClient.h"

class TESTSLATE_API FAssetLibararyViewportClient : public FEditorViewportClient , public TSharedFromThis<FAssetLibararyViewportClient>
{
public:
	FAssetLibararyViewportClient(FPreviewScene& InPreviewScene);

	virtual void Tick(float DeltaSeconds)override;
};