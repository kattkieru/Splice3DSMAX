#pragma once
#include "mouseman.h"

class FabricMouseCallback :
	public MouseCallBack
{
private:
	//bool m_dragging;
	static FabricCore::RTVal mEventDispatcher;

	// Cache previous mouse state, 
	bool m_LMouseDown;
	bool m_MMouseDown;
	bool m_RMouseDown;

	// Keyboard hook
	HHOOK m_kbHookHandle;

public:
	FabricMouseCallback(void);
	~FabricMouseCallback(void);

	virtual int override( int mode );

	virtual BOOL SupportTransformGizmo();

	virtual void DeactivateTransformGizmo();

	virtual BOOL SupportAutoGrid();

	virtual BOOL TolerateOrthoMode();

	virtual int proc( HWND hwnd, int msg, int point, int flags, IPoint2 m );

	void EnterMode();
	void ExitMode();

	static FabricCore::RTVal& GetEventDispatcher() { return mEventDispatcher; };
};

