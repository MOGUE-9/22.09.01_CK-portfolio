#include "stdafx.h"

MainCore::MainCore()
{
	coreImg->scale = Vector2(180.0f, 180.0f);
	coreImg->pivot = OFFSET_B;
	coreImg->SetWorldPos(Vector2(18.0f, 36.0f));

	slimeImg->scale = Vector2(108.0f, 144.0f);
	slimeImg->pivot = OFFSET_B;
	slimeImg->SetWorldPos(Vector2(18.0f, 36.0f * 8));

	hiveImg->scale = Vector2(108.0f, 144.0f);
	hiveImg->pivot = OFFSET_B;
	hiveImg->SetWorldPos(Vector2(18.0f + 36.0f * 8, 36.0f * 4));

	larvaImg->scale = Vector2(108.0f, 144.0f);
	larvaImg->pivot = OFFSET_B;
	larvaImg->SetWorldPos(Vector2(-(18.0f + 36.0f * 7), 36.0f * 4));
}

MainCore::~MainCore()
{
}

void MainCore::Update()
{
	coreImg->Update();
	slimeImg->Update();
	hiveImg->Update();
	larvaImg->Update();
}

void MainCore::Render()
{
	coreImg->Render();
	slimeImg->Render();
	hiveImg->Render();
	larvaImg->Render();
}
