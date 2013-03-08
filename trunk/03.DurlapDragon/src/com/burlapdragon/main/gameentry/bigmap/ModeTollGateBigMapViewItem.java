package com.burlapdragon.main.gameentry.bigmap;

import com.burlapdragon.main.R;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Rect;
import android.view.View;
import utility.method.*;

public class ModeTollGateBigMapViewItem extends View {

	// ��ͼ����
	private int m_nMapTypeId = 0;
	// ��ͼ
	private Bitmap m_MapBmp = null;
	private Paint m_paint = null;
	private Context m_Context = null;

	// ÿ��item����߿�ľ���
	private final static int VIEW_ITEM_SPACE = 5;
	// ƽԭ��ͼ
	public final static int BIG_MAP_TYPE_PLAIN = 1;
	// ��ѩ��ͼ
	public final static int BIG_MAP_TYPE_SNOW = 2;
	// ������ͼ
	public final static int BIG_MAP_TYPE_HAZE = 3;
	// ɳĮ��ͼ
	public final static int BIG_MAP_TYPE_DESERT = 4;
	// ɽ�ص�ͼ
	public final static int BIG_MAP_TYPE_HILL = 5;
	// ��ͼ��������
	public final static int BIG_MAP_TYPE_CTNS = 5;

	private Rect m_drawSrcRct = null;
	private Rect m_drawDstRct = null;

	public ModeTollGateBigMapViewItem(Context context) {
		super(context);
		m_Context = context;
		// ����Paint
		m_paint = new Paint();

		m_drawSrcRct = new Rect(0, 0, 0, 0);
		m_drawDstRct = new Rect(0, 0, 0, 0);
	}

	public boolean setMapTypeId(int nMapTypeId) {
		if (nMapTypeId <= 0 || m_Context == null || m_MapBmp != null)
			return false;

		m_nMapTypeId = nMapTypeId;

		if (m_nMapTypeId == BIG_MAP_TYPE_PLAIN) {
			// ƽԭ��ͼ
			m_MapBmp = Plotting.decodeResourceNoScaled(
					m_Context.getResources(), R.drawable.map_type_01);
		} else if (m_nMapTypeId == BIG_MAP_TYPE_SNOW) {
			// ��ѩ��ͼ
			m_MapBmp = Plotting.decodeResourceNoScaled(
					m_Context.getResources(), R.drawable.map_type_02);
		} else if (m_nMapTypeId == BIG_MAP_TYPE_HAZE) {
			// ������ͼ
			m_MapBmp = Plotting.decodeResourceNoScaled(
					m_Context.getResources(), R.drawable.map_type_03);
		} else if (m_nMapTypeId == BIG_MAP_TYPE_DESERT) {
			// ɳĮ��ͼ
			m_MapBmp = Plotting.decodeResourceNoScaled(
					m_Context.getResources(), R.drawable.map_type_04);
		} else if (m_nMapTypeId == BIG_MAP_TYPE_HILL) {
			// ɽ�ص�ͼ
			m_MapBmp = Plotting.decodeResourceNoScaled(
					m_Context.getResources(), R.drawable.map_type_05);
		}

		return (m_MapBmp != null);
	}

	@Override
	protected void onDraw(Canvas canvas) {

		canvas.drawColor(Color.BLUE);

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
