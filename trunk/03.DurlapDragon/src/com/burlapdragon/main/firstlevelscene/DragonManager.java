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
	// ��ͷ
	private Bitmap m_bmpDragonHead = null;
	// ����
	private Bitmap m_bmpDragonBady = null;
	// ��β
	private Bitmap m_bmpDragonTail = null;
	// һ����Item�Ĵ�С
	private int m_nCellWidth = 0;
	private int m_nCellHeight = 0;
	// ����
	private int m_nDragonCtns = 2;
	// ������ͼ����Ļ�е�����λ��
	private Rect m_mapInScreenRect = null;
	// ��ǰ��Ԫ�����е�֡��
	private int m_nCurCellRunFrame = 0;

	// ��ͷ�ڵ�
	private DragonItem m_DragonHead = null;
	// ��β�ڵ�
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

	// ����һ��item�Ĵ�С
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

	// ȡ�õ�ǰ�ڵ�����
	public int getDragonCounts(){
		return m_nDragonCtns;
	}
	
	// �ڶ�λ���һ���ڵ�
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

	// ��Ϸ�߼�����
	public void onBeforeDrawLogic() {
		for (DragonItem drawDragon = m_DragonHead; drawDragon != null;) {
			drawDragon.onBeforeDrawLogic(m_nCurCellRunFrame);
			drawDragon = drawDragon.m_nextItem;
		}
	}

	// ��Ϸ�߼�����
	public void onAfterDrawLogic() {
		for (DragonItem drawDragon = m_DragonHead; drawDragon != null;) {
			drawDragon.onAfterDrawLogic(m_nCurCellRunFrame);
			drawDragon = drawDragon.m_nextItem;
		}
		
		m_nCurCellRunFrame++;
		// ���е�����һ����Ԫ����
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
