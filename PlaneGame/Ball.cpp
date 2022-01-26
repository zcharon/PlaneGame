#include "StdAfx.h"
#include "Ball.h"
#include "resource.h"

CImageList CBall::m_Images;

CBall::CBall(int x,int y,int nMontion, int t):CGameObject(x,y),m_nMotion(nMontion), tag(t)
{
}

CBall::~CBall(void)
{
}

BOOL CBall::Draw(int position, CDC* pDC,BOOL bPause)
{
	if (tag % 2 != 0) {
		if (m_ptPos.x <= 0 || (m_ptPos.x + 23 > GAME_WIDTH))
			pos = -pos;
	}

	if (!bPause) {
		if (tag == 0) {
			m_ptPos.y = m_ptPos.y + m_nMotion * 8;
		}
		else if (tag == -1 || tag == -2) {
			m_ptPos.y = m_ptPos.y + m_nMotion * 8;
			m_ptPos.x = m_ptPos.x + m_nMotion * 4 * pos;
		}
		else if (tag == 1 || tag == 2) {
			m_ptPos.y = m_ptPos.y + m_nMotion * 8;
			m_ptPos.x = m_ptPos.x - m_nMotion * 4 * pos;
		}
		else if (tag == 3 || tag == 4) {
			m_ptPos.y = m_ptPos.y + m_nMotion * 8;
			m_ptPos.x = m_ptPos.x - m_nMotion * 16 * pos;
		}
		else if (tag == -3 || tag == -4) {
			m_ptPos.y = m_ptPos.y + m_nMotion * 8;
			m_ptPos.x = m_ptPos.x + m_nMotion * 16 * pos;
		}
	}

	if(m_ptPos.y > GAME_HEIGHT+BALL_HEIGHT )
		return FALSE;
	if(m_ptPos.y < -BALL_HEIGHT)
		return FALSE;

	m_Images.Draw(pDC,0,m_ptPos,ILD_TRANSPARENT);

	return TRUE;
}

BOOL CBall::LoadImage()
{
	return CGameObject::LoadImage(m_Images,IDB_BALL,RGB(0,0,0),8,8,1);
}