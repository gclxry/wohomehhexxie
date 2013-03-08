package com.burlapdragon.main.gameentry.smallmap;

import com.burlapdragon.main.R;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Rect;
import android.view.View;
import utility.method.*;

public class ModeTollGateSmallMapViewItem extends View {

	// ��ͼ����
	private int m_nMapTypeId = 0;
	// ��ͼid
	private int m_nMapId = 0;
	// ��ͼ
	private Bitmap m_MapBmp = null;
	private Paint m_paint = null;
	private Context m_Context = null;

	// ÿ��item����߿�ľ���
	private final static int VIEW_ITEM_SPACE = 50;

	private Rect m_drawSrcRct = null;
	private Rect m_drawDstRct = null;

	public ModeTollGateSmallMapViewItem(Context context) {
		super(context);
		m_Context = context;
		// ����Paint
		m_paint = new Paint();

		m_drawSrcRct = new Rect(0, 0, 0, 0);
		m_drawDstRct = new Rect(0, 0, 0, 0);
	}

	public boolean setMapId(int nMapTypeId, int nMapId) {
		if (nMapTypeId <= 0 || nMapId <= 0 || m_Context == null || m_MapBmp != null)
			return false;

		m_nMapTypeId = nMapTypeId;
		m_nMapId = nMapId;

		if (m_nMapId == 1) {
			// ƽԭ��ͼ
			m_MapBmp = Plotting.decodeResourceNoScaled(
					m_Context.getResources(), R.drawable.map_type_01);
		} else if (m_nMapId == 2) {
			// ��ѩ��ͼ
			m_MapBmp = Plotting.decodeResourceNoScaled(
					m_Context.getResources(), R.drawable.map_type_02);
		} else if (m_nMapId == 3) {
			// ������ͼ
			m_MapBmp = Plotting.decodeResourceNoScaled(
					m_Context.getResources(), R.drawable.map_type_03);
		} else if (m_nMapId == 4) {
			// ɳĮ��ͼ
			m_MapBmp = Plotting.decodeResourceNoScaled(
					m_Context.getResources(), R.drawable.map_type_04);
		} else if (m_nMapId == 5) {
			// ɽ�ص�ͼ
			m_MapBmp = Plotting.decodeResourceNoScaled(
					m_Context.getResources(), R.drawable.map_type_05);
		}

		return (m_MapBmp != null);
	}

	@Override
	protected void onDraw(Canvas canvas) {

		canvas.drawColor(Color.RED);

		if (m_MapBmp != null && m_drawSrcRct != null && m_drawDstRct != null) {
			m_drawSrcRct.left = m_drawSrcRct.top = 0;
			m_drawSrcRct.right = m_MapBmp.getWidth();
			m_drawSrcRct.bottom = m_MapBmp.getHeight();

			m_drawDstRct.left = m_drawDstRct.top = VIEW_ITEM_SPACE;
			m_drawDstRct.right = this.getWidth() - VIEW_ITEM_SPACE;
			m_drawDstRct.bottom = this.getHeight() - VIEW_ITEM_SPACE;
			canvas.drawBitmap(m_MapBmp, m_drawSrcRct, m_drawDstRct, m_paint);
		}
	}
}
