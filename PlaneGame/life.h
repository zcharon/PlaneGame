#pragma once
#include "stdafx.h"
#include "GameObject.h"

class life :
	public CGameObject
{
public:
	life();
	~life();

	BOOL Draw(int, CDC* pDC, BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + _HEIGHT, m_ptPos.y + _HEIGHT));
	}

	int GetMontion() const
	{
		return m_nMotion;
	}
private:
	static const int _HEIGHT = 35;
	static CImageList m_Images;
	int    m_nMotion;//方向 1->向下 0->停止 -1->向上
	//图像索引
	int m_nImgIndex;
	//速度
	int m_V;
	int    m_nWait;//发射延时


};

