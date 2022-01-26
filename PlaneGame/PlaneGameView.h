// PlaneGameView.h : CPlaneGameView 类的接口
//

#pragma once
#include "BossFinal.h"
class CMyPlane;

class CPlaneGameView : public CView
{
	enum ObjType{enEnemy,enBomb,enBall,enExplosion, enBoss1, enBigBall, enBoss2, enlife, enEnemy2, enWingPlane, enBoss3, enBossFinal
	};

protected: // 仅从序列化创建
	CPlaneGameView();
	DECLARE_DYNCREATE(CPlaneGameView)

// 属性
public:
	CPlaneGameDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CPlaneGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//内存DC
	CDC*        m_pMemDC;
	//设备DC
	CClientDC*  m_pDC;
	//内存位图
	CBitmap*    m_pMemBitmap;


protected:
	//初始化游戏
	BOOL InitGame();
	//结束游戏
	void StopGame();

	//刷新游戏的帧画面
	void UpdateFrame(CDC* pMemDC);

	void AI();

	//获得键的状态1->down
	int GetKey(int nVirtKey)
	{
		return (GetKeyState(nVirtKey) & 0x8000)? 1 : 0;
	}
	
	CMyPlane*  m_pMe;
	BossFinal* bossFinal = NULL;
	
	CObList    m_ObjList[11];
	
// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	afx_msg void OnDestroy();

	// 游戏的等级
	int level = 1;
	// 当前游戏积分
	int score = 0;
	// 当前游戏模式
	int model = 0;
	// 是否重新开始
	int reStart = 0;
	//  第1关弹窗口
	int checkpoint1 = 0;
	// 第2关弹窗口
	int checkpoint2 = 0;
	// 第3关弹窗口
	int checkpoint3 = 0;
	// 第四关弹窗口
	int checkpoint4 = 0;
	// 僚机召唤次数
	int wingPlaneTimes = 2;
	// 死亡等待时间
	int wait = 0;
private:
	// 飞机飞行方向
	int update = 1;
	int position = rand() % 3 - 1;
	int tag = 0;
};

#ifndef _DEBUG  // PlaneGameView.cpp 中的调试版本
inline CPlaneGameDoc* CPlaneGameView::GetDocument() const
   { return reinterpret_cast<CPlaneGameDoc*>(m_pDocument); }
#endif

