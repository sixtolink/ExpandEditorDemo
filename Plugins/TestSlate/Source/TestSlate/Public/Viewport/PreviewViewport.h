//编辑视口的样式

#pragma once

#include "CoreMinimal.h"
#include "SEditorViewport.h"

class TESTSLATE_API PreviewViewport : public SEditorViewport
{
	SLATE_BEGIN_ARGS(PreviewViewport)
	{}
	SLATE_END_ARGS()
		void Construct(const FArguments& InArgs);

	//重写实例化视口客户端接口
	virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient();

private:

	//预览场景
	TSharedPtr<class FAdvancedPreviewScene> PreviewScene;

	class USkyLightComponent* Skylight;
	class USkyAtmosphereComponent* AtmosphericFog;

	TSharedPtr<class FAssetLibararyViewportClient> EditorViewportClient;
};