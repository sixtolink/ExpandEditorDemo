//�༭�ӿڵ���ʽ

#pragma once

#include "CoreMinimal.h"
#include "SEditorViewport.h"

class TESTSLATE_API PreviewViewport : public SEditorViewport
{
	SLATE_BEGIN_ARGS(PreviewViewport)
	{}
	SLATE_END_ARGS()
		void Construct(const FArguments& InArgs);

	//��дʵ�����ӿڿͻ��˽ӿ�
	virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient();

private:

	//Ԥ������
	TSharedPtr<class FAdvancedPreviewScene> PreviewScene;

	class USkyLightComponent* Skylight;
	class USkyAtmosphereComponent* AtmosphericFog;

	TSharedPtr<class FAssetLibararyViewportClient> EditorViewportClient;
};