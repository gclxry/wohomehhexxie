package com.burlapdragon.main.firstlevelscene;

import utility.method.Plotting;

import com.burlapdragon.common.CommonDefines;
import com.burlapdragon.main.R;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.Rect;

public class DragonManager {

	private Context m_Context = null;
	// 龙头
	private Bitmap m_bmpDragonHead = null;
	// 龙身
	private Bitmap m_bmpDragonBady = null;
	// 龙尾
	private Bitmap m_bmpDragonTail = null;
	// 一个龙Item的大小
	private int m_nCellWidth = 0;
	private int m_nCellHeight = 0;
	// 总数
	private int m_nDragonCtns = 2;
	// 整个地图在屏幕中的坐标位置
	private Rect m_mapInScreenRect = null;
	// 当前单元格运行到帧数
	private int m_nCurCellRunFrame = 0;

	// 龙头节点
	private DragonItem m_DragonHead = null;
	// 龙尾节点
	private DragonItem m_DragonTail = null;

	public DragonManager(Context context) {
		m_Context = context;
	}

	public void clearDragonManager() {
		if (m_bmpDragonHead != null) {
			m_bmpDragonHead.recycle();
			m_bmpDragonHead = null;
		}
		if (m_bmpDragonBady != null) {
			m_bmpDragonBady.recycle();
			m_bmpDragonBady = null;
		}
		if (m_bmpDragonTail != null) {
			m_bmpDragonTail.recycle();
			m_bmpDragonTail = null;
		}

		for (DragonItem freeDragon = m_DragonHead.m_nextItem; freeDragon != null;) {
			DragonItem nextFreeDragon = freeDragon.m_nextItem;
			freeDragon = null;
			freeDragon = nextFreeDragon;
		}

		m_DragonHead = null;
		m_DragonTail = null;
		m_nDragonCtns = 0;
	}

	// 设置一个item的大小
	public void initManager(int nWidth, int nHeight, Rect mapInScreenRect) {
		if (isInit())
			return;

		m_nCellWidth = nWidth;
		m_nCellHeight = nHeight;
		m_mapInScreenRect = new Rect(mapInScreenRect);

		m_bmpDragonHead = Plotting.decodeResourceBySize(
				m_Context.getResources(), R.drawable.dragon1, m_nCellWidth,
				m_nCellHeight);

		m_bmpDragonBady = Plotting.decodeResourceBySize(
				m_Context.getResources(), R.drawable.dragon2, m_nCellWidth,
				m_nCellHeight);

		m_bmpDragonTail = Plotting.decodeResourceBySize(
				m_Context.getResources(), R.drawable.dragon3, m_nCellWidth,
				m_nCellHeight);

		m_DragonHead = new DragonItem(m_bmpDragonHead, m_bmpDragonHead,
				m_bmpDragonHead, m_bmpDragonHead, m_bmpDragonHead,
				m_bmpDragonHead, m_bmpDragonHead, m_bmpDragonHead,
				m_bmpDragonHead, m_bmpDragonHead, m_bmpDragonHead,
				m_bmpDragonHead);
		m_DragonTail = new DragonItem(m_bmpDragonTail, m_bmpDragonTail,
				m_bmpDragonTail, m_bmpDragonTail, m_bmpDragonTail,
				m_bmpDragonTail, m_bmpDragonTail, m_bmpDragonTail,
				m_bmpDragonTail, m_bmpDragonTail, m_bmpDragonTail,
				m_bmpDragonTail);

		if (m_DragonHead != null && m_DragonTail != null) {
			m_DragonHead.m_nextItem = m_DragonTail;
			m_DragonTail.m_preItem = m_DragonHead;

			Rect tmpRct = new Rect(0, 0, 0, 0);
			tmpRct.left = m_nCellWidth;
			tmpRct.right = tmpRct.left + m_nCellWidth;
			tmpRct.top = m_mapInScreenRect.top + m_nCellHeight * (CommonDefines.FIRST_LEVEL_CELL_V_CTNS - 2);
			tmpRct.bottom = tmpRct.top + m_nCellHeight;
			m_DragonHead.setCurrentCellRect(tmpRct);
			m_DragonHead.setImageSize(m_nCellWidth, m_nCellHeight);
			m_DragonHead.setCellSize(m_nCellWidth, m_nCellHeight);
			
			tmpRct.top = tmpRct.bottom;
			tmpRct.bottom = tmpRct.top + m_nCellHeight;
			m_DragonTail.setCurrentCellRect(tmpRct);
			m_DragonTail.setImageSize(m_nCellWidth, m_nCellHeight);
			m_DragonTail.setCellSize(m_nCellWidth, m_nCellHeight);
		}
	}

	public boolean isInit() {
		return (m_bmpDragonHead != null && m_bmpDragonBady != null && m_bmpDragonTail != null);
	}

	// 取得当前节点总数
	public int getDragonCounts(){
		return m_nDragonCtns;
	}
	
	// 在对位添加一个节点
	public boolean appendDragonItem() {
		if (!isInit())
			return false;

		DragonItem newDragon = new DragonItem(m_bmpDragonBady, m_bmpDragonBady,
				m_bmpDragonBady, m_bmpDragonBady, m_bmpDragonBady,
				m_bmpDragonBady, m_bmpDragonBady, m_bmpDragonBady,
				m_bmpDragonBady, m_bmpDragonBady, m_bmpDragonBady,
				m_bmpDragonBady);

		newDragon.m_nextItem = m_DragonTail;
		newDragon.m_preItem = m_DragonTail.m_preItem;

		m_DragonTail.m_preItem.m_nextItem = newDragon;
		m_DragonTail.m_preItem = newDragon;

		m_nDragonCtns++;
		return true;
	}

	// 游戏逻辑处理
	public void onBeforeDrawLogic() {
		for (DragonItem drawDragon = m_DragonHead; drawDragon != null;) {
			drawDragon.onBeforeDrawLogic(m_nCurCellRunFrame);
			drawDragon = drawDragon.m_nextItem;
		}
	}

	// 游戏逻辑处理
	public void onAfterDrawLogic() {
		for (DragonItem drawDragon = m_DragonHead; drawDragon != null;) {
			drawDragon.onAfterDrawLogic(m_nCurCellRunFrame);
			drawDragon = drawDragon.m_nextItem;
		}
		
		m_nCurCellRunFrame++;
		// 运行到了下一个单元格了
		if (m_nCurCellRunFrame >= CommonDefines.ONE_CELL_FRAME_CTNS){
			m_nCurCellRunFrame = 0;
		}
	}

	public void doDraw(Canvas runCanvas, Paint paint) {

//		Rect fromRct = new Rect(0, 0, m_nCellWidth, m_nCellHeight);
//		Rect toRct = new Rect(m_nCellWidth, 0, m_nCellWidth * 2, m_nCellHeight);
//		runCanvas.drawBitmap(m_bmpDragonHead, fromRct, toRct, paint);
		
		for (DragonItem drawDragon = m_DragonHead; drawDragon != null;) {
			drawDragon.doDraw(runCanvas, paint);
			drawDragon = drawDragon.m_nextItem;
		}
	}
}
