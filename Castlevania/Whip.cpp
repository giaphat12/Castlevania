﻿#include "Whip.h"
#include "Torch.h"
#include "ItemFactory.h"
#include "PlayScene.h"
#include "EffectFactory.h"

void Whip::Render()
{
	int ani;
	switch (state)
	{			
	case NORMAL:
		ani = WHIP_ANI_NORMAL;
		break;
	case CHAIN:
		ani = WHIP_ANI_CHAIN;
		break;
	case MORINGSTAR:
		ani = WHIP_ANI_MORNINGSTAR;
		break;
	}
	animations[ani]->Render(nx, x, y);
	//RenderBoundingBox();// vẽ bbox
}

void Whip::Upgrade()
{
	switch (state) {
	case NORMAL:
		state = CHAIN;
		break;
	case CHAIN:
		state = MORINGSTAR;
		break;
	case MORINGSTAR:
		break;
	default:
		break;
	}
}

void Whip::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	
	if (nx < 0)
	{
		l = x + 50;
		t = y;
		if (state == MORINGSTAR) {
			l = x + 20;
			r = l + WHIP_BBOX_NORMAL_WIDTH + 30;
		}
		else {
			r = l + WHIP_BBOX_NORMAL_WIDTH;
		}
		b = y + WHIP_BBOX_NORMAL_HEIGHT;
		
	}
	else if(nx > 0)
	{
		
		l = x + 150;
		t = y;	
		if (state == MORINGSTAR) {

			r = l + WHIP_BBOX_NORMAL_WIDTH + 30;
		}
		else {
			r = l + WHIP_BBOX_NORMAL_WIDTH;
		}
		b = y + WHIP_BBOX_NORMAL_HEIGHT;
	}
	

}

void Whip::Update(DWORD dt,Scene* scene, vector<LPGAMEOBJECT>* colliable_objects)
{
	switch (state)
	{
	case NORMAL:
		if (animations[WHIP_ANI_NORMAL]->GetCurrentFrame() < 2)
		{
			return;
		}
		break;
	case CHAIN:
		if (animations[WHIP_ANI_CHAIN]->GetCurrentFrame() < 2)
		{
			return;
		}
		break;
	case MORINGSTAR:
		if (animations[WHIP_ANI_MORNINGSTAR]->GetCurrentFrame() < 8)
		{
			return;
		}
		break;
	default:
		break;
	}
	
	for (size_t i = 0; i < colliable_objects->size(); i++)
	{
		if (dynamic_cast<CTorch*>(colliable_objects->at(i)))
		{
			CTorch* torch = dynamic_cast<CTorch*>(colliable_objects->at(i));
			if (this->isColliding(torch) && !torch->IsDestroyed()) // check CO
			{
				//khởi tạo item và effect
				auto item = ItemFactory::SpawnItem<Item*>(torch->GetItem());
				auto effect = EffectFactory::SpawnEffect<Effect*>(CEffect::FLAME);
				if (dynamic_cast<PlayScene*>(scene)) // check scene cur
				{
					float tx, ty;
					torch->GetPosition(tx, ty);
					PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
					item->SetPosition(tx,ty);
					effect->SetPosition(tx, ty);
					// bỏ vô hàng đợi
					pScene->SpawnObject(item);
					pScene->SpawnObject(effect);
				}
				torch->SetDestroy(); // check CO = true => destroy 
			}
		}
	}

}

void Whip::SetState(WHIPSTATE state)
{
	switch (state)
	{	
	case NORMAL:
		break;
	case CHAIN:
		break;
	case MORINGSTAR:
		break;
	default:
		break;
	}
	this->state = state;
}
