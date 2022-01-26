#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "MyPlane.h"
#include "Boss.h"

class CWingPlane :
	public CGameObject
{
public:
	CWingPlane(int);
	~CWingPlane(void);

	BOOL Draw(CPoint  ,CDC* , BOOL );
	BOOL Draw(int , CDC* , BOOL );
	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + BOSS1_HEIGHT, m_ptPos.y + BOSS1_HEIGHT));
	}


	int GetMontion() const
	{
		return m_nMotion;
	}

	//是否可以开火发射子弹
	BOOL Fired();
private:
	static const int BOSS1_HEIGHT = 159;
	static const int BOSS1_WIDTH = 87;
	static CImageList m_Images;
	int m_nMotion;//方向 1->向下 0->停止 
	//图像索引
	int m_nImgIndex;
	//速度
	int m_V;
	int m_nWait;//发射延时
	int blood = 10; 
public:
	// boss的数量
	static int sumNum;
	static bool shooting(CMyPlane*, CObList*, int, int);
	static bool beShootDown(CObList*, int, int, int);
	bool beInjured(int);
	int tag;
};

