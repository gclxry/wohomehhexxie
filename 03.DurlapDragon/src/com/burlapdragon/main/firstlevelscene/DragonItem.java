package com.burlapdragon.main.firstlevelscene;

import com.burlapdragon.common.CommonDefines;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.Rect;

public class DragonItem {

	// 下一个节点
	public DragonItem m_nextItem = null;
	// 上一个节点
	public DragonItem m_preItem = null;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 正常方向图片
	// 往左走图片
	private Bitmap m_bmpToLeft = null;
	// 往右走图片
	private Bitmap m_bmpToRight = null;
	// 往上走图片
	private Bitmap m_bmpToUp = null;
	// 往下走图片
	private Bitmap m_bmpToDown = null;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 拐弯图像
	// 顺时针方向
	// 左 -> 上
	private Bitmap m_bmpFromLeftToUp = null;
	// 上 -> 右
	private Bitmap m_bmpFromUpToRight = null;
	// 右 -> 下
	private Bitmap m_bmpFromRightToDown = null;
	// 下 -> 左
	private Bitmap m_bmpFromDownToLeft = null;
	// 逆时针方向
	// 左 -> 下
	private Bitmap m_bmpFromLeftToDown = null;
	// 下 -> 右
	private Bitmap m_bmpFromDownToRight = null;
	// 右 -> 上
	private Bitmap m_bmpFromRightToUp = null;
	// 上 -> 左
	private Bitmap m_bmpFromUpToLeft = null;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 在画布中的位置
	private Rect m_ItemDrawRect = null;
	// 所处在的当前单元格的位置
	private Rect m_CurCellRect = null;
	// 需要绘制的图片的位置矩形
	private Rect m_bmpDrawRect = null;
	private int m_nCellWidth = 0;
	private int m_nCellHeight = 0;
	private int m_nImageWidth = 0;
	private int m_nImageHeight = 0;
	// 当前帧位于单元格的偏移
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

	// 游戏绘画
	public void doDraw(Canvas runCanvas, Paint paint) {
		m_bmpDrawRect.right = m_nImageWidth;
		m_bmpDrawRect.bottom = m_nImageHeight;
		runCanvas.drawBitmap(m_bmpToLeft, m_bmpDrawRect, m_ItemDrawRect, paint);
	}

	// 游戏逻辑处理
	public void onBeforeDrawLogic(int nCurCellRunFrame) {
		int nStep = m_nCellHeight / CommonDefines.ONE_CELL_FRAME_CTNS;
		m_nCurFrameOffset = 0 - nCurCellRunFrame * nStep;

		m_ItemDrawRect.left = m_CurCellRect.left;
		m_ItemDrawRect.right = m_CurCellRect.right;
		m_ItemDrawRect.top = m_CurCellRect.top + m_nCurFrameOffset;
		m_ItemDrawRect.bottom = m_ItemDrawRect.top + m_nCellHeight;
	}

	// 游戏逻辑处理
	public void onAfterDrawLogic(int nCurCellRunFrame) {
	}

}
