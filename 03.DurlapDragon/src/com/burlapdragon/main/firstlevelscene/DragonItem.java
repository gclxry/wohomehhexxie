package com.burlapdragon.main.firstlevelscene;

import com.burlapdragon.common.CommonDefines;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.Rect;

public class DragonItem {

	// ��һ���ڵ�
	public DragonItem m_nextItem = null;
	// ��һ���ڵ�
	public DragonItem m_preItem = null;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ��������ͼƬ
	// ������ͼƬ
	private Bitmap m_bmpToLeft = null;
	// ������ͼƬ
	private Bitmap m_bmpToRight = null;
	// ������ͼƬ
	private Bitmap m_bmpToUp = null;
	// ������ͼƬ
	private Bitmap m_bmpToDown = null;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ����ͼ��
	// ˳ʱ�뷽��
	// �� -> ��
	private Bitmap m_bmpFromLeftToUp = null;
	// �� -> ��
	private Bitmap m_bmpFromUpToRight = null;
	// �� -> ��
	private Bitmap m_bmpFromRightToDown = null;
	// �� -> ��
	private Bitmap m_bmpFromDownToLeft = null;
	// ��ʱ�뷽��
	// �� -> ��
	private Bitmap m_bmpFromLeftToDown = null;
	// �� -> ��
	private Bitmap m_bmpFromDownToRight = null;
	// �� -> ��
	private Bitmap m_bmpFromRightToUp = null;
	// �� -> ��
	private Bitmap m_bmpFromUpToLeft = null;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// �ڻ����е�λ��
	private Rect m_ItemDrawRect = null;
	// �����ڵĵ�ǰ��Ԫ���λ��
	private Rect m_CurCellRect = null;
	// ��Ҫ���Ƶ�ͼƬ��λ�þ���
	private Rect m_bmpDrawRect = null;
	private int m_nCellWidth = 0;
	private int m_nCellHeight = 0;
	private int m_nImageWidth = 0;
	private int m_nImageHeight = 0;
	// ��ǰ֡λ�ڵ�Ԫ���ƫ��
	private int m_nCurFrameOffset = 0;
	
	public DragonItem(Bitmap bmpToLeft, Bitmap bmpToRight, Bitmap bmpToUp, Bitmap bmpToDown,
			Bitmap bmpFromLeftToUp, Bitmap bmpFromUpToRight, Bitmap bmpFromRightToDown, Bitmap bmpFromDownToLeft,
			Bitmap bmpFromLeftToDown, Bitmap bmpFromDownToRight, Bitmap bmpFromRightToUp, Bitmap bmpFromUpToLeft){
		
		m_bmpToLeft = bmpToLeft;
		m_bmpToRight = bmpToRight;
		m_bmpToUp = bmpToUp;
		m_bmpToDown = bmpToDown;

		m_bmpFromLeftToUp = bmpFromLeftToUp;
		m_bmpFromUpToRight = bmpFromUpToRight;
		m_bmpFromRightToDown = bmpFromRightToDown;
		m_bmpFromDownToLeft = bmpFromDownToLeft;

		m_bmpFromLeftToDown = bmpFromLeftToDown;
		m_bmpFromDownToRight = bmpFromDownToRight;
		m_bmpFromRightToUp = bmpFromRightToUp;
		m_bmpFromUpToLeft = bmpFromUpToLeft;
		
		m_CurCellRect = new Rect(0, 0, 0, 0);
		m_ItemDrawRect = new Rect(0, 0, 0, 0);
		m_bmpDrawRect = new Rect(0, 0, 0, 0);
	}
	
	public void setCurrentCellRect(Rect rct){
		m_CurCellRect.left = rct.left;
		m_CurCellRect.right = rct.right;
		m_CurCellRect.top = rct.top;
		m_CurCellRect.bottom = rct.bottom;
	}

	public void setImageSize(int nWidth, int nHeight) {
		m_nImageWidth = nWidth;
		m_nImageHeight = nHeight;
	}

	public void setCellSize(int nWidth, int nHeight) {
		m_nCellWidth = nWidth;
		m_nCellHeight = nHeight;
	}

	// ��Ϸ�滭
	public void doDraw(Canvas runCanvas, Paint paint) {
		m_bmpDrawRect.right = m_nImageWidth;
		m_bmpDrawRect.bottom = m_nImageHeight;
		runCanvas.drawBitmap(m_bmpToLeft, m_bmpDrawRect, m_ItemDrawRect, paint);
	}

	// ��Ϸ�߼�����
	public void onBeforeDrawLogic(int nCurCellRunFrame) {
		int nStep = m_nCellHeight / CommonDefines.ONE_CELL_FRAME_CTNS;
		m_nCurFrameOffset = 0 - nCurCellRunFrame * nStep;

		m_ItemDrawRect.left = m_CurCellRect.left;
		m_ItemDrawRect.right = m_CurCellRect.right;
		m_ItemDrawRect.top = m_CurCellRect.top + m_nCurFrameOffset;
		m_ItemDrawRect.bottom = m_ItemDrawRect.top + m_nCellHeight;
	}

	// ��Ϸ�߼�����
	public void onAfterDrawLogic(int nCurCellRunFrame) {
	}

}
