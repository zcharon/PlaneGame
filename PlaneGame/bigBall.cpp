#include "stdafx.h"
#include "bigBall.h"
#include "resource.h"

CImageList bigBall::m_Images;


bigBall::bigBall(int x, int y, int t) :CGameObject(x, y), tag(t)
{

}

bigBall::~bigBall(void)
{
}
BOOL bigBall::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_BITMAP4, RGB(0, 0, 0), 25, 40, 1);
}
BOOL bigBall::Draw(int position, CDC* pDC, BOOL bPause)
{
	if (!bPause)
	{
		// 规定战机导弹三种飞行轨迹
		if (tag == 0) {
			m_ptPos.y = m_ptPos.y - 8;
		}
		else if (tag == -1) {
			m_ptPos.y = m_ptPos.y - 8;
			m_ptPos.x = m_ptPos.x - 3;
		}
		else if (tag == 1) {
			m_ptPos.y = m_ptPos.y - 8;
			m_ptPos.x = m_ptPos.x + 3;
		}
	}

	if (m_ptPos.y < -BOMB_HEIGHT)
		return FALSE;

	m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}