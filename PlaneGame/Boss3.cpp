#include "StdAfx.h"
#include "Ball.h"
#include "Boss3.h"
#include "Bomb.h"
#include "Explosion.h"
#include "resource.h"

CImageList Boss3::m_Images;
int Boss3::sumNum = 0;

Boss3::Boss3(void)
{
	//���ȷ��Xλ��
	m_ptPos.x = rand() % (GAME_WIDTH - BOSS1_HEIGHT) + 1;

	//���ȷ��ͼ������
	// m_nImgIndex = rand()%2;

	//����ͼ������ȷ������
	m_nMotion = 1;
	m_ptPos.y = -BOSS1_HEIGHT;

	// ȡ���ӻ�������ɳ��л�
	//if (m_nImgIndex%2!=0)//�����ͼ��������ż��
	//{
	//	m_nMotion=-1;
	//	m_ptPos.y = GAME_HEIGHT+ENEMY_HEIGHT;
	//}
	//���ȷ���ٶ�
	m_V = rand() % 6 + 2;
	++sumNum;
	m_nWait = 0;
}

Boss3::~Boss3(void)
{
	--sumNum;
}

BOOL Boss3::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_BITMAP10, RGB(0, 0, 0), 170, 215, 1);
}

BOOL Boss3::Draw(int position, CDC* pDC, BOOL bPause)
{
	m_nWait++;

	// ����ս��Ѫ��
	CPoint point0 = GetPoint();
	CPen p0(PS_SOLID, 2, RGB(255, 0, 0));
	pDC->SelectObject(&p0);
	CBrush b0(RGB(255, 0, 0));
	pDC->SelectObject(&b0);
	pDC->Rectangle(point0.x + 30, point0.y - 2, point0.x + (blood * 1.3)+30, point0.y - 4);
	if (m_nWait > 90)
		m_nWait = 0;

	if (point0.x + 230 >= GAME_WIDTH && position > 0) {
		position = 0;
	}
	else if (point0.x <= 0 && position < 0) {
		position = 0;
	}

	if (!bPause)
	{
		if (m_V <= 3) {
			m_V = 4;
		}
		m_ptPos.y = m_ptPos.y + m_nMotion * m_V * 0.3;
		m_ptPos.x = m_ptPos.x + m_nMotion * m_V * position;
	}

	if (m_ptPos.y > GAME_HEIGHT + BOSS1_HEIGHT)
		return FALSE;
	if (m_ptPos.y < -BOSS1_HEIGHT)
		return FALSE;

	m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}

BOOL Boss3::Fired()
{
	if (m_nWait < 20 && m_nWait % 6 == 0)
		return TRUE;
	else
		return FALSE;
}

bool Boss3::ifOutSide()
{
	// TODO: �ڴ˴�����ʵ�ִ���.
	return m_ptPos.y + BOSS1_HEIGHT > GAME_HEIGHT;

}


bool Boss3::shooting(CMyPlane* m_pMe, CObList* m_ObjList, int enBoss1, int enBall)
{
	// TODO: �ڴ˴�����ʵ�ִ���.
	CPoint PlanePt = m_pMe->GetPoint();
	for (POSITION ePos = m_ObjList[enBoss1].GetHeadPosition(); ePos != NULL;)
	{
		Boss3* pEnemy = (Boss3*)m_ObjList[enBoss1].GetNext(ePos);
		if (!pEnemy->Fired())
			continue;
		else {
			CPoint  ePt = pEnemy->GetPoint();

			//�л���ս��ǰ��
			/*if (pEnemy->GetMontion() < 5)
				by = TRUE;*/
				//�л���ս������
				/*if(pEnemy->GetMontion()==-1 && ePt.y>PlanePt.y)
						by=  TRUE;*/

			m_ObjList[enBall].AddTail(new CBall(ePt.x + 35, ePt.y + 145, pEnemy->GetMontion(), -4));
			m_ObjList[enBall].AddTail(new CBall(ePt.x + 55, ePt.y + 155, pEnemy->GetMontion(), -2));
			m_ObjList[enBall].AddTail(new CBall(ePt.x + 75, ePt.y + 165, pEnemy->GetMontion(), 0));
			m_ObjList[enBall].AddTail(new CBall(ePt.x + 95, ePt.y + 155, pEnemy->GetMontion(), 2));
			m_ObjList[enBall].AddTail(new CBall(ePt.x + 105, ePt.y + 145, pEnemy->GetMontion(), 4));
		}
	}
	return TRUE;
}


bool Boss3::beShootDown(CObList* m_ObjList, int enBomb, int enEnemy, int enExplosion)
{
	bool tag = false;
	//ս������ը���л�
	POSITION mPos1 = NULL, mPos2 = NULL;
	for (mPos1 = m_ObjList[enBomb].GetHeadPosition(); (mPos2 = mPos1) != NULL;)
	{
		CBomb* pBomb = (CBomb*)m_ObjList[enBomb].GetNext(mPos1);
		CRect bRect = pBomb->GetRect();

		POSITION ePos1 = NULL, ePos2 = NULL;
		for (ePos1 = m_ObjList[enEnemy].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
		{
			tag = true;
			Boss3* pEnemy = (Boss3*)m_ObjList[enEnemy].GetNext(ePos1);
			CRect mRect = pEnemy->GetRect();
			CRect tmpRect;
			if (tmpRect.IntersectRect(&bRect, mRect))
			{
				//���ӱ�ըЧ��
				m_ObjList[enExplosion].AddTail(
					new CExplosion(bRect.left, bRect.top)
				);
				if (pEnemy->beInjured(pBomb->damage)) {
					//ɾ������
					m_ObjList[enBomb].RemoveAt(mPos2);
					delete pBomb;

					if (pEnemy->blood <= 0) {
						//ɾ���л�
						m_ObjList[enEnemy].RemoveAt(ePos2);
						delete pEnemy;
						break;
					}
				}
			}
		}
	}
	if (tag) {
		if (sumNum <= 0) {
				return TRUE;
		}
		else {
			return FALSE;
		}
	}
	return tag;
}

bool Boss3::beInjured(int i)
{
	// TODO: �ڴ˴�����ʵ�ִ���.
	--blood;
	return TRUE;
}