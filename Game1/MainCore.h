#pragma once
class MainCore
{
	ObImage* coreImg = new ObImage(L"coreImg.png");
	ObImage* slimeImg = new ObImage(L"slimeImg.png");
	ObImage* hiveImg = new ObImage(L"hiveImg.png");
	ObImage* larvaImg = new ObImage(L"larvaImg.png");


public:
	MainCore();
	~MainCore();

	void Update();
	void Render();
};

