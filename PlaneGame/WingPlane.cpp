#include "StdAfx.h"
#include "Ball.h"
#include "WingPlane.h"
#include "Bomb.h"
#include "Explosion.h"
#include "resource.h"

CImageList CWingPlane::m_Images;
int CWingPlane::sumNum = 0;

CWingPlane::CWingPlane(int t):tag(t)
{
	//随机确定X位置
	m_ptPos.x = rand() % (GAME_WIDTH - BOSS1_HEIGHT) + 1;

	//随机确定图像索引
	// m_nImgIndex = rand()%2;

	//根据图像索引确定方向
	m_nMotion = 1;
	m_ptPos.y = -BOSS1_HEIGHT;

	// 取消从画面下面飞出敌机
	//if (m_nImgIndex%2!=0)//如果是图像索引是偶数
	//{
	//	m_nMotion=-1;
	//	m_ptPos.y = GAME_HEIGHT+ENEMY_HEIGHT;
	//}
	//随机确定速度
	m_V = rand() % 6 + 2;
	++sumNum;
	m_nWait = 0;
}

CWingPlane::~CWingPlane(void)
{
	--sumNum;
}

BOOL CWingPlane::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_BITMAP9, RGB(0, 0, 0), 66, 60, 1);
}

BOOL CWingPlane::Draw(CPoint position, CDC* pDC, BOOL bPause)
{
	m_nWait++;

	// 绘制战机血条
	CPoint point0 = GetPoint();
	CPen p0(PS_SOLID, 2, RGB(255, 0, 0));
	pDC->SelectObject(&p0);
	CBrush b0(RGB(255, 0, 0));
	pDC->SelectObject(&b0);
	pDC->Rectangle(point0.x + 13, point0.y + 63, point0.x + (blood * 5)+3, point0.y + 65);
	if (m_nWait > 5)
		m_nWait = 0;

	if (!bPause)
	{
		if (m_V <= 3) {
			m_V = 4;
		}
		m_ptPos.y = position.y + 30;
		if (tag == -1){
			m_ptPos.x = position.x - 75;
		}
		else {
			m_ptPos.x = position.x + 20 + 87;
		}
	}

	m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}

BOOL CWingPlane::Draw(int position, CDC* pDC, BOOL bPause) {
	return TRUE;
}

BOOL CWingPlane::Fired()
{
	if (m_nWait < 40 && m_nWait % 6 == 0)
		return TRUE;
	else
		return FALSE;
}


bool CWingPlane::shooting(CMyPlane* m_pMe, CObList* m_ObjList, int enBoss1, int enBall)
{
	// TODO: 在此处添加实现代码.
	CPoint PlanePt = m_pMe->GetPoint();
	for (POSITION ePos = m_ObjList[enBoss1].GetHeadPosition(); ePos != NULL;)
	{
		CWingPlane* pEnemy = (CWingPlane*)m_ObjList[enBoss1].GetNext(ePos);
		if (!pEnemy->Fired())
			continue;
		else {
			CPoint  ePt = pEnemy->GetPoint();

			//敌机在战机前面
			/*if (pEnemy->GetMontion() < 5)
				by = TRUE;*/
				//敌机在战机后面
				/*if(pEnemy->GetMontion()==-1 && ePt.y>PlanePt.y)
						by=  TRUE;*/

			m_ObjList[enBall].AddTail(new CBomb(ePt.x + 25, ePt.y - 1));
		}
	}
	return TRUE;
}


bool CWingPlane::beShootDown(CObList* m_ObjList, int enBomb, int enEnemy, int enExplosion)
{
	//战机导弹炸掉敌机
	POSITION mPos1 = NULL, mPos2 = NULL;
	for (mPos1 = m_ObjList[enBomb].GetHeadPosition(); (mPos2 = mPos1) != NULL;)
	{
		CBomb* pBomb = (CBomb*)m_ObjList[enBomb].GetNext(mPos1);
		CRect bRect = pBomb->GetRect();

		POSITION ePos1 = NULL, ePos2 = NULL;
		for (ePos1 = m_ObjList[enEnemy].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
		{
			CWingPlane* pEnemy = (CWingPlane*)m_ObjList[enEnemy].GetNext(ePos1);
			CRect mRect = pEnemy->GetRect();
			CRect tmpRect;
			if (tmpRect.IntersectRect(&bRect, mRect))
			{
				//添加爆炸效果
				m_ObjList[enExplosion].AddTail(
					new CExplosion(mRect.left, mRect.top)
				);
				if (pEnemy->beInjured(pBomb->damage)) {
					//删除导弹
					m_ObjList[enBomb].RemoveAt(mPos2);
					delete pBomb;

					if (pEnemy->blood <= 0) {
						//删除敌机
						m_ObjList[enEnemy].RemoveAt(ePos2);
						delete pEnemy;
						break;
					}
				}
			}
		}
	}
	if (sumNum <= 0) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

bool CWingPlane::beInjured(int i)
{
	// TODO: 在此处添加实现代码.
	--blood;
	return TRUE;
}
