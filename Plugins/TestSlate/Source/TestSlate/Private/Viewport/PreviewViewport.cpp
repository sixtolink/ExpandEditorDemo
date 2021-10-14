#include "Viewport/PreviewViewport.h"
#include "Viewport/ViewportClient.h"
#include "Components/SkyLightComponent.h"
#include "Components/DirectionalLightComponent.h"
#include "Components/SkyAtmosphereComponent.h"
#include "EditorViewportClient.h"
#include "AdvancedPreviewScene.h"
#include "ViewType.h"

void PreviewViewport::Construct(const FArguments& InArgs)
{
	{
		FAdvancedPreviewScene::ConstructionValues ViewConstructionValues;
		ViewConstructionValues.bCreatePhysicsScene = false;
		ViewConstructionValues.LightBrightness = 3;
		ViewConstructionValues.SkyBrightness = 1;

		PreviewScene = MakeShareable(new FAdvancedPreviewScene(ViewConstructionValues));
		PreviewScene->SetFloorVisibility(false);
		PreviewScene->SetFloorOffset(-100000);
	}
	
	Skylight = NewObject<USkyLightComponent>();
	PreviewScene->AddComponent(Skylight, FTransform::Identity);

	AtmosphericFog = NewObject<USkyAtmosphereComponent>();
	PreviewScene->AddComponent(AtmosphericFog, FTransform::Identity);

	PreviewScene->DirectionalLight->SetMobility(EComponentMobility::Movable);
	PreviewScene->DirectionalLight->CastShadows = true;
	PreviewScene->DirectionalLight->CastStaticShadows = true;
	PreviewScene->DirectionalLight->CastDynamicShadows = true;
	PreviewScene->DirectionalLight->SetIntensity(3);

	//添加展示模型
	if (GMeshComponent)
	{
		GMeshComponent->SetRelativeScale3D(FVector(3.f, 3.f, 1.f));
		GMeshComponent->SetVisibility(true);
		PreviewScene->AddComponent(GMeshComponent, FTransform::Identity);
	}

	//执行默认构造
	SEditorViewport::Construct(SEditorViewport::FArguments());
}

TSharedRef<FEditorViewportClient> PreviewViewport::MakeEditorViewportClient()
{
	EditorViewportClient = MakeShareable(new FAssetLibararyViewportClient(*PreviewScene));
	EditorViewportClient->SetRealtime(true);

	return EditorViewportClient.ToSharedRef();
}
