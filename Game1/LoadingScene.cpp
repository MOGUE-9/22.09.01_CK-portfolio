#include "stdafx.h"

//공유 메모리
int loadingCount = 0;

mutex m;

void CreateScene()
{
	{
		Scene01* temp = new Scene01();
		SCENE->AddScene("Scene01", temp);

		//m.lock();
		//Sleep(1000);
		//loadingCount += 2;
		//m.unlock();
	}
}

LoadingScene::LoadingScene()
{
	LIGHT->light.radius = 2000.0f;

	logo = new ObImage(L"TitleText.png");
	logo->scale = Vector2(238.0f, 103.0f) * 1.5f;
	logo->SetWorldPosX(-app.GetHalfWidth() * 0.5f);

	bg = new ObImage(L"Title.png");
	bg->maxFrame.x = 4;
	bg->scale = Vector2(app.GetWidth(), app.GetHeight());
	bg->ChangeAnim(ANIMSTATE::LOOP, 0.15f);

	rc = new ObRect();
	rc->scale = Vector2(200.0f, 100.0f);
	rc->pivot = OFFSET_L;
	rc->isFilled = false;
	rc->SetWorldPosX(-app.GetHalfWidth());

	SOUND->AddSound("Loading.mp3", "loading", false);

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
	//rc->scale.x = loadingCount * app.GetWidth() / 5.0f;

	//col->MoveWorldPos(moveDir * 500.0f *
	//	cosf(rollTime / 0.6f * DIV2PI) * DELTA);

	logo->color.A(sinf(loadingCount / 5.0f * DIV4PI));

	SOUND->Play("loading");

	if (loadingCount == 5)
	{
		SCENE->ChangeScene("Scene01");
	}

	logo->Update();
	bg->Update();
	rc->Update();
}

void LoadingScene::LateUpdate()
{
}

void LoadingScene::Render()
{
	bg->Render();
	logo->Render();

	//rc->Render();
}

void LoadingScene::ResizeScreen()
{
}
