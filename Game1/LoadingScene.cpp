#include "stdafx.h"

//공유 메모리
int loadingCount = 0;

mutex m;

void CreateScene()
{
	{
		Scene01* temp = new Scene01();
		SCENE->AddScene("Scene01", temp);

		/*m.lock();
		Sleep(1000);
		loadingCount += 2;
		m.unlock();*/
	}
}

LoadingScene::LoadingScene()
{
	bg = new ObImage(L"pepe.png");
	bg->scale = Vector2(app.GetWidth(), app.GetHeight());

	rc = new ObRect();
	rc->scale = Vector2(200.0f, 100.0f);
	rc->pivot = OFFSET_L;
	rc->isFilled = false;
	rc->SetWorldPosX(-app.GetHalfWidth());

	t1 = new thread(CreateScene);
}

LoadingScene::~LoadingScene()
{
	t1->join();
	delete t1;
}

void LoadingScene::Init()
{
}

void LoadingScene::Release()
{
}

void LoadingScene::Update()
{
	rc->scale.x = loadingCount * app.GetWidth() / 5.0f;

	if (loadingCount == 5)
	{
		SCENE->ChangeScene("Scene01");
	}

	bg->Update();
	rc->Update();
}

void LoadingScene::LateUpdate()
{
}

void LoadingScene::Render()
{
	bg->Render();
	rc->Render();
}

void LoadingScene::ResizeScreen()
{
}
