#include "PlayScene.h"
#include "GameObject.h"

PlayScene::PlayScene()
{
}

PlayScene::~PlayScene()
{
}

void PlayScene::Initialize()
{
	
	GameObject* obj = new GameObject();
	obj->SetPosition(rand() % 800, rand() % 900);
	AddGameObject(obj);

}

void PlayScene::Update()
{
	Scene::Update();
	
}

void PlayScene::LateUpdate()
{
	Scene::LateUpdate();
}

void PlayScene::Render(HDC hdc)
{
	Scene::Render(hdc);
}