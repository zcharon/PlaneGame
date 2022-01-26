#pragma once
#include "stdafx.h"
#include "gameobject.h"
#include "MyPlane.h"

class CEnemy2 :public CGameObject
{
public:
	CEnemy2(void);
	~CEnemy2(void);

	BOOL Draw(int, CDC* pDC, BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + ENEMY_HEIGHT, m_ptPos.y + ENEMY_HEIGHT));
	}

	int GetMontion() const
	{
		return m_nMotion;
	}
	//是否可以开火发射子弹
	BOOL Fired();
private:
	static const int ENEMY_HEIGHT = 35;
	static CImageList m_Images;
	int m_nMotion;//方向 1->向下 0->停止 
	//图像索引
	// int m_nImgIndex;
	//速度
	int m_V;
	int m_nWait;//发射延时
	int blood = 5;
	// 被击中减血
	bool beInjured(int);
public:
	// 射击
	static bool shooting(CMyPlane*, CObList*, int, int);
	static bool beShootDown(CObList*, int, int, int);
};
