﻿#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "AssetIDs.h"

#include "PlayScene.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "Coin.h"
#include "Platform.h"
#include "Pipe.h"
#include "BGCloud.h"
#include "BGBush.h"
#include "BGTree.h"
#include "CRandomBrick.h"
#include "LargeBrick.h"
#include "ShootingPlant.h"
#include "Koopas.h"
#include "VoidSpike.h"
#include "CoinBrick.h"
#include "GoombaRed.h"
#include "ScoreBoard.h"
#include "ButtonCoinBrick.h"
#include "BlackPipe.h"
#include "KoopasGreen.h"
#include "VictoryCard.h"

#include "SampleKeyEventHandler.h"

using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	player = NULL;
	key_handler = new CSampleKeyHandler(this);
}


#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	1
#define SCENE_SECTION_OBJECTS	2

#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2

#define MAX_SCENE_LINE 1024

void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPTEXTURE tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CPlayScene::_ParseSection_ASSETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 1) return;

	wstring path = ToWSTR(tokens[0]);

	LoadAssets(path.c_str());
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (unsigned int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

/*
	Parse a line in section [OBJECTS]
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) return;

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());

	CGameObject* obj = NULL;
	CGame* game = CGame::GetInstance();
	PlayerData s = game->GetSaved();

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
		if (player != NULL)
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}

		DebugOut(L"%.4f, %.4f,", s.desX, s.desY);
		if (s.desX == -1)
			obj = new CMario(x, y);
		else
			obj = new CMario(s.desX, s.desY);

		player = (CMario*)obj;

		DebugOut(L"[INFO] Player object has been created!\n");
		break;
	case OBJECT_TYPE_GOOMBA: obj = new CGoomba(x, y); break;
	case OBJECT_TYPE_BRICK: obj = new CBrick(x, y); break;
	case OBJECT_TYPE_COIN: 
	{
		int length = atoi(tokens[3].c_str());

		for (float i = 0; i < length; i++)
		{
			obj = new CCoin(x + i * 16, y);
			objects.push_back(obj);
		}

		return;
	}
	case OBJECT_TYPE_VOIDSPIKE:
	{
		int length = atoi(tokens[3].c_str());

		obj = new CVoidSpike(
			x, y, length);

		break;
	}
	case OBJECT_TYPE_SHADOW:
	{
		int z = atoi(tokens[3].c_str());
		int sprite_id = atoi(tokens[4].c_str());
		int c = atoi(tokens[5].c_str());

		obj = new Shadow(
			x, y, z, sprite_id, c);

		break;
	}
	case OBJECT_TYPE_PIPE:
	{
		int length = atoi(tokens[3].c_str());
		int pType = atoi(tokens[4].c_str());
		int pLength = atoi(tokens[5].c_str());
		float pRange = (float)atof(tokens[6].c_str());

		CPipe* pipe = new CPipe(x, y, length, pType, pLength, pRange);

		if (pType != 1)
		{
			objects.push_back(pipe->GetHead());
		}
		
		if (pType >= 2)
		{
			objects.push_back(pipe->GetSPlant()->GetHead());
			objects.push_back(pipe->GetSPlant()->GetBody());
			if (pType < 4) objects.push_back(pipe->GetSPlant());
			else objects.push_back(pipe->GetEPlant());
		}

		objects.push_back(pipe->GetBody());
		obj = pipe;

		break;
	}
	case OBJECT_TYPE_BLACKPIPE:
	{
		CBlackPipe* pipe = new CBlackPipe(x, y);

		obj = pipe;

		break;
	}
	case OBJECT_TYPE_VICTORY_CARD:
	{
		obj = new CVictoryCard(x, y);
		break;
	}
	case OBJECT_TYPE_BGTREE:
	{
		float z = (float)atof(tokens[3].c_str());
		int bodyLength = atoi(tokens[4].c_str());
		int edgeRightLength = atoi(tokens[5].c_str());
		int edgeLeftLength = atoi(tokens[6].c_str());

		BGTree* bgtree = new BGTree(x, y, bodyLength, edgeRightLength, edgeLeftLength);
		bgtree->SetZ(z);

		obj = bgtree;
		break;
	}
	case OBJECT_TYPE_COINBRICK:
	{
		int length = atoi(tokens[3].c_str());

		for (float i = 0; i < length; i++)
		{
			obj = new CoinBrick(x + i * 16, y);
			objects.push_back(obj);
		}
		
		return; //Tránh trùng con trỏ vì có một objects.push_back 
		        //khác ở dưới cùng của hàm này
	}
	case OBJECT_TYPE_BUTTON_COINBRICK:
	{
		obj = new ButtonCoinBrick(x, y);

		break;
	}
	case OBJECT_TYPE_BGCLOUD:
	{
		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());

		obj = new CBGCloud(
			x, y,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end
		);

		break;
	}
	case OBJECT_TYPE_RANDOMBRICK:
	{
		int type = atoi(tokens[3].c_str());
		obj = new CRandomBrick(x, y, type);

		break;
	}
	case OBJECT_TYPE_KOOPAS:
	{
		obj = new CKoopas(x, y); 

		break;
	}
	case OBJECT_TYPE_GREEN_KOOPAS:
	{
		int hasWing = atoi(tokens[3].c_str()); //1: yes, others: no
		obj = new CKoopasGreen(x, y, hasWing);

		break;
	}
	case OBJECT_TYPE_REDGOOMBA:
	{
		obj = new CGoombaRed(x, y);

		break;
	}
	case OBJECT_TYPE_PLATFORM:
	{
		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());

		obj = new CPlatform(
			x, y,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end
		);

		break;
	}
	case OBJECT_TYPE_LARGEBRICK: 
	{
		int bboxWidth = atoi(tokens[3].c_str());
		int bboxHeight = atoi(tokens[4].c_str());
		int spriteID = atoi(tokens[5].c_str());
		int z = atoi(tokens[6].c_str());

		obj = new CLargeBrick(
			x, y,
			bboxWidth, bboxHeight,
			spriteID, z
		);

		break;
	}
	case OBJECT_TYPE_BGBUSH:
	{
		int length = atoi(tokens[3].c_str());

		obj = new CBGBush(
			x, y,
			length
		);

		break;
	}
	case OBJECT_TYPE_SCOREBOARD:
	{
		obj = new CScoreBoard(x, y);

		break;
	}

	case OBJECT_TYPE_PORTAL:
	{
		float desX = atof(tokens[3].c_str());
		float desY = atof(tokens[4].c_str());
		int scene_id = atoi(tokens[5].c_str());

		obj = new CPortal(x, y, desX, desY, scene_id);
	}
	break;


	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	if (object_type != OBJECT_TYPE_MARIO)
		obj->SetPosition(x, y);


	objects.push_back(obj);
}

void CPlayScene::LoadAssets(LPCWSTR assetFile)
{
	DebugOut(L"[INFO] Start loading assets from : %s \n", assetFile);

	ifstream f;
	f.open(assetFile);

	int section = ASSETS_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SPRITES]") { section = ASSETS_SECTION_SPRITES; continue; };
		if (line == "[ANIMATIONS]") { section = ASSETS_SECTION_ANIMATIONS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case ASSETS_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case ASSETS_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading assets from %s\n", assetFile);
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		if (line == "[ASSETS]") { section = SCENE_SECTION_ASSETS; continue; };
		if (line == "[OBJECTS]") { section = SCENE_SECTION_OBJECTS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 
	CMario* mario = (CMario*)player;
	bool freeze = CGame::GetInstance()->IsOthersPaused();

	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		if (freeze) 
		{
			if (objects[i] == mario && (mario->GetState() != MARIO_STATE_DIE )) continue;
			if (objects[i] != mario) continue;
		}
		objects[i]->Update(dt, &coObjects);
	}

	
	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return;

	// Update camera to follow mario
	float px, py, cx, cy;
	CGame* game = CGame::GetInstance();

	player->GetPosition(px, py);
	game->GetCamPos(cx, cy);

	if (px < 10) {
		mario->SetState(MARIO_STATE_IDLE);
		mario->SetPosition(10, py);
	}
	static float lastPx = -1.0f, lastPy = -1.0f;
	static bool  camStarted = false;

	float screenW = game->GetBackBufferWidth();
	float screenH = game->GetBackBufferHeight();

	float halfW = screenW * 0.5f;
	float halfH = screenH * 0.5f;

    // Tính quãng đường Mario vừa di chuyển
	float dy = py - lastPy;

	cx = px - halfW;

	// ------------------------------------------------------------
	float MAX_MAP_X = game->GetCurrentScene()->GetMaxMapX();
	float MAX_MAP_Y = game->GetCurrentScene()->GetMaxMapY();

	DebugOutTitle(L"Mario x: %.4f, Mario y: %.4f, Cam x: %.4f", px, py, cx);
	if (px < halfW) cx = 0;
	else if (px >= MAX_MAP_X - halfW) cx = MAX_MAP_X - screenW;

	if (py <= MAX_MAP_Y * 0.8 && MAX_MAP_Y != 0) cy = MAX_MAP_Y;
	else if (MAX_MAP_Y == 0) cy = 0;
	else if (mario->GetState() == MARIO_STATE_DIE || mario->GetLevel() != 3)
		    cy = 0;

	lastPx = px;
	lastPy = py;

	if (mario->IsArrived()) cx = px - halfW;
	if ((py <= 10 || mario->IsFly()) && mario->GetLevel() == 3) cy = py - halfH;
	else cy = 0;

	if (MAX_MAP_X == 500.0) cy = 0;
	game->SetCamPos(cx, cy);
	//mario->SetArrived(false);

	PurgeDeletedObjects();
}

void CPlayScene::Render()
{
	// z lớn che z nhỏ hơn
	sort(objects.begin(), objects.end(),
		[](LPGAMEOBJECT a, LPGAMEOBJECT b) {
			return a->GetZ() < b->GetZ();
		}
	);

	for (unsigned int i = 0; i < objects.size(); i++)
	{
		objects[i]->Render();
	}
}

/*
*	Clear all objects from this scene
*/
void CPlayScene::Clear()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		delete (*it);
	}
	objects.clear();
}

/*
	Unload scene

	TODO: Beside objects, we need to clean up sprites, animations and textures as well

*/
void CPlayScene::Unload()
{
	for (unsigned int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}

bool CPlayScene::IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }

void CPlayScene::PurgeDeletedObjects()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
			delete o;
			*it = NULL;
		}
	}

	// NOTE: remove_if will swap all deleted items to the end of the vector
	// then simply trim the vector, this is much more efficient than deleting individual items
	objects.erase(
		std::remove_if(objects.begin(), objects.end(), CPlayScene::IsGameObjectDeleted),
		objects.end());
}