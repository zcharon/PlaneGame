#include "StdAfx.h"
#include "MyPlane.h"
#include "Ball.h"
#include "Explosion.h"
#include "life.h"
#include "resource.h"

CImageList CMyPlane::m_Images;

CMyPlane::~CMyPlane(void)
{
}
CMyPlane::CMyPlane(void):m_nHorMotion(0),m_nVerMotion(0)
{
	m_nWait = 0;
	m_ptPos.x = 150;
	m_ptPos.y = 200;
}

BOOL CMyPlane::Fired()
{
	if(m_nWait==0)
		return TRUE;
	else
		return FALSE;

}

BOOL CMyPlane::LoadImage()
{
	return CGameObject::LoadImage(m_Images,IDB_BITMAP3,RGB(0,0,0),87,118,1);
}

bool CMyPlane::Draw(int position, CDC* pDC, BOOL bPause, int level) {
	m_nWait++;
	if (m_nWait > 5)
		m_nWait = 0;

	// 绘制战机血条
	CPoint point0 = GetPoint();
	CPen p0(PS_SOLID, 2, RGB(255, 0, 0));
	pDC->SelectObject(&p0);
	CBrush b0(RGB(255, 0, 0));
	pDC->SelectObject(&b0);
	if (level == 1 && blood >= 0) {
		pDC->Rectangle(point0.x + 20, point0.y + 137, point0.x + (blood * 10) + 20, point0.y + 139);
	}
	else if (level == 2 && blood >= 0) {
		pDC->Rectangle(point0.x + 20, point0.y + 137, point0.x + (blood * 5) + 20, point0.y + 139);
	}
	else if (level == 3 && blood >= 0) {
		pDC->Rectangle(point0.x + 20, point0.y + 137, point0.x + (blood * 4) + 10, point0.y + 139);
	}
	else if (level == 4 && blood >= 0) {
		pDC->Rectangle(point0.x + 20, point0.y + 137, point0.x + (blood * 3) + 10, point0.y + 139);
	}

	//// 绘制战机蓝条

	CPoint point1 = GetPoint();
	CPen p1(PS_SOLID, 2, RGB(0, 0, 255));
	pDC->SelectObject(&p1);
	CBrush b1(RGB(0, 0, 255));
	pDC->SelectObject(&b1);
	pDC->Rectangle(point1.x + 20, point1.y + 130, point1.x + (bigBomb / 20) + 20, point1.y + 132);

	if (!bPause)
	{
		m_ptPos.x = m_ptPos.x + m_nHorMotion * 6;
		m_ptPos.y = m_ptPos.y - m_nVerMotion * 6;
	}

	if (m_ptPos.x >= GAME_WIDTH - PLANE_WIDTH)
		m_ptPos.x = GAME_WIDTH - PLANE_WIDTH;
	if (m_ptPos.x <= 0)
		m_ptPos.x = 0;

	if (m_ptPos.y <= 0)
		m_ptPos.y = 0;

	if (m_ptPos.y >= GAME_HEIGHT - PLANE_HEIGHT)
		m_ptPos.y = GAME_HEIGHT - PLANE_HEIGHT;


	m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);
	return TRUE;
}

BOOL CMyPlane::Draw(int position, CDC* pDC,BOOL bPause)
{
	return TRUE;
}

bool CMyPlane::beShootDown(CObList* m_ObjList, int enBall, int enExplosion, int model)
{
	// TODO: 在此处添加实现代码.
	//敌机子弹炸掉战机
	POSITION bPos1 = NULL, bPos2 = NULL;
	CRect mRect = GetRect();
	for (bPos1 = m_ObjList[enBall].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
	{
		CBall* pBall = (CBall*)m_ObjList[enBall].GetNext(bPos1);
		CRect bRect = pBall->GetRect();
		CRect tmpRect;
		if (tmpRect.IntersectRect(&bRect, mRect))
		{
			if (blood > 0) {
				if (model == 0) {
					--blood;
				}
				//添加爆炸效果
				m_ObjList[enExplosion].AddTail(
					new CExplosion(mRect.left, mRect.top)
				);

				//删除子弹
				m_ObjList[enBall].RemoveAt(bPos2);
				delete pBall;
				return FALSE;
			}
			else
			{
				// 被击落
				return TRUE;
			}
		}
	}
}


bool CMyPlane::addBlood(CObList* m_ObjList, int enlife)
{
	//加血
	POSITION bPos13 = NULL, bPos23 = NULL;
	CRect mRect = GetRect();
	for (bPos13 = m_ObjList[enlife].GetHeadPosition(); (bPos23 = bPos13) != NULL;)
	{
		life* plife = (life*)m_ObjList[enlife].GetNext(bPos13);
		CRect bRect = plife->GetRect();
		CRect tmpRect;
		if (tmpRect.IntersectRect(&bRect, mRect))
		{
			m_ObjList[enlife].RemoveAt(bPos23);
			delete plife;
			if (blood < 9)
			{
				blood += 2;
			}
			else if (blood == 9) {
				blood++;
			}
		
		}
	}
	return TRUE;
}
