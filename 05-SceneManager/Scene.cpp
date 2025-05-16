#include "Scene.h"

CScene::CScene(int id, LPCWSTR filePath)
{
	this->id = id;
	this->sceneFilePath = filePath;
	this->key_handler = NULL;
}

void CScene::SetBackgroundColor(const D3DXCOLOR& c)
{
	backgroundColor = c;
}

D3DXCOLOR CScene::GetBackgroundColor() const
{
	return backgroundColor;
}