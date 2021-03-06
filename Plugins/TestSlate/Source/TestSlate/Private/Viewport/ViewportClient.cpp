#include "Viewport/ViewportClient.h"
#include "AssetEditorModeManager.h"

FAssetLibararyViewportClient::FAssetLibararyViewportClient(FPreviewScene& InPreviewScene)
	:FEditorViewportClient(nullptr,&InPreviewScene)
{
	((FAssetEditorModeManager*)ModeTools)->SetPreviewScene(PreviewScene);

	DrawHelper.bDrawPivot = false;
	DrawHelper.bDrawWorldBox = false;
	DrawHelper.bDrawKillZ = false;
	DrawHelper.bDrawGrid = true;
	DrawHelper.GridColorAxis = FColor(70, 70, 70);
	DrawHelper.GridColorMajor = FColor(40, 40, 40);
	DrawHelper.GridColorMinor = FColor(20, 20, 20);
	DrawHelper.PerspectiveGridSize = HALF_WORLD_MAX1;

	DrawHelper.bDrawPivot = true;

	SetRealtime(true);

	SetViewMode(VMI_Lit);
	SetViewLocation(FVector(500, 300, 500));
}

void FAssetLibararyViewportClient::Tick(float DeltaSeconds)
{
	FEditorViewportClient::Tick(DeltaSeconds);

	PreviewScene->GetWorld()->Tick(LEVELTICK_All, DeltaSeconds);
}