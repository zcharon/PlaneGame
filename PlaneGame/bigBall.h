#pragma once
#include "stdafx.h"
#include "gameobject.h"

class bigBall :
	public CGameObject
{
public:
	bigBall(int x, int y, int t);
	~bigBall(void);

	BOOL Draw(int, CDC* pDC, BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + 10, m_ptPos.y + BOMB_HEIGHT));
	}
private:
	static const int BOMB_HEIGHT = 20;
	static CImageList m_Images;

public:
	// »ðÑæµ¯µÄ·ÉÐÐ¹ì¼£
	int tag;
	// ¹¥»÷Á¦
	int damage = 3;
};
