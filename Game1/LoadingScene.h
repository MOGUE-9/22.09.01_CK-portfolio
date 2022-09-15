#pragma once

class LoadingScene : public Scene
{
public:
	ObImage* logo;
	ObImage* bg;
	ObRect* rc;
	thread* t1;

public:
	LoadingScene();
	~LoadingScene();

	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void ResizeScreen() override;
};

