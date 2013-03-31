package uif.burlapdragon.gameentry.bigmap;

import uif.burlapdragon.R;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Rect;
import android.view.View;
import utility.method.*;

public class ModeTollGateBigMapViewItem extends View {

	// 地图类型
	private int m_nMapTypeId = 0;
	// 地图
	private Bitmap m_MapBmp = null;
	private Paint m_paint = null;
	private Context m_Context = null;

	// 每个item距离边框的距离
	private final static int VIEW_ITEM_SPACE = 5;
	// 平原地图
	public final static int BIG_MAP_TYPE_PLAIN = 1;
	// 冰雪地图
	public final static int BIG_MAP_TYPE_SNOW = 2;
	// 雾霾地图
	public final static int BIG_MAP_TYPE_HAZE = 3;
	// 沙漠地图
	public final static int BIG_MAP_TYPE_DESERT = 4;
	// 山地地图
	public final static int BIG_MAP_TYPE_HILL = 5;
	// 地图类型总数
	public final static int BIG_MAP_TYPE_CTNS = 5;

	private Rect m_drawSrcRct = null;
	private Rect m_drawDstRct = null;

	public ModeTollGateBigMapViewItem(Context context) {
		super(context);
		m_Context = context;
		// 创建Paint
		m_paint = new Paint();

		m_drawSrcRct = new Rect(0, 0, 0, 0);
		m_drawDstRct = new Rect(0, 0, 0, 0);
	}

	public boolean setMapTypeId(int nMapTypeId) {
		if (nMapTypeId <= 0 || m_Context == null || m_MapBmp != null)
			return false;

		m_nMapTypeId = nMapTypeId;

		if (m_nMapTypeId == BIG_MAP_TYPE_PLAIN) {
			// 平原地图
			m_MapBmp = Plotting.decodeResourceNoScaled(
					m_Context.getResources(), R.drawable.map_type_01);
		} else if (m_nMapTypeId == BIG_MAP_TYPE_SNOW) {
			// 冰雪地图
			m_MapBmp = Plotting.decodeResourceNoScaled(
					m_Context.getResources(), R.drawable.map_type_02);
		} else if (m_nMapTypeId == BIG_MAP_TYPE_HAZE) {
			// 雾霾地图
			m_MapBmp = Plotting.decodeResourceNoScaled(
					m_Context.getResources(), R.drawable.map_type_03);
		} else if (m_nMapTypeId == BIG_MAP_TYPE_DESERT) {
			// 沙漠地图
			m_MapBmp = Plotting.decodeResourceNoScaled(
					m_Context.getResources(), R.drawable.map_type_04);
		} else if (m_nMapTypeId == BIG_MAP_TYPE_HILL) {
			// 山地地图
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
