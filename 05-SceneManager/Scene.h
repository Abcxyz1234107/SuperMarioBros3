#pragma once

#include "KeyEventHandler.h"
#include "Collision.h"
#include <d3dx9.h>

/*
*  Abstract class for a game scene
*/
class CScene
{
protected:
	D3DXCOLOR backgroundColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	LPKEYEVENTHANDLER key_handler;
	int id;
	LPCWSTR sceneFilePath;

	float max_map_x;
	float max_map_y;

public: 
	CScene(int id, LPCWSTR filePath);

	LPKEYEVENTHANDLER GetKeyEventHandler() { return key_handler; }
	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0; 

	void SetBackgroundColor(const D3DXCOLOR& c);
	D3DXCOLOR GetBackgroundColor() const;

	void SetMaxMapX(float x) { max_map_x = x; }
	void SetMaxMapY(float y) { max_map_y = y; }

	float GetMaxMapX() { return max_map_x; }
	float GetMaxMapY() { return max_map_y; }
};
typedef CScene * LPSCENE;


class CSceneKeyHandler : public CKeyEventHandler
{
protected: 
	CScene * scence; 

public:
	virtual void KeyState(BYTE *states) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;
	CSceneKeyHandler(LPSCENE s) :CKeyEventHandler() { scence = s; }
};

typedef CSceneKeyHandler* LPSCENEKEYHANDLER;